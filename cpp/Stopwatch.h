//!
//! \file main.h
//! \author jxtopher
//! \version 1
//! \date 2019-03
//! \brief Function stopwatch
//!

#ifndef JXTOPHER_STOPWATCH_H
#define JXTOPHER_STOPWATCH_H

#include <chrono>

using namespace std;
using namespace std::chrono;


namespace jxtopher {
class Stopwatch {
public:

    auto operator()(void (*f)()) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        f();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>( t2 - t1 ).count();

        return duration;
    }
    
};
}

#endif
