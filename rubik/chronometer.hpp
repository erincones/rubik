

#ifndef CHRONOMETER_HPP
#define CHRONOMETER_HPP

#include<ctime>

using std::clock;
using std::clock_t;

const double pps = CLOCKS_PER_SEC;

class chronometer
{

public:

  chronometer():active{false},t0{},t1{}{}

  void run(){active = true; t0 = clock(); }
  void stop(){if(active){active = false; t1 = clock();}}

  void reset(){ active = false; t0 = clock_t(); t1=clock_t();}

  double get_time()const{return ((active ? clock(): t1)-t0)/pps;}

private:

  bool active ;

  clock_t t0, t1;

};

#endif


