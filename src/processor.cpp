#include "processor.h"
#include "linux_parser.h"
#include <unistd.h>

// I implemented: Return the aggregate CPU utilization
float Processor::Utilization() { 

    TotalLoadNext = LinuxParser::Jiffies();
    IdleLoadNext = LinuxParser::IdleJiffies();
    TotalLoad = TotalLoadNext - TotalLoadPrev;
    IdleLoad = IdleLoadNext - IdleLoadPrev;
    sleep(0.5); //sleepin system for 0.5 sec to assess change in CPU usage
    TotalLoadPrev = TotalLoadNext;
    IdleLoadPrev = IdleLoadNext;
    if(TotalLoad>0){ //checking totoal load is not zero to avoid errors!
        utilization = (TotalLoad-IdleLoad)/TotalLoad;
        }return utilization;
    }