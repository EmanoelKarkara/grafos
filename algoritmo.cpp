/*
Algoritmo que calcula o custo da rota mais vantajosa entre duas cidades, 
onde o custo entre uma cidade e outra é dado por uma combinação linar dos 
valores da distância entre as cidades e do número médio de passageiros que 
fazem aquela rota. O algoritmo baseou-se na implementação do algoritmo de 
Dijkstra de Marcos Castro de Souza (https://github.com/marcoscastro).

Desenvolvido por Emanoel Dantas e Felipe Gilberto
*/

#include <iostream>		//cout
#include <fstream>      //ifstream
#include <string>		//string
#include <vector>		//vector
#include <list>			//list
#include <queue>		//priority_queue


using namespace std;

//Verifica se uma cidade está contida na lista de cidades
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

	//Abre o arquivo passado por parâmetro
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

  	ifs.close(); //Fecha o arquivo

  	int n_vertices = linhas.size()*2;
  	//Lista de cidades adjacentes para cada uma das cidades
  	list< pair<int, int> > * adjacentes = new list< pair<int, int> >[n_vertices];
	
	string distancia, n_passageiros;
	int cidade1, cidade2;

	while(!linhas.empty()){
		tmp = linhas.back();
		linhas.pop_back();

		//Lendo os valores de cada linha lida do arquivo
		cidade1 = stoi(tmp.substr(0, tmp.find_first_of(";")));
		tmp.erase(0, tmp.find_first_of(";")+1);

		cidade2 = stoi(tmp.substr(0, tmp.find_first_of(";")));
		tmp.erase(0, tmp.find_first_of(";")+1);

		distancia = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		n_passageiros = tmp;

		//Adiciona cidade1 na lista de cidades
		if(!contem(cidades, cidade1)){
			cidades.push_back(cidade1);
		}

		//Adiciona cidade2 na lista de cidades
		if(!contem(cidades, cidade2)){
			cidades.push_back(cidade2);
		}

		//Combinação linear da distância e número de passageiros no cálculo do custo
		int custo = (int) stoi(distancia) - stoi(n_passageiros);

		//Cria arco nos dois sentidos já que o grafo é não digigido
		adjacentes[cidade1].push_back(make_pair(cidade2, custo));
		adjacentes[cidade2].push_back(make_pair(cidade1, custo));

	}

	cout << "\nTemos as seguintes cidades:" << endl;

	//Exibe a lista de cidades
	for(int i = cidades.size()-1; i >= 0; i--){
		cout << cidades[i] << endl;
	}

	int origem, destino;

	cout << "\nEscolha a cidade origem: ";
	cin >> origem;
	cout << "Escolha a cidade destino: ";
	cin >> destino;

	int distancias[n_vertices];
	bool visitados[n_vertices];
	priority_queue < pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

	//Inicializando
	for(int i = 0; i < n_vertices; i++)
	{
		distancias[i] = 1000000;
		visitados[i] = false;
	}

	distancias[origem] = 0; //Distância da origem para a origem
	pq.push(make_pair(distancias[origem], origem));

	while(!pq.empty())
	{
		pair<int, int> p = pq.top(); 
		int u = p.second; 
		pq.pop(); 

		if(visitados[u] == false)
		{
			visitados[u] = true;
			list<pair<int, int> >::iterator it;

			for(it = adjacentes[u].begin(); it != adjacentes[u].end(); it++)
			{
				int v = it->first;
				int custo = it->second;

				if(distancias[v] > (distancias[u] + custo))
				{
					distancias[v] = distancias[u] + custo;
					pq.push(make_pair(distancias[v], v));
				}
			}
		}
	}

	cout << "\nA custo entre essas duas cidades é: " << distancias[destino] << endl << endl;

	return 0;
}