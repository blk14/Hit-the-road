
template <class T> 
class Stack {
 public:
    T *stackArray;
    int topLevel;
    int current_size ;
    int firstLevel;
    int add_size;


    Stack() {
        this->topLevel = -1;
        stackArray = new T[10];
        current_size = 0;
        this->firstLevel = 0;
        add_size = 5;
    }

    ~Stack() {
       
        delete[] stackArray;
    }

    void push(T element) {
        
        if(topLevel == current_size - 1) {

        T* resize_aux = new T[current_size + add_size];

            for(int i = 0; i < current_size; i++){
                resize_aux[i] = stackArray[i];
            }
            delete[] stackArray;
            current_size = current_size + add_size;
            stackArray = resize_aux;
        }

        topLevel++;
        stackArray[this->topLevel] = element;
    }

    // metoda push adauga un element in stiva, avand grija sa redimensioneze array-ul cand e necesar

    T pop() {
        topLevel--;
        return stackArray[this->topLevel + 1];
    }

    // metoda pop returneaza si elimina elementul de la sfarsitul stivei (ultimul adaugat)

    T peek() {   
        return stackArray[this->firstLevel];
    }
    // metoda peek returneaza elementul de la sfarsitul stivei (ultimul adaugat)



    int size() {
        return this->topLevel - this->firstLevel;
    }
    //metoda size returneaza dimensiunea stivei
};