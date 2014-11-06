
#ifndef MYKERNEL_H
#define MYKERNEL_H


#include <stdio.h>
#include <tchar.h>
#include <io.h>
#include <direct.h>

extern "C"
{

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avstring.h"
    //新版里的图像转换结构需要引入的头文件
#include "libswscale/swscale.h"
    //SDL
#include "sdl/SDL.h"
#include "sdl/SDL_thread.h"
//MYSQL
//#include <My_global.h>


};
////////////////////////////////////////////////////////////////////////

#define SDL_AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIOQ_SIZE (5 * 16 * 1024)
#define MAX_VIDEOQ_SIZE (5 * 256 * 1024)
#define AV_SYNC_THRESHOLD 0.01
#define AV_NOSYNC_THRESHOLD 10.0
#define SAMPLE_CORRECTION_PERCENT_MAX 10
#define AUDIO_DIFF_AVG_NB 20
#define FF_ALLOC_EVENT   (SDL_USEREVENT)
#define FF_REFRESH_EVENT (SDL_USEREVENT + 1)
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)

#define FF_DISPLAY_EVENT (SDL_USEREVENT+3)
#define FF_UPDATE_TOTALTIME_EVENT (SDL_USEREVENT+4)
#define FF_UPDATE_CURRENTTIME_EVENT (SDL_USEREVENT+5)

#define VIDEO_PICTURE_QUEUE_SIZE 1
#define DEFAULT_AV_SYNC_TYPE AV_SYNC_AUDIO_MASTER

///////////////////////////////////////////////////////////////////////////////////////////
    enum {
        AV_SYNC_AUDIO_MASTER,
        AV_SYNC_VIDEO_MASTER,
        AV_SYNC_EXTERNAL_MASTER,
    };

     typedef struct PacketQueue {                               //声音包的队列
      AVPacketList *first_pkt, *last_pkt;
      int nb_packets;
      int size;
      SDL_mutex *mutex;
      SDL_cond *cond;
    } PacketQueue;

     typedef struct VideoPicture {
      SDL_Overlay *bmp;
      int width, height; /* source height & width */
      int allocated;
      double pts;
    } VideoPicture;

    typedef struct VideoState {                                  //看字面意思应该是代表video的整个状态，传递信息都要用它

      AVFormatContext *pFormatCtx;
      AVCodecContext  *CodecCtx;                      //为实现stop函数增加的全局变量
      int             videoStream, audioStream;

      int             av_sync_type;
     double     external_clock; /* external clock base */
      int64_t         external_clock_time;
      int             seek_req;
      int             seek_flags;
      int64_t         seek_pos;

      ///////////////audio
      double          audio_clock;
      AVStream        *audio_st;
      PacketQueue     audioq;
      uint8_t         audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
      unsigned int    audio_buf_size;
      unsigned int    audio_buf_index;
      AVPacket        audio_pkt;
      uint8_t         *audio_pkt_data;
      int             audio_pkt_size;
      int			  audio_hw_buf_size;
      double          audio_diff_cum; /* used for AV difference average computation */
      double          audio_diff_avg_coef;
      double          audio_diff_threshold;
      int             audio_diff_avg_count;




      ///////////////////////////////video
      double          frame_timer;
      double          frame_last_pts;
      double          frame_last_delay;
      double          video_clock;
      double         video_current_pts; //时间时间戳
      int64_t         video_current_pts_time;//视频时间戳的时间值
      AVStream        *video_st;
      PacketQueue     videoq;

      VideoPicture    pictq[VIDEO_PICTURE_QUEUE_SIZE];
      int             pictq_size, pictq_rindex, pictq_windex;
      SDL_mutex       *pictq_mutex;
      SDL_cond        *pictq_cond;

      SDL_Thread      *parse_tid;
      SDL_Thread      *video_tid;

      char          filename[1024];
      int             quit;

    } VideoState;
//////////////////////////////////////////////////////////////////////////////////////////







#endif // MYKERNEL_H


