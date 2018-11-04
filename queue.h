// Copyright 2018 <Negru Bogdan Cristian 312CA>

template< class T>
struct Point {
    public:
    T command;
    Point<T> *next;
    Point<T> *prev;

    Point(T command) {
        this->command = command;
        next = NULL;
        prev = NULL;
    }
    ~Point() {
    }
};

template <class T>
class Queue {
 public:
    Point<T> *head;
    Point<T> *tail;
    int numElements;
  
    Queue() {
        head = tail = NULL;
        numElements = 0;
    }


void push(T command) {
       
        Point<T> *nod = new Point<T>(command);
        if( numElements == 0){
        numElements ++;
        head = tail = nod;
        head->next = NULL;
        head->prev = NULL;
       }
       else {
           numElements ++;
           if(tail != NULL){
           tail->next = nod;
           nod->prev = tail;
           tail = nod;
           tail->next = NULL;
           }
       }
   
    }
    
    T pop() {
            T data;
            this->numElements --;
            if(head != NULL)
            data = head->command;
            Point<T> *aux;
            aux = head;
            if(head != NULL)
            head = head->next;
            
            delete aux;
            if(head != NULL)
              head->prev = NULL;
            return data; 
    }

    // metoda dequeue returneaza elementul de la inceputul cozii, stergandu-l

    T dequeue_last() {
            T data;
            this->numElements --;
            if(tail != NULL)
            data = tail->command;
            Point<T> *aux;
            aux = tail;
            if(tail != NULL)
            tail = tail->prev;
            
            delete aux;
            if(tail != NULL)
              tail->next = NULL;
            return data; 
    }
    // metoda dequeue_last returneaza elementul de la sfarsitul cozii, stergandu-l


     T peek(int position) {
         int aux = 0;
        Point<T> *data;
        data = head;
        while(aux != position) {
            data = data->next;
            aux ++;
        }
        if(data != NULL)
            return data->command; 
    }
    // metoda peek returneaza elementul de pe o anumita pozitie

    int size() {
        return numElements;
    }
    // metoda size returneaza dimensiunea cozii


      ~Queue() {
          while(this->numElements > 0) {
              pop();
            }    
        }
};