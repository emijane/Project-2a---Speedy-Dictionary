//
// Created by rceci on 3/19/2026.
//

#ifndef PROJECT_2_B_TREE_H
#define PROJECT_2_B_TREE_H
//*****************************INCLUDES**********************************************************************
#include <iostream>
#include <string>
#include <vector>
//***************************END_OF_INCLUDES******************************************************************
//***************************B_NODE_STRUCT********************************************************************
struct b_node {
    // stores words for dictionary
    std::vector<std::string> words;
    //stores definitions, 2d since words can have multiple definitions
    std::vector<std::vector<std::string>> definitions;

    // stores pointers to node's children
    std::vector<b_node*> children;
    // constructor, takes in vector of words, vector of defs, initializes children to nullptrs if
    // no vector provided, all others to empty vectors, n to 0 representing size of 0
    b_node(const std::vector<std::string> & words = {}, const std::vector<std::vector<std::string>>& definitions = {},
        const std::vector<b_node*> &children ={}): words(words), definitions(definitions),
        children(children) {}
};
//*************************END_OF_B_NODE_STRUCT***************************************************************
//*************************B_TREE_CLASS***********************************************************************
class b_tree {
    // root stored privately, public should not have access
    b_node *root;
    //  b tree order t
    const int t;
    // helper function to split when node size too big, only called within insert
    void split( b_node *parent, int index);


    // insert helper so external doesn't have to include node
    bool insert_recurse(const std::string &term, const std::vector<std::string> &defs, b_node *root_node);

    // search helper, so external doesn't  have to use node
    std::vector<std::string> search_recurse(const std::string &term, b_node *root_node);
    // destroy, used in destructor
    void destroy(b_node *root_node);
    public:
    //constructor and destructor
    b_tree() : root(nullptr), t(50) {}
    ~b_tree();

    // insertion, takes in word, vector of definitions, adds word, defs to tree, returns whether successful
    bool insert(const std::string &term, const std::vector<std::string> &defs);

    // search function, takes in string, returning vector corresponding to definitions
    // returns empty vector if word not in dictionary.
    std::vector<std::string> search(const std::string &term);

};
//***********************END_OF_B_TREE_CLASS******************************************************************
#endif //PROJECT_2_B_TREE_H