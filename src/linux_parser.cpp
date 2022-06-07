#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <numeric>

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

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  float value;
  
  float TotalMemory;
  float FreeMemory;
  float MemoryUtilization;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline (filestream,line)) {
      std::istringstream linestream (line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          
          TotalMemory = value;
        }
        if (key == "MemFree:") {
          
          FreeMemory = value;
        }

      }
    }
  }
  MemoryUtilization =  1 - FreeMemory/TotalMemory;
  return MemoryUtilization;

 }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  float UptimeFloat;
  long UptimeLong;
  std::ifstream filestream (kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline (filestream,line);
    std::stringstream linestream (line);
    linestream >> UptimeFloat;
  }
  UptimeLong = static_cast<long>(UptimeFloat);
  return UptimeLong;


 }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  vector <long> Jiffies = CpuUtilization();
  long TotalJiffies = accumulate(Jiffies.begin(),Jiffies.end(),0);
  return TotalJiffies;

 }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function

// Getting the summation of the 14th, 15th, 16th, and 17th numbers of in the stat file
long LinuxParser::ActiveJiffies(int pid) { 
  string line;
  string value;
  vector <string> Data;
  long ActiveJiffies = 0;

  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline (filestream, line)) {

      for (int i = 0; i < 18; i++) {

        std::istringstream linestream (line);
        linestream >> value;
        Data.push_back(value);

      }
    }
  }

  for (int i = 0; i < 4; i++) {

    long Jiffie = std::stol(Data[i+13]);
    ActiveJiffies += Jiffie;


  }

return ActiveJiffies;
 }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  long TotalJiffies = Jiffies();
  long IdleJiffies = LinuxParser::IdleJiffies();
  
  long ActiveJiffies = TotalJiffies - IdleJiffies;
  return ActiveJiffies;

 }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  vector <long> Jiffies = CpuUtilization();
  long IdleJiffies = Jiffies[kIdle_] + Jiffies[kIOwait_];
  return IdleJiffies;

 }

// TODO: Read and return CPU utilization
vector<long> LinuxParser::CpuUtilization() {
  string line;
  string key;
  long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  vector <long> Jiffies;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    std::getline (filestream, line);
    std::istringstream linestream (line);
    linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
    Jiffies.push_back(user);
    Jiffies.push_back(nice);
    Jiffies.push_back(system);
    Jiffies.push_back(idle);
    Jiffies.push_back(iowait);
    Jiffies.push_back(irq);
    Jiffies.push_back(softirq);
    Jiffies.push_back(steal);
    Jiffies.push_back(guest);
    Jiffies.push_back(guest_nice);
    }

    return Jiffies;


 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  long int value;
  int NoOfTotalProcesses;
  std::ifstream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline (filestream, line)) {
      std::istringstream linestream (line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          NoOfTotalProcesses = value;

        }
      }
    }
  }

  return NoOfTotalProcesses;
 }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  int value;
  int NoOfRunningProcesses;
  std::ifstream filestream (kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline (filestream, line)) {
      std::istringstream linestream (line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          NoOfRunningProcesses = value;

        }
      }
    }
  }

  return NoOfRunningProcesses;





}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kCmdlineFilename );
  if (filestream.is_open()){
    std::getline (filestream, line);
  }

  return line;

 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  string Ram;

  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline (filestream, line)) {
      std::istringstream linestream (line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          Ram = value;
        }
      }
    }  
  }
  return Ram;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  string Uid;
  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline (filestream, line)) {
      std::istringstream linestream (line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          Uid = value;

        }
      }
    }
  }

  return Uid;



 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {

  string Uid = LinuxParser::Uid(pid);

  string line;
  string key;
  string x;
  string value;

  std::ifstream filestream (kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline (filestream, line)) {
      std::replace (line.begin(),line.end(),':',' ');
      std::istringstream linestream (line);
      while (linestream >> key >> x >> value) {
        if (value == Uid) {
          return key;
        }



  }}}return key;}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;
  string value;
  long StartTime;
  

  std::ifstream filestream (kProcDirectory + std::to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline (filestream, line)) {

      for (int i = 0; i < 22; i++) {

        std::istringstream linestream (line);
        linestream >> value;
        

      }
      return StartTime = std::stol(value);
    }
  }

  return 0;

 }
