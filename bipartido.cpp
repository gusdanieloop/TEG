#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Grafo{
    private:
        int numVertices;
        list<int> *adj;
    public:
        //construir e destruir
        Grafo(int numVertices);
        ~Grafo();

        //Adicionar / Remover Arestas
        void addAresta(int u, int v);
        void rmAresta(int u, int v);

        //verificar se tem ciclo impar
        bool verifCicloImpar(int indice);

        //print
        void toString();
};

Grafo::Grafo(int numVertices)
{
    this->numVertices = numVertices;
    this->adj = new list<int>[numVertices];
}

Grafo::~Grafo()
{
    delete [] adj;
}

void Grafo::addAresta(int u, int v)
{
    adj[u].push_back(v);
}

void Grafo::rmAresta(int u, int v)
{
    list<int>::iterator v1 = find(adj[u].begin(),adj[u].end(),v);
    *v1 = -1;
    list<int>::iterator v2 = find(adj[v].begin(),adj[v].end(),u);
    *v2 = -1;
}

bool Grafo::verifCicloImpar(int src)
{
    //vetor de cores dos vertices
    int cores[numVertices];
    //setando tudo para -1
    for ( int i = 0; i < numVertices; i++)
    {
        cores[i] = -1;
    }
    //origem fica com 1
    cores[src] = 1;

    list<int> lista;
    lista.push_back(src);

    while(!lista.empty())
    {
        int origem = lista.front();
        lista.pop_front();

        for(auto i = adj[origem].begin(); i != adj[origem].end(); i++)
        {
            //ciclo 1
            if( *i == origem)
            {
                return true;
            }
            // adjacente sem cor ainda
            if( cores[*i] == -1)
            {
                // ex: origem ta com 1, logo esse vai ter 0, se fosse 0, seria 1
                cores[*i] = 1 - cores[origem];
                lista.push_back(*i);
            }
            //se o adjacente tiver msm cor
            else if( cores[*i] == cores[origem])
            {
                return true;
            }
        }
    }
    //nao deu nada errado
    return false;
}

void Grafo::toString()
{
    for(int i = 0; i < numVertices; i++)
    {
        cout << i << "=> ";
        for (auto j = adj[i].begin(); j != adj[i].end(); j++)
        {
            cout << *j << " => ";
        }
        cout << " -." << endl;
    }
}

int quantVertices(std::ifstream & file);
void preencherLista(std::ifstream & file, Grafo & grafo);

int main()
{
    std::ifstream file;
    int vertices = quantVertices(file);
    Grafo grafo(vertices);
    preencherLista(file,grafo);
    grafo.toString();
    //true se tiver impar
    if(grafo.verifCicloImpar(0))
    {
        cout << "Não é bipartido" << endl;
    }
    else
    {
        cout << "É bipartido" << endl;
    }
    
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
                grafo.addAresta(verticeorigem,arr[i-1]);
                token = strtok(NULL, " ");
            }
        }
    }
    file.close();
}
