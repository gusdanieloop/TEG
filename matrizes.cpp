#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//CLASSES
class Adjacencia
{
    private:
        int numeroVertices;
        int** adjMatriz;
    public:
        Adjacencia(int numeroVertices)
        {
            this->numeroVertices = numeroVertices;
            adjMatriz = new int*[numeroVertices];
            for ( int i = 0; i < numeroVertices; i++)
            {
                adjMatriz[i] = new int[numeroVertices];
                for ( int j = 0; j < numeroVertices; j++)
                {
                    //deixar tudo zerado
                    adjMatriz[i][j] = 0;
                }
            }
        }

        int getVertices() const
        {
            return numeroVertices;
        }

        int** getMatriz() const
        {
            return adjMatriz;
        }

        void addAresta( int i, int j)
        {
            adjMatriz[i][j]++;
            
        }

        void removeAresta( int i, int j)
        { 
            adjMatriz[i][j]--;
        }

        bool isAresta(int i, int j)
        {
            return adjMatriz[i][j];
        }

        void toString()
        {
            cout << "   ";

            for ( int k = 0; k < numeroVertices; k++)
            {
                cout << k << " ";
            }
            cout << endl;
            for ( int i = 0; i < numeroVertices; i++)
            {
                cout << i << ": ";
                for ( int j = 0; j < numeroVertices; j++)
                {   
                    cout << adjMatriz[i][j] << " ";
                }
                cout << endl;
            }
        }

        ~Adjacencia()
        {
            for (int i = 0;i < numeroVertices; i++)
            {
                delete[] adjMatriz[i];
            }
            delete[] adjMatriz;
        }
};

class Incidencia
{
    private:
        int numeroVertices;
        int numeroArestas;
        int** incMatriz;
    public:
        Incidencia(int numeroVertices, int numeroArestas)
        {
            this->numeroVertices = numeroVertices;
            this->numeroArestas = numeroArestas;
            incMatriz = new int*[numeroArestas];
            for ( int i = 0; i < numeroArestas; i++)
            {
                incMatriz[i] = new int[numeroVertices];
                for ( int j = 0; j < numeroVertices; j++)
                {
                    //deixar tudo zerado
                    incMatriz[i][j] = 0;
                }
            }
        }

        int getVertices() const
        {
            return numeroVertices;
        }

        int getArestas() const
        {
            return numeroArestas;
        }

        int** getMatriz() const
        {
            return incMatriz;
        }

        void addAresta( int i, int j)
        {
            incMatriz[i][j]++;
        }

        void addArestaSaida(int i, int j)
        {
            incMatriz[i][j]++;
        }

        void addArestaEntrada(int i, int j)
        {
            incMatriz[i][j]--;
        }

        void removeAresta( int i, int j)
        {
            incMatriz[i][j]--;
        }

        bool isAresta(int i, int j)
        {
            return incMatriz[i][j];
        }

        void toString()
        {
            cout << "    ";

            for ( int k = 0; k < numeroVertices; k++)
            {
                cout << k << " ";
            }
            cout << endl;
            for ( int i = 0; i < numeroArestas; i++)
            {
                cout << "E" << i << ": ";
                for ( int j = 0; j < numeroVertices; j++)
                {   
                    cout << incMatriz[i][j] << " ";
                }
                cout << endl;
            }
        }

        ~Incidencia()
        {
            for (int i = 0;i < numeroVertices; i++)
            {
                delete[] incMatriz[i];
            }
            delete[] incMatriz;
        }
};

//MAIN

int quantVertices(std::ifstream & file);
void construirMatriz(Adjacencia & g, std::ifstream & file, bool direc);
int quantArestas(std::ifstream & file);
void construirMatrizInc(Incidencia & f, std::ifstream & file, bool direc);
int grauVA(Adjacencia & g, int vertice);
int grauVI(Incidencia & f, int vertice);
void mostrarGrau(Adjacencia & g);

int main()
{
    std::ifstream file;
    int sTotal = quantVertices(file);
    int aTotal = quantArestas(file);
    bool direc = true;
    Adjacencia g(sTotal);
    Incidencia f(sTotal, aTotal);
    construirMatriz(g,file,direc);
    construirMatrizInc(f,file,direc);
    cout<< "Matriz Adjacencia" <<endl;
    g.toString();
    //cout << "grau vertice 2 (começando em 0)" << endl;
    //cout << grauVA(g,4) << endl;
    cout << endl << endl << "Matriz Incidencia" << endl;
    f.toString();
    //cout << "grau vertice 2 (começando em 0)" << endl;
    //cout << grauVI(f,4) << endl;
    cout << endl << endl;
    mostrarGrau(g);
    g.~Adjacencia();
    f.~Incidencia();
    return 0;
}

//FUNCOES

int quantVertices(std::ifstream & file)
{
    string s;
    int sTotal = 0;
    file.open("arquivo.txt");
    while(!file.eof())
    {
        getline(file, s);
        sTotal++;
    }
    file.close();
    return sTotal;
}

void construirMatriz(Adjacencia & g, std::ifstream & file, bool direc)
{
    file.open("arquivo.txt");
    if (file.is_open())
    {
        std::string vertice;
        std::string destino;
        while (getline(file, vertice,':') && getline(file,destino))
        {
            int v = stoi(vertice);
            char* outrosVertices = const_cast<char *>(destino.c_str());
            char* token;
            token = strtok(outrosVertices, " ");
            int arr[destino.length()],i=0;
            while(token!=NULL)
            {
                arr[i++] = stoi(token);
                g.addAresta(v,arr[i-1]);
                token = strtok(NULL, " ");
            }
        }
    }
    file.close();
}

int quantArestas(std::ifstream & file)
{
    int vertices = quantVertices(file);
    int vetor[vertices][vertices];
    for ( int i = 0; i < vertices; i++)
    {
        for( int j = 0; j < vertices; j++)
        {
            vetor[i][j] = 0;
        }
    }
    int cont=0;
    file.open("arquivo.txt");
    if (file.is_open())
    {
        std::string vertice;
        std::string destino;
        while (getline(file, vertice, ':') && getline(file, destino))
        {
            int v = stoi(vertice);
            char* arestas = const_cast<char *>(destino.c_str());
            char* token;
            token = strtok(arestas, " ");
            int arr[destino.length()], i = 0;
            while(token!=NULL)
            {
                arr[i++] = stoi(token);
                if(vetor[arr[i-1]][v] != 1 && vetor[v][arr[i-1]] !=1)
                {
                    cont++;
                    vetor[arr[i-1]][v] = 1;
                    vetor[v][arr[i-1]] = 1;
                }
                token = strtok(NULL, " ");
            }
        }
    }
    file.close();
    return cont;
}

void construirMatrizInc(Incidencia & f, std::ifstream & file, bool direc)
{
    int vertices = f.getVertices();
    int arestas = f.getArestas();
    int vetor[arestas][vertices];
    for ( int i = 0; i < arestas; i++)
    {
        for ( int j = 0; j < vertices; j++)
        {
            vetor[i][j] = 0;
        }
    }

    int cont=0;
    file.open("arquivo.txt");
    if (file.is_open())
    {
        std::string vertice;
        std::string destino;
        while (getline(file, vertice,':') && getline(file,destino))
        {
            int v = stoi(vertice);
            char* outrosVertices = const_cast<char *>(destino.c_str());
            char* token;
            token = strtok(outrosVertices, " ");
            int arr[destino.length()],i=0;
            while(token!=NULL)
            {
                arr[i++] = stoi(token);
                if (vetor[arr[i-1]][v] !=1 && vetor[v][arr[i-1]]!=1)
                {
                    if(!direc)
                    {
                        f.addAresta(cont,arr[i-1]);
                        f.addAresta(cont,v);
                    }
                    else
                    {
                        if(v==arr[i-1] && vetor[v][v]!=1)
                        {
                            f.addAresta(cont,v);
                            vetor[v][v]=1;
                        }
                        if(v!=arr[i-1])
                        {
                            f.addArestaSaida(cont,v);
                            f.addArestaEntrada(cont,arr[i-1]);
                        }    
                    }
                    vetor[arr[i-1]][v]=1;
                    vetor[v][arr[i-1]]=1;
                    cont++;
                }
                token = strtok(NULL, " ");
                
            }
        }
    }
    file.close();
}

int grauVA(Adjacencia & g, int vertice)
{
    int** matriz = g.getMatriz();
    int cont=0;
    for(int i = 0; i < g.getVertices(); i++)
    {
        if(matriz[i][vertice]!=0)
        {
            cont++;
        }
    }
    return cont;
}

int grauVI(Incidencia & f, int vertice)
{
    int** matriz = f.getMatriz();
    int cont=0;
    for(int i = 0; i < f.getArestas(); i++)
    {
        if(matriz[i][vertice]!=0)
        {
            cont++;
        }
    }
    return cont;
}

void mostrarGrau(Adjacencia & g)
{
    int numVertices = g.getVertices();
    for (int i = 0; i < numVertices; i++)
    {
        cout << "Grau do vértice " << i << ": " << grauVA(g,i) << endl;
    }
}
