#include <string>
#include <cmath>
#include <iomanip>


#include "format.h"

using std::string;



// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    int HH;
    int MM;
    int SS;



    HH = seconds/3600;
    MM = (seconds % 3600) / 60;
    SS = (seconds % 3600) % 60;







    // return std::to_string(HH) + ":" + std::to_string(MM) + ":" + std::to_string(SS);
    std::ostringstream stream;
    stream << std::setw(2) << std::setfill('0') << HH << ":" << std::setw(2) << std::setfill('0') << MM << ":"
     << std::setw(2) << std::setfill('0') << SS;
     
     return stream.str();

    
    
 }