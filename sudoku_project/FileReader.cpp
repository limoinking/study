#define _CRT_SECURE_NO_WARNINGS
//这个文件是用来进行CNF数据的读入的
#include "Settings.h"

//思考，由于在dpll中需要进行独立变元的删去，所以需要更快去找到这样的变元
//以方便dpll算法的实现，所以在读取的时候，就额外添加一个权重（具体是什么后序再看）
//并且，注意到变元中还有正负之分，所以在读取的时候要注意正负
//注意以上1，2点


CHead* InitClause(CHead** C)
{
	//初始化链表,或者是添加新的子句
	CHead* new_one = NULL;
	CHead* cur = *C;
	new_one = (CHead*)malloc(sizeof(CHead));

	if (new_one == NULL)
		return FALSE;
	new_one->down = NULL;//兄弟
	new_one->right = NULL;//孩子
	new_one->info = 0;//权重值，初始化为0，其实就是变元的个数

	//如果为空，那就是初始化
	if (*C == NULL)
	{
		*C = new_one;
		return new_one;
	}

	while (cur->down != NULL)
	{
		cur = cur->down;
	}
	//如果不为空，就加到二维链表的末尾，并且返回指向这个新一维表的指针
	//使用头插法效率应该会更高一点
	cur->down = new_one;
	return new_one;
}

CNode* InitNode(CNode** C)
{
	CNode* new_node = NULL;
	CNode* cur = *C;
	new_node = (PNode)malloc(sizeof(CNode));
	if (new_node == NULL)
		return FALSE;//初始化失败
	new_node->next = NULL;
	new_node->data = 0;

	//下面两个情况和上面是类似的
	if (cur == NULL)
	{
		*C = new_node;
		return new_node;
	}
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = new_node;//这里使用头插法，提高效率
	return new_node;
}


void ShowFile(CHead** C)
//别忘了要先检验文件是否读取
{
	//这里是在读取后进行展示，展示读取情况
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
	//传入的是指向CHead的指针，还有文件名称

	//part1文件打开部分
	FILE* fp = NULL;
	fp = fopen(FileName, "r");
	if (!fp)
	{
		printf("读取失败！\n");
		exit(ERROR);
	}
		

	//part2前面注释处理问题
	//注意到CNF文件的格式，开头有c 以后的注释，还有p  cnf等无关信息
	//需要提前将其处理掉
	char ch;

	//由于CNF文件的形式保证，fgetc不会出现读到CNF的情况，这里就用char代替
	while ((ch = fgetc(fp)) != 'p')
	{//读到p跳出循环 
		if (ch == 'c')
		{//跳过注释行 
			while ((ch = fgetc(fp)) != '\n');
		}
	}
	while ((ch = fgetc(fp)) != 'f');
	fscanf(fp, "%d %d", &n1, &n2);//n1表示变元数目，n2表示子句的数目



	//part4文件的读取
	int x;
	//可以查看每一次的长度为多少
	//每一个子句中的变元个数都是确定的
	PHead down;
	PNode right;
	int n = n2;
	while (n--)
	{
		down = InitClause(C);
		do
		{
			fscanf(fp, "%d", &x);
			if (x == 0)break;//这样就处理了输入时变元的个数不对的问题
			//这里注意正负变元的读取
			counter[abs(x)].data = abs(x);
			right = InitNode(&(down->right));//一定要注意，传入的参数是指向指针的指针！
			right->data = x;
			down->info++;
		} while (x != 0);
	}
	fclose(fp);
	//发现SAT有时候执行速度过慢，故使用基于子句长度和变元正负，变元出现个数来决策变元
	//因为删除单个变量和长子句能加快dpll的执行过程



	//这里处理方式太过单一，不建议如此进行
	//待会在优化版本中，会引入更好的优化策略
	n = n2;
	down = *C;
	while (n--) {
		right = down->right;
		do {
			x = right->data;
			counter[abs(x)].count += pow(0.5, (double)(down->info));
			//统计正负变元不同的个数
			//原本这里的处理方式是，单纯算入变量个数
			//也就是暴力＋1
			//但是后面注意到，一些比较长的子句，包含多个变量子句有时候仅由一个变量
			//决定，所以将子句中元素的个数也作为一个权重加入到counter.count中
			//由两个变量决定，当然，构成结构是个数1+附加值
			//子句长度也会占一部分权重，当子句长的时候，权重更重
			//所以这样多维的决定因素可以很好解决变元个数和子句个数之间矛盾
			if (x > 0) {
				counter[abs(x)].positive += pow(0.5, (double)(down->info));
				//去处理长度/即权重
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

