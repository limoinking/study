#define _CRT_SECURE_NO_WARNINGS
//����ļ�����������CNF���ݵĶ����
#include "Settings.h"

//˼����������dpll����Ҫ���ж�����Ԫ��ɾȥ��������Ҫ����ȥ�ҵ������ı�Ԫ
//�Է���dpll�㷨��ʵ�֣������ڶ�ȡ��ʱ�򣬾Ͷ������һ��Ȩ�أ�������ʲô�����ٿ���
//���ң�ע�⵽��Ԫ�л�������֮�֣������ڶ�ȡ��ʱ��Ҫע������
//ע������1��2��


CHead* InitClause(CHead** C)
{
	//��ʼ������,����������µ��Ӿ�
	CHead* new_one = NULL;
	CHead* cur = *C;
	new_one = (CHead*)malloc(sizeof(CHead));

	if (new_one == NULL)
		return FALSE;
	new_one->down = NULL;//�ֵ�
	new_one->right = NULL;//����
	new_one->info = 0;//Ȩ��ֵ����ʼ��Ϊ0����ʵ���Ǳ�Ԫ�ĸ���

	//���Ϊ�գ��Ǿ��ǳ�ʼ��
	if (*C == NULL)
	{
		*C = new_one;
		return new_one;
	}

	while (cur->down != NULL)
	{
		cur = cur->down;
	}
	//�����Ϊ�գ��ͼӵ���ά�����ĩβ�����ҷ���ָ�������һά���ָ��
	//ʹ��ͷ�巨Ч��Ӧ�û����һ��
	cur->down = new_one;
	return new_one;
}

CNode* InitNode(CNode** C)
{
	CNode* new_node = NULL;
	CNode* cur = *C;
	new_node = (PNode)malloc(sizeof(CNode));
	if (new_node == NULL)
		return FALSE;//��ʼ��ʧ��
	new_node->next = NULL;
	new_node->data = 0;

	//����������������������Ƶ�
	if (cur == NULL)
	{
		*C = new_node;
		return new_node;
	}
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = new_node;//����ʹ��ͷ�巨�����Ч��
	return new_node;
}


void ShowFile(CHead** C)
//������Ҫ�ȼ����ļ��Ƿ��ȡ
{
	//�������ڶ�ȡ�����չʾ��չʾ��ȡ���
	PHead pc = NULL;
	PNode pn = NULL;
	for (pc = (*C); pc; pc = pc->down)
	{
		for (pn = pc->right; pn; pn = pn->next)
		{
			printf("%d ", pn->data);
		}
		printf("0\n");
	}
	return;
}

status ReaderFile(CHead** C, char FileName[])
{
	//�������ָ��CHead��ָ�룬�����ļ�����

	//part1�ļ��򿪲���
	FILE* fp = NULL;
	fp = fopen(FileName, "r");
	if (!fp)
	{
		printf("��ȡʧ�ܣ�\n");
		exit(ERROR);
	}
		

	//part2ǰ��ע�ʹ�������
	//ע�⵽CNF�ļ��ĸ�ʽ����ͷ��c �Ժ��ע�ͣ�����p  cnf���޹���Ϣ
	//��Ҫ��ǰ���䴦���
	char ch;

	//����CNF�ļ�����ʽ��֤��fgetc������ֶ���CNF��������������char����
	while ((ch = fgetc(fp)) != 'p')
	{//����p����ѭ�� 
		if (ch == 'c')
		{//����ע���� 
			while ((ch = fgetc(fp)) != '\n');
		}
	}
	while ((ch = fgetc(fp)) != 'f');
	fscanf(fp, "%d %d", &n1, &n2);//n1��ʾ��Ԫ��Ŀ��n2��ʾ�Ӿ����Ŀ



	//part4�ļ��Ķ�ȡ
	int x;
	//���Բ鿴ÿһ�εĳ���Ϊ����
	//ÿһ���Ӿ��еı�Ԫ��������ȷ����
	PHead down;
	PNode right;
	int n = n2;
	while (n--)
	{
		down = InitClause(C);
		do
		{
			fscanf(fp, "%d", &x);
			if (x == 0)break;//�����ʹ���������ʱ��Ԫ�ĸ������Ե�����
			//����ע��������Ԫ�Ķ�ȡ
			counter[abs(x)].data = abs(x);
			right = InitNode(&(down->right));//һ��Ҫע�⣬����Ĳ�����ָ��ָ���ָ�룡
			right->data = x;
			down->info++;
		} while (x != 0);
	}
	fclose(fp);
	//����SAT��ʱ��ִ���ٶȹ�������ʹ�û����Ӿ䳤�Ⱥͱ�Ԫ��������Ԫ���ָ��������߱�Ԫ
	//��Ϊɾ�����������ͳ��Ӿ��ܼӿ�dpll��ִ�й���



	//���ﴦ��ʽ̫����һ����������˽���
	//�������Ż��汾�У���������õ��Ż�����
	n = n2;
	down = *C;
	while (n--) {
		right = down->right;
		do {
			x = right->data;
			counter[abs(x)].count += pow(0.5, (double)(down->info));
			//ͳ��������Ԫ��ͬ�ĸ���
			//ԭ������Ĵ���ʽ�ǣ����������������
			//Ҳ���Ǳ�����1
			//���Ǻ���ע�⵽��һЩ�Ƚϳ����Ӿ䣬������������Ӿ���ʱ�����һ������
			//���������Խ��Ӿ���Ԫ�صĸ���Ҳ��Ϊһ��Ȩ�ؼ��뵽counter.count��
			//������������������Ȼ�����ɽṹ�Ǹ���1+����ֵ
			//�Ӿ䳤��Ҳ��ռһ����Ȩ�أ����Ӿ䳤��ʱ��Ȩ�ظ���
			//����������ά�ľ������ؿ��Ժܺý����Ԫ�������Ӿ����֮��ì��
			if (x > 0) {
				counter[abs(x)].positive += pow(0.5, (double)(down->info));
				//ȥ������/��Ȩ��
			}
			else {
				counter[abs(x)].negative += pow(0.5, (double)(down->info));
			}
			right = right->next;
		} while (right != NULL);
		down = down->down;
	}
	return OK;
}

