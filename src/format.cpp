#include <string>

#include "format.h"

using std::string;

// ---------------CppND - I have implemented this function--------------------//

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    
    long int hrs,min,sec; //defining hours,minutes,seconds
    long int after_hrs; //defining qty remaining after calculating hours and minutes
    hrs = seconds/3600; //getting the hours
    after_hrs = seconds%3600; //remaining seconds off of the hours we got just above
    min = after_hrs/60; //getting minutes
    sec = after_hrs%60; //getting seconds
    
    //defining string for all the variables
    std::string time_string, hrs_string, min_string, sec_string;
	
    //adding 0 if hrs,nin or sec is less than 10 to maintain HH:MM:SS format
	hrs_string = hrs<10 ? "0"+std::to_string(hrs) : std::to_string(hrs);  
    min_string = min<10 ? "0"+std::to_string(min) : std::to_string(min); 
    sec_string = sec<10 ? "0"+std::to_string(sec) : std::to_string(sec); 
    time_string = hrs_string + ":" + min_string + ":" + sec_string;

    return time_string;
 }