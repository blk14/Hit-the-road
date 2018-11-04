// Copyright 2018 <Negru Bogdan Cristian 312CA>

#ifndef __LISTGRAPH_H__
#define __LISTGRAPH_H__

#include <vector>

template< class T>
struct Node {
    std::vector<T> neighbors;    // clasa ce contine un vector de vecini
};

template< class T>
class ListGraph {
private:
    std::vector<Node<T> > nodes;
    T size;

public:
    // Constructor
    ListGraph(T size) {

        this->size = size;
        nodes.resize(size);
        for (int i = 0; i < size; ++i)
            nodes[i].neighbors.resize(0);
    }

    // Destructor
    ~ListGraph() {}

    void addEdge(T src, T dst) {

        unsigned int i;
        
     for (i = 0; i < nodes[src].neighbors.size(); i++) {  // adaug dst la vecinii nodului src
        if (nodes[src].neighbors[i] == dst) {
            return;
        }
     }

     nodes[src].neighbors.push_back(dst);
      
    }

    std::vector<T> getNeighbors(T node) {
        return nodes[node].neighbors;             // metoda ce returneaza vecinii unui nod
    }

    int getSize() {                          // metoda returneaza dimensiunea grafului
        return size;
    }

};

#endif // __LISTGRAPH_H__