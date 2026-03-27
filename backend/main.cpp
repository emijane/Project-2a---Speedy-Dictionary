#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "red-black.h"
#include "b_tree.h"
#include "csv-importer.h"

#include "httplib.h"
#include "nlohmann/json.hpp"

#include <cstdlib>


/*****<Global tree structures>*****/
rb_tree rb_tree_inst;
b_tree b_tree_inst;
/*****</Global tree structures>*****/

// returns the allowed frontend origin for local or deployed frontend
std::string get_allowed_origin(const httplib::Request& req) {
    std::string origin = req.get_header_value("Origin");

    if (origin == "http://localhost:3000") {
        return origin;
    }

    if (origin == "http://localhost:3000") {
        return origin;
    }

    if (origin == "https://project-2a-speedy-dictionary-1.onrender.com") {
        return origin;
    }

    return "";
}

int main() {

    // load data from CSV into trees
    std::string csv_path = "dictionary.csv";
    std::ifstream test_file(csv_path);

    if (!test_file.is_open()) {
        csv_path = "../../dictionary.csv";
    }
    test_file.close();

    load_csv(&rb_tree_inst, &b_tree_inst, csv_path);

    // create server object
    httplib::Server svr;

    // root endpoint to check if server is running
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
    res.set_content("Server is running", "text/plain");
    });
    
    // handle preflight requests for cors
    svr.Options(R"(.*)", [](const httplib::Request& req, httplib::Response& res) {
        // allow all origins for local and deployed frontend
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        res.status = 204;
    });

    // search endpoint
    svr.Get("/search", [&](const httplib::Request& req, httplib::Response& res) {
        // allow all origins for local and deployed frontend
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        // validate query parameter
        // if "word" parameter is missing, return 400 error with JSON message
        if (!req.has_param("word")) {
            nlohmann::json body;
            body["error"] = "Missing word parameter";
            res.status = 400;
            res.set_content(body.dump(), "application/json");
            return;
        }

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
        std::vector<std::string> b_definitions = b_tree_inst.search(normalized);
        auto b_end_time = std::chrono::high_resolution_clock::now();
        double b_time = std::chrono::duration<double, std::micro>(b_end_time - b_start_time).count();

        // Combine definitions into single string
        std::string definitions;
        std::string b_defs;
        if (rb_definitions != nullptr) {
            for (int i = 0; i < rb_definitions->size(); i++) {
                if (i > 0) definitions += "\n";
                definitions += (*rb_definitions)[i];
            }

            for (int i = 0; i < b_definitions.size(); i++) {
                if (i>0) b_defs += "\n";
                b_defs += b_definitions[i];
            }

        } else {
            definitions = "Word not found";
        }


        // build and send JSON response
        nlohmann::json body;
        body["word"] = word;
        body["definition"] = definitions;
        //body["b_definition"] = b_defs;
        body["rbTime"] = rb_time;
        body["bTime"] = b_time;

        res.set_content(body.dump(), "application/json");
    });

    // Listen for http requests
    int port = 8080;
    const char* env_port = std::getenv("PORT");

    if (env_port != nullptr) {
        port = std::stoi(env_port);
    }

    std::cout << "Server starting on port " << port << std::endl;
    svr.listen("0.0.0.0", port);

    return 0;
}