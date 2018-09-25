#include "inputter.h"

using namespace std;

//____________________________FUNCS________________________________//

void error_Handler(ul descriptor) {
    if(descriptor == 1) {
        cerr << "[ERROR] Too big value or symbol in input. Aborting!" << endl;
        exit(1);
    } else if (descriptor == 2) {
        cerr << "[ERROR] Invalid filepath. Aborting!" << endl;
        exit(1);
    } else if (descriptor == 3) {
        cerr << "[ERROR] Invalid interval borders. Aborting!" << endl;
        exit(1);
    }
}

ul getValue() {
    ul value;
    cin >> value;
    if(!cin.good())
        error_Handler(1);
    return value;
}

bool getValue(ifstream &mStream, ul &value) {
    mStream >> value;
    if(mStream.eof())   // EOF checking
        return true;
    if(mStream.fail())  // Logical error checking (like int ERANGE exception || trying to write to int a symbol)
        error_Handler(1);
    return false;
}

//  _____Basic task algorithm_____  //
void reworkAlgorithm(ul l, ul r, listQueue<ul> &mQueueLow, listQueue<ul> &mQueueMid, listQueue<ul> &mQueueHigh)
{
    string filePath;
    cout << "Enter test filepath:" << endl;
    cin >> filePath;

    // Open fileStream
    ifstream mFile;
    mFile.open(filePath, std::ifstream::binary);
    if(!mFile)
        error_Handler(2);

    // Reading fileStream
    ul value;
    bool isEOF = false;
    do {
        isEOF = getValue(mFile, value);

        // Sorting_values_between_queues
        if(value < l)
            mQueueLow += value;
        if(value >= l && value <= r)
            mQueueMid += value;
        if(value >= r)
            mQueueHigh += value;
    } while(!isEOF);                           // Reading stream until find EOF
}
