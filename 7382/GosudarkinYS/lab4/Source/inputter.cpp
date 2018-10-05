#include "inputter.h"

last_actionlog::last_actionlog() 
{
    _operation = NO_OPERATION;
    _index = NO_ELEMENT;
    _side = NO_SIDE;
}
    
last_actionlog::last_actionlog(operation_t operation, long parent, side_t side) 
{
    _operation = operation;
    _index = parent;
    _side = side;
}
void last_actionlog::p_err_log() 
{
    if(_operation == INSERT) {
    	std::cerr << "{ ACTION: INSERT; SIDE: " << _side;
    	std::cerr << "; PARENT_ID: " << _index << " }\n";
    } else if(_operation == OVERLOADED_INIT) {
    	std::cerr << "{ ACTION: OVERLOADED_INIT";
    	std::cerr << "; INDEX: " << _index << " }\n";
    }
}

bool is_s_expression(std::string &str) {
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
