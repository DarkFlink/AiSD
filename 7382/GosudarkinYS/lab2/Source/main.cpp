#include <iostream>
#include <cstdlib>

using namespace std;
typedef unsigned long ul;

bool Brackets(string &str);
void BracketRework(string &str);

template<class Type>
class listElement {
public:
    listElement* next;
    listElement* prev;
    Type liter;
};

template<class Type>
class listStack {
public:
    listStack() {
        mSize = 0;
    }
    ~listStack() {
        while(!empty())
            pop_Back();
    }

    void push_Back(Type &data){ // Вставка в конец
        listElement<Type>* ptr = new listElement<Type>;
        if(!mSize) {
            root = ptr;
            end = ptr;
            ptr->next = NULL;
            ptr->prev = NULL;
        } else {
            ptr->next = NULL;
            ptr->prev = end;
            end->next = ptr;
            end = ptr;
        }
        ptr->liter = data;
        mSize++;
    }

    void pop_Back(){ // Удаление
        if(!mSize)
            error_Handler(1);
        else if(mSize == 1) {
            delete root;
            root = NULL;
            end = NULL;
        } else {
            end = end->prev;
            delete end->next;
            end->next = NULL;
        }
        mSize--;
    }

    char top(){
        if(!mSize)
            error_Handler(2);
        return end->liter;
    }

    bool empty(){
        if(!mSize)
            return true;
        else
            return false;
    }

private:

    void error_Handler(ul descriptor){
        if(descriptor == 1) {
            cerr << "[ERROR] Trying to pop() in empty stack" << endl;
            exit(1);
        } else if(descriptor == 2) {
            cerr << "[ERROR] Trying to top() in empty stack" << endl;
            exit(1);
        }
    }

    ul mSize;
    listElement<Type>* root;
    listElement<Type>* end;
};

int main() {
    string str1;
    string str2;
    cout << "Enter 1-st string: ";
    cin >> str1;
    cout << "Enter 2-nd string: ";
    cin >> str2;

    if(!Brackets(str1) || !Brackets(str2)) {
        cerr << "[ERROR] One of strings isn't brackets. Aborting!" << endl;
        exit(1);
    }

    BracketRework(str1);
    BracketRework(str2);

    cout << "[LOG] Bracket structure [str1]:  " << str1 << endl;
    cout << "[LOG] Bracket structure [str2]:  " << str2 << endl;

    if(str1 != str2)
        cerr << "Strings !Equal" << endl;
    else
        cout << "String 1 && 2 are structure identical" << endl;

    return 0;
}

bool Brackets(string &str) {
        listStack<char> mStack;
        if(str[0] != '(')
            return false;

        for(unsigned long it=0; it<=str.size(); it++) {
            if(it == str.size()) {
                if(!mStack.empty())
                    return false;
                else
                    return true;
            }

            char c = '(';
            if(str[it] == '(')
                mStack.push_Back(c);
            else if(str[it] == ')' && !mStack.empty()) {
                mStack.pop_Back();
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
