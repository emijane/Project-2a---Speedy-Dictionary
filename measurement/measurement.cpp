/***********<Dependencies>************/
#include "measurement.h"
/***********</Dependencies>************/


/***********<Function Declarations>************/
/*****rb_timed_search*****
 * Description:
 *      - measures the average time of looking up a value
 *        in the red-black tree
 *      - searches for a term several times, returns the avg
 *        search time
 * Arguments:
 *      - rb_tree* tree: pointer to red/black tree
 *      - string& term: term to search for
 *      - int iterations: number of iterations to average over
 * Returns:
 *      - long long: average search time in nanoseconds
 */
long long rb_timed_search(rb_tree* tree, std::string& term, int iterations) {

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
        for (int i = 0; i < iterations; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            tree->search(normalized);
            auto end = std::chrono::high_resolution_clock::now();
            total += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }

    // calculate average
        long long average = total / iterations;

    // print result
        std::cout << "timed_search(\"" << term << "\") over " << iterations << " iterations: " << average << " ns" << "\n";

    // Lastly, return computed average
        return average;

}
/***********</Function Declarations>************/