#include "RecordList.h"
#include <iomanip>
#include <iostream>

using namespace std;



   TimePoint ParseDateStrings(string date) throw(){
            //This function will parse date string into a chrono time point making it a  comparable object
            try {
                tm time_struct = {};
            istringstream date_stream(date);
            
            date_stream >> get_time(&time_struct,"%Y-%m-%d");
            if (date_stream.fail()) {
                // This happens If the format given isn't valid e.g : YYYY/DD/MM 
                throw std::invalid_argument("Parser failed while processing date!");
            }
            
            // converting C time struct to chrono::time_point
            auto time_point = chrono::system_clock::from_time_t(std::mktime(&time_struct));

            return time_point;
            } catch (const exception& ex){
                cerr << ex.what();
            }
            return TimePoint::min();
    }
Record::Record(int _consomation, int _injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours):record_date(DateInfo(date, day_weather, max_temp, min_temp, sunny_hours)){
    consomation = _consomation;
    injection = _injection;
    record_date = DateInfo(date,day_weather,max_temp,min_temp,sunny_hours);
    next_record = nullptr;
}
float Record::GetInjection() const {
    return injection;
}
Record::~Record(){}

RecordList::RecordList(){
    head_record = tail_record = nullptr;
}

RecordList::~RecordList()
{
}



bool RecordList::insertRecord(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours){
    
    auto newRecord = new Record(consomation, injection, date, day_weather, max_temp, min_temp, sunny_hours);
    
    if(!head_record){
        head_record = newRecord;
        tail_record = newRecord;
        return true;
    }
    tail_record->next_record = newRecord;
    tail_record = newRecord;
    return true;
}
