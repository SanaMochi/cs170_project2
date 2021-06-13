#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

class timer {
    private:
        std::chrono::steady_clock::time_point Start;
    public:
        timer() {
            Start = std::chrono::steady_clock::now();
            std::cout << "[ ELAPSED ] ";
        }
        std::string time() {
            std::stringstream output;
            std::chrono::duration<float, std::milli> dur = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(std::chrono::steady_clock::now() - Start);

            if(dur.count() > 1000){
                output << "[ "; output.width(6); output << std::setprecision(4) << std::chrono::duration_cast<std::chrono::duration<float>>(dur).count() << "s ] ";
            }
            else {
                output << "[ "; output.width(5); output << std::setprecision(3) << dur.count() << "ms ] ";
            }

            return output.str();
        }
};

#endif