// Copyright 2018 <Negru Bogdan Cristian 312CA>

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>


unsigned long charHashingFunction(std::string key)
{
    unsigned long hash, i;
    for(hash = i = 0; i < key.length(); ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
// unsigned int charHashingFunction(std::string str){
//     return str.length() + 10000;
// }


#include "hashtable2.h"
#include "Algorithms.h"

template< class T>
class Car {
    public:
    char oras[20];
    T combustibil;
    T consum;

    Car () {
        combustibil = 0;
        consum = 0;
    }
};

template< class T>
class Bus {
    public:
    char source[20];
    char destination[20];
    T passangers;

    Bus () {
        passangers = 0;
    }
};

int task1(City<int> city[], int n) {
    int i, maxi = 0, j;
    for( i = 0; i < n; i++) {        
     if( city[i].aglomeratie > maxi ) {    // parcurg vectorul de orase si il aflu pe cel mai aglomerat (pozitia)
            maxi = city[i].aglomeratie;
            j = i;
        }
    }
    return j;
}


int main() {

        FILE *out1, *out2, *out3, *out4, *out5;

    out1 = fopen("task1.out", "wt");

    if (out1 == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", "task1.out");
        return -1;
    }

    out2 = fopen("task2.out", "wt");

    if (out2 == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", "task2.out");
        return -1;
    }

    out3 = fopen("task3.out", "wt");

    if (out3 == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", "task3.out");
        return -1;
    }

    out4 = fopen("task4.out", "wt");

    if (out4 == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", "task4.out");
        return -1;
    }

    out5 = fopen("task5.out", "wt");

    if (out5 == NULL) {
        fprintf(stderr, "ERROR: Can't open file %s", "task5.out");
        return -1;
    }
// deschid fisierele de output


    int n, m, i, j, index_source, index_destination;  // declar variabile auxiliare
   
    char name[30], destination[30], source[30];

    std::cin>>n>>m;                      // citesc nr de orase si cel de autostrazi

    City<int> *city;
    city = new City<int>[n];         // declar si aloc vectorul de orase, precum si hashtable-ul
    Hashtable<std::string, City<int> > htable(10000, &charHashingFunction);

    for( i = 0; i < n; i++) {

        std::cin >> name;        
        strcpy(city[i].name, name);      // citesc numele orasele si le pun in vector si hashtable
        city[i].index = i;
        htable.put(city[i].name, city[i]);
       
    }

    ListGraph<int> graf(n);    // declar graful

    for( i = 0; i < m; i++) {

        std::cin>>source>>destination;
        index_source = htable.get(source).index;
        index_destination = htable.get(destination).index;   // adaug autostrazile in graf si transform numele in index
        city[index_destination].aglomeratie ++;

        graf.addEdge(index_source, index_destination);

    }



    int b;
 
    std::cin >> b;
    for ( i = 0; i < b; i ++) {

        std::cin>>name;
        j = htable.get(name).index;  // citesc orasele cu benzinarii si actualizez membtul corespunzator din clasa orasului
        city[j].gas_station = 1;     // respectiv
    }
    Car<int> *car;

        Algorithms<int> algoritm(n);
        algoritm.tarjan(graf, n, city);   //declar algoritmii

    int k, nod_sursa;

    std::cin >> k;

    for ( i = 0; i < k; i++) {

        std::cin >> name;               // citesc numele orasului pt care se cere task 3

        nod_sursa = htable.get(name).index;

    std::vector<City<int> > inaccesibile;   // declar un vector de orase inaccesibile

    for (int i = 0; i < algoritm.all_sccs.size() - 1; i++) {

        if (algoritm.all_sccs[i].link_value != city[nod_sursa].link_value){

        for (int j = 0; j < algoritm.all_sccs[i].components.size(); j ++) {
            inaccesibile.push_back(city[algoritm.all_sccs[i].components[j]]);
         
        }
    }
    // parcurg matricea de comp tari conexe si daca difera low-link value pt linia din matrice cu cel pt nod sursa, inseamna ca
    // linia trebuie afisata asa ca o adaug in vectorul declarat mai sus
    }
      if (inaccesibile.size() != 0) {

          fprintf(out3, "Orase inaccesibile pentru %s: ", name);
          for (int y = 0; y < inaccesibile.size(); y++) {

              fprintf(out3, "%s ", inaccesibile[y].name);
          }
          fprintf(out3, "\n");
      }
    }

    int l, g, c;
    std::cin >> l;

    car = new Car<int>[l];   // aloc vectorul de masini

    for ( i = 0; i < l; i++) {

        std::cin >>name;
        strcpy(car[i].oras, name);    // citesc datele pt fiecare masina si la adaug in vectorul de masini

        std::cin >> g;
        car[i].combustibil = g;

        std::cin >> c;
        car[i].consum = c;
    }

    int p, nr_passangers;
    std::cin >> p;
     Bus<int> *bus;
     bus = new Bus<int>[p];            // aloc vectorul de autobuze
     for ( i = 0; i < p; i++) {

        std::cin>>source>>destination>>nr_passangers;   // citesc datele si le adaug in vector

        strcpy(bus[i].source, source);
        strcpy(bus[i].destination, destination);
        bus[i].passangers = nr_passangers;

     }


    int maxi = task1(city, n);                 // apelez functia pt task 1 si afisez rezultatul
    fprintf(out1, "%s %d", city[maxi].name, city[maxi].aglomeratie);

//task 2
        int ok = 1;
    
    if (algoritm.all_sccs.size() > 2) {
        ok = 0;
    }
    if (ok == 1){                     // verific daca sunt mai multe componente conexe, si daca nu sunt afisez
     fprintf(out2, "HARTA VALIDA");   // mesajul corespunzator pt task-ul 2 si 3, altfel doar pt 2
     fprintf(out3, "Exista drum intre oricare doua orase");
    }
     else
     fprintf(out2, "HARTA INVALIDA");

    int best_time, gas_needed;


// task 4
    for (i = 0; i < l; i ++) {
     best_time = algoritm.BFS_task4(graf, htable.get(car[i].oras).index, city);
       gas_needed = best_time * car[i].consum;         // apelez metoda ce imi returneaza cea mai mica distanta
                                                       // pana la o benzinarie si calculez combustibilul necesar
    if (best_time == -2) {
        fprintf(out4, "NU\n");
    }
    else {                                       // afisez mesajul corespunzator daca se poate ajung la benzinarie sau nu
 
       if (gas_needed > car[i].combustibil) {
           fprintf(out4, "NU\n");
       }
       else {
           fprintf(out4, "DA %d\n", car[i].combustibil - gas_needed);
       }
    }
    }


    /// task 5

        index_source = -1;
        index_destination = -1;

     int max_passangers = -1, pos;

    for (i = 0; i < p; i++) {
        for (j = i +1; j < p; j ++) {
            if (strcmp(bus[i].source, bus[j].source) == 0 && strcmp(bus[i].destination, bus[j].destination) == 0) {
                bus[i].passangers += bus[j].passangers;
                bus[j].passangers = 0;                           // aflu ruta cea mai frecventata de pasageri
            }                                                    // si ii retin pozitia din vectorul pt autobuze
        }
        if (bus[i].passangers > max_passangers) {
                max_passangers = bus[i].passangers;
                pos = i;
            }
    }
        index_source = htable.get(bus[pos].source).index;
        index_destination = htable.get(bus[pos].destination).index;  // transform numele in index 

        std::vector<City<int> > orase_parcurse;

        orase_parcurse = algoritm.BFS_task5(graf, index_source, index_destination, city); // apelez metoda ce returneaza
                                                                                          // drumul minim de la orasul sursa
    fprintf(out5, "%d %s ", bus[pos].passangers, bus[pos].source);                        // la destinatie

    for(i = orase_parcurse.size() - 1; i >= 0; i--) {                                     // si afisez rezultatul
        fprintf(out5, "%s ", orase_parcurse[i].name);
    }

    fprintf(out5, "%s\n", bus[pos].destination);


    delete[] car;
    delete[] city;                // dealoc vectorii si inchid fisierele
    delete[] bus;
    fclose(out1);
    fclose(out2);
    fclose(out3);
    fclose(out4);
    fclose(out5);
}

