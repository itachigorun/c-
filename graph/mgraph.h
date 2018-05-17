//文件名MGraph.h															
#ifndef MGRAPH_H
#define MGRAPH_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<deque>
using namespace std;

struct ArcNode {
	int adjvex;
	ArcNode * next;
};

template<typename T>
struct VerNode {
	T data;
	ArcNode * firstedge;
};

template<typename T>
class MGraph
{
private:
	vector<VerNode<T>> vertex;
public:
	MGraph(vector<T> ver_in, multimap<int, int> arc_input);//邻接矩阵存储，建立具有n个顶点e条边的图
	~MGraph() {}//析构函数为空
	bool DFSTraverse(int v);
	bool BFSTraverse(int v);
	int GetNodeNum();
};
template<typename T>
int MGraph<T>::GetNodeNum()
{
	return vertex.size();
}

template<typename T>
MGraph<T>::MGraph(vector<T> ver_input, multimap<int,int> arc_input)
{
	VerNode<T> ver;
	ver.firstedge = nullptr;
	for_each(ver_input.begin(), ver_input.end(), [&](T temp)
	{
		ver.data = temp;
		vertex.emplace_back(ver);
	});  //存储图的顶点信息
	
	for_each(arc_input.rbegin(), arc_input.rend(), [&](auto a)
	{
		auto s = new ArcNode;
		s->adjvex = a.second;
		s->next = vertex[a.first].firstedge;
		vertex[a.first].firstedge = s;
	});   //存储图的边信息
}

template<typename T>
bool MGraph<T>::DFSTraverse(int v)
{
	if (v > vertex.size()-1)
		return false;
	vector<int> visited(GetNodeNum(),0);
	visited[v] = 1;
	cout << v << endl;
	deque<int> deq;
	deq.push_back(v);
	while (!deq.empty()) {
		int x = deq.front();
		if (vertex[x].firstedge && visited[vertex[x].firstedge->adjvex] == 0){
			visited[vertex[x].firstedge->adjvex] = 1;
			deq.push_back(vertex[x].firstedge->adjvex);
			cout << vertex[x].firstedge->adjvex << endl;
		}
		else {
			deq.pop_back();
		}
	}
	return true;
}

template<typename T>
bool MGraph<T>::BFSTraverse(int v)
{
	if (v > vertex.size() - 1)
		return false;
	vector<int> visited(GetNodeNum(), 0);
	visited[v] = 1;
	cout << v << endl;
	deque<int> deq;
	deq.push_back(v);

	int w;
	int x;
	ArcNode * node;
	while (!deq.empty())
	{
		x = deq.front();
		node = vertex[x].firstedge;
		deq.pop_back();
		if (node != nullptr)
		{
			w = node->adjvex;
			while (1)
			{
				if (visited[w] == 0)
				{
					visited[w] = 1;
					cout << w << endl;

					deq.push_back(w);
				}
				if (node->next)
				{
					w = node->adjvex;
					node = node->next;
				}
				else
					break;
			}
		}
	}
	return true;
}
#endif