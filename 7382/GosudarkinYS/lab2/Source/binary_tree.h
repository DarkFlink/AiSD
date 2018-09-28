#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cctype>
#include <stack>
#include <iostream>

typedef unsigned long ul;

template<class TYPE>
class tree_element {
public:
    tree_element() {
        p_mLeftChild = NULL;
        p_mRightChild = NULL;
    }
    tree_element(TYPE &data, ul descriptor) {
        tree_element();
        mData = data;
        mDescriptor = descriptor;
    }

    tree_element* p_mLeftChild;
    tree_element* p_mRightChild;
    TYPE mData;
    ul mDescriptor;
};

template<class TYPE>
class binary_tree {
public:
    binary_tree();
    binary_tree(std::string &str);
    ~binary_tree();

    static bool is_s_expression(std::string &str);

    void push(TYPE &data, ul descriptor, bool right = true);
    void pop_last();
    void to_structure_exp(std::string &str);

    size_t size();

private:
    tree_element<TYPE>* find_tree_element(ul descriptor, tree_element<TYPE>* ptr);
    tree_element<TYPE>* find_tree_element_parent(ul descriptor, tree_element<TYPE>* ptr);
    void to_structure_exp_rec(std::string &str, tree_element<TYPE>* ptr);
    void error_handler(ul error_code);

    tree_element<TYPE>* p_mRoot;
    tree_element<TYPE>* p_mIterator;
    size_t mSize;
    bool log;
};

//__________METHODS_DEFINITION__________//
template<class TYPE>
binary_tree<TYPE>::binary_tree() {
    p_mRoot = NULL;
    mSize = 0;
}

template<class TYPE>
size_t binary_tree<TYPE>::size() {
    return mSize;
}

template<class TYPE>
void binary_tree<TYPE>::error_handler(ul error_code) {
    if(error_code == 1) {
        std::cerr << "[WARNING] This string cannot be interpreted into binary tree, cause it's not S-expression."
                     " Object has no elements [/WARNING]\n";
    } else if (error_code == 2) {
        std::cerr << "[ERROR] Wrong descriptor, trying to replace data. [/ERROR]\n";
    }
}

template<class TYPE>
bool binary_tree<TYPE>::is_s_expression(std::string &str) {
    if(isalpha(str[0]) && str.size()==1)
        return true;
    if(str[0] != '(')
        return false;

    ul brac_iter=0;
    for(ul it=0; it<=str.size(); it++) {
        if(it == str.size()) {
            if(brac_iter)
                return false;
            else
                return true;
        }

        if(str[it] == '(') {
            if(str[it-1] == ')' || str[it-1] == '(')
                return false;
            brac_iter++;
	}
        else if(str[it] == ')' && brac_iter) {
            if(str[it-1] == '(')
                return false;
            brac_iter--;
            if(it != str.size()-1 && !brac_iter)
                return false;
        }
    }
    return true;
}

template<class TYPE>
void binary_tree<TYPE>::to_structure_exp(std::string &str) {
    if(!str.empty())
        str.clear();
    if(!mSize) {
        str += "()";
        return;
    } else if(mSize == 1) {
        str.push_back('1');
        return;
    }
    to_structure_exp_rec(str, p_mRoot);
}

template<class TYPE>
void binary_tree<TYPE>::to_structure_exp_rec(std::string &str, tree_element<TYPE>* ptr) {
    if(!ptr)
        return;
    if(ptr == p_mRoot)
        str += "(1";
    if(ptr->p_mLeftChild) {
        str.push_back('(');
        str += std::to_string(ptr->p_mLeftChild->mDescriptor);
        to_structure_exp_rec(str, ptr->p_mLeftChild);
    }

    if(ptr->p_mRightChild) {
        str.push_back(',');
        str += std::to_string(ptr->p_mRightChild->mDescriptor);
        to_structure_exp_rec(str, ptr->p_mRightChild);
    } else {
        str += ')';
    }
}

template<class TYPE>
binary_tree<TYPE>::binary_tree(std::string &str)
{
    p_mRoot = NULL;
    mSize = 0;
    if(!is_s_expression(str)) {
        error_handler(1);
        return;
    }

    ul tmp_descriptor = 1;
    std::stack<ul> mDescriptorsStack;

    for(size_t it=0; it < str.size(); it++) {
        if(str[it] == '(')
            continue;
        if(str[it] == ')')
        {
            if(mDescriptorsStack.empty())
                break;
            tmp_descriptor = mDescriptorsStack.top();
            mDescriptorsStack.pop();
            continue;
        }
        if(isalpha(str[it]))
        {
            if(str[it-1] == '(') {
                push(str[it], tmp_descriptor, false);
                if(mSize != 1)
                    mDescriptorsStack.push(tmp_descriptor);
                tmp_descriptor = mSize;
            }
            else {
                push(str[it], tmp_descriptor);
                tmp_descriptor = mSize;
            }
        }
    }
}

template<class TYPE>
void binary_tree<TYPE>::pop_last() {
    if(mSize == 1) {
        mSize = 0;
        delete p_mRoot;
        return;
    }
    tree_element<TYPE>* ptr = find_tree_element_parent(mSize, p_mRoot);
    if(ptr->p_mLeftChild && ptr->p_mLeftChild->mDescriptor == mSize) {
        delete ptr->p_mLeftChild;
        ptr->p_mLeftChild = NULL;
    }
    if(ptr->p_mRightChild && ptr->p_mRightChild->mDescriptor == mSize) {
        delete ptr->p_mRightChild;
        ptr->p_mRightChild = NULL;
    }
    mSize--;
}

template<class TYPE>
binary_tree<TYPE>::~binary_tree() {
    while (mSize)
        pop_last();
}

template<class TYPE>
void binary_tree<TYPE>::push(TYPE &data, ul descriptor, bool right) {
    if(!mSize) {
        p_mRoot = new tree_element<TYPE>(data, descriptor);
        mSize++;
        return;
    }

    tree_element<TYPE>* ptr = find_tree_element(descriptor, p_mRoot);
    if(ptr->p_mLeftChild && ptr->p_mRightChild) {
        error_handler(2);
        return;
    }

    if(right) {
        ptr->p_mRightChild = new tree_element<TYPE>(data, ++mSize);
    } else {
        ptr->p_mLeftChild = new tree_element<TYPE>(data, ++mSize);
    }
}

template<class TYPE>
tree_element<TYPE>* binary_tree<TYPE>::find_tree_element_parent(ul descriptor, tree_element<TYPE>* ptr) {
    tree_element<TYPE>* tmp;
    if((ptr->p_mLeftChild && descriptor == ptr->p_mLeftChild->mDescriptor) ||
    (ptr->p_mRightChild && descriptor == ptr->p_mRightChild->mDescriptor))
        return ptr;

    if(ptr->p_mLeftChild && ptr->mDescriptor != 0)
        tmp = find_tree_element_parent(descriptor, ptr->p_mLeftChild);
    if(ptr->p_mRightChild && ptr->mDescriptor != 0)
        tmp = find_tree_element_parent(descriptor, ptr->p_mRightChild);
    return tmp;
}

template<class TYPE>
tree_element<TYPE>* binary_tree<TYPE>::find_tree_element(ul descriptor, tree_element<TYPE>* ptr) {
    tree_element<TYPE>* tmp;
    if(descriptor == ptr->mDescriptor)
        return ptr;
    if(ptr->p_mLeftChild && ptr->mDescriptor != 0)
        tmp = find_tree_element(descriptor, ptr->p_mLeftChild);
    if(ptr->p_mRightChild && ptr->mDescriptor != 0)
        tmp = find_tree_element(descriptor, ptr->p_mRightChild);
    return tmp;
}

#endif // BINARY_TREE_H
