#include "binary_tree.h"

int main()
{
    std::string str;
    std::cout << "Enter binary tree: \n";
    std::cin >> str;

    if(!is_s_expression(str)) {
        std::cerr << "[ERROR] Invalid input (string isn't a binary tree). Aborting!\n";
        return 0;
    }

    std::cout << "[LOG] Input binary tree:" << str << '\n';
    binary_tree<char> mTree(str);

    char unit;
    std::cin >> unit;
    std::cout << "[LOG] Input search unit: " << unit << "\n\n";

    long count = mTree.find(unit);
    std::cout << "Element {" << unit << "} found " << count << " times \n";
    std::cout << "Way lenght to the closest {" << unit << "}: " << mTree.find_closest(unit) << "\n";           

    return 0;
}
