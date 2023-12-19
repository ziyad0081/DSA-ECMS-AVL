#ifndef REGION_Hclear
#define REGION_H

#include "Department.h"
#include<iostream>
#include<vector>
using namespace std;

struct Region{
    string name;
    //DepartmentsTree region_departments; DepartmentTree not ready yet
    Region* left;
    Region* right;
    vector<MarketingDepartment*> region_departments;
    MarketingDepartment* GetDeptByCityName(string _name);
    MarketingDepartment* InsertDepartment(MarketingDepartment*);
    Region(string _name);
    ~Region();
    int height;
};

class RegionTree{
    Region* root;
    void Print(Region* root);
    void RotateWithLeftChild( Region * & k2 );
    void RotateWithRightChild( Region * & k1 );
    void DoubleWithLeftChild( Region * & k3 );
    void DoubleWithRightChild( Region * & k1 );
    int  height( Region *t ) const;
    void Balance( Region * & t );
public:
    RegionTree();
    void DestroyRegions(Region *root);
    ~RegionTree();
    Region* InsertRegion(string region_name);
    Region* SearchRegion(string region_name);
    void DeleteRegion(string region_name);
    void PrintRegions(Region* root);
    Customer* GetBestRegionCumInjUtil(Region* root, string year_month);
    Customer* GetBestRegionCumInj(string year_month);
};
#endif