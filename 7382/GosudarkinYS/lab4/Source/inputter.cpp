#include "inputter.h"

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
