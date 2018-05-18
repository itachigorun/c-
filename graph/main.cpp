#include<vector>
#include<map>
#include"MGraph.h"


int main()
{
	vector<int> vec;
	for (int i = 0; i<11; i++)
		vec.emplace_back(i);
	multimap<int, int> setarc;
	setarc.insert(pair<int, int>(0, 1));
	setarc.insert(pair<int, int>(1, 2));
	setarc.insert(pair<int, int>(2, 3));
	setarc.insert(pair<int, int>(0, 4));
	setarc.insert(pair<int, int>(1, 5));
	setarc.insert(pair<int, int>(2, 6));
	setarc.insert(pair<int, int>(4, 5));
	setarc.insert(pair<int, int>(5, 6));
	setarc.insert(pair<int, int>(4, 7));
	setarc.insert(pair<int, int>(6, 8));
	setarc.insert(pair<int, int>(7, 8));
	setarc.insert(pair<int, int>(7, 9));
	setarc.insert(pair<int, int>(8, 10));
	MGraph<int> graph(vec, setarc);

	graph.DFSTraverse(0);
	graph.BFSTraverse(0);

	return 0;
}