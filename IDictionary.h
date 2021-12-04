#include <iostream>

#include "DynamicArray.h"
//#include "LinkedList.h"
#include "Item.h"


template <class Key, class Element> class IDictionary{
public:

        virtual int getCount() const = 0;
        virtual int getCapacity() const = 0;

        virtual bool existsKey(Key _key) const = 0;
        virtual bool isEmpty() const = 0;

        virtual Element& get(const Key &_key) const = 0;
        virtual void add(const Key &_key, const Element &_element) = 0;
        virtual void remove(const Key _key) = 0;

};

template <class Key, class Element> class SimpleDictionary: public IDictionary <Key,Element>{
private:

        DynamicArray <Item<Key,Element>> *data;
        int size;
        int capacity;
        int maxSize;

public:

        ~ SimpleDictionary(){
                delete data;
        };

        SimpleDictionary(int _size); //

        SimpleDictionary(int _size); //

        int getCount() const override; //
        int getCapacity() const override; //
        int getMaxSize() const;

        bool existsKey(Key _key) const override; //
        bool isEmpty() const override; //

        Element& get(const Key &_key) const override;//
        void add(const Key &_key, const Element &_element) override;//
        void remove(const Key _key) override;//
        void resize();//
        void printDictionary() const;

        int hashFunction(const Key &_key) const;// const override;//
};


template <class Key, class Element> void SimpleDictionary <Key,Element>::printDictionary() const{

        for(int i = 0; i < this -> capacity; i++){

                if(!(this -> data -> get(i).isEmpty())){

                        std::cout << "key = " << this -> data -> get(i).getKey() << " value = " << this -> data -> get(i).getElement() << std::endl;

                } else if (this -> data -> get(i).isDeleted()){

                        std::cout << "deleted pair" << std::endl;

                } else{

                        std::cout << "empty pair" << std::endl;

                };

        };

};
template <class Key, class Element> int SimpleDictionary <Key,Element>::getMaxSize() const{

        return this -> maxSize;

};



template <class Key, class Element> int SimpleDictionary <Key,Element>::hashFunction (const Key &_key) const {

        return (std::hash<Key>{}(_key)) % (this -> capacity + 1);

};


template <class Key, class Element> void SimpleDictionary <Key,Element>::remove(const Key _key) {

///Тут переписать и сделать в начале проверку что такой ключ есть

        int index = hashFunction(_key);
//      bool keyExists = false;

        for(int i = index; i < this -> capacity; i++){

                if((this -> data -> get(i)).getKey() == _key){

//                      keyExists = true;
//                      delete this -> data -> get(i);
                        Item <Key,Element> t;
                        this -> data -> set(i, t);//Item <Key,Element> ());
                        this -> data -> get(i).setDeleted();
                        return;

                };


        };

//      std::cout << "Key not found" << std::endl;

};

template <class Key, class Element> void SimpleDictionary <Key,Element>::add(const Key &_key, const Element &_element){

        int index = hashFunction(_key);
        Item <Key,Element> p(_key, _element);
        bool keyUnFree = false;

        if(this -> data -> get(index).isEmpty()){

                this -> data -> set(index, p);
                this -> size++;
                return;

        };

        for(int i = index; i < this -> capacity; i++){

                while(!(this -> data -> get(i).isEmpty())){

                        i++;

                };

                if(i >= this -> capacity){

                        this -> resize();
                        add(_key, _element);
                        break;

                } else {

                        this -> data -> set(i, p);
                        break;

                };

        };

        this -> size++;
        return;

};

template <class Key, class Element> SimpleDictionary <Key,Element>::SimpleDictionary(int _size)
        :size(0)
        ,capacity(_size * 3)
        ,maxSize(_size)
        ,data(new DynamicArray <Item<Key,Element>> (_size * 3))
        {
        };


template <class Key, class Element> int SimpleDictionary <Key,Element>::getCount() const {

        return this -> size;

};

template <class Key, class Element> int SimpleDictionary <Key,Element>::getCapacity() const {

        return this -> capacity;

};

template <class Key, class Element> bool SimpleDictionary <Key,Element>::existsKey(Key _key) const{

        for(int i = 0; i < this -> capacity; i++){

                if(!(this -> data -> get(i).isEmpty())){

                        if(this -> data -> get(i).getKey() == _key){
                                return true;
                        };

                };

        };

        return false;

};

template <class Key, class Element> bool SimpleDictionary <Key,Element>::isEmpty() const{

        bool empty = true;

        for(int i = 0; i < this -> capacity; i++){

                if(!(this -> data -> get(i).isEmpty())){
                        return false;
                };

        };

        return true;

};

template <class Key, class Element> Element& SimpleDictionary <Key,Element>::get(const Key &_key) const {

        if(!(this -> isEmpty())){

                int index = hashFunction(_key);

                if(!(this -> data -> get(index).isEmpty())){

                        while(this -> data -> get(index).getKey() != _key){
                                index++;
                        };

                        return this -> data -> get(index).getElement();

                };

        };

};


template <class Key, class Element> void SimpleDictionary <Key,Element>::resize(){

        int oldCapacity = this -> capacity;
        this -> capacity *= 3;

        DynamicArray <Item<Key,Element>> *array = new DynamicArray <Item<Key,Element>> (this -> capacity);

        for(int i = 0; i < oldCapacity; i++){

                if(!(this -> data -> get(i).isEmpty())){

                        int newIndex = hashFunction(data -> get(i).getKey());

                        while(!(array -> get(newIndex).isEmpty())){

                                newIndex++;

                        };

                        array -> set(newIndex, *(new Item <Key,Element> (data -> get(i).getKey(), data -> get(i).getElement())));

                };

        };

        delete this -> data;
        this -> data = std::move(array);
};
