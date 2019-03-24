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
        void removerAresta(int vertice1, int vertice2)
        {
            list<int>::iterator v1 = find(adj[vertice1].begin(),adj[vertice1].end(),vertice2);
            *v1 = -1;
            list<int>::iterator v2 = find(adj[vertice2].begin(),adj[vertice2].end(),vertice1);
            *v2 = -1;
        }

        //verifica se todos tem conexão
        bool temConexao()
        {
            bool visitados[numVertices];
            int i;
            //setar todos os valores do vetor pra false
            memset(visitados,false,numVertices);

            //achar ponto de partida
            for(i = 0; i < numVertices; i++)
            {
                if(adj[i].size()!=0)//algum vertice que tem conexão com o resto
                    break;
            }

            //significa que nao há arestas
            if(i==numVertices)
            {
                return true;
            }

            //também conhecido como DFS
            preencherVisitados(i, visitados);

            for ( i = 0; i < numVertices; i++)
            {
                //verifica se nao foi visitado e tem aresta
                if( !visitados[i] && adj[i].size() > 0)
                {
                    //se nao foi visitado e tem arestas, é pq nao tem conexao
                    return false;

                }
            }
            return true;
        }

        //dfs
        void preencherVisitados(int i, bool visitados[])
        {
            //começa por esse, logo esse foi visitado
            visitados[i] = true;

            //recursividade
            list<int>::iterator iterador;
            for(iterador = adj[i].begin(); iterador != adj[i].end(); ++iterador)
            {
                if(!visitados[*iterador])
                {
                    preencherVisitados(*iterador,visitados);
                }
            }
        }

        //verifica se é euleriano, semi euleriano ou se não é
        int Euleriano()
        {
            if (temConexao() == false)
            {
                return 0;
            }

            int quantVerticesImpares = 0;
            for( int i = 0; i < numVertices; i++)
            {
                if (adj[i].size() & 1) //ultimo bit 1, significa impar
                {
                        quantVerticesImpares++;
                }
            }

            if ( quantVerticesImpares > 2) // significa que tem mais de dois vertices com grau impar, não é euleriano
            {
                return 0;
            }
            return (quantVerticesImpares)? 1 : 2; //retorna 1 se tiver pelo menos um impar, mesmo que sempre tera dois, pois não é direcional, retorna 1 se nao tiver impares, ou seja, euleriano 
            //caso tenha 2 impares, estes são o inicio e fim do caminho
        }

        ///a partir daqui é fleury
        void Fleury()
        {
            //achar vértice inicial, que é ou impar ou 0
            int u = 0;
            for( int i = 0; i < numVertices; i++)
            {
                if(adj[i].size() & 1) //impar
                {
                    u = i;
                    break;
                }
            }

            //começa com esse impar
            printFleury(u);
        }

        void printFleury(int u)
        {
            for(auto i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                int v = *i;
                if ( v!=-1 && naoPonte(u,v))
                {
                    cout << u << "-" << v << " ";
                    removerAresta(u,v);
                    printFleury(v);
                }
            }
        }

        bool naoPonte(int u, int v)
        {
            int contador = 0;
            for(auto i = adj[u].begin(); i != adj[u].end(); ++i)
            {
                if(*i != -1)
                {
                    contador++;
                }
            }
            //único caminho
            if( contador == 1)
            {
                return true;
            }

            //mais de um caminho
            bool visitados[numVertices];
            //setar tudo pra false
            memset(visitados,false,numVertices);
            int contador1 = consegueChegarQnt(u, visitados);
            removerAresta(u,v);
            memset(visitados,false,numVertices);
            int contador2 = consegueChegarQnt(u, visitados);

            adicionarAresta(u,v);
            adicionarAresta(v,u);

            //retorna falso se for ponte, retorna true se não for
            return (contador1 > contador2)? false: true;
        }

        int consegueChegarQnt(int v, bool visitados[])
        {
            //começa por ele, logo é true
            visitados[v] = true;
            int contador = 1;
            for(auto i = adj[v].begin(); i != adj[v].end(); ++i)
            {
                //se for um caminho nao removido e o vertice nao tiver sido visitado
                if(*i!= -1 && !visitados[*i])
                {
                    //recursividade
                    contador += consegueChegarQnt(*i, visitados);
                }
            }
            return contador;
        }

        //print lista
        void toString()
        {
            
            for (int i = 0; i < this->numVertices; i++)
            {
                cout << i << " => ";
                for(auto it = adj[i].begin(); it != adj[i].end(); ++it)
                {
                    cout << *it << " -> ";
                }
                cout << " -." <<endl; 
            }    
        }

        //destroi lista
        ~Grafo()
        {
            delete [] adj;
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
    int euler = grafo.Euleriano();
    if(euler == 0)
    {
        cout << "Não é euleriano" << endl;
    }
    else if(euler == 1)
    {
        cout << "É semi-euleriano" << endl;
        grafo.Fleury();
    }
    else
    {
        cout << "É euleriano" << endl;
        grafo.Fleury();
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
                grafo.adicionarAresta(verticeorigem,arr[i-1]);
                token = strtok(NULL, " ");
            }
        }
    }
    file.close();
}
