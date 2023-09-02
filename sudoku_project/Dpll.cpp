#include"Settings.h"
#include "DpllStrategy.cpp"
bool IsOneUnitClause(CHead* C)
{
	CHead* cur = C;
	if (cur->info == 1)//�е���Ԫ���Ӿ�
	{
		return true;
	}
	return false;
}

//2.���Ӿ���ж�
status IsEmptyClause(CHead* C)
{
	CHead* cur = C;
	while (cur != NULL)
	{
		if (cur->info == 0)//ֻҪ��һ�����Ӿ�ͷ���OKֵ
		{
			return OK;
		}
		cur = cur->down;
	}
	return NULL;
}

//�������Ǽ򻯵Ĺ��̣���Ҫɾ����a���Ӿ�ʹ�-a�ĵ�Ԫ
//���ȴ�ɾ�ڵ����֣����滹��Ҫɾ���Ӿ�
//������ʵ��˼·�Ƚ�����
//3.�ڵ�ɾ��
status DeleteClauseNode(int x, CHead** C)
{
	PHead cur1 = *C;
	PNode cur2 = NULL;
	PNode p = NULL, q = NULL;
	while (cur1 != NULL)
	{
		cur2 = cur1->right;
		//�����׽ڵ㴦��ķ�ʽ�Ƚ����⣬���Ե����ó�������
		while (cur2 != NULL && cur2->data == -x)//���������˵�Ĵ�-a�ĵ�Ԫ�����
		{
			cur1->right = cur2->next;
			free(cur2);
			cur2 = cur1->right;
			cur1->info--;
		}
		//ʣ�µľ������������
		p = cur2;
		if (p == NULL)
			return OK;//ɾ�ɿ��Ӿ�
		q = p->next;
		while (q != NULL)
		{
			if (q->data == -x)//�������
			{
				p->next = q->next;
				free(q);
				q = p->next;
				cur1->info--;
			}
			else//ʣ�²���ɾ����
			{
				p = q;
				q = p->next;
			}
		}
		cur1 = cur1->down;
	}
	return OK;
}
//4.�Ӿ�ɾ��
//4.1�����Ӿ����нڵ���ͷ�
status FreeClauseAllNodes(CHead** node)
{
	CNode* p = NULL, * q = NULL;
	p = (*node)->right;
	q = p->next;
	if (q == NULL)//ֻ��һ���ڵ�����������жϣ����Ҫ����ȫ
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

//4.2�����Ӿ���ѡ��ɾ��
status DeleteClause(int x, CHead** C)
{
	PHead p = *C, q = NULL;
	PNode cur = NULL;
	int flag = 1;//������¼��ǰ�Ӿ����Ƿ��п�������������ɾ�������

	//�������1��ֱ��Ϊ�սڵ�
	if (*C == NULL) {
		return OK;
	}

	//�������2��ɾ����һ���ڵ�
	//���Ȼ��������ӣ�Ҫ��������ĵ�һ��ΪҪɾ�������
	while (p != NULL)
	{
		cur = p->right;
		while (cur != NULL)//�ж��Ƿ���Ŀ��Ԫ��
		{
			if (cur->data == x)
			{
				flag = 0;
				break;
			}
			cur = cur->next;
		}
		if (flag == 1)
			break;//���ֵ�һ��û���⣬�ͽ���һ�㲽��
		else
			if (flag == 0)//ʣ�µģ������Ҫɾ������ѭ����һ������
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
	//���������Ǵ���һ�����
	p = *C;//�Ѿ���֤��һ������Ҫ����ڵ�
	if (p == NULL)
		return OK;//������ɾ����
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
		cnf = cnf->down;//ͷ�����ȴ���
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
		head = head->next;//ͬ����ͷ�����⴦��
	else
	{
		while (ppn && ppn->next != nd)
			ppn = ppn->next;
		ppn->next = ppn->next->next;
	}
	free(nd);
	nd = NULL;
}
//5.��ʽ�ļ�����
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

//6.����ĸ���
CHead* Duplication(CHead** C)
{
	PHead p = *C, q = NULL, dt = NULL, dnow = NULL;//dt����׷�������е��Ӿ�ͷ��� 
	PNode rnow = NULL, rt = NULL;//rt����׷�������еı�Ԫ��� 
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
//6.2�����Ӿ�ɾ��
void DestroyClause(CHead** C)//����������ݵ�ʱ�򣬶���ռ�õĿռ�
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
//�ڼ�֮�󣬽����߱�Ԫ��Ϊ���Ӿ���뵽�Ӿ伯�У����Ӿ伯�Ͻ����Ż�
//����Ϊ�˸���ı�����ʹ��ͷ�巨���в���
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




//9.���Ĳ���dpll��ʵ��
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
			pc = pc->down;//����ֻ��Ҫ��һ��
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
				counter[abs(uni)].value = -1;//ֱ�ӿ��ٸ��赥����Ԫ���ֵ��Ȼ��������������
				//��ɾ������Ϊ����Ӿ䣬ɾ������Ϊ�ٵĵ�Ԫ����Ҳ�Ǽ򻯵Ĺ���������������
			}
			/*printf("%d\n", uni);
			if (uni == -373)
			{
				printf("qqq\n");
			}*/
			SimplifyFormualtion(uni, *C);
			if (*C == NULL)
				return TRUE;//ɾ���ˣ�û�����˾�˵�����Գɹ���

			else if (IsEmptyClause(*C))//�п��Ӿ䣬�Ǿ�˵��������ⲻ���ܳ�����ֱ�ӷ��ز���������
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

	if (uni > 0)//Ȼ�������ֵ���ֵ
	{
		counter[abs(uni)].value = 1;
	}
	else
	{
		counter[abs(uni)].value = -1;
	}
	PHead temp1 = Duplication(C);//���ܸ���ԭ�е��Ǹ�
	AddOneUnit(uni, &temp1);//������Ԫ����
	if (Dpll(&temp1))//�ٴε��ã��������ε����н��
	{

		return TRUE;
	}
	else//������ָ�����ֵ���У���ô���Ը����ֵ
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
		bool ans = Dpll(C);//�ٴν��е����ݹ�
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

//10.����SAT�����ĺ���
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
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;//����ľ�������Ϊ��λ��ֵ
	SaveSATFile(solve, total_time, FileName);
	return OK;
}
