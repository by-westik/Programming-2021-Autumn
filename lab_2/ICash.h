#include <iostream>
#include <chrono>
#include "IDictionary.h"
#include "Queue.h"

template <template <class,class> class IDictionary, class Key, class Element> class ICash{
private:
        IDictionary <Key,Element> *table;
        Queue <Key> *queue;//time_t
        std::chrono::duration <double> maxTime = std::chrono::duration <double> (0.01);
public:
        ICash(int _size)
        :table(new IDictionary <Key,Element> (_size))
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
                        while((this -> queue -> getCurrentSize() >= this -> table -> getMaxSize()) || (this -> queue -> getHead()) && (duration_cast<duration<double>>(high_resolution_clock::now() - (queue -> getHead() -> getTime()))) >= maxTime ){
                                table -> remove(queue -> getHead() -> getData());
                                queue -> pop();
                        };
                };
                this -> queue -> push(_key);
                this -> table -> add(_key, _element);
        };
        
        int getCurrentSize() const {
                return this -> table -> getCount();
        };

        void remove(const Key &_key){
                queue -> remove(_key);
                table -> remove(_key);
        };
};
