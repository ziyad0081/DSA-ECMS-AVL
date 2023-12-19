#ifndef DISTRICT_H
#define DISTRICT_H

#include "CustomerTree.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;



struct District{
    public:
      friend class DistrictTree;
        District(const string& _name ="");
        string GetDistName();
        ~District();
        Customer* InsertCustomer(Customer*);
        vector<Customer*> GetCustomers() const {
            return district_customers;
        }
    private:
        string dist_name;
        District* left_dist;
        District* right_dist;
        vector<Customer*> district_customers;
        int height;
 };

 class DistrictTree{
    
    public:
        DistrictTree();
        DistrictTree(const string&);
        DistrictTree(District*);
        ~DistrictTree();
        District* InsertDist(const string&);
        void DeleteDist(const string&);
        District* SearchForDist(const string&);

        vector<District*> GetAllDistricts(){
            vector<District*> result;
            GetAllDistrictsHelper(root_dist,result);
            return result;
        }
        void PrintDistTree();
        District* root_dist;

        
        

 private:
    District* InsertDistAct(District*& new_dist, District*& root);
    void GetAllDistrictsHelper(District* root, vector<District*>& result){
        if(root){
            GetAllDistrictsHelper(root->left_dist,result);
            result.push_back(root);
            GetAllDistrictsHelper(root->right_dist,result);
        }
    }
    District* MinDist(District*);
    void DeleteDistAct(const string &, District * &);
    void PrintDistTreeAct(District*, int &);
    void RotateWithLeftChild( District * & k2 );
    void RotateWithRightChild( District * & k1 );
    void DoubleWithLeftChild( District * & k3 );
    void DoubleWithRightChild( District * & k1 );
    int  height( District *t ) const;
    void Balance( District * & t );
} ;
#endif