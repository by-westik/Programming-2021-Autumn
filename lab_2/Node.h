#include <chrono>
using namespace std::chrono;

template <class T> class Node{
private:

        T data;
        Node *next;
        high_resolution_clock::time_point startTime;

public:
        Node()
        :next(NULL)
        ,startTime(high_resolution_clock::now())
        {};

        Node(const T &_data, Node *_next)
        :data(std::move(_data))
        ,next(_next)
        ,startTime(high_resolution_clock::now())
        {};

        void printNode(){

                std::cout << "key = " << this -> getData();
                duration <double> liveTime = duration_cast <duration<double>> (high_resolution_clock::now() - this -> getTime());
                std::cout << " liveTime = " << liveTime.count() << std::endl;

        };

        void setData(const T &_data){

                this -> data = std::move(_data);

        };
        void setNext(Node *_next){

                this -> next = _next;

        };

        T getData() const{

                return this -> data;

        };

        Node* getNext() const{

                return this -> next;

        };

        void setTime() {

                this -> startTime = high_resolution_clock::now();

        };


        high_resolution_clock::time_point getTime() const {

                return this -> startTime;

        };

};