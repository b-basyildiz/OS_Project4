#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>
#include "utilities/stable_priority_queue/stable_priority_queue.hpp"

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
        //need to find quick thread to output next 
        if(queue.size() != 0){
            std::shared_ptr<SchedulingDecision> next;
            next->thread = queue.top(); 
            queue.pop();
            std::cout << "Selected from " << queue.size() << " threads. Will run to completion of burst." << std::endl;  
            return next;
        }else{
            std::cerr << "No threads available for scheduling" << std::endl;
            return(NULL); 
        }
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
        queue.push(-1,thread); 
}

size_t FCFSScheduler::size() const {
        return queue.size(); 
}
