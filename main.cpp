#include <iostream>

#include "FibonacciHeap.h"

using namespace std;

int main() {
    FibonacciHeap<int> fiboHeap;
    fiboHeap.Insert(1);
    fiboHeap.Insert(2);
    fiboHeap.Insert(3);
    fiboHeap.Insert(4);
    fiboHeap.Insert(5);
    fiboHeap.Extract_Min();
    fiboHeap.Insert(10);
    fiboHeap.Insert(12);
    fiboHeap.Insert(13);
    fiboHeap.Insert(14);
    fiboHeap.Insert(15);
    fiboHeap.Extract_Min();
    fiboHeap.printGraphViz();
    return 0;
}