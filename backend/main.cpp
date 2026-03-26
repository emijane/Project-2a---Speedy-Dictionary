#include <iostream>
#include <string>
#include <vector>

#include "red-black.h"
#include "b_tree.h"
#include "csv-importer.h"

#include "httplib.h"
#include "nlohmann/json.hpp"

/*****<Global tree structures>*****/
rb_tree rb_tree_inst;
b_tree b_tree_inst;
/*****</Global tree structures>*****/

int main() {

    // load data from CSV into trees
    load_csv(&rb_tree_inst, &b_tree_inst, "dictionary.csv");

    // create server object
    httplib::Server svr;

    // search endpoint
    svr.Get("/search", [&](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*"); // allow frontend

        std::string word = req.get_param_value("word");

        // correct case for passed-in term
        std::string normalized = word;
        if (!normalized.empty()) {
            normalized[0] = std::toupper(normalized[0]);    // first letter capitalized

            for (int i = 1; i < normalized.size(); i++) {
                normalized[i] = std::tolower(normalized[i]); // rest of letters uncapitalized
            }
        }

        // search in red/black tree
        const auto rb_start_time = std::chrono::high_resolution_clock::now();
        std::vector<std::string>* rb_definitions = rb_tree_inst.search(normalized);
        const auto rb_end_time = std::chrono::high_resolution_clock::now();
        double rb_time = std::chrono::duration<double, std::micro>(rb_end_time - rb_start_time).count();

        // search in b tree
        auto b_start_time = std::chrono::high_resolution_clock::now();
        b_tree_inst.search(normalized);
        auto b_end_time = std::chrono::high_resolution_clock::now();
        double b_time = std::chrono::duration<double, std::micro>(b_end_time - b_start_time).count();

        // Combine definitions into single string
        std::string definitions;
        if (rb_definitions != nullptr) {
            for (int i = 0; i < rb_definitions->size(); i++) {
                if (i > 0) definitions += "\n";
                definitions += (*rb_definitions)[i];
            }
        } else {
            definitions = "Word not found";
        }


        // build and send JSON response
        nlohmann::json body;
        body["word"] = word;
        body["definition"] = definitions;
        body["rbTime"] = rb_time;
        body["bTime"] = b_time;

        res.set_content(body.dump(), "application/json");
    });

    // Listen for http requests
    svr.listen("0.0.0.0", 8080);

    return 0;
}