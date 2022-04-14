#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"
#include <string>
#include <sstream>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the FCFS algorithm.
*/

FCFSScheduler::FCFSScheduler(int slice) {
    if (slice != -1) {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread() {
        std::shared_ptr<SchedulingDecision> next(new SchedulingDecision);
        if(queue.size() != 0){
            next->thread = queue.top(); 
            next->explanation = "Selected from " + std::to_string(queue.size()) + " threads. Will run to completion of burst.";
            queue.pop();   
            return next;
        }else{
            next->explanation = "No threads available for scheduling";
            return next;
        }
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
        order = order + 1;
        queue.push(order,std::move(thread)); 
}

size_t FCFSScheduler::size() const {
        return queue.size(); 
}
