#include <iostream>
#include <chrono>

#include "IDictionary.h"
#include "Queue.h"

template <class Key, class Element> class ICash{
private:

        SimpleDictionary <Key,Element> *table;
        Queue <Key> *queue;//time_t
        std::chrono::duration <double> maxTime = std::chrono::duration <double> (0.01);

public:

        ICash(int _size)
        :table(new SimpleDictionary <Key,Element> (_size))
        ,queue(new Queue <Key> ())
        {};

        ~ ICash(){

                delete table;
                delete queue;

        };

        void printTable(){
                table -> printDictionary();
        };

        void printQueue(){
                queue -> printQueue();
        };

        void add(const Key &_key, const Element &_element){

                if(this -> queue -> getHead() != NULL){

//                      std::cout << "head != NULL" << std::endl;
/*
                        if(duration_cast<duration<double>>(high_resolution_clock::now() - (queue -> getHead() -> getTime())) >= maxTime){

                                std::cout << ">>" << std::endl;

                        };
*/
                        while((this -> queue -> getCurrentSize() > this -> table -> getMaxSize()) || (this -> queue -> getHead()) && (duration_cast<duration<double>>(h$
//                              std::cout << "delete " << std::endl;
                                table -> remove(queue -> getHead() -> getData());
//                              std::cout << "remove" << std::endl;
                                queue -> pop();
//                              std::cout << "pop" << std::endl;

                        };
//                      std::cout <<"after while" << std::endl;
                };
                this -> queue -> push(_key);
//              std::cout << "push"<< std::endl;
                this -> table -> add(_key, _element);

        };

/*      int getCurrentSize() const {

                return this -> table -> getCurrentSize();

        };
*/
        void remove(const Key &_key){

                queue -> remove(_key);
                table -> remove(_key);
        };

};
