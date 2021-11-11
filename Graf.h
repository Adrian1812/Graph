#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;


class Graf
{

private:

	int nr_noduri;
	int nr_muchii;
	int start;
	vector<vector<int>> lista;
	

public:

	int get_nr_noduri() { return nr_noduri; }
	void set_nr_noduri(int n) { nr_noduri = n; }

	int get_nr_muchii() { return nr_muchii; }
	void set_nr_muchii(int m) { nr_muchii = m; }

	int get_start() { return start; }
	void set_start(int s) { start = s; }

	Graf(){}

	void citire_graf_dfs() {

		ifstream f("dfs.in");
		int x, y;
		f >> nr_noduri;
		f >> nr_muchii;

		lista.resize(get_nr_noduri() + 1);


		while (f >> x >> y) {

			lista[x].push_back(y);
			lista[y].push_back(x);
			
		}

		f.close();
	}

	void citire_graf_bfs() {
		
		ifstream f("bfs.in");
		int x, y;
		f >> nr_noduri;
		f >> nr_muchii;
		f >> start;

		lista.resize(get_nr_noduri() + 1);

		while (f >> x >> y) {

			lista[x].push_back(y);
		}
	}

	void bfs(int start) {

		queue<int>coada;
		int x;

		vector<int> vizit;
		for (int i = 0; i <= nr_noduri; i++) { vizit.push_back(-1); }

		coada.push(start);
		vizit[start] = 0;

		while (!coada.empty()) {

			x = coada.front();
			coada.pop();

			for (int i = 0; i < lista[x].size(); i++) {

				if (vizit[lista[x][i]] == -1) {

					coada.push(lista[x][i]);
					vizit[lista[x][i]] = vizit[x] + 1;
				}
			}
		}

		ofstream g("bfs.out");
		for (int i = 1; i <= nr_noduri; i++) {

			g << vizit[i] << " ";
		}
		g.close();
	}

	void dfs(int start, vector<int>& vizit) {

		int v;
		stack<int>st;
		int x;

		st.push(start);
		vizit[start] = 1;

		while (!st.empty()) {

			x = st.top();
			v = 0;


			for (int i = 0; i < lista[x].size(); i++) {


				if (vizit[lista[x][i]] == 0) {

					v = lista[x][i];
					break;
				}
			}


			if (v == 0) { st.pop(); }
			else {

				st.push(v);
				vizit[v] = 1;
			}
		}
	}

	
	void comp_conexe() {

		citire_graf_dfs();

		vector<int> vizit;
		for (int i = 0; i <= nr_noduri ; i++) { vizit.push_back(0); }

		int count = 0;
		
		for (int i = 1; i <= nr_noduri ; i++) {

			if (vizit[i] == 0) {

				dfs(i, vizit);
				count++;
			}
			
		}

		ofstream g("dfs.out");
		g << count;
		g.close();
	}

	void dfs_topologic(int start, vector<int>& vizit, vector<int>& topo) {

		int v;
		stack<int>st;
		int x;

		st.push(start);
		vizit[start] = 1;

		while (!st.empty()) {

			x = st.top();
			v = 0;


			for (int i = 0; i < lista[x].size(); i++) {


				if (vizit[lista[x][i]] == 0) {

					v = lista[x][i];
					break;
				}
			}


			if (v == 0) { topo.push_back(st.top()); st.pop(); }
			else {

				st.push(v);
				vizit[v] = 1;
			}
		}
	}

	void citire_ST() {

		ifstream f("sortaret.in");
		int x, y;
		f >> nr_noduri;
		f >> nr_muchii;


		lista.resize(get_nr_noduri() + 1);


		while (f >> x >> y) {

			lista[x].push_back(y);

		}
		f.close();
	}

	void SortareTopologica() {

		citire_ST();

		vector<int> topo;
		vector<int> vizit;

		for (int i = 0; i <= nr_noduri; i++) { vizit.push_back(0); }

		for (int i = 1; i <= nr_noduri; i++) {

			if (vizit[i] == 0) {

				dfs_topologic(i, vizit, topo);

			}

		}

		ofstream g("sortaret.out");
		for (int i = topo.size() - 1; i >= 0; i--) {

			g << topo[i] << " ";
		}
		g.close();
	}

	void HavelHakimi() {

		ifstream f("havel.in");
		int x;

		vector<int> v;

		while (f >> x) {

			v.push_back(x);
		}

		
		
		int ok = 0;
		int fst;

		while (ok == 0) {


			sort(v.begin(), v.end(), greater<>());

			if (v[0] == 0) { ok = 1; break; }

			fst = v[0];
			v.erase(v.begin() + 0);

			if (fst > v.size()) { break; }


			for (int i = 0; i < v.size(); i++) {

				v[i]--;

				if (v[i] < 0) { break; }
			}

		}


		ofstream g("havel.out");
		if (ok == 0) {

			g << "NU";
		}
		else { g << "DA"; }

		g.close();
	}
	void citire_muchie_critica(int& m, vector<vector<int>>& connections) {

		int x, y;
		cin >> m;

		connections.resize(m + 1);

		for (int i = 0; i < m; i++) {

			cin >> x >> y;

			connections.push_back({ x,y });
		}
	}

	void muchie_critica(int& n, vector<vector<int>>& connections) {

		int m;
		cin >> n;
		cin >> m;

		citire_muchie_critica(m, connections);

	}

	void df(int i, vector<int>&vizit, vector<int>&nivel, vector<int>&nivel_min, vector<vector<int>> lista, vector<vector<int>>&muchii) {


		vizit[i] = 1;
		nivel_min[i] = nivel[i];

		for (int j = 0; j < lista[i].size(); j++) {

			if (vizit[lista[i][j]] == 0) {

				nivel[lista[i][j]] = nivel[i] + 1;

				df(lista[i][j], vizit, nivel, nivel_min, lista, muchii);

				nivel_min[i] = min(nivel_min[i], nivel_min[lista[i][j]]);

				if (nivel_min[lista[i][j]] > nivel[i]) { muchii.push_back({ i, lista[i][j] }); }

			}
			else {

				if (nivel[lista[i][j]] < nivel[i] - 1) { nivel_min[i] = min(nivel_min[i], nivel[lista[i][j]]); }
			}

		}


	}

	vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {

		//vector<vector<int>> connections;
		muchie_critica(n, connections);

		vector<vector<int>>lista, muchii;
		lista.resize(n + 1);

		for (int i = 0; i < connections.size(); i++) {

			lista[connections[i][0]].push_back(connections[i][1]);
			lista[connections[i][1]].push_back(connections[i][0]);
		}


		vector<int>vizit, nivel_min, nivel;

		for (int i = 0; i <= n; i++) { vizit.push_back(0); nivel.push_back(0); nivel_min.push_back(0); }


		df(0, vizit, nivel, nivel_min, lista, muchii);

		return muchii;

	}



};

