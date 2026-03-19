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