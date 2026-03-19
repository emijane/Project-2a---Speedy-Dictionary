
/***********<Dependencies>************/
#include "red-black.h"
/***********</Dependencies>************/


/***********<Private Class Operations>************/

/******rotate_left******
 * Description:
 *      - Performs a left rotation about a given node
 * Arguments:
 *      - rb_node* node: node around which to rotate
 * Returns:
 *      - N/A
 */
void rb_tree::rotate_left(rb_node* node) {

    // determine new parent for this node
        rb_node* new_parent = node->right;

    // if new parent does not exist, exit
        if (new_parent == nullptr) {
            return;
        }

    // rearrange pointers
        node->right = new_parent->left;
        if (new_parent->left != nullptr) {
            new_parent->left->parent = node;
        }

    // new parent links to node's old parent
        new_parent->parent = node->parent;
        if (node->parent == nullptr) {
            root = new_parent;
        }
        else if (node == node->parent->left) {
            node->parent->left = new_parent;
        }
        else {
            node->parent->right = new_parent;
        }

    // node becomes new parent's left child
        new_parent->left = node;
        node->parent = new_parent;
}


/******rotate_right******
 * Description:
 *      - Performs a right rotation about a given node
 * Arguments:
 *      - rb_node* node: node around which to rotate
 * Returns:
 *      - N/A
 */
void rb_tree::rotate_right(rb_node* node) {

    // determine new parent for this node
    rb_node* new_parent = node->left;

    // if new parent does not exist, exit
    if (new_parent == nullptr) {
        return;
    }

    // rearrange pointers
    node->left = new_parent->right;
    if (new_parent->right != nullptr) {
        new_parent->right->parent = node;
    }

    // new parent links to node's old parent
    new_parent->parent = node->parent;
    if (node->parent == nullptr) {
        root = new_parent;
    }
    else if (node == node->parent->right) {
        node->parent->right = new_parent;
    }
    else {
        node->parent->left = new_parent;
    }

    // node becomes new parent's right child
    new_parent->right = node;
    node->parent = new_parent;
}



/******balance******
 * Description:
 *      - Restores red/black tree properties after an insertion
 * Arguments:
 *      - rb_node* node: newly inserted node from which to begin balancing
 * Returns:
 *      - N/A
 */
void rb_tree::balance(rb_node* node) {

    // Case 1: node is root, must be black
        if (node->parent == nullptr) {
            node->color = 'b';
            return;
        }

    // Case 2: parent is black, no violation
        if (node->parent->color == 'b') {
            return;
        }

    rb_node* parent      = node->parent;
    rb_node* grandparent = get_grandparent(node);
    rb_node* uncle       = get_uncle(node);

    // Case 3: uncle is red, recolor and recurse upward
        if (uncle != nullptr && uncle->color == 'r') {
            parent->color = uncle->color = 'b';
            grandparent->color = 'r';
            balance(grandparent);
            return;
        }

    // Case 4: left-right or right-left rotation
        if (node == parent->right && parent == grandparent->left) {
            rotate_left(parent);
            node = parent;
            parent = node->parent;
        }
        else if (node == parent->left && parent == grandparent->right) {
            rotate_right(parent);
            node = parent;
            parent = node->parent;
        }

        grandparent = get_grandparent(node); // get updated grandfather after potential rotation

    // Case 5: left-left or right-right rotation
        parent->color = 'b';
        grandparent->color = 'r';
        if (node == parent->left) {
            rotate_right(grandparent);
        }
        else {
            rotate_left(grandparent);
        }
}



/******get_grandparent******
 * Description:
 *      - Returns the grandparent of the passed-in node
 * Arguments:
 *      - rb_node* node: node for which to find grandparent
 * Returns:
 *      - rb_node*: pointer to grandparent node
 */
rb_node* rb_tree::get_grandparent(const rb_node* node) {
    // if node or parent is null, no grandfather exists
        if (node == nullptr || node->parent == nullptr) {
            return nullptr;
        }

    // else, return grandparent
        return node->parent->parent;
}


/******get_uncle******
 * Description:
 *      - Returns the uncle of the passed-in node
 * Arguments:
 *      - rb_node* node: node for which to find uncle
 * Returns:
 *      - rb_node*: pointer to uncle node
 */
rb_node* rb_tree::get_uncle(const rb_node* node) {
    // get node's grandparent
        rb_node* grandparent = get_grandparent(node);

    // if no grandparent exists, uncle does not exist
        if (grandparent == nullptr) {
            return nullptr;
        }

    // find the uncle
        if (node->parent == grandparent->left) {
            return grandparent->right;
        }
        else {
            return grandparent->left;
        }
}



/*****insert_recursive*****
 * Description:
 *      - Recursively inserts a new node into the tree
 * Arguments:
 *      - rb_node* new_node: new node in which to store term/definition
 *      -      string& term: term to store in new node
 *      -       string& def: definition to store in new node
 * Returns:
 *      - rb_node*: pointer to new root node
 */
rb_node* rb_tree::insert_recursive(rb_node* node, const std::string& term, const std::string& def) {

    // if the node doesn't exist yet, insert as red leaf
        if (node == nullptr) {
            return new rb_node(term, def, 'r');
        }

    // traverse left/right to find place for node
        if (term < node->term) {
            node->left = insert_recursive(node->left, term, def);
            node->left->parent = node;
        }
        else if (term > node->term) {
            node->right = insert_recursive(node->right, term, def);
            node->right->parent = node;
        }
        else {  // term already exists, append new definition to vector
            node->definitions.push_back(def);
            return node;
        }

    // update height
        int left_height = 0;
        int right_height = 0;

        if (node->left != nullptr){left_height = node->left->height;}
        if (node->right!= nullptr){right_height = node->right->height;}

        node->height = 1 + std::max(left_height, right_height);

    // Lastly, return
        return node;
}


/*****preorder_recursive*****
 * Description:
 *      - Performs a preorder traversal recursively
 *      - Prints out the term for each node
 * Arguments:
 *      - rb_node* node: node currently being visited
 * Returns:
 *      - N/A
 */
void rb_tree::preorder_recursive(rb_node* node) {
    // base case: node is null, return
        if (node == nullptr) {
            return;
        }

    // traversal
        std::cout << node->term << std::endl;
        preorder_recursive(node->left);
        preorder_recursive(node->right);
}

/*****inorder_recursive*****
 * Description:
 *      - Performs a inorder traversal recursively
 *      - Prints out the term for each node
 * Arguments:
 *      - rb_node* node: node currently being visited
 * Returns:
 *      - N/A
 */
void rb_tree::inorder_recursive(rb_node* node) {
    // base case: node is null, return
    if (node == nullptr) {
        return;
    }

    // traversal
    inorder_recursive(node->left);
    std::cout << node->term << std::endl;
    inorder_recursive(node->right);
}


/*****postorder_recursive*****
 * Description:
 *      - Performs a postorder traversal recursively
 *      - Prints out the term for each node
 * Arguments:
 *      - rb_node* node: node currently being visited
 * Returns:
 *      - N/A
 */
void rb_tree::postorder_recursive(rb_node* node) {
    // base case: node is null, return
    if (node == nullptr) {
        return;
    }

    // traversal
    postorder_recursive(node->left);
    postorder_recursive(node->right);
    std::cout << node->term << std::endl;
}


/*****search_recursive*****
 * Description:
 *      - Recursively searches for a term
 * Arguments:
 *      - rb_node* node: node currently being visited
 *      -  string& term: term to find
 * Returns:
 *      - rb_node*: pointer to node containing searched-for term
 */
rb_node* rb_tree::search_recursive(rb_node* node, const std::string& term) {
    // base case: node is null, term does not exist in tree
        if (node == nullptr) {
            return nullptr;
        }

    // base case: term matches node, return pointer to node
        if (term == node->term) {
            return node;
        }

    // traverse left/right depending on alpha order
        if (term < node->term) {
            return search_recursive(node->left, term);
        }
        else {
            return search_recursive(node->right, term);
        }
}




// Destructor helper
void rb_tree::destroy(rb_node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

/***********</Private Class Operations>************/


/***********<Public Class Operations>************/

/*****Destructor*****/
rb_tree::~rb_tree() {
    destroy(root);
}


/*****insert*****
 * Description:
 *      -  Inserts a new node into the tree
 * Arguments:
 *      - string& term: term to store in new node
 *      -  string& def: definition to store in new node
 * Returns:
 *      - N/A
 */
void rb_tree::insert(const std::string& term, const std::string& def) {
    // recursively insert new node
        root = insert_recursive(root, term, def);

    // balance upward from the newly inserted node
        rb_node* inserted = root;
        while (inserted->left != nullptr || inserted->right != nullptr) {
            if (term < inserted->term && inserted->left != nullptr) {
                inserted = inserted->left;
            }
            else if (term > inserted->term && inserted->right != nullptr) {
                inserted = inserted->right;
            }
            else {
                break;
            }
        }

        balance(inserted);

    // ensure root is black
        root->color = 'b';
}


/*****preorder*****
 * Description:
 *      -  performs a preorder traversal of the tree
 * Arguments:
 *      - N/A
 * Returns:
 *      - N/A
 */
void rb_tree::preorder() {
    preorder_recursive(root);
}


/*****inorder*****
 * Description:
 *      -  performs a inorder traversal of the tree
 * Arguments:
 *      - N/A
 * Returns:
 *      - N/A
 */
void rb_tree::inorder() {
    inorder_recursive(root);
}


/*****postorder*****
 * Description:
 *      -  performs a postorder traversal of the tree
 * Arguments:
 *      - N/A
 * Returns:
 *      - N/A
 */
void rb_tree::postorder() {
    postorder_recursive(root);
}


/*****search*****
 * Description:
 *      - searches for a term and returns its definition
 * Arguments:
 *      - string& term: term for which to find definition
 * Returns:
 *      - vector<string>*: pointer to vector storing definitions for this term
 */
std::vector<std::string>* rb_tree::search(const std::string& term) {
    // search for node storing passed-in term
        rb_node* result = search_recursive(root, term);

    // if term does not exist, return nullptr
        if (result == nullptr) {
            return nullptr;
        }

    // if term exists, return pointer to definition
        return &result->definitions;
}



/*****timed_search*****
 * Description:
 *      - measures the average time of searching for a term
 *      - searches for a term several times, returns the avg
 *        search time
 * Arguments:
 *      - string& term: term to search for
 *      - int iterations: number of iterations to average over
 * Returns:
 *      - long long: average search time in nanoseconds
 */
long long rb_tree::timed_search(const std::string& term, int iterations) {
    // correct case for passed-in term
        std::string normalized = term;
        if (!normalized.empty()) {
            normalized[0] = std::toupper(normalized[0]);    // first letter capitalized

            for (int i = 1; i < normalized.size(); i++) {
                normalized[i] = std::tolower(normalized[i]); // rest of letters uncapitalized
            }
        }

    // run search for given number of iterations, accumulate total time
        long long total = 0;
        std::vector<std::string>* defs = nullptr;
        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            defs = search(normalized);
            auto end = std::chrono::high_resolution_clock::now();
            total += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }

    // if term not found
        if (defs == nullptr) {
            std::cout << "search(\"" << normalized << "\"): term not found" << std::endl;
        }

    // calculate average
        long long average = total / iterations;

    // print result
        std::cout << "timed_search(\"" << term << "\") over " << iterations << " iterations: " << average << " ns" << "\n";

    // print definition(s)
        for (int i = 0; i < defs->size(); i++) {
            std::cout << "\t[" << i + 1 << "] " << (*defs)[i] << "\n";
        }

    // Lastly, return computed average
        return average;
}
/***********</Public Class Operations>************/