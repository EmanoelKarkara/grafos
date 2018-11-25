/*
* Usando algoritmo de Dijkstra implementado por
* Marcos Castro de Souza (https://github.com/marcoscastro)
* para calcular o custo da rota mais curta entre duas cidades,
* onde o custo entre uma cidade e outra é dado por uma combinação
* linar dos valores da distância entre as cidades, do número médio 
* de passageiros que fazem aquela rota e do tempo de duração de viagem.
*
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
	}

	// adiciona uma aresta ao grafo de v1 à v2
	void addAresta(int v1, int v2, int custo)
	{
		adj[v1].push_back(make_pair(v2, custo));
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

				// percorre os vértices "v" adjacentes de "u"
				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					// obtém o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

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

bool contem(vector<int> v, int cidade){
	for(int i = 0; i < v.size(); i++){
		if(v[i] == cidade) return true;
	}
	return false;
}

int main(int argc, char ** argv){

	if(argc != 2){
		cout << "Falha ao executar!" << endl;
		cout << "Execute com: ./executavel arquivoDeEntrada" << endl;
		return 1;
	} 

	ifstream ifs (argv[1], ifstream::in);
	list<string> linhas;
	vector<int> cidades;
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
	string distancia, n_passageiros, duracao;
	int cidade1, cidade2;

	while(!linhas.empty()){
		tmp = linhas.back();
		linhas.pop_back();

		cidade1 = stoi(tmp.substr(0, tmp.find_first_of(";")));
		tmp.erase(0, tmp.find_first_of(";")+1);

		cidade2 = stoi(tmp.substr(0, tmp.find_first_of(";")));
		tmp.erase(0, tmp.find_first_of(";")+1);

		distancia = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		n_passageiros = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		duracao = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		if(!contem(cidades, cidade1)){
			cidades.push_back(cidade1);
		}

		if(!contem(cidades, cidade2)){
			cidades.push_back(cidade2);
		}

		int custo = (int) stoi(distancia) + stof(duracao) - stoi(n_passageiros);

		g.addAresta(cidade1, cidade2, custo);
		g.addAresta(cidade2, cidade1, custo);	
	}

	cout << "\nTemos as seguintes cidades:" << endl;

	for(int i = cidades.size()-1; i >= 0; i--){
		cout << cidades[i] << endl;
	}

	int c1, c2;

	cout << "\nEscolha a cidade origem: ";
	cin >> c1;
	cout << "Escolha a cidade destino: ";
	cin >> c2;

	cout << "\nA custo entre essas duas cidades é: " << g.dijkstra(c1, c2) << endl << endl;

	return 0;
}