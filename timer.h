#ifndef TIMER_HPP
  #define TIMER_HPP
  #include <windows.h>
class Timer
{
public:
  Timer();
  ~Timer();
  void start();
  void stop();
  void reset();
  void resetAndStart();
  double time_ms();
  double time_s();
  bool operator < ( Timer );
  bool operator > ( Timer );
private:
  LARGE_INTEGER freq;
  LARGE_INTEGER starttime;
  LARGE_INTEGER stoptime;
  double duration;
};





#endif
