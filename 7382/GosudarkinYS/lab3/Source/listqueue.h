#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include <iostream>
typedef unsigned long ul;

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
    listQueue();
    ~listQueue();

    void push_Front(Type &data);
    void pop_Back();
    void clear(); // destructor + print

    Type top();
    bool empty();

    void operator +=(Type &data);

private:
    void error_Handler(ul descriptor);

    typeObj<Type>* root;
    typeObj<Type>* end;
    ul mSize;
};

template<class Type>
listQueue<Type>::listQueue() {
    mSize = 0;
}

template<class Type>
listQueue<Type>::~listQueue() {
    while(!empty())
        pop_Back();
}

template<class Type>
void listQueue<Type>::clear() {
    std::cout << "{";
    while(!empty()) {
        if(mSize == 1)
            std::cout << top();
        else
            std::cout << top() << ", ";
        pop_Back();
    }
    std::cout << "}" << std::endl;
}

template<class Type>
Type listQueue<Type>::top() {
    if(!mSize)
        error_Handler(2);
    return end->mData;
}

template<class Type>
bool listQueue<Type>::empty() {
    if(!mSize)
        return true;
    else
        return false;
}

template<class Type>
void listQueue<Type>::operator+=(Type &data) {
    push_Front(data);
}

template<class Type>
void listQueue<Type>::pop_Back() {
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

template<class Type>
void listQueue<Type>::push_Front(Type &data) {
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

template<class Type>
void listQueue<Type>::error_Handler(ul descriptor) {
    if(descriptor == 1) {
        std::cerr << "[ERROR] Trying to Pop() in Empty Queue" << std::endl;
        exit(1);
    } else if(descriptor == 2) {
        std::cerr << "[ERROR] Trying to Top() in Empty Queue" << std::endl;
        exit(1);
    }
}

#endif // LISTQUEUE_H
