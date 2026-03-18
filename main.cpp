#include <iostream>

#include <iostream>
#include <string>
#include "red-black.h"
#include "csv-importer.h"

int main() {

    // First, create tree
        rb_tree tree;

    // Second, load entries from .csv file
        load_csv(&tree, "dictionary.csv");

    // Third, test search
        tree.timed_search("MANGO", 1);
        tree.timed_search("apple", 5);
        tree.timed_search("oRANGE", 5);
        tree.timed_search("zythum", 10);


    return 0;
}


/*
 //***********<Insertion Tests>************
    std::cout << "=== Insertion Tests ===" << "\n\n";

    // insert a set of terms and definitions
        std::cout << "Inserting terms..." << "\n";
        tree.insert("mango",      "a tropical fruit with sweet orange flesh");
        tree.insert("apple",      "a round fruit that is typically red or green");
        tree.insert("cherry",     "a small, round fruit that is typically red or dark purple");
        tree.insert("banana",     "a long curved fruit with a yellow skin");
        tree.insert("elderberry", "a small dark berry from the elder tree");
        tree.insert("fig",        "a soft sweet fruit with a thin skin");
        tree.insert("grape",      "a small sweet fruit that grows in clusters");
        tree.insert("durian",     "a large spiky fruit known for its strong odor");
        tree.insert("kiwi",       "a small fruit with brown fuzzy skin and green flesh");
        tree.insert("lemon",      "a yellow citrus fruit known for its sour taste");
        tree.insert("honeydew",   "a sweet melon with pale green flesh");
        tree.insert("jackfruit",  "a large tropical fruit with a spiky exterior");
        std::cout << "Done." << "\n\n";

    // test duplicate insertion
        std::cout << "Inserting duplicate term (apple)..." << "\n";
        tree.insert("apple", "a crunchy fruit that keeps the doctor away");
        std::cout << "Done." << "\n\n";

    //***********</Insertion Tests>************


    //***********<Traversal Tests>************
    std::cout << "=== Traversal Tests ===" << "\n\n";

    // inorder — should print alphabetically
        std::cout << "Inorder traversal (expect alphabetical order):" << "\n";
        tree.inorder();
        std::cout << "\n";

    // preorder
        std::cout << "Preorder traversal:" << "\n";
        tree.preorder();
        std::cout << "\n";

    // postorder
        std::cout << "Postorder traversal:" << "\n";
        tree.postorder();
        std::cout << "\n";

    //***********</Traversal Tests>************


    //***********<Search Tests>************
    std::cout << "=== Search Tests ===" << "\n\n";

    // helper lambda to print all definitions for a term
    auto print_definitions = [](const std::string& term, std::vector<std::string>* defs) {
        if (defs == nullptr) {
            std::cout << "search(\"" << term << "\"): term not found" << "\n";
            return;
        }
        std::cout << "search(\"" << term << "\"):" << "\n";
        for (int i = 0; i < defs->size(); i++) {
            std::cout << "  [" << i + 1 << "] " << (*defs)[i] << "\n";
        }
    };

    // search for a term that exists
    print_definitions("mango",  tree.search("mango"));

    // search for the duplicate term (should show both definitions)
    print_definitions("apple",  tree.search("apple"));

    // search for a term that does not exist
    print_definitions("orange", tree.search("orange"));

    std::cout << "\n";
    //***********</Search Tests>************
 */