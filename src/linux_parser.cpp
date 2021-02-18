#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <algorithm> //for remove 
#include <numeric> //for std::accumulate - summing up the vector

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// I implemented: Read and return the system memory utilization -------------------------------------
float LinuxParser::MemoryUtilization() { 
  string line;
	string key;
	int value; //converting string into float at the same time using linestream
	int TotalMem;
	int FreeMem;
	int UsedMem;
	string UsedMem_string;
	std::ifstream filestream(kProcDirectory + kMeminfoFilename);
	if (filestream.is_open()){
		while(std::getline(filestream, line)){ //MemTotal:    7918692 KB
			std::replace(line.begin(), line.end(), ' ', '_'); //MemTotal:_____7918692_KB, can not use "", only use ''
			std::replace(line.begin(), line.end(), ':', ' ');//MemTotal _____7918692_KB
			line.erase(line.end()-3, line.end()); //MemTotal _____7918692
			line.erase(std::remove(line.begin(),line.end(),'_'),line.end()); //MemTotal 7918692
			std::stringstream linestream(line);
			while(linestream>>key>>value){
				if (key == "MemTotal"){
					TotalMem = value;
					}
				if (key == "MemFree"){
					FreeMem = value;
					}
				}
			}
		}
	UsedMem = TotalMem-FreeMem;
	return UsedMem;
}

// I implemented : Read and return the system uptime ---------------------------------
long LinuxParser::UpTime() { 
  string line;
  long double TotalUpTime; //converting string into long int at the same time using linestream
	long double IdleTime;
  long double UpTime;
	std::ifstream filestream(kProcDirectory + kUptimeFilename);
	if (filestream.is_open()){
		while(std::getline(filestream, line)){ //13145.68 43993.58 - Up time of the system, idle time of the system
			std::stringstream linestream(line);
			linestream>>TotalUpTime>>IdleTime;	
		}
    UpTime = TotalUpTime - IdleTime;
  }
  return UpTime;
}

// I implemented:Read and return the number of jiffies for the system -----------------------------------
long LinuxParser::Jiffies() { 
  vector<int long> CpuLoad;
  long int jiffies;
  CpuLoad = LinuxParser::CpuUtilization();
  jiffies = std::accumulate (CpuLoad.begin(), CpuLoad.end(), 0);
  return jiffies;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// I implemented : Read and return the number of active jiffies for the system -----------------------------------
long LinuxParser::ActiveJiffies() { 
  vector<long int> CpuLoad;
  CpuLoad = LinuxParser::CpuUtilization();
  long int active_jiffies;
  active_jiffies = CpuLoad[LinuxParser::kUser_]+ CpuLoad[LinuxParser::kNice_] + CpuLoad[LinuxParser::kSystem_] 
                  + CpuLoad[LinuxParser::kIRQ_] + CpuLoad[LinuxParser::kSoftIRQ_] + CpuLoad[LinuxParser::kSteal_];
  return active_jiffies; 
}

// I implemented: Read and return the number of idle jiffies for the system------------------------------------
long LinuxParser::IdleJiffies() { 
  vector<long int> CpuLoad;
  CpuLoad = LinuxParser::CpuUtilization();
  long int idle_jiffies;
  idle_jiffies = CpuLoad[LinuxParser::kIdle_]+ CpuLoad[LinuxParser::kIOwait_];
  return idle_jiffies; 
}

// I Implemented : Read and return CPU utilization --------------------------------
vector<long int> LinuxParser::CpuUtilization() { 
  string line;
  long int value;
  string title_of_line;
  vector<long int> CpuLoad;
  std::ifstream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while(getline(filestream, line)){
      std::stringstream linestream(line);
      linestream >> title_of_line;
      if(title_of_line == "cpu"){
        for(int i = 0 ; i<10 ; i++){
          linestream >> value;
          CpuLoad.push_back(value);
        }
        return CpuLoad; 
      }
    }
  }return CpuLoad; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  int totalProcesses;
  string title_of_line;
  std::ifstream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while(getline(filestream, line)){
      std::stringstream linestream(line);
      linestream >> title_of_line;
      if(title_of_line == "processes"){
        linestream >> totalProcesses;
        return totalProcesses; 
      }
    }
  }return totalProcesses; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  int runningProcesses;
  string title_of_line;
  std::ifstream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()){
    while(getline(filestream, line)){
      std::stringstream linestream(line);
      linestream >> title_of_line;
      if(title_of_line == "procs_running"){
        linestream >> runningProcesses;
        return runningProcesses;
      }
    }
  }return runningProcesses; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }