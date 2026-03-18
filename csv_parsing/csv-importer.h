#ifndef CSV_IMPORTER_H
#define CSV_IMPORTER_H

/***********<Dependencies>************/
#include <iostream>
#include <fstream>
#include <string>
#include <red-black.h>
/***********</Dependencies>************/


/***********<Function Declaration>************/
void load_csv(rb_tree* tree, const std::string& filename);
/***********</Function Declaration>************/


#endif //CSV_IMPORTER_H