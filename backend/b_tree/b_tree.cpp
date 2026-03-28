//*****************************INCLUDES**********************************************************************
#include "b_tree.h"
//***************************END_OF_INCLUDES******************************************************************
//***************************INSERT_FUNCTION******************************************************************
//Inputs: string term, term to insert, vector defs, list of definitions for the term, in the case of multiple,
//Returns bool, whether successful insertion
//Description: wrapper for input, made so main can call insert without having to reference a node. Also handles root split.
bool b_tree::insert(const std::string &term,const std::vector<std::string> &defs) {
    bool res =  insert_recurse(term,defs, root);
    if (root != nullptr) {
        // avoid referencing nullptr, check if root needs to split, if so use split function after making new root
        if (root -> words.size() >= 2*t -1) {
            // make new tmp to be parent of root
            b_node *tmp = new b_node();
            // only parent, previous was root
            tmp -> children.push_back(root);
            // set new root
            root = tmp;
            // let split handle value splitting, now former root is child of new root, format split expects
            split(root, 0);
        }

    }
    // returns result of insert recurse after root check, insert recurse checks if all other nodes need to split
    return res;
}
//**************************END_OF_INSERT_FUNCTION*************************************************************
//**************************INSERT_RECURSE*********************************************************************
//Inputs: string term to insert, vector defs to insert, node to start at
//Returns: bool, whether term inserted successfully
//Description: main functionality of insertion, starts at tree, recurses until
bool b_tree::insert_recurse(const std::string &term, const std::vector<std::string> &defs, b_node *root_node) {
    // base case, root_node doesn't exist, first entry
    if (root_node == nullptr) {
        std::vector<std::string> term_tmp = {};
        term_tmp.push_back(term);
        std::vector<std::vector<std::string>> def_tmp = {};
        def_tmp.push_back(defs);
        b_node *tmp = new b_node(term_tmp,  def_tmp);
        root = tmp;
        return true;
    }
    // node not leaf, recurse to correct child
    else if (root_node -> children.empty() == false) {
        std:: string curr_term;
        // compare to find first node where term is greater than the term to insert
      for (int i = 0; i < root_node -> words.size(); i++) {
          curr_term = root_node -> words[i];
          // term already in tree
          if (term == curr_term) {
              return false;
          }
          // first term greater, spot to recurse to child
          if (term < curr_term) {
              bool res = insert_recurse(term, defs, root_node -> children[i]);
              // check if node path inserted needs to split on the way up and need parent node of node to split
              if (root_node -> children [i]-> words.size() > (2 * t - 1)) {
                  split(root_node , i);
              }
              return res;
          }
      }
        // greater than all in list, go to rightmost child
        bool res = insert_recurse(term, defs, root_node -> children[root_node -> children.size()-1]);
        // last child word size
        if (root_node -> children[root_node -> children.size() -1] -> words.size()  > (2 * t - 1)) {
            split(root_node, root_node -> children.size() - 1);
        }
        return res;
    }
    // node is leaf, find right spot to insert and check sizing
    else {
        // find spot to insert using similar logic
        std::string curr_term;
        for (int i = 0; i < root_node -> words.size(); i++) {
            curr_term = root_node -> words[i];
            // in tree
            if (term == curr_term) {
                return false;
            }
            // first greater term .insert inserts before current index, correct spot for new term/def
            if (term < curr_term) {
                root_node ->words.insert(root_node->words.begin() + i, term);
                root_node -> definitions.insert(root_node-> definitions.begin() + i, defs);
                // check if node now overfull
                return true;
            }
        }
        root_node -> words.push_back(term);
        root_node -> definitions.push_back(defs);
        return true;
    }
}
//************************SPLIT_FUNCTION********************************************************************
// Inputs: takes in parent pointer and index of child to insert at
// Returns: N/A
// Description: when node overfull, split called in insert recurse splits node into new node
void b_tree::split(b_node *parent, const int index) {
    // median, t-1 is median, since num terms is 2t
    int mid = t-1;
    // make pointer to child node, avoids messy arrows
    b_node* child = parent -> children[index];
    // extract mid_term, mid def from appropriate child
    std::string mid_term = child  ->words[mid];
    std::vector<std::string> mid_defs = child ->definitions[mid];
    // make new right node
    b_node *right = new b_node();
    // assign right half of words from child to new right node, starts one past med, goes to end
    right -> words.assign(child -> words.begin() + mid + 1,child -> words.end());
    right -> definitions.assign(child -> definitions.begin() + mid + 1,child -> definitions.end());
    // we know node has terms, but if it doesn't have children (leaf node) .empty will crash
    if (!child -> children.empty()) {
        right -> children.assign(child -> children.begin() + mid + 1,child -> children.end());
    }
    // erase items from existing child median included
    child -> words.erase(child -> words.begin() + mid ,child -> words.end());
    child -> definitions.erase(child -> definitions.begin() + mid ,child -> definitions.end());
    // .empty also crashes if node has no children
    if (!child -> children.empty()) {
        child -> children.erase(child -> children.begin() + mid +1,child -> children.end());
    }
    // insert median to parent and right as child past left
    parent -> words.insert(parent-> words.begin() + index ,mid_term);
    parent -> definitions.insert(parent-> definitions.begin() + index ,mid_defs);
    // add 1 so child is right of median term, fits b_ tree structure
    parent -> children.insert(parent -> children.begin() + index + 1 ,right);
}
//**********************END_OF_SPLIT**************************************************************
//**********************SEARCH_FUNCTION***********************************************************
//Inputs: term, passed by reference to search
// Returns: result of search recurse, definition of term, if found. Empty vector if not
// Description: wrapper function so main doesn't have to pass in root as well as term
std::vector<std::string> b_tree::search(const std::string & term) {
    return search_recurse(term, root);
}
//********************END_OF_SEARCH**************************************************************
//********************SEARCH_RECURSE*************************************************************
//Inputs: term to find, node currently at
//Returns: vector of definitions, if found, empty vector if not
//Description: recurses through tree, down correct path of nodes, returns corresponding vector of defs if term in tree
std::vector<std::string> b_tree::search_recurse(const std::string & term, b_node *root_node) {
    // cannot exist and avoids any dereferencing
    if (root_node == nullptr) {
        return {};
    }
    for (int i = 0; i < root_node -> words.size(); i++) {
        // check for tree empty
        if (term == root_node -> words[i]) {
            return root_node -> definitions[i];
        }
        if (term < root_node -> words[i]) {
            // avoid undefined behavior if child doesn't exist
            if (!root_node -> children.empty()) {
                return search_recurse(term, root_node -> children[i]);
            }
        }
    }
    if (root_node -> children.empty()) {
        // leaf node and key not found, not in tree
        return {};
    }
    return search_recurse(term, root_node -> children[root_node->children.size() -1]);
}
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