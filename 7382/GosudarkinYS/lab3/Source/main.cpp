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

    cout << "____________________________________________________" << endl << endl;
    reworkAlgorithm(leftBorder, rightBorder, mQueueLow, mQueueMid, mQueueHigh);
    cout << "____________________________________________________" << endl << endl;

    cout << "Values <left :            "; mQueueLow.clear();
    cout << "Values from [left,right] :"; mQueueMid.clear();
    cout << "Values >right :           "; mQueueHigh.clear();
    return 0;
}
