
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "ICash.h"

template <template <class,class> class IDictionary> void generateCash(ICash <IDictionary,std::string,int> *cash){
        std::ifstream myfile("animals.txt");
        std::vector <int> randomNumbers(200);
        for(int i = 0; i < 200; i++){
                randomNumbers[i] = i;
        }
        std::random_shuffle (randomNumbers.begin(), randomNumbers.end());
        if(myfile.is_open()){
                std::string line;
                int n = 0;
                while(std::getline(myfile, line)){
                        cash -> add(line, randomNumbers[n]);
                        n++;
                };
        };
        myfile.close();
};
int main(){
        ICash<TwoHashDictionary,std::string,int> *cash = new ICash <TwoHashDictionary,std::string,int> (100);
//      ICash<SimpleDictionary,std::string,int> *cash = new ICash <SimpleDictionary,std::string,int> (100);
        generateCash(cash);
        cash -> printQueue();
        std::cout<<std::endl<<std::endl;
        cash -> printTable();
        std::cout<<std::endl<<std::endl;
        delete cash;
        return 0;
};
