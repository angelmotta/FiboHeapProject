#ifndef FIBOHEAP_NODE_H
#define FIBOHEAP_NODE_H
#include <list>
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

#endif //FIBOHEAP_NODE_H
