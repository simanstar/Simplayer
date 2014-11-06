#ifndef SIMPLAYER_H
#define SIMPLAYER_H
#include <QThread>
#include "my_kernel.h"
#include "../base/BaseConstant.h"

//class PlayLabel;
class DecodeThread;
class VideoThread;
class QMatrix;
class SimPlayer :public QThread,public BaseConstant
{
    Q_OBJECT
public:
    explicit SimPlayer();
    ~SimPlayer();

    //全局变量
    VideoState *global_video_state;       //线程间联系通过这个
    SDL_Surface     *screen;
    uint8_t *out_buffer=NULL;
    AVFrame *pFrameYUV;
    uint64_t global_video_pkt_pts = AV_NOPTS_VALUE;
    AVPacket flush_pkt;

    int is_paused=0;
    int64_t  during_time_temp=0;
    int64_t during_time=0;
    int volume=0;    //音量
    int synchronizeDleta;//同步时差
    static int gTrack;//声道设置
    int rotateAngle;      //旋转度数
     QMatrix *leftmatrix;           //旋转类
     bool isGray;

     float kernel_totaltime=0;   //总时长
     float kernel_currenttime=0;   //当前播放时间



     static  QString filepath;

     int screen_w;
     int screen_h;
    //成员

     DecodeThread *decode_thread;
     VideoThread  *video_thread;

    //功能函数
   void kernel_pause();                  //暂停和播放
   void kernel_stop();                   //停止播放视频和音频
   void kernel_seek(float incr);         //快进快退
   void kernel_seek_pausing(float incr); //暂停时的快进快退
   int  setSynchronizeDleta(int value);  //同步音视频
   void rotateScreen();                  //旋转屏幕
   bool isPlaying();                     //是否正在播放视频
   bool isExisted();                     //是否存在文件
   QPixmap imageGray(QImage &image,int grayValue,int width,int height);
public slots:
   void setState(State state);

private:
   State playState;


   void  video_refresh_timer(void *userdata);
   void schedule_refresh(VideoState *is, int delay);
   static Uint32 sdl_refresh_timer_cb(Uint32 interval,void *opaque);
   void  video_display();
   void alloc_picture(void *userdata);
   double get_audio_clock(VideoState *is);
   double get_video_clock(VideoState *is);
   double get_external_clock(VideoState *is);
   double get_master_clock(VideoState *is);
   void stream_seek(VideoState *is, int64_t pos, int rel);


signals:
    void display();
    void UpdateTime(void);





protected:
    void run();



};


class DecodeThread : public QThread
{
    Q_OBJECT



public:
    explicit DecodeThread(SimPlayer *parent);
    ~DecodeThread();

  static SimPlayer *parent;


private:



    int stream_component_open(VideoState *is, int stream_index) ;
    void packet_queue_init(PacketQueue *q);
    int packet_queue_put(PacketQueue *q, AVPacket *pkt);
  static  int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block);
    void packet_queue_flush(PacketQueue *q);
   static double get_video_clock(VideoState *is);
   static double get_external_clock(VideoState *is);
   static void  audio_track_change(Uint8 *pBuffer, int iSize, int AudioChannel, int AudioBits );
  static  void audio_callback(void *userdata, Uint8 *stream, int len);
  static  int audio_decode_frame(VideoState *is, uint8_t *audio_buf, int buf_size,double *pts_ptr);
     void schedule_refresh(VideoState *is, int delay);
  static  Uint32 sdl_refresh_timer_cb(Uint32 interval,void *opaque);
   static int our_get_buffer(struct AVCodecContext *c, AVFrame *pic);
   static void our_release_buffer(struct AVCodecContext *c, AVFrame *pic);
  static  int synchronize_audio(VideoState *is, short *samples, int samples_size, double pts);

  static  double get_audio_clock(VideoState *is);
  static  double get_master_clock(VideoState *is);



protected:
    void run();
signals:
     void UpdateTime(void);


};


class VideoThread : public QThread
{
    Q_OBJECT


public:
    explicit VideoThread(SimPlayer *parent);
    ~VideoThread();





private:
   SimPlayer *parent;


   int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block);
   int queue_picture(VideoState *is, AVFrame *pFrame,double pts);
   double synchronize_video(VideoState *is, AVFrame *src_frame, double pts);

protected:
    void run();
signals:

     void UpdateTime(void);
};
#endif // SIMPLAYER_H

