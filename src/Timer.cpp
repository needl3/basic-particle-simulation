#include "../headers/Timer.hpp"
void Timer::start(){
    previous = std::chrono::system_clock::now();
    intermediate = previous;
    is_running = true;
}
void Timer::stop(){
    if(is_running){
        is_running = false;
        now = std::chrono::system_clock::now();            
    }
}
double Timer::timeGoneMicro(){
    if(is_running)
    {
        double temp = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-intermediate).count();
        intermediate =  std::chrono::system_clock::now();
        return temp;
    }
    else
        return std::chrono::duration_cast<std::chrono::microseconds>(now-previous).count();
}