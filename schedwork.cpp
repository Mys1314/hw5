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
//function from wordle
bool testSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int row_day, int col_worker, vector<int>& ws);
bool canBeSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int row_day, int col_worker, vector<int>& ws);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    sched = vector<vector<Worker_T>>(avail.size(), vector<Worker_T>(dailyNeed,0));
    vector<int> workerSchedule(avail[0].size(),0);
    // Add your code below
    return testSchedule(avail, dailyNeed, maxShifts, sched, 0, 0, workerSchedule);
}

bool testSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int row_day, int col_worker, vector<int>& ws){
  sched[row_day][col_worker] = 0;
  //cout << sched[row_day][col_worker] << endl;
  while((int)sched[row_day][col_worker] < (int)(avail[0].size())){
    if(canBeSchedule(avail, dailyNeed, maxShifts, sched, row_day, col_worker, ws)){
      ws[sched[row_day][col_worker]] += 1;
      // cout << "here" << endl;
      // cout << col_worker << " " << row_day<< " " << sched.size() << " "<<dailyNeed<<endl;
      if(col_worker < (int)dailyNeed - 1){
        if(testSchedule(avail, dailyNeed, maxShifts, sched, row_day, col_worker+1, ws)){
          return true;
        }else{
          ws[sched[row_day][col_worker]] -= 1;
          sched[row_day][col_worker] += 1;
        }
      }else if(row_day < (int)sched.size() - 1){
        if(testSchedule(avail, dailyNeed, maxShifts, sched, row_day+1, 0, ws)){
          return true;
        }else{
          ws[sched[row_day][col_worker]] -= 1;
          sched[row_day][col_worker] += 1;
        }
      }else{
        return true;
      }
    }else{
      sched[row_day][col_worker] += 1;
    }
  }
  sched[row_day][col_worker] = 0;
  return false;
}

bool canBeSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int row_day, int col_worker, vector<int>& ws){
  if(avail[row_day][sched[row_day][col_worker]]==0){
    return false;
  }
  if(ws[sched[row_day][col_worker]] == (int)maxShifts){
    return false;
  }
  return true;
}

