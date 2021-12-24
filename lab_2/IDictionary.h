#include <iostream>

#include "DynamicArray.h"
#include "Item.h"

template <class Key, class Element> class IDictionary{
public:
        virtual int getCount() const = 0;
        virtual int getCapacity() const = 0;
        virtual int getMaxSize() const = 0;

        virtual bool existsKey(const Key &_key) const = 0;
        virtual bool isEmpty() const = 0;

        virtual Element& get(const Key &_key) const = 0;
        virtual void add(const Key &_key, const Element &_element) = 0;
        virtual void remove(const Key &_key) = 0;

};

template <class Key, class Element> class TwoHashDictionary: public IDictionary <Key,Element>{
private:
        DynamicArray <Item<Key,Element>> *data;
        int size;
        int capacity;
        int maxSize;
public:
        TwoHashDictionary (int _size);
        ~TwoHashDictionary(){
                delete data;
        };

        int getCount() const override; //
        int getCapacity() const override; //
        int getMaxSize() const override;

        bool existsKey(const Key &_key) const override; //
        bool isEmpty() const override; //

        Element& get(const Key &_key) const override;//
        void add(const Key &_key, const Element &_element) override;//
        void remove(const Key &_key) override;//
        void resize();//
        void printDictionary() const;

        int hashFunction(const Key &_key) const;// const override;//
        int secondHashFunction(const Key &_key) const;

};

template <class Key, class Element> TwoHashDictionary <Key,Element>::TwoHashDictionary(int _size)
        :size(0)
        ,capacity(_size * 3)
        ,maxSize(_size)
        ,data(new DynamicArray <Item<Key,Element>> (_size * 3))
        {};

template <class Key, class Element> int TwoHashDictionary <Key,Element>::getCount() const{
        return this -> size;
};

template <class Key, class Element> int TwoHashDictionary <Key,Element>::getCapacity() const{
        return this -> capacity;
};

template <class Key, class Element> int TwoHashDictionary <Key,Element>::getMaxSize() const{
        return this -> maxSize;
};

template <class Key, class Element> bool TwoHashDictionary <Key,Element>::existsKey(const Key &_key) const{

        for(int i = 0; i < this -> capacity; i++){
                if(!(this -> data -> get(i).isEmpty())){
                        if(this -> data -> get(i).getKey() == _key){
                                return true;
                        };
                };
        };

        return false;
};

template <class Key, class Element> bool TwoHashDictionary <Key,Element>::isEmpty() const{
        bool empty = true;
        for(int i = 0; i < this -> capacity; i++){
                if(!(this -> data -> get(i).isEmpty())){
                        return false;
                };
        };
        return true;
};

template <class Key, class Element> Element& TwoHashDictionary <Key,Element>::get(const Key &_key) const{
        if(!(this -> isEmpty())){
                int index = this -> hashFunction(_key);
                int secondIndex = this -> secondHashFunction(_key);

                for(int i = 0; i < this -> capacity; i++){
                        if(index + i * secondIndex >= this -> capacity){
                                std::cout << "There is not this key in hashTable (get)" << std::endl;
                                break;
                        };
                        if(!(this -> data -> get(index + secondIndex * i).isEmpty()) && !(this -> data -> get(index + secondIndex * i).isDeleted())){
                                return this -> data -> get(index + secondIndex * i).getElement();
                        };
                };
        };
};

template <class Key, class Element> void TwoHashDictionary <Key,Element>::add(const Key &_key, const Element &_element){
        int index = this -> hashFunction(_key);
        Item <Key,Element> p(_key, _element);
        int secondIndex = this -> secondHashFunction(_key);
        for(int i = 0; i < this -> capacity; i++){
                if(index + i * secondIndex >= this -> capacity){
                        this -> resize();
                        this -> add(_key, _element);
                        break;
                }
                if(this -> data -> get(index + secondIndex * i).isEmpty() && !(this -> data -> get(index + secondIndex * i).isDeleted())){
                        this -> data -> set(index + secondIndex * i, p);
                        break;
                };
        };
        this -> size++;
        return;
};

template <class Key, class Element> void TwoHashDictionary <Key,Element>::remove(const Key &_key){
        int index = this -> hashFunction(_key);
        int secondIndex = this -> secondHashFunction(_key);
        for(int i = 0; i < this -> capacity; i++){
                if(index + i * secondIndex >= this -> capacity){
                        std::cout << "There is not this key in hashTable (remove)" << std::endl;
                        return;
                }

                if(!(this -> data -> get(index + secondIndex * i).isEmpty()) && !(this -> data -> get(index + secondIndex * i).isDeleted())){
                        Item <Key,Element> t;
                        this -> data -> set(index + secondIndex * i, t);//Item <Key,Element> ());
                        this -> data -> get(index + secondIndex * i).setDeleted();
                        this -> size--;
                        return;
                };
        };
};

template <class Key, class Element> void TwoHashDictionary <Key,Element>::resize(){
        int oldCapacity = this -> capacity;
        this -> capacity = oldCapacity * 2;
        DynamicArray <Item<Key,Element>> *array = new DynamicArray <Item<Key,Element>> (this -> capacity);
        for(int i = 0; i < oldCapacity; i++){
                if(!(this -> data -> get(i).isEmpty())){
                        int newIndex = this -> hashFunction(this -> data -> get(i).getKey());
                        for(int j = 0; j < oldCapacity; j++){
                                if(newIndex >= this -> capacity){
                                        this -> capacity *=2;
                                        array -> resize(this -> capacity);
                                };
                                if(!(array -> get(newIndex).isEmpty())){
                                        newIndex = newIndex + j * this -> secondHashFunction(this -> data -> get(i).getKey());
                                } else {
                                        break;
                                };
                        };
                        array -> set(newIndex, *(new Item <Key,Element> (data -> get(i).getKey(), data -> get(i).getElement())));
                };
        };
        delete this -> data;
        this -> data = std::move(array);
};

template <class Key, class Element> void TwoHashDictionary <Key,Element>::printDictionary() const{
        for(int i = 0; i < this -> capacity; i++){
                if(!(this -> data -> get(i).isEmpty())){
                        std::cout << "key = " << this -> data -> get(i).getKey() << " value = " << this -> data -> get(i).getElement() << " index = " << i << std::endl;                } else if(this -> data -> get(i).isDeleted()){
                        std::cout << "deleted pair in index = " << i << std::endl;
                } else {
                        std::cout << "empty pait in index = " << i << std::endl;
                };
        };
};

template <class Key, class Element> int TwoHashDictionary <Key,Element>::secondHashFunction(const Key &_key) const{
        return (std::hash<Key> {}(_key)) % (this -> capacity) + 1;
};

const int PRIME_CONST = 31;
const int DEL_CONST = 19;

template <> int TwoHashDictionary <std::string,int>::hashFunction(const std::string &_key) const{
        size_t index = 0;
        for(int i = 0; i < _key.length(); i++){
                index += (_key[i] * (int)std::pow(PRIME_CONST, i)) % DEL_CONST;
        }

        return index % (this -> capacity);
};

const int SECOND_DEL_CONST = 67;

template <> int TwoHashDictionary <std::string,int>::secondHashFunction (const std::string &_key) const{
        size_t hash = 5381;
        for(int i = 0; i < _key.length(); i++){
                hash = ((hash << 5) + hash + _key[i]) % SECOND_DEL_CONST;
        };
        return hash % (this -> capacity) + 1;
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

        int getCount() const override; //
        int getCapacity() const override; //
        int getMaxSize() const override;

        bool existsKey(const Key &_key) const override; //
        bool isEmpty() const override; //

        Element& get(const Key &_key) const override;//
        void add(const Key &_key, const Element &_element) override;//
        void remove(const Key &_key) override;//
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

template <class Key, class Element> void SimpleDictionary <Key,Element>::remove(const Key &_key) {
        int index = hashFunction(_key);
        for(int i = index; i < this -> capacity; i++){
                if((this -> data -> get(i)).getKey() == _key){
                        Item <Key,Element> t;
                        this -> data -> set(i, t);//Item <Key,Element> ());
                        this -> data -> get(i).setDeleted();
                        return;
                };
        };
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

template <class Key, class Element> bool SimpleDictionary <Key,Element>::existsKey(const Key &_key) const{
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
                        int newIndex = this -> hashFunction(this -> data -> get(i).getKey());
                        while(!(array -> get(newIndex).isEmpty())){
                                newIndex++;
                        };
                        array -> set(newIndex, *(new Item <Key,Element> (data -> get(i).getKey(), data -> get(i).getElement())));
                };
        };
        delete this -> data;
        this -> data = std::move(array);
};
