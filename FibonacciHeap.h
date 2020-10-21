#ifndef FIBOHEAP_FIBONACCIHEAP_H
#define FIBOHEAP_FIBONACCIHEAP_H

#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <cmath>
#include <chrono>
#include "Node.h"
#define cimg_use_jpeg 1
#include "CImg.h"

using namespace cimg_library;
using namespace std;

template <typename T>
class FibonacciHeap {

private:
    int m_size;
    list <Node<T>*> m_heap;
    Node<T>* min;
    void printGraphVizBinomialTree(Node<T>* ptrNodo);
    string filename = "ngrafo.vz";
    string fileListPics = "listPathPictures.txt";
    vector<float> vectorizar(CImg<float>& img);
    vector<Picture*> pictureVector;
public:
    FibonacciHeap();
    ~FibonacciHeap();
    void Extract_Min();
    T GetMin();
    Node<T>* GetMinv2();
    void Delete(T deletekey);
    void Insert(T newkey, Picture* a = nullptr, Picture* b = nullptr);
    void Compactar();
    Node<T>* Unir(Node<T>* p1, Node<T>* p2);
    void printGraphViz();
    void loadPictures();
};

template <typename T>
FibonacciHeap<T>::FibonacciHeap(){
    m_size = 0;
    min = nullptr;
}

template <typename T>
void FibonacciHeap<T>::Insert(T newkey, Picture* a, Picture* b){
    auto newNode = new Node<T>(newkey, a, b);
    m_heap.push_back(newNode);
    m_size++;
    if(min == nullptr){
        min = newNode;
    }else{
        if(min->m_key > newkey){
            min = newNode;
        }
    }
}

template <typename T>
T FibonacciHeap<T>::GetMin() {
    return min->m_key;
}

template <typename T>
Node<T>* FibonacciHeap<T>::GetMinv2() {
    return min;
}

template <typename T>
void FibonacciHeap<T>::Extract_Min() {
    // promote children from min node towards linked list
    for (auto n : min->m_Hijos) {
        m_heap.push_front(n);
    }
    m_heap.remove(min);
    m_size--;
    delete min; // free memory
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
    if(m_heap.size() < 2) return;  // base case
    int maxGrado = floor(log2(m_size));
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

template <typename T>
void FibonacciHeap<T>::loadPictures(){
    cout << "** Load Pictures **\n";
    // Generate list path of pictures
    system("find faces_subSet -type f -name \"*.jpg\" > listPathPictures.txt");
    // Open List path of Pictures and apply haar function to each picture
    string picFile;
    ifstream inFileList(fileListPics);
    // Create vector of picture Objects
    auto start = chrono::steady_clock::now();
    while(getline(inFileList, picFile)){
        //cout << "load this: " << picFile << '\n';
        CImg<float> img(picFile.c_str());
        img.resize(128, 128);
        CImg<float> imgB = img.haar(false,2);
        CImg<float> imgC = imgB.crop(0,0,27,27);
        // Vectorizar
        vector<float> vc = vectorizar(imgC); // get vector caracteristico
        auto picObject = new Picture(picFile, vc);  // constructor Picture
        pictureVector.push_back(picObject);
    }
    auto end = chrono::steady_clock::now();
    cout << "Create picure objects : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << "\n";
    // Get Euclidean distance between Pictures Objects in O(n^2)
    //cout << "Get Euclidean distance from pictures\n";
    //start = chrono::steady_clock::now();

    for(int i = 0; i < pictureVector.size(); i++){
        for(int j = i + 1; j < pictureVector.size(); j++){
            //cout << "Euclidean distance: " << pictureVector[i].pathFile << " and " << pictureVector[j].pathFile << "\n";
            float sum = 0;
            for(int k = 0; k < pictureVector[i]->vc.size(); k++){
                sum += pow(pictureVector[i]->vc[k] - pictureVector[j]->vc[k], 2);
            }
            //cout << "Distance sum: " << sum << '\n';
            float distance = sqrt(sum);
            //cout << "Distance sum: " << distance << '\n';
            this->Insert(distance, pictureVector[i], pictureVector[j]);
        }
    }
    //end = chrono::steady_clock::now();
    //cout << "Euclidean distance O(n^2) : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << "\n";
}

template <typename T>
vector<float> FibonacciHeap<T>::vectorizar(CImg<float>& img){
    vector<float> result;
    cimg_forXY(img,x,y){
        result.push_back( (img(x,y,0) + img(x,y,1) +  img(x,y,2))/3);
    }
    return result;
}

template <typename T>
FibonacciHeap<T>::~FibonacciHeap(){
    cout << "** Destructure called **\n";
    // Delete picture objects
    for(auto & i : pictureVector){
        delete i;
    }
}

#endif //FIBOHEAP_FIBONACCIHEAP_H
