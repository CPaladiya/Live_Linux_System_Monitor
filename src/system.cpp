#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm> //for sorting the vector

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// I implemented: Return the system's CPU-----------------
Processor& System::Cpu() { 
    return cpu_; 
    }

// I implemented : Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> ListofPIDs = LinuxParser::Pids();
    for (const int& pid : ListofPIDs){ //creating new Process object everytime with set pid value
        processes_.emplace_back(pid);
    }
    std::sort(processes_.begin(),processes_.end());
    return processes_;
}

// I implemented: Return the system's kernel identifier (string)-----------------
std::string System::Kernel() { 
    return LinuxParser::Kernel(); 
    }
// I implemented: Return the system's memory utilization-----------------
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); 
    }

// I implemented: Return the operating system name-----------------
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem(); 
    }

// I implemented: Return the number of processes actively running on the system -----------------
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
    }

// I implemented: Return the total number of processes on the system -------------
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
    }

// I implemented: Return the number of seconds since the system started running -----------------
long int System::UpTime() { 
    return LinuxParser::UpTime(); 
    }