#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "ICash.h"

void generateCash(ICash <std::string,int> *cash){

        std::ifstream myfile("animals.txt");
        std::vector <int> randomNumbers(200);// = new std::vector <int> (200);//generateRandomNumbers(200);
        for(int i = 0; i < 200; i++){
                randomNumbers[i] = i;
        };

        std::random_shuffle (randomNumbers.begin(), randomNumbers.end());

        if(myfile.is_open()){

                std::string line;
                int n = 0;

                while(std::getline(myfile, line)){
                        cash -> add(line, randomNumbers[n]);
                        n++;
                };

//      std::cout << "n = " << n << std::endl;

        };
        myfile.close();

};

int main(){

        //ICash<int,std::string> *cash = new ICash <int,std::string> (100);
        ICash<std::string,int> *cash = new ICash <std::string,int> (100);
        generateCash(cash);
        cash -> printQueue();
        std::cout<<std::endl<<std::endl;
        cash -> printTable();
        std::cout<<std::endl<<std::endl;
        delete cash;

        return 0;
};