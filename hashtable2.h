// Copyright 2018 <Negru Bogdan Cristian 312CA>

#ifndef __HASHTABLE__H
#define __HASHTABLE__H
#include <algorithm>
#include <iterator>
#include <list>

#define TRESHOLD 0.75

template <typename Tkey, typename Tvalue> struct elem_info {
	Tkey key;
	Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
private:
	std::list<struct elem_info<Tkey, Tvalue> > * H;            // pointer la buckets
	int HMAX;                                                  // numarul de buckets
	unsigned long (*hash)(Tkey);                               // pointer la functia de hash
	unsigned int size;                                         // numarul total de elemente

public:
    // 	Constructor
	Hashtable(int hmax, unsigned long (*h)(Tkey)) {
		this->HMAX = hmax;
		this->hash = h;
		H = new std::list<struct elem_info<Tkey, Tvalue> > [hmax]; // aloc vectorul de buckets
	}

	~Hashtable() {
		delete[] H ;
	}

	void put(Tkey key, Tvalue value) {

		int hkey = hash(key) % HMAX;

		struct elem_info<Tkey, Tvalue> data;    // adaug element in hashtable in bucket-ul ales de fct de hash
		data.key = key; 
		data.value = value;

		
		H[hkey].push_back(data);
 	}

	Tvalue get(Tkey key) {               // metoda returneaza valoare de la o anumita cheie

		int hkey = hash(key) % HMAX;    // ma pozitionez la bucket-ul corespunzator

		typename std::list<struct elem_info<Tkey,Tvalue> >::iterator it;

		for(it = H[hkey].begin(); it != H[hkey].end(); ++it){   // si il parcurg pana gasesc cheia cautata si returnez valoarea

			if(it->key == key){

				return it->value;
			}
		}
		return Tvalue();
		
	}



};

#endif //__HASHTABLE__

