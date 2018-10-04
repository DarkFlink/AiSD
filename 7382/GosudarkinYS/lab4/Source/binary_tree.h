#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stack>
#include <cstring>
#include "inputter.h"

#define NO_ELEMENT -1
#define MEMORY_ADD_BLOCK 50

enum merrno_t {UNEXCITED_PARENT = 1, REPLACE_DATA, ARRAY_INDEX_OUTRANGE};
enum side_t {NO_SIDE, RIGHT, LEFT};
enum operation_t {NO_OPERATION, OVERLOADED_INIT, INSERT};

class last_actionlog {
public:
    last_actionlog() {
        _operation = NO_OPERATION;
        _index = NO_ELEMENT;
        _side = NO_SIDE;
    }
    last_actionlog(operation_t operation, long parent, side_t side) {
        _operation = operation;
        _index = parent;
        _side = side;
    }
    void p_err_log() {
        if(_operation == INSERT) {
            std::cerr << "{ ACTION: INSERT; SIDE: " << _side;
            std::cerr << "; PARENT_ID: " << _index << " }\n";
        } else if(_operation == OVERLOADED_INIT) {
            std::cerr << "{ ACTION: OVERLOADED_INIT";
            std::cerr << "; INDEX: " << _index << " }\n";
        }
    }

    long _index;
    operation_t _operation;
    side_t _side;
};

template<class TYPE>
class binary_tree {
public:
    binary_tree();
    binary_tree(const std::string &string);
    ~binary_tree();

    void insert(const TYPE &data, size_t parent, side_t side);
    void extend_tree_capacity();

    size_t count();
    size_t capacity();

    long find(const TYPE &data);
    long find_closest(const TYPE &data);

    TYPE operator [](size_t index);

private:

    template<class T>
    void extend_size(T** ptr);

    void error_handler(merrno_t err_code);
    void construct_unit(const TYPE &data, size_t parent, side_t side);

    size_t _capacity;   // allocated memory
    size_t _count;      // count of elements
    last_actionlog _log;     // structure with log data about last action

    long* mParents;
    long* mLeft;
    long* mRight;
    TYPE* mData;
};

template<class TYPE>
size_t binary_tree<TYPE>::count() {
    return _count;
}

template<class TYPE>
long binary_tree<TYPE>::find_closest(const TYPE &data) {
    long min_len = NO_ELEMENT;
    for(size_t it=0; it<_count; it++) {
        if(mData[it] == data) {
            size_t tmp_parent = it;
            long curr_len = 0;
            while(mParents[tmp_parent] != NO_ELEMENT) {
                tmp_parent = mParents[tmp_parent];
                curr_len++;
            }
            if(min_len == NO_ELEMENT || min_len > curr_len)
                min_len = curr_len;
        }
    }
    return min_len;
}

template<class TYPE>
long binary_tree<TYPE>::find(const TYPE &data) {
    long count = 0;
    for(size_t it=0; it<_count; it++) {
        if(mData[it] == data)
            count++;
    }
    return count;
}

template<class TYPE>
TYPE binary_tree<TYPE>::operator[](size_t index) {
    if(index > _count-1)
        error_handler(ARRAY_INDEX_OUTRANGE);

    return mData[index];
}

template<class TYPE>
void binary_tree<TYPE>::construct_unit(const TYPE &data, size_t parent, side_t side) {
    if(!_count)
        mParents[_count] = NO_ELEMENT;
    else {
        mParents[_count] = static_cast<long>(parent);
        if(side == RIGHT)
            mRight[parent] = static_cast<long>(_count);
        if(side == LEFT)
            mLeft[parent] = static_cast<long>(_count);
    }
    mData[_count] = data;
    mLeft[_count] = NO_ELEMENT;
    mRight[_count] = NO_ELEMENT;
    _count++;
}

template<class TYPE>
void binary_tree<TYPE>::insert(const TYPE &data, size_t parent, side_t side) {
    if(_count == _capacity)
        extend_tree_capacity();
    if(!_count) {
        construct_unit(data, parent, side);
        return;
    }
    if(parent >= _count) {
        _log = last_actionlog(INSERT, parent, side);
        error_handler(UNEXCITED_PARENT);
        return;
    }
    if((mLeft[parent] != NO_ELEMENT && side == LEFT) || (mRight[parent] != NO_ELEMENT && side == RIGHT)) {
        _log = last_actionlog(INSERT, parent, side);
        error_handler(REPLACE_DATA);
        return;
    }
    construct_unit(data, parent, side);
}

template<class TYPE>
void binary_tree<TYPE>::extend_tree_capacity() {
    extend_size<long> (&mParents);
    extend_size<long> (&mLeft);
    extend_size<long> (&mRight);
    extend_size<TYPE> (&mData);
    _capacity += MEMORY_ADD_BLOCK;
}

template<class TYPE>
size_t binary_tree<TYPE>::capacity() {
    return _capacity;
}

template<class TYPE>
binary_tree<TYPE>::binary_tree() {
    _count = 0;
    _capacity = 0;
    _log = last_actionlog();
    mParents = NULL;
    mLeft = NULL;
    mRight = NULL;
    mData = NULL;
}

template<class TYPE>
binary_tree<TYPE>::binary_tree(const std::string &string) : binary_tree() {
    ul index = 0;
    std::stack<ul> mDescriptorsStack;

    for(size_t it=0; it < string.size(); it++) {
        if(string[it] == '(')
            continue;
        if(string[it] == ')')
        {
            if(mDescriptorsStack.empty())
                break;
            index = mDescriptorsStack.top();
            mDescriptorsStack.pop();
            continue;
        }
        if(isalpha(string[it]))
        {
            if(string[it-1] == '(') {
                if(!_count) {
                    insert(string[it], index, LEFT);
                    continue;
                }
                insert(string[it], index, LEFT);
                if(_count != 1)
                    mDescriptorsStack.push(index);
                index = _count-1;
            }
            else {
                insert(string[it], index, RIGHT);
                index = _count-1;
            }
        }
    }
}

template<class TYPE>
binary_tree<TYPE>::~binary_tree() {
    delete[] mData;
    delete[] mRight;
    delete[] mLeft;
    delete[] mParents;
}

template<class TYPE>
template<class T>
void binary_tree<TYPE>::extend_size(T** root) {
    T* ptr = new T[_capacity+MEMORY_ADD_BLOCK];
    memcpy(ptr, *root, _capacity*sizeof(T));
    delete[] *root;
    *root = ptr;
}

template<class TYPE>
void binary_tree<TYPE>::error_handler(merrno_t err_code) {
    if(err_code == UNEXCITED_PARENT) {
        std::cerr << "[WARNING]: Unexcited parent entered. Check count() of tree and enter another.\n";
    } else if (err_code == REPLACE_DATA) {
        std::cerr << "[WARNING]: Replacing excited tree element.\n";
    } else if (err_code == ARRAY_INDEX_OUTRANGE) {
        std::cerr << "[ERROR]: Invalid using [] overloaded operator: outranged index. Aborting!\n";
        _log.p_err_log();
        exit(1);
    }
    _log.p_err_log();
}

#endif // BINARY_TREE_H
