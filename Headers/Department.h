#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "District.h"
using namespace std;

struct DeptRecord{
    string year;
    int amount;
    DeptRecord(string _year, int _amount){
        year = _year;
        amount = _amount;
    }
};
class MarketingDepartment {

public:
    string city;
    vector<DeptRecord*> yearly_payment;
    DeptRecord* GetYearlyRecord(string date_year){
        auto target_record = find_if(yearly_payment.begin(),yearly_payment.end(),[date_year](const DeptRecord* rec){
            return date_year == rec->year;
        });

        if(target_record != yearly_payment.end()){
            return *target_record;
        }
        else{
            yearly_payment.push_back(new DeptRecord(date_year,0));
            return *(yearly_payment.end()-1);
        }
    }
    vector<DeptRecord*> yearly_budget;
    DistrictTree* department_districts;
    MarketingDepartment(string _city) : city(_city){
        department_districts = new DistrictTree();
    }
};

#endif