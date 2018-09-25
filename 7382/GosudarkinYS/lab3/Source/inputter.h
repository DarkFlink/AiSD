#ifndef INPUTTER_H
#define INPUTTER_H

#include <cstdlib>
#include <fstream>
#include "listqueue.h"

void error_Handler(ul descriptor);
ul getValue();                                              // Getting value from cin
bool getValue(std::ifstream &mStream, ul &value);           //               from custom ifstream
void reworkAlgorithm(ul l, ul r, listQueue<ul> &mQueueLow, listQueue<ul> &mQueueMid, listQueue<ul> &mQueueHigh); // Reading Stream && putting values to queues

#endif // INPUTTER_H
