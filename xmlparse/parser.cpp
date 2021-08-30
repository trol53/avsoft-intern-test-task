#include "headers/parser.h"

void Parser::Save(std::string file_name){
    std::ofstream file(file_name);
    file << "<departments>\n";
    for (auto node : dict){
        file << dep_head << node.first.name << '\"' << '>' << '\n';
        file << "<employments>\n";
        for (auto employ : node.second){
            file << empl_head << '\n';
            file << "<surname>" << employ.last_name << "</surname>\n";
            file << "<name>" << employ.first_name << "</name>\n";
            file << "<middleName>" << employ.middle_name << "</middleName>\n";
            file << "<function>" << employ.function << "</function>\n";
            file << "<salary>" << employ.salary <<  "</salary>\n";
            file << empl_tail;
        }
        file << "</employments>\n";

    }
    file << "</departments>\n";
}

std::map <Department, std::vector<Employment>> Parser::Load(std::string file_name){
    std::ifstream file(file_name);
    std::string line;
    while (getline(file, line)){
        line = delete_space(line);
        if (line == "<departments>")
            continue;
        if (line == "</departments>"){
            file.close();
            return dict;
        }
        if (dep_head_comp(line)){
            std::string name = get_dep_name(line);
            Department dep(name);
            add_employments(dep, file);
        }
        line.clear();
    }
    file.close();
    return dict;
}

std::string Parser::delete_space(const std::string& str){
    auto iter_b = str.begin();
    for (;;iter_b++){
        if (*iter_b != ' ' && *iter_b != '\t')
            break;
    }
    auto iter_e = str.end();
    iter_e--;
    for (;;iter_b--){
        if (*iter_e != ' ' && *iter_e != '\t')
            break;
    }
    std::string res(iter_b, iter_e + 1);
    res.pop_back();
    return res;
}

bool Parser::dep_head_comp(const std::string& str){
    if (std::string(str.begin(), str.begin() + 18) == dep_head)
        return true;
    return false;
}

std::string Parser::get_dep_name(std::string& line){
    return std::string(line.begin() + 18, line.end() - 2);
}

void Parser::add_employments(Department dep, std::ifstream& file){
    std::vector<Employment> tmp;
    for (std::string line; std::getline(file, line);){
        line = delete_space(line);
        if (line == "<employments>")
            continue;
        if (line == "</employments>")
            break;

        if (line == empl_head){

            tmp.push_back(add_employment(dep, file));
        }
        if (line == empl_tail){
            continue;
        }
    }
    dep.employments_count = tmp.size();
    for (Employment employ : tmp){
        dep.average_salary += employ.salary;
    }
    dep.average_salary /= static_cast<double>(dep.employments_count);
    dict.insert({dep, tmp});

}

Employment Parser::add_employment(Department& dep, std::ifstream& file){
    std::string line;
    Employment employ;
    employ.last_name = get_data(file, 9);
    employ.first_name = get_data(file, 6);
    employ.middle_name = get_data(file, 12);
    employ.function = get_data(file, 10);
    employ.salary = std::atoi(get_data(file, 8).c_str());
    return employ;
}

std::string Parser::get_data(std::ifstream& file, int step){
    std::string line;
    std::getline(file, line);
    line = delete_space(line);
    return std::string(line.begin() + step, line.end() - step - 1);
}
