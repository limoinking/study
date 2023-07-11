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
vector <int> g[MAXN];//��¼��������������Բ�����ʽǰ���ǣ���Ϊ������ͼ
bool cut[MAXN];//��¼�����Ŀ

int dfn[MAXN], low[MAXN], tim;
int st[MAXN], top;
bool inst[MAXN];
void tarjan(int u, int fa)//fa�Ǽ�¼���ڵ��õģ������ڵ��Ƿ����������Ϻ���
{
	dfn[u] = low[u] = ++tim;
	int child = 0;
	for (auto v : g[u])//�Զ�����
	{
		if (!dfn[v])
		{
			tarjan(v, fa);
			low[u] = min(low[u], low[v]);//����ǻ��ݵ�ʱ�򣬸����ӵ���Сֵ
			if (low[v] >= dfn[u] && u != fa)
			{
				//������Ǹ��ڵ����
				cut[u] = true;//����������ߴ洢�����ɱ����
				//���ܻᷴ����һ������Ϊ���
				//������bool���͵�������
			}
			if (u == fa)
			{
				child++;
			}
		}
		else
			low[u] = min(low[u], dfn[v]);//������ǻ��ݹ��̣�������̽Ѱ
		//�Ѿ����ʹ��Ľڵ�Ľ���ʱ��͵�ǰʱ�������������������Сʱ��
	}
	if (child >= 2 && u == fa)
	{
		cut[u] = true;//���ڵ������
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
			tarjan(i, i);//�������нڵ�����£���֤���
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