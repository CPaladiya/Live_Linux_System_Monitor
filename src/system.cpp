#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

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

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    vector<int> ListofPIDs = LinuxParser::Pids();
    for (int pid : ListofPIDs){
        Process process(pid);
        processes_.push_back(process);
    }
    processes_;
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