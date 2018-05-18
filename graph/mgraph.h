//无向图MGraph.h															
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
	~MGraph();
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
		// 无向图两个节点都存储边信息
		auto n = new ArcNode;
		n->adjvex = a.first;
		n->next = vertex[a.second].firstedge;
		vertex[a.second].firstedge = n;  
	});   //存储图的边信息
}

template<typename T>
bool MGraph<T>::DFSTraverse(int v)
{
	if (v > vertex.size()-1)
		return false;
	vector<int> visited(GetNodeNum(),0);
	visited[v] = 1;
	cout << v << " ";
	deque<int> deq;
	deq.push_back(v);
	while (!deq.empty()) {
		int x = deq.back();
		ArcNode * node = vertex[x].firstedge;
		while (node && visited[node->adjvex] == 1)
		{
			node = node->next;
		}
		if (node && visited[node->adjvex] == 0){
			visited[node->adjvex] = 1;
			deq.push_back(node->adjvex);
			cout << node->adjvex << " ";
		}
		else
		{
			deq.pop_back();
		}
	}
	cout << endl;
	return true;
}

template<typename T>
bool MGraph<T>::BFSTraverse(int v)
{
	if (v > vertex.size() - 1)
		return false;
	vector<int> visited(GetNodeNum(), 0);
	visited[v] = 1;
	cout << v << " ";
	deque<int> deq;
	deq.push_back(v);

	int w, x;
	ArcNode * node;
	while (!deq.empty())
	{
		x = deq.front();
		node = vertex[x].firstedge;
		deq.pop_front();
		if (node != nullptr)
		{
			w = node->adjvex;
			while (1)
			{
				if (visited[w] == 0)
				{
					visited[w] = 1;
					cout << w << " ";
					deq.push_back(w);
				}
				if (node->next)
				{
					node = node->next;
					w = node->adjvex;
				}
				else
					break;
			}
		}
	}
	cout << endl;
	return true;
}

template<typename T>
MGraph<T>::~MGraph()
{
	ArcNode * temp = nullptr;
	ArcNode * temp1 = nullptr;
	for_each(vertex.begin(), vertex.end(), [&](auto p) 
	{
		temp = p.firstedge;
		while (temp) {
			temp1 = temp;
			temp = temp->next;
			free(temp1);
		}
	});
}

#endif