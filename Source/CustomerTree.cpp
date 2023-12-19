#include <chrono>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "../Headers/CustomerTree.h"
//FIXME:path
using namespace std;
pair<TimePoint,TimePoint> GetDayPeriodFromMonth(string year_month) throw() {
    //Evil chrono hacks to turn a YYYY/MM into a period by  day and return them as a pair;
    try {
        tm time_struct = {};
    istringstream iss(year_month);
    iss >> get_time(&time_struct, "%Y-%m");
    if(iss.fail()) {
        throw invalid_argument("Invalid format was passed to the parser function");
    }
    time_struct.tm_mday = 1; //Set the day of the time struct to the beggining of the month
    auto period_start = chrono::system_clock::from_time_t(mktime(&time_struct));
    //To get the end of the month , we advance the month by 1 then go back by a second to land on the last day. (evil c++ hacks)

    time_struct.tm_mon += 1;
    auto period_end = chrono::system_clock::from_time_t(mktime(&time_struct)) - chrono::seconds(1);
    
    //Returning them as a pair
    return make_pair(period_start,period_end);
    } catch(const exception& ex){
        cerr << ex.what() << endl;
        return make_pair(TimePoint::min(),TimePoint::min());
    }
}
string GetLastMonthFromMonthString(const string& year_month) throw(){ //YYYY-MM
    try {
        istringstream iss(year_month);
    tm time_info = {};
     
    iss >> get_time(&time_info, "%Y-%m");

    if(iss.fail()){
        throw invalid_argument("Invalid format was passed to the parser function");
    }
    //Converting into chrono timepoints to manipulate into last month
    auto timepoint = chrono::system_clock::from_time_t(mktime(&time_info));
    //Substracting a day
    timepoint -= chrono::hours(1);

    //Converting manipulated timepoint back to C standard time_t format
    auto last_month_time_t = chrono::system_clock::to_time_t(timepoint) ;
    //then to time_m
    auto last_month_tm = *localtime(&last_month_time_t); //gmtime returns time in GMT format so not wise to use it without accomodation for time zones if hours are needed so we used localtime instead
    
    ostringstream output_stream_result;
    output_stream_result << put_time(&last_month_tm,"%Y-%m") ; //Extract YYYY-MM format to the output stream
    return output_stream_result.str(); //converting the stream into an std::string
    } catch(const exception& ex){
        cerr << ex.what() << endl;   
    }
    return "ERROR";
}
Customer::Customer(int id,string _name, string addr,const vector<unsigned int>& _family_ages)
{
    account_id = id;
    customer_name = _name;
    customer_address = addr;
    family_ages = vector<unsigned int>(family_ages);
    family_members_count = _family_ages.size();
}

Customer::~Customer()
{
    //Destruction of the tree and updating the files (if implemented)
}
string Customer::GetCustomerName(){
    return customer_name;
}


Record* Customer::addRecord(int consomation, int injection, string _date, string day_weather, int max_temp, int min_temp, int sunny_hours){
    auto _date_month = _date.substr(0,_date.size()-3);
    auto _date_year = _date.substr(0,4);
    auto last_month = GetLastMonthFromMonthString(_date_month);
    auto cumulative_inj_record = find_if(cumulative_inj.begin(),cumulative_inj.end(),[_date_month](const pair<string,float>& Rec){return Rec.first == _date_month;}); 
    //Here we check whether the cumulative record for this month exists or not
    if(cumulative_inj_record == cumulative_inj.end()){
        //If it doesn't exist we create a record for it
        cumulative_inj.push_back(make_pair(_date_month,injection));
        //We point the iterator to the last dererefenceable element to use it, that is because the find iteration leaves it in the end() non-deref iterator 
        cumulative_inj_record = cumulative_inj.end() - 1;
    }
    else{
        //If it exists we just add this new injection to it
        cumulative_inj_record->second += injection;
    }
    //We check for existing last month record
    auto target_last_month = find_if(cumulative_inj.begin() , cumulative_inj.end(),[last_month](const pair<string,float>& Rec){return Rec.first == last_month;});
    if(target_last_month != cumulative_inj.end()){
        //If it exists we just add its injection to the new one .
            cumulative_inj_record->second += target_last_month->second;
    }

    
    return addRecord_(consomation, injection, _date, day_weather, max_temp,  min_temp, sunny_hours);
    
}

Record* Customer::addRecord_(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours){
    auto _date_month = date.substr(0,date.size()-3);
    auto _date_year = date.substr(0,4);
    auto last_month = GetLastMonthFromMonthString(_date_month);
    auto cumulative_inj_record = find_if(cumulative_inj.begin(),cumulative_inj.end(),[_date_month](const pair<string,float>& Rec){return Rec.first == _date_month;}); 
    //Here we check whether the cumulative record for this month exists or not
    if(cumulative_inj_record == cumulative_inj.end()){
        //If it doesn't exist we create a record for it
        cumulative_inj.push_back(make_pair(_date_month,injection));
        //We point the iterator to the last dererefenceable element to use it, that is because the find iteration leaves it in the end() non-deref iterator 
        cumulative_inj_record = cumulative_inj.end() - 1;
    }
    else{
        //If it exists we just add this new injection to it
        cumulative_inj_record->second += injection;
    }
    //We check for existing last month record
    auto target_last_month = find_if(cumulative_inj.begin() , cumulative_inj.end(),[last_month](const pair<string,float>& Rec){return Rec.first == last_month;});
    if(target_last_month != cumulative_inj.end()){
        //If it exists we just add its injection to the new one .
            cumulative_inj_record->second += target_last_month->second;
    }
    return _customer_records.insertForCustomer(Record(consomation, injection, date, day_weather, max_temp, min_temp, sunny_hours));
    
}
// vector<Record> Customer::GetRecordsByPeriod(string start_date, string end_date) //DATES ARE IN YYYY-MM-DD
// {
//     // This checks for errors in parsing the period
//         auto start_tp = ParseDateStrings(start_date);
//         auto end_tp = ParseDateStrings(end_date);
//         if(start_tp > end_tp){
//             return vector<Record>({});
//         }
//         vector<Record> records; // Records will be gathered in a vector and redirected to the interface function
//         auto it = customer_records.head_record;
//         while(it){
//             if(it->getDate() >= start_tp && it->getDate() <= end_tp){
//                 records.push_back(*it);
//             }
//             it = it->next_record;
//         }
//         return records; //Returning vectors is appearently not as costly since c++ compilers use RVO (Return Value Optimization) to construct the return variable directly with the resulting vector instead of copying it
// }
vector<Record> Customer::GetRecordsByPeriod(string start_date, string end_date){

    auto start_tp = ParseDateStrings(start_date);
    auto end_tp = ParseDateStrings(end_date);
    
    if(start_tp > end_tp){
            return vector<Record>({});
    }

    vector<Record> records =  _customer_records.RangeSearch(start_tp,end_tp);
    
    return records;


}
float Customer::GetCumInjectionByMonth(string year_month) {    
    if(cumulative_inj.empty()) return 0.0f;
    //Here we get the injection record of the customer in format YYYY-MM
    for(auto& record : cumulative_inj){
        if (year_month == record.first){
            return record.second;
        }
    }
    return 0.0f;
}

float Customer::GetPaidAmountByYear(string year){
    auto year_start = year + "-01-01";
    auto year_end = year+ "-12-31";
    auto year_records = GetRecordsByPeriod(year_start,year_end);
    float result = 0;
    for(auto& rec : year_records){
        result += rec.GetNetCost();
    }
    return -result;
}