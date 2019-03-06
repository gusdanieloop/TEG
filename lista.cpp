#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Grafo
{
    private:
        int numVertices;
        list<int> *adj; 
    public:
        Grafo(int numVertices)
        {
            this->numVertices = numVertices;
            adj = new list<int>[numVertices]; //lista pra cada vertice
        }
        void adicionarAresta(int vertice1,int vertice2)
        {
            adj[vertice1].push_back(vertice2);
        }
        void toString()
        {
            
            for (int i = 0; i < this->numVertices; i++)
            {
                cout << i << " -> ";
                for(auto it = adj[i].begin(); it != adj[i].end(); ++it)
                {
                    cout << *it << " -> ";
                }
                cout << " -." <<endl; 
            }    
        }
};

int quantVertices(std::ifstream & file);
void preencherLista(std::ifstream & file, Grafo & grafo);

int main()
{
    std::ifstream file;
    int vertices = quantVertices(file);
    Grafo grafo(vertices);
    preencherLista(file,grafo);
    grafo.toString();

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

void preencherLista(std::ifstream & file, Grafo & grafo)
{
    file.open("arquivo.txt");
    if(file.is_open())
    {
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
                grafo.adicionarAresta(verticeorigem,arr[i-1]);
                token = strtok(NULL, " ");
            }
        }
    }
    file.close();
}
