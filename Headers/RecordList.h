#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

typedef chrono::system_clock::time_point TimePoint;

TimePoint ParseDateStrings(string) throw();
struct DateInfo {
            
            TimePoint date;
            string day_weather;
            unsigned int max_temp;
            unsigned int min_temp;
            unsigned int sunny_hours;
            
            DateInfo(string _date ,string _day_weather , int _max_temp, int _min_temp, int sunny_hrs){
                
                date = ParseDateStrings(_date);
                //Parsing the string we have into the date array
                day_weather = _day_weather;
                max_temp = _max_temp;
                min_temp = _min_temp;
                sunny_hours = sunny_hrs;
            }

            string Formatted() const{
                time_t c_time = chrono::system_clock::to_time_t(date);
                tm* time_info = localtime(&c_time);
                char buffer[12] ;
                if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", time_info) == 0) {
                throw std::runtime_error("Error formatting time point");
            }
                return string(buffer);
            }           
         
};
class Record{
            public:
                friend class Customer;
                friend class RecordList;
                Record(int _consomation, int _injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours);
                ~Record();
                float   GetNetCost() const {
                    return 5*consomation - 3*injection;
                }
                string GetDayWeather() const {
                    return record_date.day_weather;
                }
                int GetDayMaxTemp() const {
                    return record_date.max_temp;
                }
                int GetDayMinTemp() const {
                    return record_date.min_temp;
                }
                 //This retrieves the net price for the daily transaction of the customer
                float   GetInjection()  const;
                float   GetConsumption() const {
                    return consomation;
                }

                TimePoint getDate() const { return record_date.date;}
                string getDateString() const {
                    return record_date.Formatted();
                }

                bool operator<(const Record & rec){
                    return this->getDate() < rec.getDate();
                }
                
                Record*  next_record;

            private:
                float    consomation;
                float    injection;
                DateInfo record_date;

};

class RecordList
{
    public:
        RecordList();
        ~RecordList();

        bool insertRecord(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours);

        Record* head_record;
        Record* tail_record;

};
#endif