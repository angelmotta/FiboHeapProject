#ifndef FIBOHEAP_FIBONACCIHEAP_H
#define FIBOHEAP_FIBONACCIHEAP_H

#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <cmath>
#include "Node.h"
using namespace std;

template <typename T>
class FibonacciHeap {

private:
    int m_size;
    list <Node<T>*> m_heap;
    Node<T>* min;
    void printGraphVizBinomialTree(Node<T>* ptrNodo);
    string filename = "../ngrafo.vz";

public:
    void Extract_Min();
    T GetMin();
    void Delete(T deletekey);
    void Insert(T newkey);
    void Compactar();
    Node<T>* Unir(Node<T>* p1, Node<T>* p2);
    void printGraphViz();

};

template <typename T>
void FibonacciHeap<T>::Insert(T newkey){
    auto newNode = new Node<T>(newkey);
    m_heap.push_back(newNode);
    if(m_heap.size() == 0){
        min = newNode;
    }else{
        if(min->m_key > newkey){
            min = newNode;
        }
    }
    return;
}

template <typename T>
T FibonacciHeap<T>::GetMin() {
    return min->m_key;
}

template <typename T>
void FibonacciHeap<T>::Extract_Min() {
    for (auto n : min->m_Hijos) {
        m_heap.push_front(n);
    }
    m_heap.remove(min);
    m_size--;
    min = m_heap.front();
    for (auto n : m_heap) {
        if (min->m_key > n->m_key) {
            min = n;
        }
    }
    Compactar();
}

template <typename T>
Node<T>* FibonacciHeap<T>::Unir(Node<T>* p1, Node<T>* p2) {
    if (p1->m_key < p2->m_key) {
        p1->m_Hijos.push_back(p2);
        p2->m_Padre = p1;
        p1->m_Grado++;
        m_heap.remove(p2);
        return p1;
    }
    else {
        p2->m_Hijos.push_back(p1);
        p1->m_Padre = p2;
        p2->m_Grado++;
        m_heap.remove(p1);
        return p2;
    }
}

template <typename T>
void FibonacciHeap<T>::Compactar() {
    //int maxGrado = floor(log2(m_size));
    int maxGrado = 20;
    //Get max Grado
    /*int maxGrado = -1;
    for (auto it=m_heap.begin(); it != m_heap.end(); ++it){
      if((*it)->m_Grado > maxGrado){
        maxGrado = (*it)->m_Grado;
      }
    }*/
    vector<Node<T> *> grados(maxGrado + 2, nullptr);
    auto it = m_heap.begin();
    auto itDel = m_heap.end(); // temporal
    while(it != m_heap.end()){
        int c_grado = (*it)->m_Grado;
        if(grados[c_grado]){    // si hay conflict
            itDel = it;
            it++;
            auto ptrNode = Unir(*itDel, grados[c_grado]);
            grados[c_grado] = nullptr;
            while(true){
                if(grados[ptrNode->m_Grado]){
                    int gradoPrev = ptrNode->m_Grado;
                    ptrNode = Unir(ptrNode, grados[ptrNode->m_Grado]);
                    grados[gradoPrev] = nullptr;
                }
                else {
                    grados[ptrNode->m_Grado] = ptrNode;
                    grados[c_grado] = nullptr;
                    break;
                }
            }
        }
        else{
            grados[c_grado] = *it;
            it++;
        }
    }
}

template <typename T>
void FibonacciHeap<T>::printGraphVizBinomialTree(Node<T>* ptrNodo) {
    std::cout << "- Grapviz Fibo Tree -\n";
    queue<Node<T>*> queueNodes;
    queueNodes.push(ptrNodo);
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::app);
    while(!queueNodes.empty()){
        auto ptrNode = queueNodes.front();
        queueNodes.pop();
        //std::cout << "Key: " << (ptrNode)->get_key() << ", Grado: " << (ptrNode)->get_grado() << '\n';
        for(auto it = ptrNode->m_Hijos.begin(); it != ptrNode->m_Hijos.end(); ++it){
            file << '\t' << (ptrNode)->m_key << " -> " << (*it)->m_key << '\n';
            queueNodes.push((*it));
        }
    }
    file.close();
}

template <typename T>
void FibonacciHeap<T>::printGraphViz(){
    cout << "** Print GraphViz **\n";
    std::ofstream outFile;
    outFile.open(filename, std::ios::out | std::ios::trunc); // trunc 'discard existing content'
    outFile << "digraph {" << '\n';
    outFile.close();
    for (auto it=m_heap.begin(); it != m_heap.end(); ++it){
        if((*it)->m_Hijos.size() == 0){
            outFile.open(filename, std::ios::out | std::ios::app);
            outFile << '\t' << (*it)->m_key << '\n';
            outFile.close();
        }
        else {
            printGraphVizBinomialTree(*it);
        }

    }
    outFile.open(filename, std::ios::out | std::ios::app);
    outFile << "}";
    outFile.close();
};

#endif //FIBOHEAP_FIBONACCIHEAP_H