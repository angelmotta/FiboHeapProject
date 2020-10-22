#include <iostream>

#include "FibonacciHeap.h"

using namespace std;

int main() {
    FibonacciHeap<int> fiboHeap;
    /*
    fiboHeap.Insert(1);
    fiboHeap.Insert(2);
    fiboHeap.Insert(3);
    fiboHeap.Insert(4);
    fiboHeap.Insert(5);
    cout << "Min: " << fiboHeap.GetMin() << "\n";
    fiboHeap.Extract_Min();
    fiboHeap.Insert(10);
    fiboHeap.Insert(12);
    fiboHeap.Insert(13);
    fiboHeap.Insert(14);
    fiboHeap.Insert(15);
    cout << "Min: " << fiboHeap.GetMin() << "\n";
    fiboHeap.Extract_Min();
    fiboHeap.printGraphViz();
    */

    fiboHeap.loadPictures();
    /*
    for(int i = 3; i >= 1; i--){
        cout << "Min: " << fiboHeap.GetMin() << "\n";
        auto minNode = fiboHeap.GetMinv2();
        cout << "picA: " << minNode->pictureA->pathFile << '\n';
        cout << "picB: " << minNode->pictureB->pathFile << '\n';
        fiboHeap.Extract_Min();
    }
     */
    // Stress and Correctness Test
    /*
    for(int i = 5000; i >= 1; i--){
        fiboHeap.Insert(i);
    }
    for(int i = 5000; i >= 1; i--){
        cout << "Min: " << fiboHeap.GetMin() << "\n";
        fiboHeap.Extract_Min();
    }
    */
    return 0;
}