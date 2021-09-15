#ifndef XMLPARSE_EMPLOYMENT_H
#define XMLPARSE_EMPLOYMENT_H

#include <string>
#include <fstream>
#include <iostream>

class Employment {
public:

    Employment() = default;

    void input() {
        std::cout << "input first name\n";
        std::getline(std::cin, first_name);
        std::cout << "input last name\n";
        std::getline(std::cin, last_name);
        std::cout << "input middle name\n";
        std::getline(std::cin, middle_name);
        std::cout << "input salary\n";
        std::string sal_str;
        std::getline(std::cin, sal_str);
        salary = std::atoi(sal_str.c_str());
        std::cout << "input function name\n";
        std::getline(std::cin, function);
    }

    void set_first_name(std::string name){
        first_name = name;
    }

    void set_last_name(std::string name){
        last_name = name;
    }

    void set_middle_name(std::string name){
        middle_name = name;
    }

    void set_function(std::string name){
        function = name;
    }

    void set_salary(int salary){
        this->salary = salary;
    }

    bool operator==(Employment& rhs){
        return this->first_name == rhs.first_name &&
            this->last_name == rhs.last_name &&
            this->middle_name == rhs.middle_name;
    }

    bool operator!=(Employment& rhs){
        return this->first_name != rhs.first_name ||
               this->last_name != rhs.last_name ||
               this->middle_name != rhs.middle_name;
    }

    bool is_empty(){
        return salary <= 0;
    }

    void print() const{
        std::cout << '\t' << first_name <<  " " << last_name << " " << middle_name << '\n'
            << '\t' << function << '\n'
            << '\t' << "salary: " << salary << '\n';
    }

    void save(std::ofstream& file){
        file << tab << "<surname>" << last_name << "</surname>\n";
        file << tab << "<name>" << first_name << "</name>\n";
        file << tab << "<middleName>" << middle_name << "</middleName>\n";
        file << tab << "<function>" << function << "</function>\n";
        file << tab << "<salary>" << salary <<  "</salary>\n";
    }

    std::string first_name;
    std::string last_name;
    std::string middle_name;
    std::string function;
    std::string tab = "\t\t\t\t";
    int salary;
};


#endif //XMLPARSE_EMPLOYMENT_H
