#include"Settings.h"
#include "DpllStrategy.cpp"
bool IsOneUnitClause(CHead* C)
{
	CHead* cur = C;
	if (cur->info == 1)//有单变元的子句
	{
		return true;
	}
	return false;
}

//2.空子句的判断
status IsEmptyClause(CHead* C)
{
	CHead* cur = C;
	while (cur != NULL)
	{
		if (cur->info == 0)//只要有一个空子句就返回OK值
		{
			return OK;
		}
		cur = cur->down;
	}
	return NULL;
}

//接下来是简化的过程，需要删除带a的子句和带-a的单元
//首先从删节点入手，后面还需要删除子句
//两个的实现思路比较类似
//3.节点删除
status DeleteClauseNode(int x, CHead** C)
{
	PHead cur1 = *C;
	PNode cur2 = NULL;
	PNode p = NULL, q = NULL;
	while (cur1 != NULL)
	{
		cur2 = cur1->right;
		//由于首节点处理的方式比较特殊，所以单独拿出来处理
		while (cur2 != NULL && cur2->data == -x)//这就是上面说的带-a的单元的情况
		{
			cur1->right = cur2->next;
			free(cur2);
			cur2 = cur1->right;
			cur1->info--;
		}
		//剩下的就是正常的情况
		p = cur2;
		if (p == NULL)
			return OK;//删成空子句
		q = p->next;
		while (q != NULL)
		{
			if (q->data == -x)//符合情况
			{
				p->next = q->next;
				free(q);
				q = p->next;
				cur1->info--;
			}
			else//剩下不用删除的
			{
				p = q;
				q = p->next;
			}
		}
		cur1 = cur1->down;
	}
	return OK;
}
//4.子句删除
//4.1整个子句所有节点的释放
status FreeClauseAllNodes(CHead** node)
{
	CNode* p = NULL, * q = NULL;
	p = (*node)->right;
	q = p->next;
	if (q == NULL)//只有一个节点情况的特殊判断，情况要考虑全
	{
		free(p);
	}
	while (q != NULL)
	{
		free(p);
		p = q;
		q = p->next;
	}
	return OK;
}

//4.2整个子句挑选并删除
status DeleteClause(int x, CHead** C)
{
	PHead p = *C, q = NULL;
	PNode cur = NULL;
	int flag = 1;//用来记录当前子句中是否有可以让整个句子删除的情况

	//特殊情况1，直接为空节点
	if (*C == NULL) {
		return OK;
	}

	//特殊情况2，删除第一个节点
	//首先还是老样子，要处理特殊的第一个为要删除的情况
	while (p != NULL)
	{
		cur = p->right;
		while (cur != NULL)//判断是否有目标元素
		{
			if (cur->data == x)
			{
				flag = 0;
				break;
			}
			cur = cur->next;
		}
		if (flag == 1)
			break;//发现第一个没问题，就进入一般步骤
		else
			if (flag == 0)//剩下的，如果需要删除，就循环第一个步骤
			{
				q = *C;
				*C = (*C)->down;
				p = *C;
				FreeClauseAllNodes(&q);
				free(q);
				q = NULL;
				flag = 1;

			}
	}
	//接下来就是处理一般情况
	p = *C;//已经保证第一个不是要处理节点
	if (p == NULL)
		return OK;//不能再删除了
	q = p->down;
	flag = 0;
	while (q != NULL)
	{
		cur = q->right;
		while (cur != NULL)
		{
			if (cur->data == x)
			{
				flag = 1;
				p->down = q->down;
				FreeClauseAllNodes(&q);
				free(q);
				q = NULL;
				break;
			}
			cur = cur->next;
		}
		if (flag == 0) {
			p = p->down;
			q = q->down;
		}
		else if (flag == 1) {
			q = p->down;
			flag = 0;
		}

	}
	return OK;
}
void removeClause(CHead*& cnf, CHead*& cl)
{
	if (cl == cnf)
	{
		cnf = cnf->down;//头部首先处理
	}
	else
	{
		CHead* ppc = cnf;
		while (ppc && ppc->down != cl)
			ppc = ppc->down;
		ppc->down = ppc->down->down;
	}
	CNode* pn1, * pn2;
	for (pn1 = cl->right; pn1;)
	{
		pn2 = pn1->next, free(pn1), pn1 = pn2;
	}
	free(cl);
	cl = NULL;
}

void removeNode(CNode*& head, CNode*& nd)
{
	CNode* ppn = head;
	if (ppn == nd)
		head = head->next;//同样是头部特殊处理
	else
	{
		while (ppn && ppn->next != nd)
			ppn = ppn->next;
		ppn->next = ppn->next->next;
	}
	free(nd);
	nd = NULL;
}
//5.公式的简化流程
status SimplifyFormualtion(int n, CHead*& cnf)
{
	PHead tmp;
	PHead ppc = NULL;
	PNode ppn = NULL;
	for (ppc = cnf; ppc; ppc = tmp)
	{
		tmp = ppc->down;
		for (ppn = ppc->right; ppn; ppn = ppn->next)
		{
			if (ppn->data == n)
			{
				removeClause(cnf, ppc);
				break;
			}
			if (ppn->data == -n)
			{
				removeNode(ppc->right, ppn);
				ppc->info--;
				break;
			}
		}
	}
	//DeleteClause(x, C);
	//DeleteClauseNode(x, C);
	return OK;
}

//6.链表的复制
CHead* Duplication(CHead** C)
{
	PHead p = *C, q = NULL, dt = NULL, dnow = NULL;//dt用来追踪正本中的子句头结点 
	PNode rnow = NULL, rt = NULL;//rt用来追踪正本中的变元结点 
	while (p != NULL) {
		dnow = InitClause(&q);
		dnow->info = p->info;
		rt = p->right;
		while (rt != NULL) {
			rnow = InitNode(&(dnow->right));
			rnow->data = rt->data;
			rt = rt->next;
		}
		p = p->down;
	}
	return q;
}
//6.2多余子句删除
void DestroyClause(CHead** C)//用来处理回溯的时候，额外占用的空间
{
	CHead* pc1, * pc2;
	CNode* pl1, * pl2;
	for (pc1 = (*C); pc1 != NULL; pc1 = pc2)
	{
		for (pl1 = (pc1->right); pl1 != NULL; pl1 = pl2)
		{
			pl2 = pl1->next;
			free(pl1);
		}
		pc2 = pc1->down;
		free(pc1);
	}
	(*C) = NULL;
}
//7.
//在简化之后，将决策变元作为单子句加入到子句集中，对子句集合进行优化
//并且为了更快的遍历，使用头插法进行插入
status AddOneUnit(int x, CHead** C)
{
	PHead nex = NULL;
	nex = (PHead)malloc(sizeof(CHead));
	if (nex == NULL)
		return false;
	nex->down = *C;
	nex->right = NULL;
	nex->info = 0;
	*C = nex;
	nex->info = 1;
	PNode node = InitNode(&(nex->right));
	node->data = x;
	/*counter[abs(x)].count += 1;
	if (x > 0) {
		counter[abs(x)].positive += 1;
	}
	else {
		counter[abs(x)].negative += 1;
	}*/
	return OK;
}




//9.核心步骤dpll的实现
status Dpll(CHead** C)
{
	PHead pc = NULL;
	int uni = 0;
	int flag = 1;
	while (flag)
	{
		flag = 0;
		pc = *C;
		while (pc != NULL && !(IsOneUnitClause(pc)))
		{
			pc = pc->down;//这样只需要搜一遍
		}
		if (pc != NULL)
		{
			uni = pc->right->data;
			if (uni > 0)
			{
				counter[abs(uni)].value = 1;
			}
			else
			{
				counter[abs(uni)].value = -1;//直接快速赋予单个变元真假值，然后来简化整个句子
				//先删除本身为真的子句，删除本身为假的单元，这也是简化的过程中所做的事情
			}
			/*printf("%d\n", uni);
			if (uni == -373)
			{
				printf("qqq\n");
			}*/
			SimplifyFormualtion(uni, *C);
			if (*C == NULL)
				return TRUE;//删完了，没东西了就说明可以成功了

			else if (IsEmptyClause(*C))//有空子句，那就说明这个玩意不可能成立，直接返回不成立即可
				return FALSE;
			flag = 1;
		}
	}

	switch (method)
	{
	case 1:
		uni = JW1(C);
		break;
	case 2:
		uni = JW2(C);
		break;
	case 3:
		uni = JW3(C);
		break;
	case 4:
		uni = JW4(C);
		break;
	case 5:
		uni = JW5(C);
		break;
	case 6:
		uni = JW6(C);
		break;
	default:
		uni = MyStartegy1(C);
		break;
	}

	if (uni > 0)//然后赋予这个值真假值
	{
		counter[abs(uni)].value = 1;
	}
	else
	{
		counter[abs(uni)].value = -1;
	}
	PHead temp1 = Duplication(C);//不能更改原有的那个
	AddOneUnit(uni, &temp1);//将单变元加入
	if (Dpll(&temp1))//再次调用，看看本次的运行结果
	{

		return TRUE;
	}
	else//如果发现赋予真值不行，那么尝试赋予假值
	{
		DestroyClause(&temp1);
		AddOneUnit(-uni, C);
		if (uni > 0)
		{
			counter[abs(uni)].value = -1;
		}
		else
		{
			counter[abs(uni)].value = 1;
		}
		bool ans = Dpll(C);//再次进行迭代递归
		DestroyClause(C);
		return ans;
	}
}



status SaveSATFile(int solve, double time, char FileName[])
{
	for (int i = 0; FileName[i] != '\n'; i++)
	{
		if (FileName[i] == '.')
		{
			FileName[i + 1] = 'r';
			FileName[i + 2] = 'e';
			FileName[i + 3] = 's';
			break;
		}
	}
	FILE* fp;
	fp = fopen(FileName, "w");
	if (!fp)
		exit(-1);
	if (solve == TRUE)
	{
		fprintf(fp, "s 1\n");
		fprintf(stdout, "s 1\n");
		fprintf(fp, "v ");
		fprintf(stdout, "v ");
		for (int i = 1; counter[i].data != 0 && i < MAXN; i++)
		{
			if (counter[i].value == 1) {
				fprintf(fp, "%d ", i);
				fprintf(stdout, "%d ", i);
			}
			else if (counter[i].value == -1) {
				fprintf(fp, "%d ", -i);
				fprintf(stdout, "%d ", -i);
			}
		}
		fprintf(fp, "\n");
		fprintf(stdout, "\n");
	}
	else
	{
		fprintf(fp, "s 0\n");
		fprintf(stdout, "s 0\n");
	}
	fprintf(fp, "t %fms", time);
	fprintf(stdout, "t %fms", time);
	fclose(fp);
	return OK;
}

//10.进行SAT操作的函数
status EntrySAT(char FileName[])
{
	PHead C = NULL;
	int solve;
	clock_t start_time, end_time;
	double total_time;
	ReaderFile(&C, FileName);
	start_time = clock();
	solve = Dpll(&C);
	end_time = clock();
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;//输出的就是以秒为单位的值
	SaveSATFile(solve, total_time, FileName);
	return OK;
}
