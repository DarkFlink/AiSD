#include <fstream>
#include <cctype>
#include <iostream>
#include <cerrno>
#include <string>
#include <cstdlib>
using namespace std;

typedef unsigned long ul;

void error_Handler(ul descriptor, ul iter = 0 ) {
    if(descriptor == 1) {
        cerr << "[ERROR] Too big value. Aborting!" << endl;
        exit(1);
    } else if (descriptor == 2) {
        cerr << "[ERROR] Invalid filepath. Aborting!" << endl;
        exit(1);
    } else if (descriptor == 3 && iter) {
        cerr << "[ERROR_TEST#" << iter << "]  Invalid expression, symbol detected in input. Skipping." << endl;
    } else if (descriptor == 4) {
        cerr << "[ERROR] Invalid interval borders. Aborting!" << endl;
        exit(1);
    }
}

ul inputInt() {
    ul value;
    cin >> value;
    if(!cin.good())
        error_Handler(1);
    return value;
}

template<class Type>  // One queue element
class typeObj {
public:
    typeObj* next;
    typeObj* prev;
    Type mData;
};

template<class Type>  // queue class
class listQueue {
public:
    listQueue() {
        mSize = 0;
    }
    ~listQueue() {
        while(!empty())
            pop_Back();
    }

    void push_Front(Type &data){
        typeObj<Type>* ptr = new typeObj<Type>;
        if(!mSize) {
            root = ptr;
            end = ptr;
            ptr->next = NULL;
            ptr->prev = NULL;
        } else {
            ptr->next = root;
            ptr->prev = NULL;
            root->prev = ptr;
            root = ptr;
        }
        ptr->mData = data;
        mSize++;
    }

    void pop_Back(){
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

    void clear(){
        cout << "{";
        while(!empty()) {
            if(mSize == 1)
                cout << top();
            else
                cout << top() << ", ";
            pop_Back();
        }
        cout << "}" << endl;
    }

    Type top(){
        if(!mSize)
            error_Handler(2);
        return end->mData;
    }

    ul size(){
        return mSize;
    }

    bool empty(){
        if(!mSize)
            return true;
        else
            return false;
    }

    void operator +=(Type &data){
        push_Front(data);
    }

private:

    void error_Handler(ul descriptor){
        if(descriptor == 1) {
            cerr << "[ERROR] Trying to Pop() in Empty Queue" << endl;
            exit(1);
        } else if(descriptor == 2) {
            cerr << "[ERROR] Trying to Top() in Empty Queue" << endl;
            exit(1);
        }
    }

    typeObj<Type>* root;
    typeObj<Type>* end;
    ul mSize;
};

//  _____Basic task algorithm_____  //
void reworkAlgorithm(ul &l, ul &r, listQueue<ul> &mQueueLow, listQueue<ul> &mQueueMid, listQueue<ul> &mQueueHigh)
{
    string str;
    string filePath;
    cout << "Enter test filepath:" << endl;
    cin >> filePath;
    ifstream mFile;
    mFile.open(filePath, std::ifstream::binary);
    if(!mFile)
        error_Handler(2);

    for(ul j=0; getline(mFile, str, '\n'); j++) {
        bool valFlag = true;
        if (!str.size())
            valFlag = false;

        for(ul it=0; it < str.size(); it++) {
            if(!isdigit(str[it]) && str[it] != '\n') {
                valFlag = false;
                break;
            } else if(str[it] == '\n') {
                str.erase(str.begin()+static_cast<long>(it));
            }
        }

        if(valFlag) {
            ul value = stoul(str);
            if(errno == ERANGE)
                error_Handler(1);

            cout << "[LOG_TEST#" << j+1 << "] Sucess" << endl;
            if(value < l)
                mQueueLow += value;
            if(value >= l && value <= r)
                mQueueMid += value;
            if(value >= r)
                mQueueHigh += value;
        } else {
            error_Handler(3, j+1);
        }
    }
}

int main()
{
    ul leftBorder;   // interval borders
    ul rightBorder;  //
    listQueue<ul> mQueueLow;  // for <a
    listQueue<ul> mQueueMid;  // for [a,b]
    listQueue<ul> mQueueHigh; // for >b

    cout << "Input left border of interval" << endl;
    leftBorder = inputInt();
    cout << "Input right border of interval"<< endl;
    rightBorder = inputInt();

    if(leftBorder > rightBorder || leftBorder == rightBorder)
        error_Handler(4);

    cout << "____________________________________________________" << endl << endl;
    reworkAlgorithm(leftBorder, rightBorder, mQueueLow, mQueueMid, mQueueHigh);
    cout << "____________________________________________________" << endl << endl;

    mQueueLow.clear();
    mQueueMid.clear();
    mQueueHigh.clear();
    return 0;
}
