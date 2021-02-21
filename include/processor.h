#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // I declared : Declare any necessary private members ------
 private:
 float TotalLoad;
 float IdleLoad;
 float TotalLoadPrev;
 float IdleLoadPrev;
 float TotalLoadNext;
 float IdleLoadNext;
 float utilization;
};

#endif