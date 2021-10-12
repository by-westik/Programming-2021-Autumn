#include <iostream>

class Item{
public:
        int data;
        Item *next;
        Item(){};
        Item(const int& _data, Item* _next = NULL)
        :data(_data)
        ,next(_next)
        {
        };

        int getData(){
                return this -> data;
        };

        Item *getNext(){
                return this -> next;
        };

        void setNext(Item *_next){
                this -> next = std::move(_next);
        };

        void setData(int _data){
                this -> data = std::move(_data);
        };
};

class LinkedList{
public:
        Item *head;
        int size;
        LinkedList()
        :head()
        ,size()
        {
        };

        ~LinkedList(){
                Item *ptr = this -> head, *ptr_pred = this -> head;
                while(ptr){
                        ptr = ptr -> getNext();
                        delete ptr_pred;
                        ptr_pred = ptr;
                };
        };

        Item *getHead(){
                return this -> head;
        };

        void append(int value){
                Item *newHead = new Item(value, head);
                this -> head = newHead;
                this -> size++;
        };

        void prepend(int value){
                Item *newTail = new Item(value, NULL);

                if(!head){
                        this -> head = newTail;
                } else {
                        Item *ptr = this -> head;

                        while(ptr -> getNext() != NULL){
                                ptr = ptr -> getNext();
                        };

                        ptr -> setNext(newTail);
                };

                this -> size++;
        };

        void printList(){
                Item *ptr = this -> head;

                while(ptr != NULL){
                        std::cout << ptr -> getData() << " ";
                        ptr = ptr -> getNext();
                };

                std::cout << std::endl;
        };

        Item *getTail(){
                Item *ptr = this -> head;

                while(ptr -> getNext() != NULL){
                        ptr = ptr -> getNext();
                };

                return ptr;
        };
        Item *quickSort(Item *start, Item *end){

                if(start == end){
                        return end;
                };

                if(start -> next == end){

                        if(start -> data > end -> data){
                                start -> next = end -> next;
                                end -> next = start;
                                return end;
                        };

                        return start;
                };
                Item *current = start, *previous = NULL, *pivot = end, *newHead = NULL, *newEnd = end, *newTail = end, *previousPivot = NULL;
                if((start != end) && (start != NULL)){
                        while(current != pivot){
                                if(current -> data <= pivot -> data){
                                        if(newHead == NULL){
                                                std::cout << "newHead != NULL" << std::endl;
                                                newHead = current;
                                        };
                                        previous = current;
                                        current = current -> next;
                                } else {
//                                      std::cout << "current > pivot" << std::endl;
                                        if(previous != NULL){
                                                previous -> next = current -> next;
                                        };
                                        Item *ptr = current -> next;
                                        newTail -> next = current;
                                        current -> next = NULL;
                                        newTail = newTail -> next;
                                        current = ptr;
                                };
                        };
                        if(newHead == NULL){
                                std::cout << "newHead = NULL" << std::endl;
                                newHead = pivot;
                        };

                        newEnd = newTail;

                        if(newHead != pivot){
                                std::cout << "newHead new Tail before quickSort = " << newHead -> data << "    " << newTail -> data << std::endl;
                                newHead = quickSort(newHead, previous);
                                std::cout <<  "newHead new Tail after quickSort = " << newHead -> data << "    " << newTail -> data << std::endl;
                        };
Item *pivotNext = quickSort(pivot -> next, newTail);
                        pivot -> next = pivotNext;

                        return newHead;
                };
        };
};

int main(){
        LinkedList *list = new LinkedList();
//      list -> prepend(8);
  //   list -> prepend(10);
        list -> prepend(7);
list -> prepend(-1);
//list -> prepend(-2);
        list -> prepend(6);
        list -> prepend(5);
        list -> prepend(3);
        list -> prepend(2);
        list -> prepend(4);
        std::cout << "head = " << list -> getHead() -> data << " tail = " << list -> getTail() -> data<< std::endl;
        list -> head = list -> quickSort(list -> getHead(), list -> getTail());//, list -> getTail());
       std::cout << "head = " << list -> getHead() -> data << " tail = " << list -> getTail() -> data<< std::endl;
//      std::cout << list -> head -> data << std::endl;
        list -> printList();
        std::cout << "exit" << std::endl;
        return 0;
};
