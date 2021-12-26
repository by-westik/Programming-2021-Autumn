#include <iostream>
#include <vector>
#include <queue>
#include <stack>

const int MAX = 1000;

class WeightedDirectedGraph{
private:
        std::vector <std::vector<std::pair<int,int>>> adjList;

public:

        WeightedDirectedGraph()
        :adjList(std::move (std::vector <std::vector<std::pair<int,int>>> ()))
        {
        };

        void addNode(int first, int second, int weight){
                if (adjList.size() <= std::max(first, second)){
                        adjList.resize(std::max(first,second));
                };
                adjList[first].push_back(std::make_pair(second,weight));
        };

        void printGraph() const{
                for(int i = 0; i < adjList.size(); i++){
                        for(auto j = adjList[i].begin(); j != adjList[i].end(); j++){
                                if(!adjList[i].empty()){
                                        std::cout << "   " << j -> second << std::endl;
                                        std::cout << i << " -> " << j -> first << std::endl;
                                };
                        };
                };
        };


        void dex(int node){
                std::vector <int> distances(adjList.size() + 1, MAX);
                distances[node] = 0;
                std::queue <std::pair<int,int>> queue;
                queue.push(std::make_pair(0,node));
                while(!queue.empty()){
                        std::pair <int,int> p = queue.front();
                        queue.pop();
                        if(p.first > distances[p.second]){
                                continue;
                        };
                        for(int i = 0; i < adjList[p.second].size(); i++){
                                int index = adjList[p.second][i].first, newDist = distances[p.second] + adjList[p.second][i].second;
                                if(distances[index] > newDist){
                                        distances[index] = newDist;
                                        queue.push(std::make_pair(distances[index], index));
                                };

                        };

                };
                for(int i = 1; i < adjList.size() + 1; i++){
                        std::cout << distances[i] << " ";
                };
                std::cout << std::endl;
        };

        void bfs(){
                bool visited[adjList.size()];
                for(int i = 0; i < adjList.size(); i++){
                        visited[i] = false;
                };
                int src = 1;
                for(int i = 0; i < adjList.size(); i++){
                        if(!adjList[i].empty()){
                                src = i;
                                break;
                        };
                };
                std::cout << src << " ";
                visited[src] = true;
                std::queue <int> queue;
                queue.push(src);
                while(!queue.empty()){
                        int ptr = queue.front();
                        for(auto it = adjList[ptr].begin(); it != adjList[ptr].end(); it++){
                                if(!visited[it -> first]){
                                        visited[it -> first] = true;
                                        std::cout << it -> first << " ";
                                        queue.push(it -> first);
                                };
                        };
                        queue.pop();
                };
                std::cout << std::endl;
        };

        void dfs(){
                bool visited[adjList.size()];
                for(int i = 0; i < adjList.size(); i++){
                        visited[i] = false;
                };
                int src = 1;
                for(int i = 0; i < adjList.size(); i++){
                        if(!adjList[i].empty()){
                                src = i;
                                break;
                        };
                };
                std::cout << src << " ";
                visited[src] = true;
                std::stack <int> stack;
                stack.push(src);
                while(!stack.empty()){
                        int ptr = stack.top();
                        stack.pop();
                        if(!visited[ptr]){
                                visited[ptr] = true;
                                std::cout << ptr << " ";
                        };
                        for(auto it = adjList[ptr].begin(); it != adjList[ptr].end(); it++){
                                if(!visited[it -> first]){
                                        stack.push(it -> first);
                                };
                        };
                };
                std::cout << std::endl;
        };

        void ford(int node){
                std::vector <int> distances(adjList.size() + 1, MAX);
                distances[node] = 0;
                for(int i = 0; i < adjList.size() + 1; i++){
                        for(int j = 0; j < adjList.size() + 1; j++){
                                auto start = adjList[j].begin();
                                while(start != adjList[j].end()){
                                        if(distances[j] == MAX){
                                                start++;
                                                continue;
                                        };

                                        if(start -> second + distances[j] < distances[start -> first]){
                                                distances[start -> first] = start -> second + distances[j];
                                        };
                                        start++;
                                };
                        };
                };

                for(int i = 0; i < adjList.size() + 1; i++){
                        auto it = adjList[i].begin();
                        while(it != adjList[i].end()){
                                if(it -> second + distances[i] < distances[it -> first]){
                                        std::cout << "Negative cycle" << std::endl;
                                };
                                it++;
                        };
                };

                for(int i = 1; i < adjList.size() + 1; i++){
                        std::cout << distances[i] << " ";// << std::endl;
                };
                std::cout << std::endl;
        };

};


int main(){

        WeightedDirectedGraph *g = new WeightedDirectedGraph ();
        g -> addNode(1,2,4);
        g -> addNode(1,3,3);
        g -> addNode(1,4,5);
        g -> addNode(2,5,6);
        g -> addNode(3,6,5);
        g -> addNode(3,7,8);
        g -> printGraph();
        g -> bfs();
        g -> dfs();
        for(int i = 1; i < 8; i++){
                std::cout << "node = " << i << " " << std::endl;
                g -> dex(i);
                g -> ford(i);
        };
//      delete g;
        return 0;
};


