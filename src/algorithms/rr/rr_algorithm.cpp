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
    if(slice <= 0 ){
        //throw("Error: Time slice needs to be postive integer");
        this->time_slice = 3;
    }else{
        this->time_slice = slice; 
    }
}

std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread() {
    std::shared_ptr<SchedulingDecision> next(new SchedulingDecision);
    if(queue.size() != 0){
        next->thread = queue.top(); 
        next->explanation = next->explanation = "Selected from " + std::to_string(queue.size()) + " threads. Will run for at most " + std::to_string(this->time_slice) + " ticks.";
        next->time_slice = this->time_slice; 
        queue.pop();
        return next; 
    }
    else{
        next->explanation = "No threads available for scheduling";
        return next;
    }
}

void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    order = order + 1;
    queue.push(order,thread); 
}

size_t RRScheduler::size() const {
    return queue.size();
}
