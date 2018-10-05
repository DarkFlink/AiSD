#ifndef INPUTTER_H
#define INPUTTER_H

#include <iostream>
#define NO_ELEMENT -1

typedef unsigned long ul;

bool is_s_expression(std::string &str);

enum merrno_t {UNEXCITED_PARENT = 1, REPLACE_DATA, ARRAY_INDEX_OUTRANGE};
enum side_t {NO_SIDE, RIGHT, LEFT};
enum operation_t {NO_OPERATION, OVERLOADED_INIT, INSERT};

class last_actionlog {
public:
    last_actionlog();
    last_actionlog(operation_t operation, long parent, side_t side);
    void p_err_log();

    long _index;
    operation_t _operation;
    side_t _side;
};
#endif // INPUTTER_H
