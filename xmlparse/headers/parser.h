#ifndef XMLPARSE_PARSER_H
#define XMLPARSE_PARSER_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "employment.h"
#include "department.h"

class Parser {
public:
    Parser() = default;
    std::map <Department, std::vector<Employment>> Load(std::string& file_name);

    void Save(std::string& file_name, std::map <Department, std::vector<Employment>>&);

private:
    std::string delete_space(const std::string& str);

    bool dep_head_comp(const std::string& str);

    std::string get_dep_name(std::string& line);

    void add_employments(Department dep, std::ifstream& file);

    Employment add_employment(Department& dep, std::ifstream& file);

    std::string get_data(std::ifstream& file, int step);

    std::map <Department, std::vector<Employment>> dict;
    std::string dep_head = "<department name=\"";
    std::string dep_tail = "</department>";
    std::string empl_head = "<employment>";
    std::string empl_tail = "</employment>";

};


#endif //XMLPARSE_PARSER_H
