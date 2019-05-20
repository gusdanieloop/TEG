#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Grafo
{
    private:
        int numVertices;
        list<pair<int,int>> *listaAdjacencia;
    public:
        Grafo(int numVertices); 
        void adicionar(int origem, int distancia, int destino);
        void dijkstra(int origem, int objetivo);
};

Grafo::Grafo(int numVertices)
{
    this->numVertices = numVertices;
    this->listaAdjacencia = new list<pair<int,int>> [numVertices];
}

void Grafo::adicionar(int origem, int distancia, int destino)
{
    this->listaAdjacencia[origem].push_back(make_pair(distancia, destino));
}

void Grafo::dijkstra(int origem, int objetivo)
{
    priority_queue <pair<int, int>> pq;
    int distancia[numVertices];
    int pai[numVertices];

    distancia[0] = 0;
    for(int i = 1; i < numVertices; ++i)
    {
        distancia[i] = numeric_limits<int>::max();
    }

    pq.push(make_pair(distancia[origem], origem));

    while(!pq.empty())
    {
        int menor_valor = pq.top().second;
        pq.pop();

        for(auto i = listaAdjacencia[menor_valor].begin(); i != listaAdjacencia[menor_valor].end(); ++i)
        {
            int dist = (*i).first;
            int destino = (*i).second;

            if(distancia[destino] > distancia[menor_valor] + dist)
            {
                pai[destino] = menor_valor;
                distancia[destino] = distancia[menor_valor] + dist;
                pq.push(make_pair(distancia[destino], destino));
            }
        }
    }
    
    list<int> caminho;

    while(objetivo != origem)
    {
        caminho.push_front(objetivo);
        for(auto i = listaAdjacencia[pai[objetivo]].begin(); i != listaAdjacencia[pai[objetivo]].end(); ++i)
        {
            if((*i).second == objetivo)
            {
                listaAdjacencia[pai[objetivo]].remove(*i);
                break;
            }
        }
        objetivo = pai[objetivo];
    }
    caminho.push_front(origem);
    
    for(auto i = caminho.begin(); i != caminho.end(); ++i)
    {
        cout << " " << *i;
    }
    cout << endl;
}

int main()
{
    Grafo grafo = Grafo(4);
    grafo.adicionar(0,6,3);
    grafo.adicionar(0,3,1);
    grafo.adicionar(1,1,2);
    grafo.adicionar(2,1,3);
    grafo.dijkstra(0,3);
    puts("esse foi o menor!");
    grafo.dijkstra(0,3);
    puts("esse o segundo menor!");
    return 0;
}