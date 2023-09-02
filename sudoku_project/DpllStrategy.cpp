#include "Settings.h"


int abs(int x)
{
	return x > 0 ? x : -x;
}

//���������û�����������б�Ԫ�����Ƚϻ���
//�ڶ��ֵû���ҵ����ʱ�Ԫ�������
status MyStartegy1(CHead** C)//���Ų��Գ�ʼ��
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
		pos = (*C)->right->data;//���Ż�����û�ҵ����߱�Ԫʱ,Ҳ����ֱ�ӽ���һ����Ԫ��ΪĿ���Ԫ
	if (counter[pos].positive > counter[pos].negative)
		return pos;//��ֵƵ�ʴ��ڸ�ֵ��������ֵ��Ϊ���߱�Ԫ 
	else
		return -pos;
}




//Ϊ����������ٶȣ���������JW�Ż�����
// ������ǰ����һ�£���Ȩ��ѡȡ���ԣ�����Խ�����Ӿ�Խ���״�����������ѡ����Ӽ򵥵��Ӿ�
// ���Բ���2^(-�Ӿ䳤��)������Ϊ��Ȩ���д���

//��һ���Ż���ѡȡ���Ӿ�����Ż�
int JW1(CHead** C)//���Ӿ��Ż�,���ݱ�Ԫ�����Ӿ䳤�Ⱥʹ������ܺͿ��ǣ���mystrategy����һ��
{
	double* w = (double*)malloc(sizeof(double) * (n1 + 2));
	if (w == NULL)
		exit(-1);
	for (int i = 0; i <= n1; i++)
	{
		w[i] = 0.0;
	}//��ʼ��
	PHead pc = NULL;
	PNode pn = NULL;
	for (pc = (*C); pc; pc = pc->down)
	{
		for (pn = pc->right; pn; pn = pn->next)
		{
			w[abs(pn->data)] += pow(2.0, double(-(pc->info)));//��Ԫ��Ŀ���Ӿ䳤��
		}
	}
	double maxW = 0;
	int maxBool = 0;
	for (int i = 1; i <= n1; i++)
	{
		if (w[i] > maxW)
			maxW = w[i], maxBool = i;//Ѱ�ҵ�ǰ�Ż��������������Ԫ
	}
	free(w);
	return maxBool;
}

int JW2(CHead** C)//JW����
{
	//�ڶ��ֲ��Խ�������ԪJ(x)+J(-x)+a * (min(J(x),J(-x)))��a����Ϊ0��������������Ȼ
	//a��ֵ���Խ��е���
	//������൱����ѧϰ��
	//ѧϰ������Ϊ0�������ٽ��е���
	//ͳ��������Ԫ���ֵ�����
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
				w[abs(pn->data)].positive += pow(2.0, double(-(pc->info)));//��Ԫ��Ŀ���Ӿ䳤��
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
	//����㷨���Դ����ű�Ԫ�Ƚ϶���������Ϊʵ���߼��ǣ����ҵ�����Ԫ�г��ִ�������
	// Ȼ�����û�и��ű�Ԫ������ȥ������Ԫ
	//���ң������и���Ԫ�Ƚ϶࣬�������ȴ�����Ԫ��Ȼ���
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
	for (int i = 1; i <= n1; i++)//�ȿ���Ԫ�صĸ������ȴ����ı�Ԫ��ע�⵽���ı�Ԫ�Ƚ϶�
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


int JW4(CHead** C)//���Ӿ�Ԫ�ش���
{
	//���һ�֣�����������Ӿ������ɾ�����Ӿ��
	//��Ҫ����һ���߼������ҵ�����Ӿ�
	//������Ӿ����ҵ����ִ�������Ԫ�أ���������һ�飩
	//Ȼ�󷵻ظñ�Ԫ
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
			minBool = pc->info;//Ѱ������Ӿ�
	}
	for (pc = (*C); pc; pc = pc->down)
	{
		if (pc->info == minBool)
		{
			for (pn = pc->right; pn; pn = pn->next)
			{
				cnt[abs(pn->data)]++;//Ѱ������Ӿ���abs(Ele)�����Ǹ���ͳ�ƴ���
			}
		}
	}
	int maxapper = 0, maxBool = 0;
	for (int i = 1; i <= n1; i++)
	{
		if (cnt[i] > maxapper)
			maxapper = cnt[i], maxBool = i;//Ѱ�ҳ��ִ�������Ԫ
	}
	free(cnt);
	/*printf("%d:%d\n", count++, maxbool);
	if (count % 2700 == 0)
	{
		printf("\n");
	}*/
	return maxBool;
}

int JW5(CHead** C)//��ͳ��һ�仰��ȫΪ���ı�Ԫ������Ǽ�¼��Ȼ���ڴ˼�¼������cnf�����
//absֵΪ�����ֵ��ֵ�ĸ����������ݱ�ǹ���������Ԫ��������ѡ�����ִ������ģ�Ȼ����
{
	int* mark = (int*)malloc(sizeof(int) * (n1 + 2));

	index* cnt = (index*)malloc(sizeof(index) * (n1 + 2));//��ʼ��
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
			else if (pn->next == NULL)//Ѱ�ҵ�����ĩβ�����ҷ���ֵ����
			{
				for (PNode tmp = pc->right; tmp; tmp = tmp->next)
				{
					mark[tmp->data] = 1;//�����ݴ浽�Ǹ����棬��¼����Ӿ�ȫΪ��
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
					cnt[abs(pn->data)].positive += pow(2.0, (double)(-pc->info));//ͳ��
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

int JW6(CHead** C)//��Ѱ�ҳ��ִ������ģ������Ǿ��ӳ��ȵ�Ӱ��
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