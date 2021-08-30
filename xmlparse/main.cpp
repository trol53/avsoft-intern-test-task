#include <iostream>
#include "headers/worker.h"

const std::string FILE_NAME = "/home/trol53/intern/avsoft/xmlparse/tst.xml";

int main() {
    Parser pars;
    auto dict = pars.Load(FILE_NAME);

    Worker work(dict);
    work.Run();
    return 0;
}
