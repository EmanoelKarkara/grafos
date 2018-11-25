/*
* Implementação de uma modificação do algoritmo de Dijkstra
* baseado na implementação de Marcos Castro de Souza (https://github.com/marcoscastro).
* Desenvolvido por Emanoel Dantas e Felipe Gilberto
*/

#include <iostream>		//cout
#include <fstream>      //ifstream
#include <string>		//string
#include <list>
#include <queue>
#include <set>

#define INFINITO 10000000

using namespace std;

class Grafo
{
private:
	int V; // número de vértices

	// ponteiro para um array contendo as listas de adjacências
	list<pair<int, int> > * adj;
	list<pair<int, float> > * adj_complementar;

public:

	// construtor
	Grafo(int V)
	{
		this->V = V; // atribui o número de vértices

		/*
			cria as listas onde cada lista é uma lista de pairs
			onde cada pair é formado pelo vértice destino e o custo
		*/
		adj = new list<pair<int, int> >[V];
		adj_complementar = new list<pair<int, float> >[V];
	}

	// adiciona uma aresta ao grafo de v1 à v2
	void addAresta(int v1, int v2, int custo, int n_passageiros, float duracao)
	{
		adj[v1].push_back(make_pair(v2, custo));
		adj_complementar[v1].push_back(make_pair(n_passageiros, duracao));
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest)
	{
		// vetor de distâncias
		int dist[V];

		/*
		   vetor de visitados serve para caso o vértice já tenha sido
		   expandido (visitado), não expandir mais
		*/
		int visitados[V];

		// fila de prioridades de pair (distancia, vértice)
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		// inicia o vetor de distâncias e visitados
		for(int i = 0; i < V; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		// a distância de orig para orig é 0
		dist[orig] = 0;

		// insere na fila
		pq.push(make_pair(dist[orig], orig));

		// loop do algoritmo
		while(!pq.empty())
		{
			pair<int, int> p = pq.top(); // extrai o pair do topo
			int u = p.second; // obtém o vértice do pair
			pq.pop(); // remove da fila

			// verifica se o vértice não foi expandido
			if(visitados[u] == false)
			{
				// marca como visitado
				visitados[u] = true;

				list<pair<int, int> >::iterator it;
				list<pair<int, float> >::iterator it_complementar;

				// percorre os vértices "v" adjacentes de "u"
				for(it = adj[u].begin(), it_complementar = adj_complementar[u].begin(); it != adj[u].end(); it++, it_complementar++)
				{
					// obtém o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;
					int n_passageiros = it_complementar->first;
					float duracao = it_complementar->first;

					// relaxamento (u, v)
					if(dist[v] > (dist[u] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}

		// retorna a distância mínima até o destino
		return dist[dest];
	}
};

int main(int argc, char ** argv){

	if(argc != 2){
		cout << "Falha ao executar!" << endl;
		cout << "Execute com: ./executavel arquivoDeEntrada" << endl;
		return 1;
	} 

	ifstream ifs (argv[1], ifstream::in);
	list<string> linhas;
	string tmp;

	//Lendo as linhas do arquivo
	while (!ifs.eof()) {
		getline(ifs,tmp);
		if(tmp.size() != 0){
			linhas.push_back(tmp);
		}
  	}	

  	ifs.close();

  	Grafo g(linhas.size()*2);
	string cidade1, cidade2, distancia, n_passageiros, duracao;

	while(!linhas.empty()){
		tmp = linhas.back();
		linhas.pop_back();

		cidade1 = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		cidade2 = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		distancia = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		n_passageiros = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		duracao = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		g.addAresta(stoi(cidade1), stoi(cidade2), stoi(distancia), stoi(n_passageiros), stof(duracao));
		g.addAresta(stoi(cidade2), stoi(cidade1), stoi(distancia), stoi(n_passageiros), stof(duracao));	
	}

	cout << g.dijkstra(1, 0) << endl;
	cout << g.dijkstra(0, 1) << endl;
	cout << g.dijkstra(1, 1) << endl;
	return 0;
}