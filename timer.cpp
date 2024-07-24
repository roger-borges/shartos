#include "timer.h"

Timer::Timer()
{
  QueryPerformanceFrequency( & freq );
  reset();
}

Timer::~Timer()
{
}

void Timer::start()
{
  QueryPerformanceCounter( & starttime );
}

void Timer::stop()
{
  QueryPerformanceCounter( & stoptime );
  duration += stoptime.QuadPart - starttime.QuadPart;
}

void Timer::reset()
{
  duration = 0;
  starttime.QuadPart = stoptime.QuadPart = 0;
}

void Timer::resetAndStart()
{
  reset();
  start();
}

double Timer::time_ms()
{
  stop();
  start();
  return duration / ( freq.QuadPart ) * 1000;
}

double Timer::time_s()
{
  stop();
  start();
  return duration / ( freq.QuadPart );
}
bool Timer::operator < ( Timer t)
{
  return this->time_ms() < t.time_ms();
}

bool Timer::operator > ( Timer t)
{
  return this->time_ms() > t.time_ms();
}