#include <iostream>
#include <bits/stdc++.h>

using namespace std;


class Grafo
{
    private:
        int numVertices;
        vector<vector<int>> adj;
    public:
        Grafo(int numVertices)
        {
            this->numVertices = numVertices;
            adj.resize(numVertices);
        }
        void preencherVetor(std::ifstream & file)
        {
            file.open("arquivo.txt");
            if(file.is_open())
            {
                int cont=0;
                std::string vertice1;
                std::string vertices;
                while(getline(file, vertice1,':') && getline(file,vertices))
                {
                    int verticeorigem = stoi(vertice1);
                    char* verticesdestino = const_cast<char *>(vertices.c_str());
                    char* token;
                    token = strtok(verticesdestino, " ");
                    int arr[vertices.length()],i=0;
                    while(token!=NULL)
                    {
                        arr[i++] = stoi(token);
                        token = strtok(NULL, " ");
                    }
                    adj.push_back(i);
                    for(int j = 0; j < i ; j++)
                    {
                        adj[cont].push_back(arr[j]);
                    }
                    cont++;
                }
            }
            file.close();
        }
};

int quantVertices(std::ifstream & file);

int main()
{  
    std::ifstream file;
    Grafo g(quantVertices(file));
    g.preencherVetor(file);
    return 0;
}

int quantVertices(std::ifstream & file)
{
    string s;
    int verticesTotais = 0;
    file.open("arquivo.txt");
    while(!file.eof())
    {
        getline(file,s);
        verticesTotais++;
    }
    file.close();
    return verticesTotais;
}

