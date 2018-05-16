//文件名MGraph.h															
#ifndef MGRAPH_H
#define MGRAPH_H

#include<iostream>
#include<vector>
using namespace std;

struct ArcNode {
	int adjvex;
	struct ArcNode * next;
};

template<typename T>
struct VerNode {
	T data;
	struct ArcNode * firstedge;
};

template<typename T>
class MGraph
{
private:
	int vertexNum;  // 无向图的顶点数
	int arcNum;     // 无向图的边数
	vector<VerNode<T>> vertex;
public:
	MGraph();//邻接矩阵存储，建立具有n个顶点e条边的图
	~MGraph() {}//析构函数为空
	void DFSTraverse1(int v);//递归深度遍历
	void DFSTraverse0(int v);//非递归
	void BFSTraverse(int v);
};

template<class T>
MGraph<T>::MGraph()
{
	cout << "Please input the number of graph'node: " << endl;
	cin >> vertexNum;
	VerNode<T> ver;
	ver.firstedge = nullptr;
	for (int i = 0; i < vertexNum; i++)  //存储图的顶点信息
	{
		cin >> ver.data;
		vertex.emplace_back(cin);
	}

	cout << "Please input the number of graph'arc: " << endl;
	cin >> arcNum;
	for (int i,int j, int k = 0; k<arcNum; k++)//存储图的边信息
	{
		cout << "请输入边的两个顶点的序号: " << endl;
		cin >> i >> j;
		ArcNode *s = new ArcNode;
		s->adjvex = j;
		s->next = nullptr;
		

	}
}

#endif