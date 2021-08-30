#ifndef XMLPARSE_EMPLOYMENT_H
#define XMLPARSE_EMPLOYMENT_H

#include <string>
#include <iostream>

class Employment {
public:

    Employment() = default;

    void input() {
        std::cout << "input first name\n";
        std::cin >> first_name;
        std::cout << "input last name\n";
        std::cin >> last_name;
        std::cout << "input middle name\n";
        std::cin >> middle_name;
        std::cout << "input salary\n";
        std::cin >> salary;
        std::cout << "input function name\n";
        std::cin >> function;
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

    void print() const{
        std::cout << '\t' << first_name <<  " " << last_name << " " << middle_name << '\n'
            << '\t' << function << '\n'
            << '\t' << "slary: " << salary << '\n';
    }

    std::string first_name;
    std::string last_name;
    std::string middle_name;
    std::string function;
    int salary;
};


#endif //XMLPARSE_EMPLOYMENT_H
