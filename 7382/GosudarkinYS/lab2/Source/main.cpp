#include "hier_list.h"

using namespace std;
using namespace h_list;

int main (){

    lisp _hierList1;
    lisp _hierList2;
    string str1;
    string str2;

    cout << "list1: ";
    read_lisp(_hierList1);
    write_lisp(_hierList1);

    cout << "\nlist2: ";
    read_lisp(_hierList2);
    write_lisp(_hierList2);

    tostr_hierlist(_hierList1, str1);
    tostr_hierlist(_hierList2, str2);

    if(str1 == str2)
        cout << "\nLists 1 && 2 are structure identical\n";
    else
        cout << "\nLists 1 && 2 are NOT structure identical\n";

    destroy(_hierList1);
    destroy(_hierList2);

    return 0;
}
