#pragma once

#include "Base.h"
#include "WorkType.h"
#include "SerializableClass.h"

enum class ePriority {
    ABSOLUTE = 100, //Do not assign this priority to character. Only for situational priority.
    VERY_HIGH = 5,
    HIGH = 4,
    MIDDLE = 3,
    LOW = 2,
    VERY_LOW = 1,
    NEVER = -200,
};

class WorkPriority : SerializableClass {
private:
    vector<pair<ePriority, eWorkType> > work_vector;

    void Sort() {
        sort(work_vector.begin(), work_vector.end());
        reverse(work_vector.begin(), work_vector.end()); //temp
    }

    int ToInt(ePriority priority) {
        return static_cast<int>(priority);
    }
    int ToInt(eWorkType type) {
        return static_cast<int>(type);
    }

    int FindIndexOf(eWorkType type) {
        for(int i=0;i<work_vector.size();i++)
            if(work_vector[i].second == type)
                return i;
        printf("ERROR: [WorkPriority] Missed WorkType. %d\n", ToInt(type));
        return -1;
    }
    
public:
    WorkPriority() {
        //To-do push_back with csv file
        work_vector.push_back({ePriority::MIDDLE, eWorkType::COLLECT_WOOD});
        work_vector.push_back({ePriority::MIDDLE, eWorkType::COLLECT_STONE});
        work_vector.push_back({ePriority::MIDDLE, eWorkType::CREATE_ITEM});
        work_vector.push_back({ePriority::MIDDLE, eWorkType::SELL_ITEM});
    }

    ePriority GetPriorityOf(eWorkType type) {
        int index = FindIndexOf(type);
        return work_vector[index].first;
    }

    eWorkType GetMostImportantWorkWhenCombinedWithOtherPrioirities(WorkPriority *other_proirities) {
        int highest_priority = -1000;
        eWorkType most_important_work = eWorkType::SELL_ITEM; //temporal

        for(int i=0;i<work_vector.size();i++) {
            int combined_priority = 
                ToInt(work_vector[i].first) + 
                ToInt(other_proirities->GetPriorityOf(work_vector[i].second));

            if(combined_priority > highest_priority) {
                highest_priority = combined_priority;
                most_important_work = work_vector[i].second;
            }
        }
        return most_important_work;
    }
    void UpdatePriority(eWorkType type, ePriority new_priority) {
        int index = FindIndexOf(type);
        work_vector[index].first = new_priority;
        Sort();
    }

    Array Serialize() {

    }
};