#include <iostream>
#include <vector>
#include "binary_tree.h"

using namespace std;

int main()
{
    string str1;
    string str2;
    cin >> str1;
    cin >> str2;

    binary_tree<char> mTree1(str1);
    binary_tree<char> mTree2(str2);
    mTree1.to_structure_exp(str1);
    mTree2.to_structure_exp(str2);

    cout << "[OUT] Binary tree 1 s_expression: " << str1 << '\n';
    cout << "[OUT] Binary tree 2 s_expression: " << str2 << '\n';
    if(str1 == str2)
        cout << "[OUT] Binary trees are stucture identical." << '\n';
    else
        cout << "[OUT] Binary trees are NOT stucture identical." << '\n';
    cout << "__________________________________________________\n";

    return 0;
}
