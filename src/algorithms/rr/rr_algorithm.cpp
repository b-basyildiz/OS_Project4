#include "algorithms/rr/rr_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

#include <string>
#include <sstream>

/*
    Here is where you should define the logic for the round robin algorithm.
*/

RRScheduler::RRScheduler(int slice) {    
    if(slice < 0 ){
        throw("Error: Time slice needs to be postive integer");
    }
    this->time_slice = slice; 
}

std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread() {
    if(queue.size() != 0){
        std::shared_ptr<SchedulingDecision> next; 
        next->thread = queue.top(); 
        std::ostringstream oss;
        oss << "Selected from " << queue.size() << " threads. Will run to completion of burst.";
        queue.pop();
        next->explanation = oss.str();
        return next; 
    }
    else{
        throw("No threads available for scheduling"); 
    }
}

void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    order = order + 1;
    queue.push(order,thread); 
}

size_t RRScheduler::size() const {
    return queue.size();
}
