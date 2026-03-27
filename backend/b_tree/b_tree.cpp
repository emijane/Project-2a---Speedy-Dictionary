//*****************************INCLUDES**********************************************************************
#include "b_tree.h"
//***************************END_OF_INCLUDES******************************************************************
//***************************INSERT_FUNCTION******************************************************************
//Inputs: string term, term to insert, vector defs, list of definitions for the term, in the case of multiple,
//Returns bool, whether successful insertion
//Description: checks root node, if not full inserts there, if full calls recurse
bool b_tree::insert(const std::string &term, std::vector<std::string> &defs) {
    // tree empty, puts first value in root, returns true after making node and incrementing n
    if (root == nullptr) {
        root = new b_node({},{},0, std::vector<b_node*>(6,nullptr),nullptr);
        root-> words.push_back(term);
        root-> definitions.push_back(defs);
        root-> n = 1;
        return true;
    }
    else {
        for (int i = 0; i < root->n; i++) {
            if (root->words[i] == term) {
                for (const auto& def : defs) {
                    root->definitions[i].push_back(def);
                }
                return true;
            }
            // check for when next value greater, list is in ascending order, so corresponding child
            //pointer will be the one to recurse down
            if (root-> words[i] > term) {
                if (root-> children[i] != nullptr) {
                    return insert_recurse(term, defs, root-> children[i]);
                }
                // means root has no children, if not 5 vals, insert at root
                if (root-> n <= 5) {
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

        // means root has no children, if not 5 vals, insert at root
        if (root-> n <= 5) {
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
bool b_tree::insert_recurse(const std::string &term, std::vector<std::string> &defs, b_node *root_node) {
    for (int i = 0; i < root_node->n; i++) {
        if (root_node->words[i] == term) {
            for (const auto& def : defs) {
                root_node->definitions[i].push_back(def);
            }
            return true;
        }
        if (root_node-> words[i] > term) {
            if (root_node-> children[i] != nullptr) { // first term greater, spot to insert
                return insert_recurse(term, defs, root_node-> children[i]);
            }
            if (root_node -> n <= 5) {
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
        if (root_node -> n <= 5) {
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
std::vector<std::string> b_tree::search(const std::string &term) {
    // all checking occurs in recursive
    levels = 0;
    return search_recurse(term, root);
}
//***************END_OF_SEARCH******************************************************************
//***************SEARCH_RECURSE*****************************************************************
//INPUTS: takes in term, b_node* recursing through tree to find correct spot
//Returns vector of defs corresponding to term, most of the body of the search functionality contained here
std::vector<std::string> b_tree::search_recurse(const std::string &term, b_node *root_node) {
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
    if (root_node == nullptr) {
        return;
    }
    if (root_node->n <= 5) {
        return;
    }

    if (root_node == root) {
        int med = root_node->n / 2;
        std::string med_term = root_node->words[med];
        root->words.erase(root->words.begin() + med);
        std::vector<std::string> med_def = root->definitions[med];
        root->definitions.erase(root->definitions.begin() + med);
        root->n--;

        b_node *tmp = new b_node();
        tmp->words.push_back(med_term);
        tmp->definitions.push_back(med_def);
        tmp->n = 1;

        b_node *right = new b_node();
        right->n = 0;
        // leftmost child
        right ->children[0] = root-> children[med];
        root -> children[med] = nullptr;
        // assign parent if non null
        if (right-> children[0] != nullptr) {
            right ->children[0]->parent = right;
        }
        int end = root->n;
        for (int i = med; i < end; i++) {
            right->words.push_back(root->words[med]);
            right->definitions.push_back(root->definitions[med]);
            right->children[right->n+1] = root->children[med + 1];
            if (right->children[right->n+1] != nullptr) {
                right->children[right->n+1]->parent = right;
            }
            root->children[med + 1] = nullptr;
            right->n++;
            root->words.erase(root->words.begin() + med);
            root->definitions.erase(root->definitions.begin() + med);
            root->n--;
        }

        root->parent = tmp;
        right->parent = tmp;
        tmp->children[0] = root;
        tmp->children[1] = right;
        root = tmp;
    }
    else {
        int med = root_node->n / 2;
        std::string med_term = root_node->words[med];
        root_node->words.erase(root_node->words.begin() + med);
        std::vector<std::string> med_def = root_node->definitions[med];
        root_node->definitions.erase(root_node->definitions.begin() + med);
        root_node->n--;

        b_node *right = new b_node();
        right->n = 0;
        right ->children[0] = root_node-> children[med];
        root_node -> children[med] = nullptr;
        // assign parent if non null
        if (right-> children[0] != nullptr) {
            right ->children[0]->parent = right;
        }
        int end = root_node->n;
        for (int i = med; i < end; i++) {
            right->words.push_back(root_node->words[med]);
            right->definitions.push_back(root_node->definitions[med]);
            right->children[right->n+1] = root_node->children[med + 1];
            if (right->children[right->n+1] != nullptr) {
                right->children[right->n+1]->parent = right;
            }
            root_node->children[med + 1] = nullptr;
            right->n++;
            root_node->words.erase(root_node->words.begin() + med);
            root_node->definitions.erase(root_node->definitions.begin() + med);
            root_node->n--;
        }
        right->parent = root_node->parent;

        // find root_node's position in parent's children array
        int node_pos = -1;
        for (int i = 0; i <= root_node->parent->n; i++) {
            if (root_node->parent->children[i] == root_node) {
                node_pos = i;
                break;
            }
        }

        // insert med_term at node_pos in parent
        root_node->parent->words.insert(root_node->parent->words.begin() + node_pos, med_term);
        root_node->parent->definitions.insert(root_node->parent->definitions.begin() + node_pos, med_def);
        root_node->parent->n++;

        // shift children right from the end down to node_pos+1 to make room for right
        for (int i = root_node->parent->n; i > node_pos + 1; i--) {
            root_node->parent->children[i] = root_node->parent->children[i - 1];
        }
        // place right child immediately after root_node
        root_node->parent->children[node_pos + 1] = right;

        // recurse up
        split(root_node->parent);
    }
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