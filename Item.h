#include <iostream>

template <class Key, class Element> class Item{
private:

        Key key;
        Element element;
        bool empty;
        bool deleted;

public:

        Item();
        Item(const Key &_key, const Element &_element);

//        ~Item;

        Key& getKey();
        Element& getElement();

        void setKey(const Key& _key);
        void setElement(const Element& _element);
        void setDeleted();

        bool isEmpty() const;
        bool isDeleted() const;

//Переопределить оператор (вывода в поток и) чтения с потока
};

template <class Key, class Element> void Item <Key,Element>::setDeleted() {

        this -> deleted = true;

};

template <class Key, class Element> std::ostream& operator<< (std::ostream &out, const Item <Key,Element> &_item){

        out << "[ " << _item.getKey() << " " << _item.getElement() << " ]";
        return out;

};

template <class Key, class Element> Item <Key,Element>::Item()
        :empty(true)
        ,deleted(false)
        {
        };

template <class Key, class Element> Item <Key,Element>::Item(const Key &_key, const Element &_element)
        :key(std::move(_key))
        ,element(std::move(_element))
        ,empty(false)
        ,deleted(false)
        {
        };


template <class Key, class Element> Key& Item <Key,Element>::getKey() {

        return this -> key;

};

template <class Key, class Element> Element& Item <Key,Element>::getElement() {

        return this -> element;

};

template <class Key, class Element> void Item <Key,Element>::setKey(const Key &_key){

        this -> key = std::move(_key);

};

template <class Key, class Element> void Item <Key,Element>::setElement(const Element &_element){

        this -> element = std::move(_element);

};

template <class Key, class Element> bool Item <Key,Element>::isEmpty() const{

        return this -> empty;

};

template <class Key, class Element> bool Item <Key,Element>::isDeleted() const{

        return this -> deleted;

};

