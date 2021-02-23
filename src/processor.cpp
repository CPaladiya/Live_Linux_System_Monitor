#include "processor.h"
#include "linux_parser.h"
#include <unistd.h>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

    TotalLoadPrev = LinuxParser::Jiffies();
    IdleLoadPrev = LinuxParser::IdleJiffies();
    //sleep(0.5);
    TotalLoadNext = LinuxParser::Jiffies();
    IdleLoadNext = LinuxParser::IdleJiffies();
    TotalLoad = TotalLoadNext - TotalLoadPrev;
    IdleLoad = IdleLoadNext - IdleLoadPrev;
    if(TotalLoad>0){
        utilization = (TotalLoad-IdleLoad)/TotalLoad;
        return utilization;
        }
    }