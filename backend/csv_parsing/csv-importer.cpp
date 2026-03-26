
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
 std::ifstream file(filename);
 if (!file.is_open()) {
  std::cerr << "could not open .csv file" << std::endl;
  return;
 }

 std::string line;
 std::getline(file, line); // skip header

 // pre-collect all definitions per term
 std::map<std::string, std::vector<std::string>> all_defs;
 std::vector<std::string> term_order; // preserve insertion order

 while (std::getline(file, line)) {
  if (line.empty()) continue;

  int first_comma = line.find(',');
  if (first_comma == std::string::npos) continue;
  std::string term = line.substr(0, first_comma);

  int second_comma = line.find(',', first_comma + 1);
  if (second_comma == std::string::npos) continue;
  std::string definition = line.substr(second_comma + 1);

  if (term.empty() || definition.empty()) continue;

  if (all_defs.find(term) == all_defs.end()) {
   term_order.push_back(term);
  }
  all_defs[term].push_back(definition);
 }
 file.close();

 // now insert each term once with all its definitions
 for (const std::string& term : term_order) {
  // rb_tree called once per definition, as it was originally
  for (const std::string& def : all_defs[term]) {
   rb_tree->insert(term, def);
  }
  // b_tree called once with all definitions at once
  b_tree->insert(term, all_defs[term]);
 }
}

/***********</Public Functions>************/