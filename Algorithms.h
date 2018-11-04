// Copyright 2018 <Negru Bogdan Cristian 312CA>

#ifndef __ALGORITHMS_H__
#define __ALGORITHMS_H__

#include <vector>
#include "queue.h"
#include "stack.h"
#include "ListGraph.h"
#include <iostream>

template< class T>
struct myclass {
  bool operator() (T i,T j) { return (i<j);}     // clasa ce ma ajuta la sortarea vectorilor
};
myclass<int> myobject;

template< class T>
class SCC {
    public:
     std::vector<T> components;  // clasa cu vectorii de componente conexe si low-link value al componentei
     T link_value;

};

template< class T>
class City {
    public:
    char name[20];
    T index;
    T gas_station;
    T aglomeratie;
    T link_value;             //clasa City ce contine toate caracteristicile pe care le are un oras

    City () {
        gas_station = 0;
        aglomeratie = 0;
        index = -1;
        gas_station = -10;
        link_value = -2;
    }
};

template< class T>
class Algorithms {                      // clasa Algorithms are vectori pt aplicarea algoritmului tarjan
public:

    Stack<T> dfs_stack;
    std::vector<T> on_stack; //vector ce retine daca un element e pe stiva
    std::vector<T> visited;   // retine elementele vizitate
    T nr_sccs;                // nr de comp tari conexe
    std::vector<SCC<int> > all_sccs;      // matrice cu toate comp tari conexe
    std::vector<T> ids;                   // vector pt id-uri
    std::vector<T> low;                   // vector pt low-link value 
    std::vector<T> aux_comp;              // vector auxiliar
    int timp;                               // variabila de timp
    
    // Constructor
    Algorithms(T size) {
        this->nr_sccs = 0;
        this->timp = 1;
        for (int i = 0; i < size; i ++) {
            on_stack.push_back(0);
            visited.push_back(-1);         //initializez vectorii
            ids.push_back(-1);
            low.push_back(-1);
        }
    }

    T myfunction (T i,T j) { return (i<j); }      // functie auxiliara pt sortare

    void DFS (ListGraph<int> listGraph, int nod_sursa, City<int> city[], int sccs_size) { // DFS recursiv pt tarjan
        int i, v, minim = timp;
        low[nod_sursa] = ids[nod_sursa] = timp++;               // initializez low si ids cu timpul curent
       on_stack[nod_sursa] = 1;                                // cand se porneste un nou dfs se pune elem pe stiva
        dfs_stack.push(nod_sursa);                             // pun pe stiva elementul sursa
        visited[nod_sursa] = 1;                              // marchez ca vizitat
        std::vector<int> n = listGraph.getNeighbors(nod_sursa); // iau vecinii nodului

        for (i = 0; i < n.size(); i ++) {

            if (visited[n[i]] != 1) {
                DFS(listGraph, n[i], city, sccs_size);   // ii parcurg si daca nu este vreunul vizitat pornesc un nou DFS

                if (low[n[i]] < low[nod_sursa]) {         // actualizez low-link value in caz ca e mai mic al vecinului
                    low[nod_sursa] = low[n[i]];
                    minim = low[n[i]]; 
                }
            }
             else { 
                 if (on_stack[n[i]] == 1) {
                                                       // daca este vizitat verific daca este pe stiva si actualizez low-link
                if (low[n[i]] < low[nod_sursa]) {
                    low[nod_sursa] = low[n[i]];
                    minim = low[n[i]];
                }
             
            }
             }
             v = i;
        }
                int x;                                  // daca se ajunge aici inseamna ca pe stiva se afla elementele
                                                        // unei componente tari conexe
                while (dfs_stack.size() >= 0) {
                    x = dfs_stack.pop();
                    aux_comp.push_back(x);
                    city[x].link_value = sccs_size;   // pun toate elementele din componenta conexa intr-un vector si le atribui
                    on_stack[x] = 0;                   // ca low-link value dimensiunea matricei(in linii) de le momentul 
                }                                       // respectiv

                std::sort(aux_comp.begin(), aux_comp.end(), myobject);

           
    }


    void tarjan (ListGraph<int> listgraph, int n, City<int> city[]) { // metoda asigura ca se vor afla toate comp tari conexe
        int sccs_size = 1;                                            // un DFS afla o singura componenta
        all_sccs.resize(sccs_size);
        for (int i = 0; i < n; i ++) {
            if (visited[i] != 1) {                                    // daca intalnesc un nod nevizitat ii aplic un DFS
                DFS(listgraph, i, city, sccs_size);
                all_sccs[sccs_size - 1].components = aux_comp;         // adaug elementele noii comp in matrice
                all_sccs[sccs_size - 1].link_value = sccs_size;      // atribui liniei din matrice un low-link vaue
                aux_comp.resize(0);                                // redimensionez matricea
                sccs_size ++;
                all_sccs.resize(sccs_size);

            }
        }
    }



    int BFS_task4(ListGraph<int> listGraph, int nod_sursa, City<int> city[]) {
     int size = listGraph.getSize();
     Queue<int> q;
     std::vector<int> vect;
     std::vector<int> d(size);            // distanta pana la nodul sursa
     std::vector<int> p(size);            // nodul parinte
     std::vector<std::string> color(size);
     int best_time = -2;

    for (int u = 0; u < size; u++) {
        color[u] = "white";                // nodul este nedescpoerit
        d[u] = 0;
        p[u] = 0;
    }

    color[nod_sursa] = "grey"; // nodul sursa a fost descoperit si e in curs de procesare, atunci vizitam vecinii
    d[nod_sursa] = 0;
    q.push(nod_sursa);          // adaug in coada
    vect.push_back(nod_sursa);  // vectorul cu toate nodurile parcurse
    
    while (q.size() > 0) {
        int v = q.pop();           // iau primul nod din coada
        std::vector<int> n = listGraph.getNeighbors(v);       // ii aflu vecinii si ii parcurg
        for (unsigned int u = 0; u < n.size(); u++) {
            if (color[n[u]] == "white") {
                color[n[u]] = "grey";
                p[n[u]] = v;                                // ii marchez ca descoperiti si le actualize informatiile
                d[n[u]] = d[v]+1;

                if (city[n[u]].gas_station == 1){
                    return d[n[u]];                        // daca gasesc benzinarie cautarea s-a terminat
                }
                q.push(n[u]);                               // adaug in coada
                vect.push_back(n[u]);                       // adaug in vectorul de noduri gasite
            }
        }
        color[v] = "black";                                  // procesarea nodului s-a incheiat
    }

        return best_time;
    }







     static std::vector<City<int> > BFS_task5(ListGraph<int> listGraph, int nod_sursa, int nod_destinatie, City<int> city[]) {
     int size = listGraph.getSize();
     Queue<int> q;
     std::vector<int> vect;
     std::vector<int> d(size);                       // distanta pana la nodul sursa
     std::vector<int> p(size);                       // nodul parinte
     std::vector<std::string> color(size);
     std::vector<City<int> > orase_parcurse;          // vector pt orase parcurse

    for (int u = 0; u < size; u++) {
        color[u] = "white"; // nodul este nedescpoerit inca
        d[u] = 0;
        p[u] = 0;
    }

    color[nod_sursa] = "grey"; // nodul sursa a fost descoperit si e in curs de procesare, atunci vizitam vecinii
    d[nod_sursa] = 0;
    q.push(nod_sursa);         // adaug in coada
    vect.push_back(nod_sursa); // creez vectorul pe care il voi afisa cu toate nodurile parcurse
    
    while (q.size() > 0) {
        int v = q.pop();         // iau primul nod din coada
        std::vector<int> n = listGraph.getNeighbors(v);        // ii aflu vecinii si ii sortez, apoi ii parcurg
        std::sort(n.begin(), n.end(), myobject);

        for (unsigned int u = 0; u < n.size(); u++) {
            if (color[n[u]] == "white") {
                color[n[u]] = "grey";                   // il marchez ca descoperit si ii actualizez informatiile
                p[n[u]] = v;
                d[n[u]] = d[v]+1;
                if (n[u] == nod_destinatie) {

                    orase_parcurse.resize(0);                      // daca ajung la destinatie ma intorc din parinte in parinte
                                                                   // pana la nodul sursa si retin calea intr-un vector
                    while(p[n[u]] != nod_sursa) {
                        orase_parcurse.push_back(city[p[n[u]]]);
                        p[n[u]] = p[p[n[u]]];
                    }
                    p[n[u]] = v;
                    return orase_parcurse;
                }
                q.push(n[u]);                                 // bag in coada
                vect.push_back(n[u]);                          // bag in vectorul de noduri gasite
            }
        }
        color[v] = "black";                               // procesarea nodului s-a incheiat
    }

        return orase_parcurse;
    }


    
};

#endif // __ALGORITHMS_H__
