#include <iostream>		//cout
#include <fstream>      //ifstream
#include <string>		//string
#include <vector>		//vector

using namespace std;

struct rota{
	string cidade1;
	string cidade2;
	int distancia;
	int n_passageiros;
	float duracao;
};

int contem(vector<string> v, string cidade){
	for(int i = 0; i < v.size(); i++){
		if(v[i].compare(cidade) == 0) return i;
	}
	return -1;
};

int main(int argc, char ** argv){

	if(argc != 2){
		cout << "Falha ao executar!" << endl;
		cout << "Execute com: ./executavel arquivoDeEntrada" << endl;
		return 1;
	} 

	ifstream ifs (argv[1], ifstream::in);
	vector<string> cidades;
	vector< vector<rota> > adj;
	vector<rota> rotas;
	string tmp;
	rota r;

	//Lendo as linhas do arquivo
	while (!ifs.eof()) {
		getline(ifs,tmp);

		if(tmp.compare("") == 0) continue;

		r.cidade1 = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		r.cidade2 = tmp.substr(0, tmp.find_first_of(";"));
		tmp.erase(0, tmp.find_first_of(";")+1);

		r.distancia = stoi(tmp.substr(0, tmp.find_first_of(";")));
		tmp.erase(0, tmp.find_first_of(";")+1);

		r.n_passageiros = stoi(tmp.substr(0, tmp.find_first_of(";")));
		tmp.erase(0, tmp.find_first_of(";")+1);

		r.duracao = stof(tmp);

		int i1 = contem(cidades, r.cidade1);
		int i2 = contem(cidades, r.cidade2);

		if(i1 == -1){
			cidades.push_back(r.cidade1);
			rotas.push_back(r);
			adj.push_back(rotas);
			rotas.pop_back();
		}else{
			adj[i1].push_back(r);
		}

		if(i2 == -1){
			cidades.push_back(r.cidade2);
			rotas.push_back(r);
			adj.push_back(rotas);
			rotas.pop_back();
		}else{
			adj[i2].push_back(r);
		}

  	}

  	ifs.close();

  	cout << "\nEscolhendo a rota mais vantajosa entre duas cidades:" << endl;
  	cout << "Menu de cidades:" << endl;
	for(int i = 0; i < cidades.size(); i++){
		cout << i << " - " << cidades[i] << endl;
	}	

	string origem, destino;

	cout << "\nEscolha a cidade de origem: ";
	cin >> origem;
	cout << "Escolha a cidade de destino: ";
	cin >> destino;

	

	return 0;
}