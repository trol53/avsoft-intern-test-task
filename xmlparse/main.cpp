#include <iostream>
#include "headers/worker.h"

const std::string FILE_NAME = "/home/trol53/intern/avsoft/xmlparse/tst.xml";

int main() {
    Parser pars;

    Worker work;
    work.Run();
    return 0;
}
