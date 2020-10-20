#ifndef FIBOHEAP_NODE_H
#define FIBOHEAP_NODE_H
#include <list>
#include <utility>
using namespace std;

template <typename T>
struct Node {
    int m_Grado;
    T m_key;
    std::list <Node<T>*> m_Hijos;
    Node<T> * m_Padre;
    bool is_black;

    Node(T newkey) {
        m_key = newkey;
        m_Grado = 0;
        is_black = false;
        m_Padre = nullptr;
    }
};

struct Picture {
    string pathFile;
    vector<float> vc;

    Picture(string _pathFile, vector<float> _vc) {
        pathFile = std::move(_pathFile);
        vc = std::move(_vc);
    }
};

#endif //FIBOHEAP_NODE_H
