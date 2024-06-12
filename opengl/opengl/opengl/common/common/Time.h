//
// Created by captain on 2021/8/5.
//

#ifndef UNTITLED_TIME_H
#define UNTITLED_TIME_H


#include <string>
#include <spdlog/fmt/chrono.h>

class Time
{
public:
    Time();
    ~Time();

    //��ʼ��
    static void Init();

    static void Update();

    //��ȡ��Ϸ����ʱ��
    static float TimeSinceStartup();

    static float delta_time() { return delta_time_; }

private:
    static std::chrono::system_clock::time_point startup_time_;
    static float last_frame_time_;
    static float delta_time_;//��һ֡���ѵ�ʱ��
};


#endif //UNTITLED_TIME_H
