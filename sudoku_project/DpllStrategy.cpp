#include "Settings.h"


int abs(int x)
{
	return x > 0 ? x : -x;
}

//分析，采用基本的情况进行变元处理，比较基础
//在多个值没有找到合适变元的情况会
status MyStartegy1(CHead** C)//最优策略初始化
{
	PHead dcur = *C;
	PNode rcur = NULL;
	int x, pos = 0;
	double max = 0.0;
	while (dcur != NULL)
	{
		rcur = dcur->right;
		while (rcur != NULL)
		{
			x = rcur->data;
			if (counter[x].count > max)
			{
				max = counter[x].count;
				pos = x;
			}
			rcur = rcur->next;
		}
		dcur = dcur->down;
	}
	if (pos == 0)
		pos = (*C)->right->data;//用优化方法没找到决策变元时,也就是直接将第一个变元作为目标变元
	if (counter[pos].positive > counter[pos].negative)
		return pos;//正值频率大于负值，返回正值作为决策变元 
	else
		return -pos;
}




//为了提高运行速度，现在引入JW优化策略
// 这里提前声明一下，加权的选取策略，由于越长的子句越不易处理，所以优先选择更加简单的子句
// 所以采用2^(-子句长度)，来作为加权进行传递

//第一种优化，选取短子句进行优化
int JW1(CHead** C)//短子句优化,根据变元所在子句长度和次数来总和考虑，和mystrategy几乎一样
{
	double* w = (double*)malloc(sizeof(double) * (n1 + 2));
	if (w == NULL)
		exit(-1);
	for (int i = 0; i <= n1; i++)
	{
		w[i] = 0.0;
	}//初始化
	PHead pc = NULL;
	PNode pn = NULL;
	for (pc = (*C); pc; pc = pc->down)
	{
		for (pn = pc->right; pn; pn = pn->next)
		{
			w[abs(pn->data)] += pow(2.0, double(-(pc->info)));//变元数目和子句长度
		}
	}
	double maxW = 0;
	int maxBool = 0;
	for (int i = 1; i <= n1; i++)
	{
		if (w[i] > maxW)
			maxW = w[i], maxBool = i;//寻找当前优化策略下面的最大变元
	}
	free(w);
	return maxBool;
}

int JW2(CHead** C)//JW方法
{
	//第二种策略将正负变元J(x)+J(-x)+a * (min(J(x),J(-x)))中a设置为0，进行修正，当然
	//a的值可以进行调整
	//这个就相当于是学习率
	//学习率先设为0，后期再进行调整
	//统计正负变元出现的总数
	index* w = (index*)malloc(sizeof(index) * (n1 + 2));
	if (w == NULL)
		exit(-1);
	for (int i = 0; i <= n1; i++)
	{
		w[i].negative = 0, w[i].positive = 0;
	}
	PHead pc = NULL;
	PNode pn = NULL;
	for (pc = (*C); pc; pc = pc->down)
	{
		for (pn = pc->right; pn; pn = pn->next)
		{
			if (pn->data > 0)
				w[abs(pn->data)].positive += pow(2.0, double(-(pc->info)));//变元数目和子句长度
			else
				w[abs(pn->data)].negative += pow(2.0, double(-(pc->info)));
		}
	}
	double maxW = 0;
	int maxBool = 0;
	for (int i = 1; i <= n1; i++)
	{
		double total = w[i].negative + w[i].positive + a * fmin(w[i].negative, w[i].positive);
		if (total > maxW)
		{
			maxW = total, maxBool = i;
		}
	}
	if (w[maxBool].positive < w[maxBool].negative)
	{
		maxBool = -maxBool;
	}
	free(w);
	return maxBool;
}

int JW3(CHead** C)
{
	//这个算法可以处理负号变元比较多的情况，因为实现逻辑是，先找到负变元中出现次数最多的
	// 然后如果没有负号变元，就再去找正变元
	//并且，数独中负变元比较多，所以优先处理负变元，然后简化
	index* cnt = (index*)malloc(sizeof(index) * (n1 + 2));
	PHead pc = NULL;
	PNode pn = NULL;
	for (pc = (*C); pc; pc = pc->down)
	{
		for (pn = pc->right; pn; pn = pn->next)
		{
			if (pn->data > 0)
			{
				cnt[abs(pn->data)].positive++;
			}
			else
			{
				cnt[abs(pn->data)].negative++;
			}
		}
	}
	int maxTime = 0;
	int maxBool = 0;
	for (int i = 1; i <= n1; i++)//先看变元素的个数，先处理负的变元，注意到负的变元比较多
	{
		if (cnt[i].negative > maxTime)
		{
			maxTime = cnt[i].negative, maxBool = -i;
		}
	}
	if (maxTime == 0)
	{
		for (int i = 1; i <= n1; i++)
		{
			if (cnt[i].positive > maxTime)
			{
				maxTime = cnt[i].positive, maxBool = i;
			}
		}
	}
	free(cnt);
	return maxBool;
}


int JW4(CHead** C)//短子句元素处理
{
	//最后一种，用来处理短子句多且易删除的子句的
	//简要陈述一下逻辑，先找到最短子句
	//在最短子句中找到出现次数最多的元素（正负加在一块）
	//然后返回该变元
	static int count = 0;
	int minBool = n1;
	int* cnt = (int*)malloc((n1 + 1) * sizeof(int));
	for (int i = 0; i < n1; i++)
		cnt[i] = 0;
	PHead pc = NULL;
	PNode pn = NULL;
	for (pc = (*C); pc; pc = pc->down)
	{
		if (pc->info < minBool)
			minBool = pc->info;//寻找最短子句
	}
	for (pc = (*C); pc; pc = pc->down)
	{
		if (pc->info == minBool)
		{
			for (pn = pc->right; pn; pn = pn->next)
			{
				cnt[abs(pn->data)]++;//寻找最短子句中abs(Ele)最大的那个，统计次数
			}
		}
	}
	int maxapper = 0, maxBool = 0;
	for (int i = 1; i <= n1; i++)
	{
		if (cnt[i] > maxapper)
			maxapper = cnt[i], maxBool = i;//寻找出现次数最大变元
	}
	free(cnt);
	/*printf("%d:%d\n", count++, maxbool);
	if (count % 2700 == 0)
	{
		printf("\n");
	}*/
	return maxBool;
}

int JW5(CHead** C)//先统计一句话中全为正的变元，并标记记录，然后在此记录在整个cnf语句中
//abs值为标记正值的值的个数，最后根据标记过的正负变元的总数，选出出现次数最多的，然后处理
{
	int* mark = (int*)malloc(sizeof(int) * (n1 + 2));

	index* cnt = (index*)malloc(sizeof(index) * (n1 + 2));//初始化
	for (int i = 0; i <= n1; i++)
	{
		mark[i] = 0;
	}
	for (int i = 0; i <= n1; i++)
	{
		cnt[i].negative = 0;
		cnt[i].positive = 0;
	}

	PHead pc = NULL;
	PNode pn = NULL;
	for (pc = (*C); pc; pc = pc->down)
	{
		for (pn = pc->right; pn; pn = pn->next)
		{
			if (pn->data < 0)
				break;
			else if (pn->next == NULL)//寻找到文字末尾，并且发现值可以
			{
				for (PNode tmp = pc->right; tmp; tmp = tmp->next)
				{
					mark[tmp->data] = 1;//将数据存到那个里面，记录这个子句全为正
				}
				break;
			}
		}
	}


	for (pc = (*C); pc; pc = pc->down)
	{
		for (pn = pc->right; pn; pn = pn->next)
		{
			if (mark[abs(pn->data)])
			{
				if (pn->data > 0)
				{
					cnt[abs(pn->data)].positive += pow(2.0, (double)(-pc->info));//统计
				}
				else
				{
					cnt[abs(pn->data)].negative += pow(2.0, (double)(-pc->info));
				}
			}

		}
	}
	free(mark);
	double maxW = 0.0;
	int maxBool = 0;
	for (int i = 1; i <= n1; i++)
	{
		if (cnt[i].negative + cnt[i].positive > maxW)
		{
			maxW = cnt[i].negative + cnt[i].positive;
			maxBool = i;
		}
	}
	if (cnt[maxBool].negative > cnt[maxBool].positive)
		maxBool = -maxBool;
	free(cnt);
	if (maxBool == 0)
		maxBool = JW3(C);
	return maxBool;


}

int JW6(CHead** C)//仅寻找出现次数最多的，不考虑句子长度的影响
{
	int* cnt = (int*)malloc(sizeof(int) * (n1 * 2 + 1));
	for (int i = 0; i <= n1 * 2; i++)
		cnt[i] = 0;
	PHead pc = NULL;
	PNode pn = NULL;
	for (pc = (*C); pc; pc = pc->down)
		for (pn = pc->right; pn; pn = pn->next)
		{
			if (pn->data > 0)
				cnt[pn->data]++;
			else
				cnt[n1 - pn->data]++;
		}
	int maxBool, maxTimes = 0;
	for (int i = 1; i <= n1; i++)
		if (cnt[i] > maxTimes)
			maxTimes = cnt[i], maxBool = i;
	if (maxTimes == 0)
	{
		for (int i = n1 + 1; i <= n1 * 2; i++)
			if (cnt[i] > maxTimes)
				maxTimes = cnt[i], maxBool = i - n1;
	}
	free(cnt);
	return maxBool;
}