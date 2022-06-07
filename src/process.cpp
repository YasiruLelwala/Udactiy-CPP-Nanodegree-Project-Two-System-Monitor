#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid()  { 
    return pid_ ; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization()  { 

    long TotalTime = LinuxParser::ActiveJiffies(pid_);
    long StartTime = LinuxParser::UpTime(pid_);

    long SystemUptime = LinuxParser::UpTime();

    long Hertz = sysconf(_SC_CLK_TCK);

    float Seconds = static_cast<float> (SystemUptime) - 
    ( static_cast<float> (StartTime) / static_cast<float> (Hertz) );

    float CpuUsage = ( static_cast<float> (TotalTime) / static_cast<float> (Hertz) ) / Seconds;

    Cpu_ = CpuUsage;

    return CpuUsage;
                                                                                        


 }

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    
    string RamString =  LinuxParser::Ram(pid_); 
    long Ram = std::stoi(RamString) * 0.001;

    return std::to_string(Ram);
    
    }

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(pid_);
    
 }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 

    long UptimeClockTicks = LinuxParser::UpTime(pid_);

    long Uptime =  UptimeClockTicks / sysconf(_SC_CLK_TCK);

    return Uptime;

 }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 

    return a.Cpu_ < this->Cpu_;
}


    

    
 