#ifndef BASECONSTANT_H
#define BASECONSTANT_H
class QString;
class BaseConstant
{
public:
    BaseConstant();
    enum State         //表示播放状态的值
    {
        PlayingState,
        PausedState,
        StoppedState,
        StartState
    };

};

#endif
