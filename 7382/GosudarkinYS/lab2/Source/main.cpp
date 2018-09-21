#include <vector>
#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

bool Brackets(string &str);
void BracketRework(string &str);

int main() {
    string str1;
    string str2;
    cin >> str1;
    cin >> str2;

    if(!Brackets(str1) || !Brackets(str2)) {
        cerr << "[ERROR] One of strings isn't brackets. Aborting!" << endl;
        exit(1);
    }

    BracketRework(str1);
    BracketRework(str2);

    cout << "Bracket structure [str1]:  " << str1 << endl;
    cout << "Bracket structure [str2]:  " << str2 << endl;

    if(str1 != str2)
        cerr << "Strings !Equal" << endl;
    else
        cout << "String 1 && 2 are structure identical" << endl;

    return 0;
}

bool Brackets(string &str) {
        stack<char> mStack;
        if(str[0] != '(')
            return false;

        for(unsigned long it=0; it<=str.size(); it++) {
            if(it == str.size()) {
                if(!mStack.empty())
                    return false;
                else
                    return true;
            }

            if(str[it] == '(')
                mStack.push('(');
            else if(str[it] == ')' && !mStack.empty()) {
                mStack.pop();
                if(it != str.size()-1 && mStack.empty())
                    return false;
            }
        }
        return true;
}

void BracketRework(string &str) {
    for(unsigned long i=0; i<str.size();) {
        if(str[i] != '(' && str[i] != ')') {
            str.erase(str.begin() + static_cast<long>(i));
            continue;
        }
        i++;
    }
}
