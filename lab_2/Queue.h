#include "Node.h"

template <class T> class Queue{
private:

        Node <T> *head;
        Node <T> *tail;
        int currentSize;

public:

        Queue()
        :head(NULL)
        ,tail(NULL)
        ,currentSize(0)
        {};

        Queue(Node <T> *_head)
        :head(_head)
        ,tail(_head)
        ,currentSize(1)
        {};

        ~ Queue(){

                Node <T> *ptr = this -> head, *ptrPrev;

                while(ptr){

                        ptrPrev = ptr;
                        ptr = ptr -> getNext();
                        delete ptrPrev;

                };

        };
        void printQueue() {

                Node <T> *ptr = this -> head;
                int size = 0;
                while(ptr != NULL){
//                      std::cout << "key = " << ptr -> getData() << "time = " << (duration_cast<duration<double>>(high_resolution_clock::now - ptr -> getTime())).coun$                        ptr -> printNode();
                        ptr = ptr -> getNext();
                        size++;
                };

//              std::cout << "size = " << size << std::endl;

        };

        Node <T> *getHead() const {

                return this -> head;

        };
        Node <T> *getTail() const {

                return this -> tail;

        };

        int getCurrentSize() const{

                return this -> currentSize;

        };
        Node <T> get (const T &_key){

                Node <T> *ptr = this -> head;
                while(ptr -> getData() != _key){

                        ptr = ptr -> getNext();

                };

                return ptr;

        };
        void remove(const T &_key){

                if(this -> head -> getData() == _key){

                        Node <T> *ptr = this -> head;
                        this -> head = this -> head -> getNext();
                        delete ptr;
                        return;

                };

                Node <T> *tmp = this -> head, *tmpPrev;
                while(tmp -> getData() != _key){

                        tmpPrev = tmp;
                        tmp = tmp -> getNext();

                };

                tmpPrev -> setNext(tmp -> getNext());
                delete tmp;

                return;

        };


        void push(const T &_newTail){

                if(!(this -> head)){

                        this -> head = std::move(new Node <T> (_newTail, NULL));//, steady_clock::now()));
                        this -> tail = this -> head;
                        this -> currentSize = 1;
                        return;

                };

                this -> tail -> setNext(new Node <T> (_newTail, NULL));//, steady_clock::now()));
                this -> tail = this -> tail -> getNext();
                this -> currentSize++;

        };
        void pop() {

                if(this -> head == NULL){

                        return;

                };


                if(this -> head -> getNext() == NULL){

                        delete this -> head;
                        this -> head = NULL;
                        this -> tail = NULL;
                //      return;

                } else {

                        Node <T> *tmp = this -> head -> getNext();
                        delete this -> head;
                        this -> head = std::move(tmp);

                };

                this -> currentSize--;

        };


};


