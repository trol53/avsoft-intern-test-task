#include <iostream>
#include <string>
#include <fstream>

void jump(std::ifstream& file){
	std::string str;
	std::getline(file, str);
}

std::string delete_space(const std::string& str){
        auto iter = str.begin();
        for (;;iter++){
            if (*iter != ' ' && *iter != '\t')
                break;
        }
        std::string res(iter, str.end());
        return res;
    }

int main(){
	setlocale(LC_ALL, "Russian");
	std::string str = "   fgdlkf";
	str = delete_space(str);
	std::cout << str;

	/*std::ifstream file("/home/trol53/intern/avsoft/xmlparse/tst.xml");
	file.peek(0);
	std::getline(file, str);
	std::getline(file, str);
	std::getline(file, str);
	std::getline(file, str);
	std::cout << str << file.is_open();
	while (true){
		std::getline(file, str);
		std::cout << str;
	}
	//jump(file);
	//std::getline(file, str);
	//std::cout << str;*/
}

