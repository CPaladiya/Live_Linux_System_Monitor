#include "processor.h"
#include "linux_parser.h"
#include <unistd.h>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

    TotalLoadNext = LinuxParser::Jiffies();
    IdleLoadNext = LinuxParser::IdleJiffies();
    TotalLoad = TotalLoadNext - TotalLoadPrev;
    IdleLoad = IdleLoadNext - IdleLoadPrev;
    if(TotalLoad>0){
        utilization = (TotalLoad-IdleLoad)/TotalLoad;
        return utilization;
        }
    sleep(0.5);
    TotalLoadPrev = TotalLoadNext;
    IdleLoadPrev = IdleLoadNext;
    
    }