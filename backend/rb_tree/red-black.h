
#ifndef RED_BLACK_H
#define RED_BLACK_H

/***********<Dependencies>************/
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
/***********</Dependencies>************/


/***********<Class Declaration>************/
// Red/Black Node
class rb_node {
public:
    // Data
    std::string term;
    std::vector<std::string> definitions;

    // Relation to other nodes
    rb_node* parent;
    rb_node* left;
    rb_node* right;

    // For tree balancing
    int height;
    char color;      //'b'=black, 'r'=red

    // Constructor declaration
    rb_node(const std::string& term_input, const std::string& def_input, const char color_input)
        :   term(term_input),
            parent(nullptr), left(nullptr), right(nullptr),
            height(1),
            color(color_input) {
                definitions.push_back(def_input);       // store first definition for this term
            }
};

// Red/Black Tree
class rb_tree {
private:
    rb_node* root;          // tree root node

    // Rotation
    void rotate_left(rb_node* node);
    void rotate_right(rb_node* node);

    // Balancing
    void balance(rb_node* node);

    // Helper functions
    rb_node* get_grandparent(const rb_node* node);
    rb_node* get_uncle(const rb_node* node);

    // Recursive Insertion / Deletion
    rb_node* insert_recursive(rb_node* node, const std::string& term, const std::string& def);

    // Recursive traversal
    void preorder_recursive(rb_node* node);
    void inorder_recursive(rb_node* node);
    void postorder_recursive(rb_node* node);

    // Recursive search
    rb_node* search_recursive(rb_node* node, const std::string& term);

    // Destructor helper
    static void destroy(rb_node* node);

public:
    // Constructors / Destructors
    rb_tree() : root(nullptr) {}     // constructor
    ~rb_tree();                      // destructor

    // Public insertion / deletion operations
    void insert(const std::string& term, const std::string& def);

    // Public traversal functions
    void preorder();
    void inorder();
    void postorder();

    // Public search function
    std::vector<std::string>* search(const std::string& term);
};
/***********</Class Declaration>************/


#endif //RED_BLACK_H
