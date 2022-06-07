#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

    float CurrentTotal = static_cast <float> (LinuxParser::Jiffies());
    float CurrentIdle = static_cast <float> (LinuxParser::IdleJiffies());

    float ChangeInTotal = CurrentTotal - Processor::PreviousTotal_;
    float ChangeInIdle = CurrentIdle - Processor::PreviousIdle_;

    float CPUPercentage = (ChangeInTotal - ChangeInIdle) / ChangeInTotal;

    

    //set the private variables of processor class to current total and current idle
    PreviousTotal_ = CurrentTotal;
    PreviousIdle_ = CurrentIdle;

    return CPUPercentage;

 }