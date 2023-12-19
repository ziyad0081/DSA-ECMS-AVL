#include<iostream>
#include<stack>
#include "../Headers/Region.h"
//FIXME: include path

/*--------------------Region----------------------------------------*/
Region::Region(string n) {
    name = n;
    left = right = nullptr;
    height=0;
}
    

Region::~Region(){
    delete left;
    delete right;
}

MarketingDepartment* Region::GetDeptByCityName(string _name){
    if(!region_departments.size()){
        return nullptr;
    }
    for(int i = 0; i < region_departments.size(); i++){
        if(region_departments[i]->city == _name){
            return region_departments[i];
        }
    }
    return nullptr;
}
MarketingDepartment* Region::InsertDepartment(MarketingDepartment* dept){
    region_departments.push_back(dept);
    return dept;
}
/*--------------------RegionTree----------------------------------------*/

RegionTree::RegionTree(): root(nullptr) {}

void RegionTree::DestroyRegions(Region *root){
    if (root){
        DestroyRegions(root->left);
        DestroyRegions(root->right);
        delete root;
    }
}

RegionTree::~RegionTree(){
    DestroyRegions(root);
}

Region* RegionTree::InsertRegion(string region_name){
    Region* new_region= new Region(region_name);
    //Check if tree is empty
    if(!root) root=new_region;
    else{
        //Set current to traverse the tree and parent to keep updated with current's parent
        Region* current=root, *parent=root;
        while(current){
            parent=current; //Parent gets updated before each movement of the current
            if(region_name<current->name){
                current=current->left;
                if(!current){
                    parent->left=new_region;
                }
            }
            else if(region_name>current->name){
                current=current->right;
                if(!current){
                    parent->right=new_region;
                }
            }
            else break;
        }
    }
    return new_region;
}

Region* RegionTree::SearchRegion(string region_name){
    Region* current=root;
    if(!current) return nullptr;
    //Will traverse the tree while current is non null
    //And compare the tageted name to the name of the current Region
    while(current){
        if(current->name==region_name) return current;
        if(region_name<current->name) current=current->left;
        else current=current->right;
    }
    return nullptr;
}

void RegionTree::DeleteRegion(string region_name){
    Region* target= SearchRegion(region_name);
    if(!target) return;
    //No children; Delete directly
    if(!target->left && !target->right){
        delete target;
        target=nullptr;
    }
    //No left child; Keep right child
    else if(!target->left){
        Region* temp=target->right;
        delete target;
        target=temp;
    }
    //No right child; Keep left child
    else if(!target->right){
        Region* temp=target->left;
        delete target;
        target=temp;
    }
    //Both children there; 
    else{
        Region* temp=target->right;
        while(temp->left) temp=temp->left;
        target->name=temp->name;
        DeleteRegion(temp->name);
    }
}

void RegionTree::Print(Region* root) {
    if (root == nullptr) return;
    Print(root->left);
    cout << root->name << " ";
    Print(root->right);
}

void RegionTree::PrintRegions(Region* root){
    Print(root);
}
/*
Customer* RegionTree::GetBestRegionCumInjUtil(Region* root, string year_month){
    if (root == nullptr) return nullptr;

    stack<Customer*> best_region_customers;
    GetBestRegionCumInjUtil(root->left);
    if(root->region_departments.GetBestDepartmentCumInj(year_month).GetCumInjectionByMonth(year_month)>best_region_customers.top()->GetCumInjectionByMonth(year_month))
        best_region_customers.push(root->region_departments.GetBestDepartmentCumInj(year_month).GetCumInjectionByMonth(year_month));
    GetBestRegionCumInjUtil(root->right);
    return best_region_customers.top();
}

Customer* RegionTree::GetBestRegionCumInj(string year_month){
    return GetBestRegionCumInjUtil(root, year_month);
}
*/

    int RegionTree::height( Region *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }



    void RegionTree::RotateWithLeftChild( Region * & k2 )
    {
        Region *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
	// right right imbalance
    void RegionTree::RotateWithRightChild( Region * & k1 )
    {
        Region *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
	// Left right imbalance
    void RegionTree::DoubleWithLeftChild( Region * & k3 )
    {
        RotateWithRightChild( k3->left );
        RotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
	// right left imbalance
    void RegionTree::DoubleWithRightChild( Region * & k1 )
    {
        DoubleWithRightChild( k1->right );
        DoubleWithRightChild( k1 );
    }

    // Assume t is balanced or within one of being balanced
    void RegionTree::Balance( Region * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > 1 )
			// Left left imbalance
            if( height( t->left->left ) >= height( t->left->right ) )
                RotateWithLeftChild( t );
			// Left right imbalance
            else
                DoubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > 1 )
			// Right right imbalance
            if( height( t->right->right ) >= height( t->right->left ) )
                RotateWithRightChild( t );
			// Right left imbalance
            else
                DoubleWithRightChild( t );
        
		// Update the height
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }