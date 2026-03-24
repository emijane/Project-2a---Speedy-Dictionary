//
// Created by rceci on 3/19/2026.
//

#ifndef PROJECT_2_B_TREE_H
#define PROJECT_2_B_TREE_H
//*****************************INCLUDES**********************************************************************
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
//***************************END_OF_INCLUDES******************************************************************
//***************************B_NODE_STRUCT********************************************************************
struct b_node {
    // stores words for dictionary
    vector<string> words;

    //stores definitions, 2d since words can have multiple definitions
    vector<vector<string>> definitions;

    // number of terms stored at node max will be 19
    int n;
    // stores pointers to node's children, max will be 20
    vector<b_node*> children;
    // parent pointer, useful for splitting
    b_node *parent;
    // constructor, takes in vector of words, vector of defs, initializes children to nullptrs if
    // no vector provided, all others to empty vectors, n to 0 representing size of 0
    b_node(const vector<string> & words = {}, const vector<vector<string>>& definitions = {}, const int &n = 0,
        const vector<b_node*> &children = vector<b_node*>(20, nullptr), b_node * parent = nullptr): words(words), definitions(definitions),
        n(n), children(children), parent(parent) {}
};
//*************************END_OF_B_NODE_STRUCT***************************************************************
//*************************B_TREE_CLASS***********************************************************************
class b_tree {
    // root stored privately, public should not have access
    b_node *root;

    // helper function to split when node size too big, only called within insert
    void split(b_node *root_node);


    // insert helper so external doesn't have to include node
    bool insert_recurse(string term, vector<string> &defs, b_node *root_node);

    // search helper, so external doesn't  have to use node
    vector<string> search_recurse(string term, b_node *root_node);
    // destroy, used in destructor
    void destroy(b_node *root_node);
    // levels count for recursion
    public:
    int levels;
    //constructor and destructor
    b_tree() : root(nullptr), levels(0) {}
    ~b_tree();

    // insertion, takes in word, vector of definitions, adds word, defs to tree, returns whether successful
    bool insert(string term, vector<string> &defs);

    // search function, takes in string, returning vector corresponding to definitions
    // returns empty vector if word not in dictionary.
    vector<string> search(string term);
};
//***********************END_OF_B_TREE_CLASS******************************************************************
#endif //PROJECT_2_B_TREE_H