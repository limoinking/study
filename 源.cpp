#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define MAXN 20100
#define MAXM 100010
#define inf  2147483647
typedef long long ll;
int n, m, ans;
vector <int> g[MAXN];//记录出入点的情况，可以不用链式前行星，因为是无向图
bool cut[MAXN];//记录割点数目

int dfn[MAXN], low[MAXN], tim;
int st[MAXN], top;
bool inst[MAXN];
void tarjan(int u, int fa)//fa是记录根节点用的，看根节点是否有两个以上孩子
{
	dfn[u] = low[u] = ++tim;
	int child = 0;
	for (auto v : g[u])//自动迭代
	{
		if (!dfn[v])
		{
			tarjan(v, fa);
			low[u] = min(low[u], low[v]);//这个是回溯的时候，更新子的最小值
			if (low[v] >= dfn[u] && u != fa)
			{
				//如果不是根节点情况
				cut[u] = true;//由于是无向边存储，不可避免的
				//可能会反复将一个点作为割点
				//所以用bool类型的来处理
			}
			if (u == fa)
			{
				child++;
			}
		}
		else
			low[u] = min(low[u], dfn[v]);//这个不是回溯过程，而是在探寻
		//已经访问过的节点的进入时间和当前时间相比来更新这个点的最小时间
	}
	if (child >= 2 && u == fa)
	{
		cut[u] = true;//根节点的特批
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++)
	{
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) 
			tarjan(i, i);//遍历所有节点情况下，保证输出
	for (int i = 1; i <= n; i++)
		if (cut[i]) ans++;
	cout << ans << endl;
	for (int i = 1; i <= n; i++)
	{
		if (cut[i])
			cout << i << " ";
	}
	cout << endl;
	return 0;
}