#include "../Headers/District.h"
//FIXME: include path



District :: District(const string& name) : dist_name(name), right_dist(nullptr), left_dist(nullptr), height(0) {}


District :: ~District(){}


string District :: GetDistName() {return dist_name;}


DistrictTree :: DistrictTree() : root_dist(nullptr){}//default constructor;


//constructor for tree with already made root District:
DistrictTree :: DistrictTree(District* root) : root_dist(root){}


//directly create tree with root_dist name;
DistrictTree :: DistrictTree(const string & name) : root_dist(new District(name)){};


DistrictTree:: ~DistrictTree(){}



//the function to call when needing to insert, the work is done by the other function
District* DistrictTree :: InsertDist(const string& name)
{   //if root is null then done
    if(!root_dist) {root_dist=new District(name); return root_dist;}
    //else
    District* new_dist=new District(name);//creating a new dist obj to place in other insert funct;
    InsertDistAct(new_dist, root_dist);//insertion process
    return new_dist;
}

Customer* District::InsertCustomer(Customer* new_customer){
    district_customers.push_back(new_customer);
    return *(district_customers.end()-1);
}

District* DistrictTree :: InsertDistAct(District*& new_dist, District*& root)//Insertion process
{
       if(!root){
            return new_dist; // this would be the right value for the current root's parent;
    }
    //traverse until correct position
    if(root->dist_name > new_dist->dist_name)
    {
      root->left_dist=InsertDistAct(new_dist, root->left_dist);
    }

     if(root->dist_name < new_dist->dist_name)
    {
      root->right_dist=InsertDistAct(new_dist, root->right_dist);
    }

    return root;//if it already exists; just to not get a non void with no return type;
}



 District* DistrictTree :: SearchForDist(const string& name)
 {
     District* search_dist=root_dist;
     //traverse tree;
     while( search_dist !=nullptr   && search_dist->dist_name != name)
     {
        if(search_dist->dist_name > name) search_dist=search_dist-> left_dist;
        else search_dist=search_dist-> right_dist;
     }
     return search_dist ;

 }



//just to make it easier to use with one parameter string;
 void DistrictTree :: DeleteDist(const string& name)
 {
     DeleteDistAct(name, root_dist); //deletion process;
 }



  void DistrictTree :: DeleteDistAct(const string &name, District * & traverse_dist) {

    if (traverse_dist == nullptr)
        return;
//traverse tree;
    if (name < traverse_dist->GetDistName())
        DeleteDistAct(name, traverse_dist->left_dist);
    else if (traverse_dist->GetDistName() < name)
        DeleteDistAct(name, traverse_dist->right_dist);

        //found it;
        //case 1 : both children not null
    else if (traverse_dist->left_dist != nullptr &&  traverse_dist->right_dist != nullptr)
    {
        traverse_dist->dist_name = MinDist(traverse_dist->right_dist)->GetDistName();//MinDist returns pointer to most left leaf;
        DeleteDistAct(traverse_dist->GetDistName(), traverse_dist->right_dist);
    }

    //case 2, only one is null;
     else {
        District *old_dist = traverse_dist;//keep traverse_dist which is now the node to be deleted;
        traverse_dist = (traverse_dist->left_dist != nullptr) ? traverse_dist->left_dist : traverse_dist->right_dist;
        delete old_dist;
    }
}



District* DistrictTree ::  MinDist(District* node) {
    //returns most left node ptr;
    while (node->left_dist != nullptr) {
        node = node->left_dist;
    }
    return node;
}


void DistrictTree :: PrintDistTree()
{
  int n=0;//to keep track of n in recursive function;
  PrintDistTreeAct(root_dist, n);//printing process;
}


 void DistrictTree :: PrintDistTreeAct(District* root, int& n) {

    if (root == nullptr) return;
    PrintDistTreeAct(root->left_dist,n);//keep going until most left node;
    cout << root->dist_name << " "; ++n;//first occurence of this: name of most left leaf
    if( n % 10==0) cout<<endl;    //this would print 10 Districts per line from smallest upwards;
    PrintDistTreeAct(root->right_dist,n);//first occurence of this: goes to right subtree of the most left leaf's parent and continues;

    //keep going up until root then move to right subtree of root;
}


    int DistrictTree::height( District *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }



    void DistrictTree::RotateWithLeftChild( District * & k2 )
    {
        District *k1 = k2->left_dist;
        k2->left_dist = k1->right_dist;
        k1->right_dist = k2;
        k2->height = max( height( k2->left_dist ), height( k2->right_dist ) ) + 1;
        k1->height = max( height( k1->left_dist ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
	// right right imbalance
    void DistrictTree::RotateWithRightChild( District * & k1 )
    {
        District *k2 = k1->right_dist;
        k1->right_dist = k2->left_dist;
        k2->left_dist = k1;
        k1->height = max( height( k1->left_dist ), height( k1->right_dist ) ) + 1;
        k2->height = max( height( k2->right_dist ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
	// Left right imbalance
    void DistrictTree::DoubleWithLeftChild( District * & k3 )
    {
        RotateWithRightChild( k3->left_dist );
        RotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
	// right left imbalance
    void DistrictTree::DoubleWithRightChild( District * & k1 )
    {
        DoubleWithRightChild( k1->right_dist );
        DoubleWithRightChild( k1 );
    }

    // Assume t is balanced or within one of being balanced
    void DistrictTree::Balance( District * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left_dist ) - height( t->right_dist ) > 1 )
			// Left left imbalance
            if( height( t->left_dist->left_dist ) >= height( t->left_dist->right_dist ) )
                RotateWithLeftChild( t );
			// Left right imbalance
            else
                DoubleWithLeftChild( t );
        else
        if( height( t->right_dist ) - height( t->left_dist ) > 1 )
			// Right right imbalance
            if( height( t->right_dist->right_dist ) >= height( t->right_dist->left_dist ) )
                RotateWithRightChild( t );
			// Right left imbalance
            else
                DoubleWithRightChild( t );
        
		// Update the height
        t->height = max( height( t->left_dist ), height( t->right_dist ) ) + 1;
    }