#include "algorithms/priority/priority_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"


/*
    Here is where you should define the logic for the priority algorithm.
*/

PRIORITYScheduler::PRIORITYScheduler(int slice) {
    if (slice != -1) {
        throw("PRIORITY must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> PRIORITYScheduler::get_next_thread() {
    std::shared_ptr<SchedulingDecision> next(new SchedulingDecision);
        if(s_queue.size() != 0){
            next->thread = s_queue.top(); 
            next->explanation = "[S: " + std::to_string(s_queue.size()) + " I: " + std::to_string(i_queue.size()) + " N: " + std::to_string(n_queue.size()) + " B: " + std::to_string(b_queue.size()) + "] -> " + "[S: " + std::to_string(s_queue.size()-1) + " I: " + std::to_string(i_queue.size()) + " N: " + std::to_string(n_queue.size()) + " B: " + std::to_string(b_queue.size()) + "]. Will run to completion of burst.";
            s_queue.pop();   
            return next;
        }else if(i_queue.size() != 0){
            next->thread = i_queue.top(); 
            next->explanation = "[S: " + std::to_string(s_queue.size()) + " I: " + std::to_string(i_queue.size()) + " N: " + std::to_string(n_queue.size()) + " B: " + std::to_string(b_queue.size()) + "] -> " + "[S: " + std::to_string(s_queue.size()) + " I: " + std::to_string(i_queue.size()-1) + " N: " + std::to_string(n_queue.size()) + " B: " + std::to_string(b_queue.size()) + "]. Will run to completion of burst.";
            i_queue.pop();   
            return next;
        }else if(n_queue.size() != 0){
            next->thread = n_queue.top(); 
            next->explanation = "[S: " + std::to_string(s_queue.size()) + " I: " + std::to_string(i_queue.size()) + " N: " + std::to_string(n_queue.size()) + " B: " + std::to_string(b_queue.size()) + "] -> " + "[S: " + std::to_string(s_queue.size()) + " I: " + std::to_string(i_queue.size()) + " N: " + std::to_string(n_queue.size()-1) + " B: " + std::to_string(b_queue.size()) + "]. Will run to completion of burst.";
            n_queue.pop();   
            return next;
        }else if(b_queue.size() != 0){
            next->thread = b_queue.top(); 
            next->explanation = "[S: " + std::to_string(s_queue.size()) + " I: " + std::to_string(i_queue.size()) + " N: " + std::to_string(n_queue.size()) + " B: " + std::to_string(b_queue.size()) + "] -> " + "[S: " + std::to_string(s_queue.size()) + " I: " + std::to_string(i_queue.size()) + " N: " + std::to_string(n_queue.size()) + " B: " + std::to_string(b_queue.size()-1) + "]. Will run to completion of burst.";
            b_queue.pop();   
            return next;
        }else{
            next->explanation = "No threads available for scheduling";
            return next;
        }
}

void PRIORITYScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    switch(thread->priority) {
    case SYSTEM:
        orders[0] += 1;
        s_queue.push(orders[0],std::move(thread)); 
        break;
    case INTERACTIVE:
        orders[1] += 1;
        i_queue.push(orders[1],std::move(thread)); 
        break;
    case NORMAL:
        orders[2] += 1;
        n_queue.push(orders[2],std::move(thread)); 
        break;
    case BATCH:
        orders[3] += 1;
        b_queue.push(orders[3],std::move(thread)); 
        break;
    }
}

size_t PRIORITYScheduler::size() const {
    return s_queue.size() + i_queue.size() + n_queue.size() + b_queue.size();
}
