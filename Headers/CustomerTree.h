#ifndef CUSTOMER_H
#define CUSTOMER_H



#include<iostream>
#include<vector>
#include "RecordList.h"
#include "AvlTree.h"
using namespace std;




class Customer
        {
            public:
                
                Customer(int id ,string , string addr,const vector<unsigned int>&);
                ~Customer();
                bool operator<(const Customer& operand){
                    return this->GetCustomerID() < operand.GetCustomerID();
                }
                string GetCustomerName();
                string GetCustomerAddress() const {
                    return customer_address;
                }
                int GetFamilyMembersCount() const {
                    return family_members_count;
                }
                Record* GetHeadRecord() const{
                    return customer_records.head_record;
                }
                int GetCustomerID() const { return account_id; }
                Record* addRecord(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours); //Adding a record into the customer's account;
                Record* addRecord_(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours); //Adding a record into the customer's account;
                vector<Record> GetRecordsByPeriod(string start_date, string end_date) ; //Start and end dates will be passed as strings and parsed in the records tree.
                float GetCumInjectionByMonth(string year_month) ; // This will return customer total injection by month specified in format YYYY/MM
                float GetPaidAmountByYear(string year);

            private:
                int unsigned account_id;
                string customer_name;
                string customer_address;
                unsigned int family_members_count;
                vector<unsigned int>family_ages;
                vector<pair<string,float>> cumulative_inj;
                RecordList customer_records;
                AvlTree<Record> _customer_records;
};
#endif
