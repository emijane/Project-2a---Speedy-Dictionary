//*****************************INCLUDES**********************************************************************
#include "b_tree.h"
#include <string>
#include <vector>
#include <chrono>
using namespace std;
//***************************END_OF_INCLUDES******************************************************************
//***************************INSERT_FUNCTION******************************************************************
//Inputs: string term, term to insert, vector defs, list of definitions for the term, in the case of multiple,
//Returns bool, whether successful insertion
//Description: checks root node, if not full inserts there, if full calls recurse
bool b_tree::insert(string term, vector<string> &defs) {
    // tree empty, puts first value in root, returns true after making node and incrementing n
    if (root == nullptr) {
        root = new b_node({},{},0, vector<b_node*>(20,nullptr),nullptr);
        root-> words.push_back(term);
        root-> definitions.push_back(defs);
        root-> n = 1;
        return true;
    }
    else {
        for (int i = 0; i < root->n; i++) {
            if (root-> words[i] == term) {
                return false;
            }
            // check for when next value greater, list is in ascending order, so corresponding child
            //pointer will be the one to recurse down
            if (root-> words[i] > term) {
                if (root-> children[i] != nullptr) {
                    return insert_recurse(term, defs, root-> children[i]);
                }
                // means root has no children, if not 19 vals, insert at root
                if (root-> n <= 19) {
                    root-> words.insert(root->words.begin() + i, term);
                    root-> definitions.insert(root->definitions.begin() + i, defs);
                    root-> n++;
                    return true;
                }
                // add value to node and call split
                root-> words.insert(root->words.begin() + i, term);
                root-> definitions.insert(root->definitions.begin() + i, defs);
                root-> n++;
                split(root);
                return true;
            }
        }

        // means greater than all in the list, recurse with rightmost pointer (n value)
        if (root-> children[root-> n ] != nullptr) {
            return insert_recurse(term, defs, root-> children[root-> n]);
        }

        // means root has no children, if not 19 vals, insert at root
        if (root-> n <= 19) {
            root-> words.insert(root->words.begin() + root->n , term);
            // inserts before n, so at last index
            root-> definitions.insert(root->definitions.begin() + root-> n, defs);
            root-> n++;
            return true;
        }
        root-> words.insert(root->words.begin() + root->n , term);
        // inserts before n, so at last index
        root-> definitions.insert(root->definitions.begin() + root-> n, defs);
        root-> n++;
        split(root);
        return true;


    }
}
//*****************END_OF_INSERT*****************************************************************************
//*****************INSERT_RECURSE****************************************************************************
//INPUTS: takes in term to insert, vector of definitions corresponding to the term, and node currently at, b_node*
//Returns boolean, whether successful.
//Description, recurses through tree to find correct spot to insert
bool b_tree::insert_recurse(string term, vector<string> &defs, b_node *root_node) {
    for (int i = 0; i < root_node->n; i++) {
        if (root_node-> words[i] == term) {
            return false;
        }
        if (root_node-> words[i] > term) {
            if (root_node-> children[i] != nullptr) { // first term greater, spot to insert
                return insert_recurse(term, defs, root_node-> children[i]);
            }
            if (root_node -> n <= 19) {
                root_node-> words.insert(root_node->words.begin() + i, term);
                root_node-> definitions.insert(root_node->definitions.begin() + i, defs);
                root_node-> n++;
                return true;
            }
            // node has max values, needs to split. Insert word and definition, call split
            root_node-> words.insert(root_node->words.begin() + i, term);
            root_node-> definitions.insert(root_node->definitions.begin() + i, defs);
            root_node-> n++;
            split(root_node);
            return true;
        }
    }
    // got through for loop, if greater pointer, recurse to it, otherwise add if space
    if (root_node -> children[root_node->n] == nullptr) {
        if (root_node -> n <= 19) {
            root_node-> words.push_back(term);
            root_node-> definitions.push_back(defs);
            root_node-> n++;
            return true;
        }
        // add and split, similar to others.
            root_node-> words.push_back(term);
            root_node-> definitions.push_back(defs);
            root_node-> n++;
            split(root_node);
            return true;
    }
    return insert_recurse(term, defs, root_node->children[root_node->n]);


}
//*****************SEARCH**********************************************************************
//Inputs: term to search
//Returns definition vector corresponding to the term
// only calls search recurse so there is an easy way to call function with just term
vector<string> b_tree::search(string term) {
    // all checking occurs in recursive
    levels = 0;
    return search_recurse(term, root);
}
//***************END_OF_SEARCH******************************************************************
//***************SEARCH_RECURSE*****************************************************************
//INPUTS: takes in term, b_node* recursing through tree to find correct spot
//Returns vector of defs corresponding to term, most of the body of the search functionality contained here
vector<string> b_tree::search_recurse(string term, b_node *root_node) {
    // if root is null and val hasn't been found, return empty vector
    if (root_node == nullptr) {
        return {};
    }
    // not null, search through values, find right place
        for (int i = 0; i < root_node->n; i++) {
            if (root_node-> words[i] == term) { // equal condition, return corresponding def
                return root_node-> definitions[i];
            }
            if (root_node-> words[i] > term) { // greater, means first term that's greater, right spot
                if (root_node-> children[i] != nullptr) {
                    // recurse through corresponding child
                    return search_recurse(term,root_node->children[i]);
                }
                return {};
            }
        }
    // got through whole list, should be last pointer
        if (root_node->children[root_node->n] == nullptr) { // no last pointer, val not in list
            return {};
        }
        // recurse through greater than pointer
    levels++;
    return search_recurse(term,root_node->children[root_node->n]);
}
//********************SPLIT_FUNCTION***********************************************************************
//Inputs: b_node*, node to start splitting at
//Returns nothing
// Description: only way to create new nodes, split takes a node with too many values,
// finds the median value, and moves it up.
void b_tree::split(b_node *root_node) {
    // base case,
    if (root_node == nullptr) {
        return;
    }
    // other base case, node no longer needs to split
    if (root_node -> n <= 19) {
        return;
    }
    // check if node to split is root, special case
    if (root_node == root) {
            // left of med values, split always occurs with 20 values
            int med = root_node-> n / 2;
            //make temporary copies of median term and definition to be passed to new node
            string med_term = root_node-> words[med];
            root->words.erase(root->words.begin() + med);
            vector <string> med_def = root-> definitions[med];
            root->definitions.erase(root->definitions.begin() + med);
            root -> n--;
            // create new node which will be new root node
            b_node *tmp = new b_node();
            // create tmp node while values assigned
            tmp->words.push_back(med_term);
            tmp->definitions.push_back(med_def);
            tmp->n = 1;
            // make new right node, left node will be old root
            b_node *right = new b_node();
            right -> n = 0;
            // push all values right of median from root to right node and pop from left node
            // root n modified in loop, need to save before to use as condition
            int end = root-> n;
            for (int i = med; i < end; i++) {
                right->words.push_back(root-> words[i]);
                right->definitions.push_back(root-> definitions[i]);
                // transfer children, set former equal to nullptr
                right -> children[right->n] = root-> children[i+1];
                root-> children[i+1] = nullptr;
                right-> n++;
                // removing back n/2 times will get the second half of the list gone
                root -> words.pop_back();
                root -> definitions.pop_back();
                root -> n--;
            }
        // last child, rightmost
        right -> children[right-> n] = root-> children[end];
        root -> children[end] = nullptr;
        // set both parents to new root
        root-> parent = tmp;
        right -> parent = tmp;
        // push children, former root, new node
        tmp -> children[0] =root;
        tmp -> children[1] =right;
        root = tmp;
    }
    else {
        // similar to root, but don't need to make a new root node, and instead recurse up tree after med added
        // make median var, along with temp vals for med term and def, delete from original node
        int med = root_node-> n / 2;
        string med_term = root_node-> words[med];
        root_node->words.erase(root_node->words.begin() + med);
        vector <string> med_def = root_node-> definitions[med];
        root_node->definitions.erase(root_node->definitions.begin() + med);
        root_node-> n--;
        // new temp right node, same logic as root, push values in order
        b_node *right = new b_node();
        right -> n = 0;
        int end = root_node-> n;
        for (int i = med; i < end; i++) {
            right -> words.push_back(root_node-> words[i]);
            right -> definitions.push_back(root_node-> definitions[i]);
            right -> children[right-> n] = root_node-> children[i+1];
            root_node -> children[i+1] = nullptr;
            right -> n++;
            root_node -> words.pop_back();
            root_node -> definitions.pop_back();
            root_node -> n--;
        }
        //rightmost
        right -> children[right-> n] = root_node-> children[end];
        root_node -> children[end] = nullptr;
        // set root parent as right parent
        right-> parent = root_node-> parent;
        // find where new values belong in parent, add right child at spot past
        // need flag because not returning if inserted
        bool added = false;
        for (int i = 0; i < root_node -> parent -> n; i++) {
            if (root_node -> parent -> words[i] > med_term) {
                added = true;
                root_node-> parent -> words.insert(root_node-> parent -> words.begin() + i, med_term);
                root_node-> parent -> definitions.insert(root_node-> parent -> definitions.begin() + i, med_def);
                root_node-> parent -> n++;
                if (root_node -> parent -> children[i+1] == nullptr) {
                    root_node -> parent -> children[i+1] = right;
                }
                else {
                    int j = i+1; // start at current node, move to next non null child
                    while (root_node -> parent -> children[j] != nullptr) {
                        j++;
                    }
                    // j now at first index where child is null
                    while (j > i+1) {
                        // shifts values one to right, first val overwritten, already established as nullptr
                        root_node -> parent -> children[j] = root_node -> parent -> children[j-1];
                        j--;
                    }
                    // values shifted, set right to correct spot
                    root_node -> parent -> children[i+1] = right;
                }
                // exit loop, correct spot found
                break;
            }
        }
        if (!added) {
            // not found greater, add term at end
            root_node -> parent -> words.push_back(med_term);
            root_node-> parent -> definitions.push_back(med_def);
            root_node -> parent -> children[root_node -> parent -> n] = right;
            root_node-> parent -> n++;
        }

        // recurse up tree
        split(root_node -> parent);
    }
};

b_tree::~b_tree() {
    destroy(root);
}
void b_tree::destroy(b_node *root_node) {
    //  base case
    if (root_node == nullptr) {
        return;
    }
    for (int i = 0; i < root_node -> children.size(); i++) {
        // recursive call on each child of node
        destroy(root_node -> children[i]);
    }
    // after recurse through all children, delete root node
    delete root_node;
}