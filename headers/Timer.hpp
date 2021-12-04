#pragma once
#include <chrono>

class Timer{
    std::chrono::time_point<std::chrono::system_clock> previous, now, intermediate;

    bool is_running = false;

    public:
        void start();
        void stop();
        double timeGoneMicro();
};