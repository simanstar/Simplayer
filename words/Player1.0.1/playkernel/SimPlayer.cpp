#include "SimPlayer.h"
#include <QtWidgets>



int SimPlayer::gTrack=0;

SimPlayer::SimPlayer(){


    synchronizeDleta=0;
    gTrack=0;
    rotateAngle=0;
    leftmatrix=new QMatrix;
    isGray=false;
    leftmatrix->rotate(0);
    playState=StoppedState;

    decode_thread=new DecodeThread(this);
    video_thread=new VideoThread(this);

    connect(decode_thread,SIGNAL(UpdateTime()),this,SIGNAL(UpdateTime()));
    connect(video_thread,SIGNAL(UpdateTime()),this,SIGNAL(UpdateTime()));


}

SimPlayer::~SimPlayer(){

}

QString SimPlayer::filepath=NULL;
void SimPlayer::run()
{
        SDL_Event event;
        VideoState      *is;

        char filepath_temp[1024];


       during_time_temp=0;
       during_time=0;


      kernel_totaltime=0;   //总时长
      kernel_currenttime=0;   //当前播放时间



        is_paused=0;

        av_register_all();
       // pFormatCtx = avformat_alloc_context();
        is = (VideoState*)av_mallocz(sizeof(VideoState));

         global_video_state = is;
         pFrameYUV=avcodec_alloc_frame();
        //初始化SDLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
                printf( "Could not initialize SDL - %s\n", SDL_GetError());
                exit(1);
            }

    //    QByteArray ba  = filepath.toLatin1();
         std::string str=filepath.toStdString();
         const char*ch=str.c_str();
        strcpy(filepath_temp,ch);

      av_strlcpy(is->filename,  filepath_temp,sizeof(is->filename));


      is->pictq_mutex = SDL_CreateMutex();
      is->pictq_cond = SDL_CreateCond();

     schedule_refresh(is, 40);

     is->av_sync_type = DEFAULT_AV_SYNC_TYPE;

     //开始解码线程
       decode_thread->start();

      //定义和创建清空包
      av_init_packet(&flush_pkt);
      flush_pkt.data =(uint8_t *) "FLUSH";

      for(;;) {
       float incr, pos;
       SDL_WaitEvent(&event);
        switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
            case SDLK_LEFT:
                incr = -5.0;
                goto do_seek;
            case SDLK_RIGHT:
                incr = 5.0;
                goto do_seek;
            case SDLK_UP:
                incr = -10.0;
                goto do_seek;
            case SDLK_DOWN:
                incr = 10.0;
                goto do_seek;
    do_seek:
                if(global_video_state) {
                  pos = get_master_clock(global_video_state);
                  pos += incr;
                    stream_seek(global_video_state, (int64_t)(pos * AV_TIME_BASE), incr);
                }
                break;
            default:
                break;
            }
            break;
        case FF_QUIT_EVENT:
        case SDL_QUIT:

         is->quit = 1;
         SDL_Quit();
         delete [] out_buffer;
         out_buffer=NULL;
//         if(video_thread->isRunning())
//            video_thread->wait(250);
//         if(video_thread->isRunning())
//         {
//              printf("video_thread is still running before quitting");
//             video_thread->quit();
//                video_thread->wait(250);
//         }
         if(video_thread->isRunning())
         {
          //   printf("video_thread is still running before terminating");
             video_thread->terminate();
             // video_thread->wait(250);
         }


         return ;
          break;
        case FF_ALLOC_EVENT:
          alloc_picture(event.user.data1);
          break;
        case FF_REFRESH_EVENT:
          video_refresh_timer(event.user.data1);
          break;
        default:
          break;
        }
      }

      return ;
}

void SimPlayer::setState(State state)
{
    playState=state;
}

void SimPlayer::kernel_pause()        //暂停和播放
{
    is_paused=!is_paused;
    if   (is_paused)
    {
        SDL_PauseAudio(1);
        during_time_temp=av_gettime();

    }
    else
          {
               during_time=during_time+av_gettime()-during_time_temp;
              stream_seek(global_video_state, (int64_t)(get_master_clock(global_video_state) * AV_TIME_BASE), get_master_clock(global_video_state)); //掩盖 快进，快退完第一次暂停，不同步的bug
               SDL_PauseAudio(0);
           }

}





void SimPlayer::kernel_stop()                       //停止播放视频和音频
{

    SDL_Event event;
     event.type = FF_QUIT_EVENT;
     SDL_PushEvent(&event);
}


void SimPlayer::stream_seek(VideoState *is, int64_t pos, int rel) {

   if(!is->seek_req) {
       is->seek_pos = pos;
       is->seek_flags = rel <0 ? AVSEEK_FLAG_FRAME : AVSEEK_FLAG_BACKWARD; //其实跟正负无关，原作者有误
       is->seek_req = 1;
   }
}






void SimPlayer::kernel_seek(float incr)
{

    float pos;
    if(global_video_state) {
      pos = get_master_clock(global_video_state);
      pos += incr;
        stream_seek(global_video_state, (int64_t)(pos * AV_TIME_BASE), incr);
    }
}
void SimPlayer::kernel_seek_pausing(float incr)
{
    int i,j,k,volume_temp;
    is_paused=0;


     during_time=during_time+av_gettime()-during_time_temp;
      kernel_seek(incr);
      volume_temp=volume;
     volume=0;
      SDL_PauseAudio(0);
   //延迟
   this->msleep(100);

    is_paused=1;
    SDL_PauseAudio(1);
    volume=volume_temp;
   during_time_temp=av_gettime();
}



int SimPlayer::setSynchronizeDleta(int value)
{
    this->synchronizeDleta=value;
}



void SimPlayer::rotateScreen()
{
    rotateAngle+=90;
    if(rotateAngle>=360)
    {
        rotateAngle=0;
    }
    leftmatrix->rotate(90);
}


bool SimPlayer::isPlaying()
{
    if(playState==PlayingState||playState==StartState)
    {
        return true;
    }
    return false;
}

bool SimPlayer::isExisted()
{
    if(playState==StoppedState)
    {
        return false;
    }
    return true;
}



//audio_callback函数，它花费了时间来把数据从声音包中移到我们的输出缓冲区中。
//这意味着我们声音时 钟中记录的时间比实际的要早太多。所以我们必须要检查一下我们还有多少没有写入。
//经过这个函数得到的是最终的音频时间戳
double SimPlayer::get_audio_clock(VideoState *is) {
 double pts;
 int hw_buf_size, bytes_per_sec, n;

 pts = is->audio_clock; /* maintained in the audio thread */
 hw_buf_size = is->audio_buf_size - is->audio_buf_index;
 bytes_per_sec = 0;
 n = is->audio_st->codec->channels * 2;
 if(is->audio_st) {
   bytes_per_sec = is->audio_st->codec->sample_rate * n;
 }
 if(bytes_per_sec) {
   pts -= (double)hw_buf_size / bytes_per_sec;      //时间戳要延迟吧？？？为什么是减，不是加
 }
 this->kernel_currenttime=pts;         //获得当前播放时间，以秒为单位
 emit UpdateTime();
 return pts;
}

double SimPlayer::get_video_clock(VideoState *is) {
 double delta;

 delta = (av_gettime() - is->video_current_pts_time) / 1000000.0;
 return (is->video_current_pts + delta);

}


double SimPlayer::get_external_clock(VideoState *is) {
   return av_gettime() / 1000000.0;
}


//新的封装函数get_master_clock，用来检测 av_sync_type变量然后决定调用 get_audio_clock
//还是get_video_clock或者其它的想使用的获得时钟的函数
double SimPlayer::get_master_clock(VideoState *is) {
   if(is->av_sync_type == AV_SYNC_VIDEO_MASTER) {
       return get_video_clock(is);
   } else if(is->av_sync_type == AV_SYNC_AUDIO_MASTER) {
       return get_audio_clock(is);
   } else {
       return get_external_clock(is);
   }
}



void SimPlayer::alloc_picture(void *userdata) {

 VideoState *is = (VideoState *)userdata;
 VideoPicture *vp;

 vp = &is->pictq[is->pictq_windex];
 if(vp->bmp) {
   // we already have one make another, bigger/smaller
   SDL_FreeYUVOverlay(vp->bmp);
}
 // Allocate a place to put our YUV image on that screen
   screen = SDL_SetVideoMode(is->video_st->codec->width, is->video_st->codec->height, 0, 0);


       if(!screen) {  printf("SDL: could not set video mode - exiting\n");
       exit(1);
       }
 vp->bmp = SDL_CreateYUVOverlay(is->video_st->codec->width, is->video_st->codec->height, SDL_YV12_OVERLAY,screen);
 vp->width = is->video_st->codec->width;
 vp->height = is->video_st->codec->height;


 SDL_LockMutex(is->pictq_mutex);
 vp->allocated = 1;
 SDL_CondSignal(is->pictq_cond);
 SDL_UnlockMutex(is->pictq_mutex);

}





void  SimPlayer::video_refresh_timer(void *userdata) {

 VideoState *is = (VideoState *)userdata;
 VideoPicture *vp;
 double actual_delay;
 double delay;
 double sync_threshold;
 double ref_clock;
 double diff;

 if(is->video_st&&is_paused==0) {
   if(is->pictq_size == 0) {
     schedule_refresh(is, 1);
   } else {
     vp = &is->pictq[is->pictq_rindex];
      is->video_current_pts = vp->pts;
      is->video_current_pts_time = av_gettime();     //;//更新

     delay = vp->pts - is->frame_last_pts;//当前时间戳前上一帧的时间戳，得到上次的延迟时间
          if(delay <= 0 || delay >= 1.0) {//不正确的延迟，用上次的吧
          delay = is->frame_last_delay;
     }
    //为下次计算作准备
     is->frame_last_delay = delay;
     is->frame_last_pts = vp->pts;

     if(is->av_sync_type !=AV_SYNC_VIDEO_MASTER){
     ref_clock = get_audio_clock(is); //得到audio的时间戳
     diff = vp->pts - ref_clock+synchronizeDleta;      //视频时间戳减audio时间戳，比较谁快谁慢

     sync_threshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;  //取较大的，因为尽量要多延迟
     if(fabs(diff) < AV_NOSYNC_THRESHOLD) {
   if(diff <= -sync_threshold) {
     delay = 0;                        //视频落后音频太多了，把延迟置0，赶快刷新
   } else if(diff >= sync_threshold) {
     delay = 2 * delay;                //视频太快了，延迟多点，让时间戳相等
   }
     }

     }

      is->frame_timer += delay;

     actual_delay = is->frame_timer - ((av_gettime()-during_time)/ 1000000.0); //不懂？？？
     if(actual_delay < 0.010) {  //小于这个阀值，需要延迟的时间太短，干脆跳过这个帧
       actual_delay = 0.010;
     }
     schedule_refresh(is, (int)(actual_delay * 1000 + 0.5));    //为什么要这样算？具体细节不懂
     /* show the picture! */
     video_display();


     /* update queue for next picture! */
     if(++is->pictq_rindex == VIDEO_PICTURE_QUEUE_SIZE) {
   is->pictq_rindex = 0;
     }
     SDL_LockMutex(is->pictq_mutex);
     is->pictq_size--;
     SDL_CondSignal(is->pictq_cond);
     SDL_UnlockMutex(is->pictq_mutex);
   }
 } else {
   schedule_refresh(is, 100);
 }
}




void SimPlayer::schedule_refresh(VideoState *is, int delay) {
 SDL_AddTimer(delay, sdl_refresh_timer_cb, is);
}


Uint32 SimPlayer::sdl_refresh_timer_cb(Uint32 interval,void *opaque) {
 SDL_Event event;
 event.type = FF_REFRESH_EVENT;
 event.user.data1 = opaque;
 SDL_PushEvent(&event);
 return 0; /* 0 means stop timer */
}


QPixmap SimPlayer::imageGray(QImage &image,int grayValue,int w,int h)
{
    unsigned char *data=image.bits();
    int width=image.width();
    int height=image.height();
    int bytePerLine=(width*24+31)/8;
    unsigned char *graydata=new unsigned char[bytePerLine*height];
    unsigned char r,g,b;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            r = *(data+2);
            g = *(data+1);
            b = *data;
//                graydata[i*bytePerLine+j*3+1]=0;
//                  graydata[i*bytePerLine+j*3+2]=0;
            graydata[i*bytePerLine+j*3+0]=(r*30+g*59+b*11)/100;
            graydata[i*bytePerLine+j*3+1]=(r*30+g*59+b*11)/100;
            graydata[i*bytePerLine+j*3+2]=(r*30+g*59+b*11)/100;
            data+=3;

        }
    }
    QImage grayImg(graydata,width,height,bytePerLine,QImage::Format_RGB888);


     return  QPixmap::fromImage(grayImg.scaled(QSize(w,h), Qt::KeepAspectRatio));
}


void SimPlayer::video_display() {

  emit display();

}


////////////////////////////////////////////decodethread
SimPlayer* DecodeThread::parent=NULL;

DecodeThread::DecodeThread(SimPlayer *parent)
{
     DecodeThread::parent=parent;
}


DecodeThread::~DecodeThread()
{

}

void DecodeThread::run()
{



    //该线程完成从读取上下文信息到形成视频包和音频包队列所有工作

 //   printf("decode_thread started");

     VideoState *is = parent->global_video_state;
     AVFormatContext *pFormatCtx;
     AVPacket pkt1, *packet = &pkt1;
     int video_index = -1;
     int audio_index = -1;
     int i;
     is->videoStream=-1;
     is->audioStream=-1;
     AVRational r = {1,AV_TIME_BASE };   //解决不能用AV_TIME_BASE_Q的bug

     pFormatCtx=avformat_alloc_context();

     // will interrupt blocking functions if we quit!
     //url_set_interrupt_cb(decode_interrupt_cb);


     // Open video file
     if(avformat_open_input(&pFormatCtx, is->filename, NULL,  NULL)!=0)
        { printf("Couldn't open file");
          return ; // Couldn't open file
        }

     is->pFormatCtx = pFormatCtx;

    parent->kernel_totaltime=pFormatCtx->duration/1000000.0;   //获得总时长，以秒为单位
    emit UpdateTime();


     // Retrieve stream information
     if(av_find_stream_info(pFormatCtx)<0)
     {
         printf("Couldn't find stream information");
       return ; // Couldn't find stream information
     }

     // Dump information about file onto standard error
     av_dump_format(pFormatCtx, 0, is->filename, 0);

     // Find the first video stream

     for(i=0; i<pFormatCtx->nb_streams; i++) {
       if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO&&video_index <0 ) {
         video_index=i;
       }
       if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO &&audio_index<0) {
         audio_index=i;
       }
     }
     if(audio_index >= 0) {
       stream_component_open(is, audio_index);
     }
     if(video_index >= 0) {
       stream_component_open(is, video_index);
     }

     if(is->videoStream < 0 && is->audioStream < 0) {
       fprintf(stderr, "%s: could not open codecs\n", is->filename);
       goto fail;
     }
     if(is->videoStream<0)  //mp3  临时
     {
          get_audio_clock(is);
         emit parent->display();

     }
     // main decode loop


     for(;;) {
       if(is->quit) {

       //    printf("decode_thread quited");
         break;
       }
       if(is->videoStream<0)  //mp3  临时
       {
           get_audio_clock(is);


       }



       // seek stuff goes here
       if(is->seek_req) {
           int stream_index= -1;
           int64_t seek_target = is->seek_pos;

           if     (is->videoStream >= 0) stream_index = is->videoStream;
           else if(is->audioStream >= 0) stream_index = is->audioStream;

           if(stream_index>=0){
               seek_target= av_rescale_q(seek_target,  r, pFormatCtx->streams[stream_index]->time_base);
           }
           if(av_seek_frame(is->pFormatCtx, stream_index, seek_target, is->seek_flags)) {
               fprintf(stderr, "%s: error while seeking\n", is->pFormatCtx->filename);
           } else {
               if(is->audioStream >= 0) {
               //	printf("packet_queue_flush");
                   packet_queue_flush(&is->audioq);
                   packet_queue_put(&is->audioq, &parent->flush_pkt);
               }
               if(is->videoStream >= 0) {
                   packet_queue_flush(&is->videoq);
                   packet_queue_put(&is->videoq, &parent->flush_pkt);
               }
           }
           is->seek_req = 0;
       }



       if(is->audioq.size > MAX_AUDIOQ_SIZE || is->videoq.size > MAX_VIDEOQ_SIZE) {
         SDL_Delay(10);
         continue;
       }
       if(av_read_frame(is->pFormatCtx, packet) < 0) {
         if(pFormatCtx->pb&&pFormatCtx->pb->error) {                          //url_ferror(&pFormatCtx->pb) == 0
       SDL_Delay(100); /* no error; wait for user input */
       continue;
         } else {
       break;
         }
       }
       // Is this a packet from the video stream?
       if(packet->stream_index == is->videoStream) {
         packet_queue_put(&is->videoq, packet);
       } else if(packet->stream_index == is->audioStream) {
         packet_queue_put(&is->audioq, packet);
       } else {
         av_free_packet(packet);
       }
     }
     /* all done - wait for it */
     while(!is->quit) {
       SDL_Delay(100);
     }

    fail:
     if(1){
       SDL_Event event;
       event.type = FF_QUIT_EVENT;
       event.user.data1 = is;
       SDL_PushEvent(&event);
     }

    av_close_input_file(pFormatCtx);
     return ;
    }

void DecodeThread::packet_queue_flush(PacketQueue *q) {
  AVPacketList *pkt, *pkt1;

  SDL_LockMutex(q->mutex);
  for(pkt = q->first_pkt; pkt != NULL; pkt = pkt1) {
      pkt1 = pkt->next;
      av_free_packet(&pkt->pkt);
      av_freep(&pkt);
  }
  q->last_pkt = NULL;
  q->first_pkt = NULL;
  q->nb_packets = 0;
  q->size = 0;
  SDL_UnlockMutex(q->mutex);
}


double DecodeThread::get_video_clock(VideoState *is) {
 double delta;

 delta = (av_gettime() - is->video_current_pts_time) / 1000000.0;
 return (is->video_current_pts + delta);

}


double DecodeThread::get_external_clock(VideoState *is) {
   return av_gettime() / 1000000.0;
}



int DecodeThread::stream_component_open(VideoState *is, int stream_index) {


 AVFormatContext *pFormatCtx = is->pFormatCtx;
 AVCodecContext *codecCtx;
 AVCodec *codec;
 SDL_AudioSpec wanted_spec, spec;


 parent->kernel_totaltime=pFormatCtx->duration/1000000.0;   //获得总时长，以秒为单位
 emit UpdateTime();


 if(stream_index < 0 || stream_index >= pFormatCtx->nb_streams) {
   return -1;
 }

 // Get a pointer to the codec context for the video stream
 codecCtx = pFormatCtx->streams[stream_index]->codec;

 if(codecCtx->codec_type == AVMEDIA_TYPE_AUDIO) {
   // Set audio settings from codec info
   wanted_spec.freq = codecCtx->sample_rate;
   wanted_spec.format = AUDIO_S16SYS;
   wanted_spec.channels = codecCtx->channels;
   wanted_spec.silence = 0;
   wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
   wanted_spec.callback = audio_callback;
   wanted_spec.userdata = is;
  // wanted_spec.userdata = is;

   if(SDL_OpenAudio(&wanted_spec, &spec) < 0) {
     fprintf(stderr, "SDL_OpenAudio: %s\n", SDL_GetError());
     return -1;
   }
 }
 codec = avcodec_find_decoder(codecCtx->codec_id);
 if(!codec || (avcodec_open(codecCtx, codec) < 0)) {
   fprintf(stderr, "Unsupported codec!\n");
   return -1;
 }

 switch(codecCtx->codec_type) {
 case AVMEDIA_TYPE_AUDIO:
   is->audioStream = stream_index;
   is->audio_st = pFormatCtx->streams[stream_index];
   is->audio_buf_size = 0;
   is->audio_buf_index = 0;
   memset(&is->audio_pkt, 0, sizeof(is->audio_pkt));
   packet_queue_init(&is->audioq);
   SDL_PauseAudio(0);

   break;
 case AVMEDIA_TYPE_VIDEO:
   is->videoStream = stream_index;
   is->video_st = pFormatCtx->streams[stream_index];

   is->frame_timer = (double)av_gettime() / 1000000.0;//上次没看到
   is->frame_last_delay = 40e-3;                      //同样没看到
   is->video_current_pts_time = av_gettime();         //初始化视频时间戳时间值

   packet_queue_init(&is->videoq);

   parent->video_thread->start();
   codecCtx->get_buffer =our_get_buffer; //为保存第一个包的dts申请一个缓冲
   codecCtx->release_buffer = our_release_buffer;


   break;
 default:
   break;
 }

}

 int DecodeThread::our_get_buffer(struct AVCodecContext *c, AVFrame *pic) {
 int ret = avcodec_default_get_buffer(c, pic);
 uint64_t *pts = (uint64_t *)av_malloc(sizeof(uint64_t));
 *pts = parent->global_video_pkt_pts;
 pic->opaque = pts;
 return ret;
}


void DecodeThread::our_release_buffer(struct AVCodecContext *c, AVFrame *pic) {
 if(pic) av_freep(&pic->opaque);
 avcodec_default_release_buffer(c, pic);
}

void DecodeThread::packet_queue_init(PacketQueue *q) {
 memset(q, 0, sizeof(PacketQueue));
 q->mutex = SDL_CreateMutex();
 q->cond = SDL_CreateCond();
}







int DecodeThread::packet_queue_put(PacketQueue *q, AVPacket *pkt) {

 AVPacketList *pkt1;
 if(pkt != &parent->flush_pkt&&av_dup_packet(pkt) < 0) {
   return -1;
 }
 pkt1 = (AVPacketList*)av_malloc(sizeof(AVPacketList));
 if (!pkt1)
   return -1;
 pkt1->pkt = *pkt;
 pkt1->next = NULL;

 SDL_LockMutex(q->mutex);

 if (!q->last_pkt)
   q->first_pkt = pkt1;
 else
   q->last_pkt->next = pkt1;
 q->last_pkt = pkt1;
 q->nb_packets++;
 q->size += pkt1->pkt.size;
 SDL_CondSignal(q->cond);

 SDL_UnlockMutex(q->mutex);
 return 0;
}





void DecodeThread::audio_track_change(Uint8 *pBuffer, int iSize, int AudioChannel, int AudioBits )
{
  int i=0,w_pos=0,r_pos=0, n=0;

  n = iSize / 4; //循环次数

  switch (AudioBits)
  {
  case 8:
    //进行声道选择
    switch(AudioChannel)
    {
    case 1:r_pos=0;
      w_pos=1;
      break;             //左声道

    case 2:r_pos=1;
      w_pos=0;
      break;             //右声道

    default:return ;           //不处理（双声道模式）

    }
    //执行声道切换操作
    for(i=0;i<n;i++){
      memcpy(pBuffer+w_pos,pBuffer+r_pos,1);
      w_pos+=2;
      r_pos+=2;
    }
    break;
  case 16:
    //进行声道选择
    switch(AudioChannel)
    {
    case 1:r_pos=0;
      w_pos=2;
      break;             //左声道

    case 2:r_pos=2;
      w_pos=0;
      break;             //右声道

    default:return ;           //不处理（双声道模式）

    }
    //执行声道切换操作
    for(i=0;i<n;i++){
      memcpy(pBuffer+w_pos,pBuffer+r_pos,2);
      w_pos+=4;
      r_pos+=4;
    }
    break;
  case 24:
    //进行声道选择
    switch(AudioChannel)
    {
    case 1:r_pos=0;
      w_pos=3;
      break;             //左声道

    case 2:r_pos=3;
      w_pos=0;
      break;             //右声道

    default:return;           //不处理（双声道模式）

    }
    //执行声道切换操作
    for(i=0;i<n;i++){
      memcpy(pBuffer+w_pos,pBuffer+r_pos,3);
      w_pos+=6;
      r_pos+=6;
    }
    break;
  case 32:
    //进行声道选择
    switch(AudioChannel)
    {
    case 1:r_pos=0;
      w_pos=4;
      break;             //左声道

    case 2:r_pos=4;
      w_pos=0;
      break;             //右声道

    default:return ;           //不处理（双声道模式）

    }
    //执行声道切换操作
    for(i=0;i<n;i++){
      memcpy(pBuffer+w_pos,pBuffer+r_pos,4);
      w_pos+=8;
      r_pos+=8;
    }
    break;
  }
  return ;
}



void DecodeThread::audio_callback(void *userdata, Uint8 *stream, int len) {

 VideoState *is = (VideoState *)userdata;
 int len1, audio_size;
  double pts;


 while(len > 0) {
   if(is->audio_buf_index >= is->audio_buf_size) {
     /* We have already sent all our data; get more */
     audio_size = audio_decode_frame(is, is->audio_buf, sizeof(is->audio_buf),&pts);
     if(audio_size < 0) {
   /* If error, output silence */
   is->audio_buf_size = 1024;
   memset(is->audio_buf, 0, is->audio_buf_size);
     } else {
     audio_size = synchronize_audio(is, (int16_t *)is->audio_buf,audio_size, pts);//同步修正后的音频样本大小
   is->audio_buf_size = audio_size;
     }
     is->audio_buf_index = 0;
   }
   len1 = is->audio_buf_size - is->audio_buf_index;
   if(len1 > len)
     len1 = len;
    audio_track_change((uint8_t *)is->audio_buf + is->audio_buf_index, len1, SimPlayer::gTrack, 16);    // 声道控制函数, gTrack 1 - 左声道, 2 - 右声道, 0 - 立体声
   SDL_MixAudio(stream, (uint8_t *)is->audio_buf+4 + is->audio_buf_index, len1, parent->volume); //与memcpy替换

 //  memcpy(stream, (uint8_t *)is->audio_buf + is->audio_buf_index, len1);
   len -= len1;
   stream += len1;
   is->audio_buf_index += len1;
 }
}


//同步音频到视频
int DecodeThread::synchronize_audio(VideoState *is, short *samples, int samples_size, double pts) {
 int n;
 double ref_clock;

 n = 2 * is->audio_st->codec->channels;        //一秒时间的声音样本数

 if(is->av_sync_type != AV_SYNC_AUDIO_MASTER) {
   double diff, avg_diff;
   int wanted_size, min_size, max_size, nb_samples;

   ref_clock = get_master_clock(is);
   diff = get_audio_clock(is) - ref_clock;

   if(diff < AV_NOSYNC_THRESHOLD) {
     // accumulate the diffs
     is->audio_diff_cum = diff + is->audio_diff_avg_coef* is->audio_diff_cum;
     if(is->audio_diff_avg_count < AUDIO_DIFF_AVG_NB) {
   is->audio_diff_avg_count++;
     } else {
   avg_diff = is->audio_diff_cum * (1.0 - is->audio_diff_avg_coef);             //加权平均值
   if(fabs(avg_diff) >= is->audio_diff_threshold) {
     wanted_size = samples_size + ((int)(diff * is->audio_st->codec->sample_rate) * n);
     min_size = samples_size * ((100 - SAMPLE_CORRECTION_PERCENT_MAX) / 100);
     max_size = samples_size * ((100 + SAMPLE_CORRECTION_PERCENT_MAX) / 100);
     if(wanted_size < min_size) {
       wanted_size = min_size;
     } else if (wanted_size > max_size) {
       wanted_size = max_size;
     }
     if(wanted_size < samples_size) {
       /* remove samples */
       samples_size = wanted_size;                //让样本更小一些
     } else if(wanted_size > samples_size) {            //否则，要自己推算声音，在缓冲的末尾添加上最后的样本
       uint8_t *samples_end, *q;
       int nb;

       /* add samples by copying final sample*/
       nb = (samples_size - wanted_size);
       samples_end = (uint8_t *)samples + samples_size - n;
       q = samples_end + n;                //在q地址开始复制
       while(nb > 0) {
         memcpy(q, samples_end, n);//以n个单位进行复制
         q += n;
         nb -= n;
       }
       samples_size = wanted_size;
     }
   }
     }
   } else {
     /* difference is TOO big; reset diff stuff */
     is->audio_diff_avg_count = 0;
     is->audio_diff_cum = 0;
   }
 }
 return samples_size;
}

double DecodeThread::get_master_clock(VideoState *is) {
   if(is->av_sync_type == AV_SYNC_VIDEO_MASTER) {
       return get_video_clock(is);
   } else if(is->av_sync_type == AV_SYNC_AUDIO_MASTER) {
       return get_audio_clock(is);
   } else {
       return get_external_clock(is);
   }
}


double DecodeThread::get_audio_clock(VideoState *is) {
 double pts;
 int hw_buf_size, bytes_per_sec, n;

 pts = is->audio_clock; /* maintained in the audio thread */
 hw_buf_size = is->audio_buf_size - is->audio_buf_index;
 bytes_per_sec = 0;
 n = is->audio_st->codec->channels * 2;
 if(is->audio_st) {
   bytes_per_sec = is->audio_st->codec->sample_rate * n;
 }
 if(bytes_per_sec) {
   pts -= (double)hw_buf_size / bytes_per_sec;      //时间戳要延迟吧？？？为什么是减，不是加
 }
 parent->kernel_currenttime=pts;         //获得当前播放时间，以秒为单位
 emit parent->UpdateTime();
 return pts;
}



int DecodeThread::audio_decode_frame(VideoState *is, uint8_t *audio_buf, int buf_size,double *pts_ptr) {

 int len1, data_size,n;
 AVPacket *pkt = &is->audio_pkt;
 double pts;


 for(;;) {
   while(is->audio_pkt_size > 0) {
     data_size = buf_size;
     len1 = avcodec_decode_audio3(is->audio_st->codec,
                 (int16_t *)audio_buf+2, &data_size,
                 &(is->audio_pkt));
     if(len1 < 0) {
   /* if error, skip frame */
   is->audio_pkt_size = 0;
   break;
     }
     is->audio_pkt_data += len1;
     is->audio_pkt_size -= len1;
     if(data_size <= 0) {
   /* No data yet, get more frames */
   continue;
     }
      pts = is->audio_clock;
     *pts_ptr = pts;         //得到音频时间戳，传给参数

     n = 2 * is->audio_st->codec->channels;
     is->audio_clock += (double)data_size /(double)(n * is->audio_st->codec->sample_rate);//通过样本数和采样率来计算????

     /* We have data, return it and come back for more later */
     return data_size;
   }
   if(pkt->data)
     av_free_packet(pkt);

   if(is->quit) {
     return -1;
   }
   /* next packet */
   if(packet_queue_get(&is->audioq, pkt, 1) < 0) {
     return -1;
   }
   //如果是清除包，就把缓存清除
   if(pkt->data == parent->flush_pkt.data) {
   //	printf("清除音频缓存");
       avcodec_flush_buffers(is->audio_st->codec);
   //	avcodec_default_free_buffers(is->audio_st->codec);


       continue;
   }
   is->audio_pkt_data = pkt->data;
   is->audio_pkt_size = pkt->size;
   if(pkt->pts != AV_NOPTS_VALUE) {
     is->audio_clock = av_q2d(is->audio_st->time_base)*pkt->pts;   //先暂时把声音时钟设置为这个包的时间戳
   }

 }
}



int DecodeThread::packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{
AVPacketList *pkt1;
int ret;

SDL_LockMutex(q->mutex);

for(;;) {

  if(parent->global_video_state->quit) {
    ret = -1;
    break;
  }

  pkt1 = q->first_pkt;
  if (pkt1) {
    q->first_pkt = pkt1->next;
    if (!q->first_pkt)
  q->last_pkt = NULL;
    q->nb_packets--;
    q->size -= pkt1->pkt.size;
    *pkt = pkt1->pkt;
    av_free(pkt1);
    ret = 1;
    break;
  } else if (!block) {
    ret = 0;
    break;
  } else {
    SDL_CondWait(q->cond, q->mutex);
  }
}
SDL_UnlockMutex(q->mutex);
return ret;
}




void DecodeThread::schedule_refresh(VideoState *is, int delay) {
 SDL_AddTimer(delay, sdl_refresh_timer_cb, is);
}


Uint32 DecodeThread::sdl_refresh_timer_cb(Uint32 interval,void *opaque) {
 SDL_Event event;
 event.type = FF_REFRESH_EVENT;
 event.user.data1 = opaque;
 SDL_PushEvent(&event);
 return 0; /* 0 means stop timer */
}


//////////////////////////////////////////////videothread





VideoThread::VideoThread(SimPlayer *parent)
{
       this->parent=parent;
}


VideoThread::~VideoThread()
{

}






void VideoThread::run()
{



    //该线程操作视频包队列，一个个包取出成帧，再调用queue_picture开成picture队列，为显示图像作最后准备

  //  printf("video_thread start");
      VideoState *is = parent->global_video_state;


     AVPacket pkt1, *packet = &pkt1;
     int len1;
     int frameFinished;
     AVFrame *pFrame;
     double pts;
     pts=0;

     pFrame = avcodec_alloc_frame();

     for(;;) {

         if(is->quit) {
             printf("video_thread quited");
             break;
         }

       if(packet_queue_get(&is->videoq, packet, 1) < 0) {
         // means we quit getting packets
         return ;
       }
       if(packet->data == parent->flush_pkt.data) {
           avcodec_flush_buffers(is->video_st->codec);

           //avcodec_default_free_buffers(is->video_st->codec);
           continue;
       }

        //从包中得到pts信息
        parent->global_video_pkt_pts = packet->pts;
       // Decode video frame
       len1 = avcodec_decode_video2(is->video_st->codec, pFrame, &frameFinished, packet);

        if(packet->dts == AV_NOPTS_VALUE && pFrame->opaque && *(uint64_t*)pFrame->opaque != AV_NOPTS_VALUE) {
         pts = *(uint64_t *)pFrame->opaque;
       } else if(packet->dts != AV_NOPTS_VALUE) {
         pts = packet->dts;             //用dts代替
       } else {
         pts = 0;                       //用0代替
       }

         pts *= av_q2d(is->video_st->time_base); //   得到了以秒为单位的PTS

       // 从包中得到一帧数据后，就把该帧转化为picture,并加入到picture队列
       if(frameFinished) {
           pts = synchronize_video(is, pFrame, pts);
       //    parent->kernel_currenttime=pts;         //获得当前播放时间，以秒为单位
       //    emit UpdateTime();


         if(queue_picture(is, pFrame,pts) < 0) {
       break;
         }
       }
       av_free_packet(packet);
     }
     av_free(pFrame);
     return ;


}

double VideoThread::synchronize_video(VideoState *is, AVFrame *src_frame, double pts) {

 double frame_delay;

 if(pts != 0) {

   is->video_clock = pts;
 } else {

   pts = is->video_clock;
 }
           //基本时间作为延迟的初始值，time_base应该为倒数时间
 frame_delay = av_q2d(is->video_st->codec->time_base);
//repeat_pict为重复的帧数目，每帧算上延迟，加起来，作为一个新的延迟。这样就不用每个重复帧都刷新一下
 frame_delay += src_frame->repeat_pict * (frame_delay * 0.5);
 is->video_clock += frame_delay;  //video_clock应该为倒数的时钟，倒数完就刷新，所以把delay加上去
 return pts;
}


int VideoThread::queue_picture(VideoState *is, AVFrame *pFrame,double pts) {

 VideoPicture *vp;

// AVFrame *pFrameYUV;
 static struct SwsContext *img_convert_ctx;
// uint8_t *out_buffer;  // AVFrame *pFrameYUV;
// vp = (VideoPicture *)av_mallocz(sizeof(VideoPicture));

// pFrameYUV=avcodec_alloc_frame();




 SDL_LockMutex(is->pictq_mutex);
 while(is->pictq_size >= VIDEO_PICTURE_QUEUE_SIZE &&
   !is->quit) {
   SDL_CondWait(is->pictq_cond, is->pictq_mutex);
 }
 SDL_UnlockMutex(is->pictq_mutex);

 if(is->quit)
   return -1;

 // windex is set to 0 initially
 vp = &is->pictq[is->pictq_windex];

 /* allocate or resize the buffer! */
 if(!vp->bmp ||
    vp->width != is->video_st->codec->width ||
    vp->height != is->video_st->codec->height) {
   SDL_Event event;

   vp->allocated = 0;
   /* we have to do it in the main */
   event.type = FF_ALLOC_EVENT;
   event.user.data1 = is;
   SDL_PushEvent(&event);

   /* wait until we have a picture allocated */
   SDL_LockMutex(is->pictq_mutex);
   while(!vp->allocated && !is->quit) {
     SDL_CondWait(is->pictq_cond, is->pictq_mutex);
   }
   SDL_UnlockMutex(is->pictq_mutex);
   if(is->quit) {
     return -1;
   }
 }
 /* We have a place to put our picture on the queue */

 if(vp->bmp) {
     if(parent->out_buffer==NULL)
        parent->out_buffer=new uint8_t[avpicture_get_size(PIX_FMT_RGB24,is->video_st->codec->width, is->video_st->codec->height)];

       //p_frame_yuv数据自动关联到out_buffer
       avpicture_fill((AVPicture *)parent->pFrameYUV, parent->out_buffer, PIX_FMT_RGB24, is->video_st->codec->width,is->video_st->codec->height);
 /* wait until we have space for a new pic */
   img_convert_ctx = sws_getContext(is->video_st->codec->width,is->video_st->codec->height,is->video_st->codec->pix_fmt,is->video_st->codec->width,is->video_st->codec->height, PIX_FMT_RGB24,SWS_BICUBIC,NULL, NULL, NULL);
   sws_scale(img_convert_ctx,(const uint8_t* const*) pFrame->data, pFrame->linesize, 0,is->video_st->codec->height, parent->pFrameYUV->data, parent->pFrameYUV->linesize);

  SDL_LockYUVOverlay(vp->bmp);
  vp->bmp->pixels[0]= parent->pFrameYUV->data[0];
  vp->bmp->pixels[2]= parent->pFrameYUV->data[1] ;
  vp->bmp->pixels[1]= parent->pFrameYUV->data[2] ;

  vp->bmp->pitches[0]=parent->pFrameYUV->linesize[0] ;
   vp->bmp->pitches[2]=parent->pFrameYUV->linesize[1] ;
   vp->bmp->pitches[1]=parent->pFrameYUV->linesize[2];
  SDL_UnlockYUVOverlay(vp->bmp);
    //保存pts到video_picture结构
     vp->pts = pts;

  /* now we inform our display thread that we have a pic ready */
   if(++is->pictq_windex == VIDEO_PICTURE_QUEUE_SIZE) {
     is->pictq_windex = 0;
   }
   SDL_LockMutex(is->pictq_mutex);
   is->pictq_size++;                   //这个队列在写的时候会一直写入到满为止，在读的时 候会一直读空为止。因此所有的都依
                                       //赖于is->pictq_size值，这要求我们必需要锁定它。
   SDL_UnlockMutex(is->pictq_mutex);
 }



 return 0;
}




int VideoThread::packet_queue_get(PacketQueue *q, AVPacket *pkt, int block)
{
AVPacketList *pkt1;
int ret;

SDL_LockMutex(q->mutex);

for(;;) {

  if(parent->global_video_state->quit) {
    ret = -1;
    break;
  }

  pkt1 = q->first_pkt;
  if (pkt1) {
    q->first_pkt = pkt1->next;
    if (!q->first_pkt)
  q->last_pkt = NULL;
    q->nb_packets--;
    q->size -= pkt1->pkt.size;
    *pkt = pkt1->pkt;
    av_free(pkt1);
    ret = 1;
    break;
  } else if (!block) {
    ret = 0;
    break;
  } else {
    SDL_CondWait(q->cond, q->mutex);
  }
}
SDL_UnlockMutex(q->mutex);
return ret;
}

