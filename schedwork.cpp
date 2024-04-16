#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
void schedule_helper(size_t curr_day, bool& found, vector<int>& shifts, const AvailabilityMatrix& avail, const size_t d, DailySchedule& sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Create Possible Shifts
    vector<int> shifts;
    for(size_t i = 0; i < avail[0].size(); i ++){
        shifts.push_back(maxShifts);
    }
    for(size_t i = 0; i < avail.size(); i ++){
        sched.push_back(vector<Worker_T>());
    }

    bool found = false;
    schedule_helper(0, found, shifts, avail, dailyNeed, sched);
    return found;
}


void schedule_helper(size_t curr_day, bool& found, vector<int>& shifts, const AvailabilityMatrix& avail, const size_t d, DailySchedule& sched){
    if(found)
        return;
    else if(curr_day == avail.size()){
        found = true;
        return;
    }
    else if(sched[curr_day].size() == d)
        schedule_helper(curr_day + 1, found, shifts, avail, d, sched);
    else{
        Worker_T start = sched[curr_day].empty() ? 0 : (sched[curr_day].back() + 1);
        for(Worker_T i = start; i < avail[curr_day].size(); i ++){
            if(avail[curr_day][i] && shifts[i] > 0){
                sched[curr_day].push_back(i);
                shifts[i] --;
                schedule_helper(curr_day, found, shifts, avail, d, sched);
                if(found)
                    return;
                sched[curr_day].pop_back();
                shifts[i] ++;
            }
        }
    }
}
