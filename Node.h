#ifndef FIBOHEAP_NODE_H
#define FIBOHEAP_NODE_H
#include <list>
#include <utility>
using namespace std;

struct Picture {
    string pathFile;
    vector<float> vc;

    Picture(string _pathFile, vector<float> _vc) {
        pathFile = std::move(_pathFile);
        vc = std::move(_vc);
    }
};

template <typename T>
struct Node {
    int m_Grado;
    T m_key;
    std::list <Node<T>*> m_Hijos;
    Node<T> * m_Padre;
    bool is_black;
    struct Picture* pictureA;
    struct Picture* pictureB;
    int src;
    int dst;

    Node(T newkey) {
        m_key = newkey;
        m_Grado = 0;
        is_black = false;
        m_Padre = nullptr;
        pictureA = nullptr;
        pictureB = nullptr;
    }

    Node(T newkey, Picture* picA, Picture* picB) {
        m_key = newkey;
        m_Grado = 0;
        is_black = false;
        m_Padre = nullptr;
        pictureA = picA;
        pictureB = picB;
    }

    Node(T newkey, Picture* picA, Picture* picB, int _src, int _dst) {
        m_key = newkey;
        m_Grado = 0;
        is_black = false;
        m_Padre = nullptr;
        pictureA = picA;
        src = _src;
        pictureB = picB;
        dst = _dst;
    }
};

struct subset {
    int parent;
    int rank;
};

#endif //FIBOHEAP_NODE_H
