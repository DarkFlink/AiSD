#define DEBUG
#include <iostream>

using namespace std;

int function(int val) {
    int result = 0;
    if(val == 1)
        return 1;
    for(int i=2;i <= val;i++) {
        result += function(val/i);
        #ifndef DEBUG
        cout << "     f(" << result << ")" << endl;
        #endif
    }
    #ifndef DEBUG
    cout << "f(" << result << ")" << endl;
    #endif
    return result;
}

int main() {
    int input;
    cin >> input;
    if(input < 0) {
        cerr << ("[ERROR] Unvalid input (negative value exception)") << endl;
        return 0;
    }
//    cout << "For " << input << ": " << function(input) << " [Success]" << endl;
    cout << function(input);
    return 0;
}
