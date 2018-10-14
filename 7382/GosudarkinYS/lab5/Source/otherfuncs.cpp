#include "otherfuncs.h"

void print_tabs(size_t _count) {
    for(size_t it = 0; it < _count; it++)
        std::cout << '\t';
}

bool getInt(ul& _value) {
    bool res = true;
    std::cin >> _value;    
    if(std::cin.eof())
        res = false;
    if(std::cin.fail())
    {
        std::cout << "Input error. Aborting!\n";
        exit(1);
    }
    return res;
}
