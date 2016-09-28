// http://www.spoj.com/problems/TOPOSORT/

#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define ll long long
#define ff first
#define ss second

//  10^3  10^6
int nodes,edges,cycle;
vector<vector<int> >graph;
vector<int>visited;
stack<int>topostack;
vector<int>instack;

void isCycle(int u)
{
	if(visited[u]==1)
	{
		if(instack[u]==1)
			{cycle=1;return;}
		return;
	}
	if(cycle)return;

	visited[u]=1;
	instack[u]=1;

	for (int i = 0; i < graph[u].size(); ++i)
	{
		int v=graph[u][i];
		isCycle(v);
	}
	instack[u]=0;
}

void topoSorting(int u)
{
	if(visited[u]==1)
		return;
	visited[u]=1;
	// all neighbors of u node
	for (int i = 0; i < graph[u].size(); ++i)
	{
		int v = graph[u][i];
		if(visited[v]==0)
			topoSorting(v);
	}
	topostack.push(u);
}

int main(int argc, char const *argv[])
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(0);
	int u,v;

	cin>>nodes>>edges;
	graph.resize(nodes+1);
	visited.resize(nodes+1);
	instack.resize(nodes+1);

	for (int i = 0; i < edges; ++i)
	{
		cin>>u>>v;
		graph[u].pb(v);
	}
	for (int i = 1; i <= nodes; ++i)
	{
		sort(graph[i].rbegin(), graph[i].rend());
	}

	for (int i = 1; i <= nodes; ++i)
	{
		if(visited[i]==0)
			isCycle(i);
	}
	if(cycle==1)
	{cout<<"Sandro fails.";return 0;}
	
	fill(visited.begin(), visited.end(),0);

	for (int i = nodes; i >=1; --i)
	{
		if(visited[i]==0)
			topoSorting(i);
	}

	while(!topostack.empty())
		cout<<topostack.top()<<" ",topostack.pop();
	
	return 0;
}