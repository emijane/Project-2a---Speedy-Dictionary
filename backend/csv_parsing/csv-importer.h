#ifndef CSV_IMPORTER_H
#define CSV_IMPORTER_H

/***********<Dependencies>************/
#include <iostream>
#include <fstream>
#include <string>

#include "red-black.h"
#include "b_tree.h"
/***********</Dependencies>************/


/***********<Function Declaration>************/
void load_csv(rb_tree* rb_tree, b_tree* b_tree, const std::string& filename);
/***********</Function Declaration>************/


#endif //CSV_IMPORTER_H