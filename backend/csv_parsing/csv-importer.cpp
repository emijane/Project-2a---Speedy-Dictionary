
/***********<Dependencies>************/
#include "csv-importer.h"
/***********</Dependencies>************/

/***********<Public Functions>************/

/*****load_csv*****
 * Description:
 *      - reads .csv file
 *      - inserts term/definition pairs into red/black tree
 *      - data starts on row 2 of csv
 * Arguments:
 *      - rb_tree* rb_tree: pointer to red/black tree
 *      - b_tree* b_tree: pointer to B tree
 *      - string& filename: path to CSV file
 * Returns:
 *      - N/A
 */
void load_csv(rb_tree* rb_tree, b_tree* b_tree, const std::string& filename) {
    // attempt to open .csv file
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "could not open .csv file" << std::endl;
        return;
    }

    // skip header row
    std::string line;
    std::getline(file, line);

    // load each row into trees
    while (std::getline(file, line)) {
        // skip empty lines
        if (line.empty()) { continue; }

        // get term
        std::string term;
        std::string definition;

        int first_comma = line.find(',');
        if (first_comma == std::string::npos) { continue; }
        term = line.substr(0, first_comma);

        // get definition (after second comma, ignore part of speech)
        int second_comma = line.find(',', first_comma + 1);
        if (second_comma == std::string::npos) { continue; }
        definition = line.substr(second_comma + 1);

        // skip rows with missing fields
        if (term.empty() || definition.empty()) { continue; }

        // insert pair into trees
        rb_tree->insert(term, definition);
        std::vector<std::string> defs = {definition};  // wrap in vector for b-tree
        //b_tree->insert(term, defs);
    }

    // close file
    file.close();
}

/***********</Public Functions>************/