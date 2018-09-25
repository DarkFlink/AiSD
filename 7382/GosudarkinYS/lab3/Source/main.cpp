#include "inputter.h"

using namespace std;

int main()
{
    ul leftBorder;   // interval borders
    ul rightBorder;  //
    listQueue<ul> mQueueLow;  // for <a
    listQueue<ul> mQueueMid;  // for [a,b]
    listQueue<ul> mQueueHigh; // for >b

    cout << "Input left border of interval" << endl;
    leftBorder = getValue();
    cout << "Input right border of interval"<< endl;
    rightBorder = getValue();

    if(leftBorder > rightBorder || leftBorder == rightBorder)
        error_Handler(3);

    reworkAlgorithm(leftBorder, rightBorder, mQueueLow, mQueueMid, mQueueHigh);

    cout << "____________________________________________________\n\n";
    cout << "VALUES <" << leftBorder << ":   ";                      mQueueLow.clear();
    cout << "____________________________________________________\n\n";
    cout << "VALUES [" << leftBorder << "," << rightBorder << "] :"; mQueueMid.clear();
    cout << "____________________________________________________\n\n";
    cout << "VALUES >" << rightBorder << " :   ";                    mQueueHigh.clear();
    cout << "____________________________________________________\n\n";
    return 0;
}
