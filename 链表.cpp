#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //数据元素类型定义
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode {  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;

typedef struct {  //线性表的管理表定义
    struct {
        char name[30];
        LinkList L;
    }elem[10];
    int length;
    int listsize;
}LISTS;
int fg = 1;
status InitList(LinkList& L);
status DestroyList(LinkList& L);
status ClearList(LinkList& L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType& e);
status LocateElem(LinkList L, ElemType e);
status PriorElem(LinkList L, ElemType e, ElemType& pre);
status NextElem(LinkList L, ElemType e, ElemType& next);
status ListInsert(LinkList& L, int i, ElemType e);
status ListDelete(LinkList& L, int i, ElemType& e);
status ListTraverse(LinkList L);
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList& L, char FileName[]);
status AddList(LISTS& Lists, char ListName[]);
status RemoveList(LISTS& Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
LinkList ChooseList(LinkList& L, LISTS& Lists, int i);
status sortList(LinkList& L);
LinkList reverseList(LinkList& L);
status RemoveNthFromEnd(LinkList &L, int n);
LinkList* mylist = NULL;

int main()
{
    LinkList L = NULL;
    int op = 1, flag, length, i, e, pre, next;
    LISTS Lists;
    Lists.length = 0;
    for (int i = 0; i < 10; i++)
        Lists.elem[i].L = NULL;
    char FileName[30] = { '\0' };
    char ListName[30] = { '\0' };

    while (op) {
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("------------------------------------------------\n");
        printf("     1. InitList       2. DestroyList\n");
        printf("     3. ClearList      4. ListEmpty\n");
        printf("     5. ListLength     6. GetElem\n");
        printf("     7. LocateElem     8. PriorElem\n");
        printf("     9. NextElem       10.ListInsert\n");
        printf("     11.ListDelete     12.ListTraverse\n");
        printf("     13.SaveList       14.LoadList\n");
        printf("     15.AddList        16.RemoveList\n");
        printf("     17.LocateList     18.ListsTraverse\n");
        printf("     19.ChooseList     20 sortlist\n");
        printf("     21.reverseList    22.RemoveNthFromEnd\n");
        printf("     0. Exit\n");
        printf("------------------------------------------------\n");
        printf("\n请选择你的操作[0~19]:\n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            if (InitList(L) == OK)
                printf("线性表创建成功！\n");
            else
                printf("线性表创建失败！\n");
            getchar(); getchar();
            break;
        case 2:
            if (DestroyList(L) == OK)
                printf("成功销毁线性表并释放数据元素的空间。\n");
            else
                printf("不能对不存在的线性表进行销毁操作！\n");
            getchar(); getchar();
            break;
        case 3:
            if (ClearList(L) == OK)
                printf("成功删除线性表中所有的元素。\n");
            else
                printf("不能对不存在的线性表进行清空操作！\n");
            getchar(); getchar();
            break;
        case 4:
            flag = ListEmpty(L);
            if (flag == TRUE)
                printf("线性表为空。\n");
            else if (flag == ERROR)
                printf("线性表非空。\n");
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表判空。\n");
            getchar(); getchar();
            break;
        case 5:
            length = ListLength(L);
            if (length >= 0)
                printf("线性表的长度为%d。\n", length);
            else
                printf("不能对不存在的线性表求长！\n");
            getchar(); getchar();
            break;
        case 6:
            printf("请输入想要从线性表中获取的元素的序号：");
            scanf("%d", &i);
            flag = GetElem(L, i, e);
            if (flag == OK)
                printf("线性表中第%d个元素为%d。\n", i, e);
            else if (flag == ERROR)
                printf("输入的序号不合法！\n");
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行此操作！\n");
            getchar(); getchar();
            break;
        case 7:
            printf("请输入想要在线性表中查找的元素：");
            scanf("%d", &e);
            flag = LocateElem(L, e);
            if (flag == 0)
                printf("线性表中不存在%d这个元素。\n", e);
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行此操作！\n");
            else
                printf("元素%d在线性表中的序号为%d\n", e, flag);
            getchar(); getchar();
            break;
        case 8:
            printf("请输入想要在线性表中查找其前驱的元素：");
            scanf("%d", &e);
            flag = PriorElem(L, e, pre);
            if (flag == OK)
                printf("元素%d在线性表中的前驱为%d。\n", e, pre);
            else if (flag == ERROR)
                printf("元素%d在线性表中没有前驱。\n", e);
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行此操作！\n");
            getchar(); getchar();
            break;
        case 9:
            printf("请输入想要在线性表中查找其后继的元素：");
            scanf("%d", &e);
            flag = NextElem(L, e, next);
            if (flag == OK)
                printf("元素%d在线性表中的后继为%d。\n", e, next);
            else if (flag == ERROR)
                printf("元素%d在线性表中没有后继。\n", e);
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行此操作！\n");
            getchar(); getchar();
            break;
        case 10:
            printf("请输入想要插入的元素：");
            scanf("%d", &e);
            printf("请输入想要插入的位置(某一个位置之前）：");
            scanf("%d", &i);
            flag = ListInsert(L, i, e);
            if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行插入！\n");
            else if (flag == ERROR)
                printf("插入位置不正确！\n");
            else
                printf("元素已插入线性表中。\n");
            getchar(); getchar();
            break;
        case 11:
            printf("请输入想要删除的元素的序号：");
            scanf("%d", &i);
            flag = ListDelete(L, i, e);
            if (flag == OK)
                printf("序号为%d的元素%d已经从线性表中删除。\n", i, e);
            else if (flag == ERROR)
                printf("删除位置不正确！\n");
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行删除！\n");
            getchar(); getchar();
            break;
        case 12:
            flag = ListTraverse(L);
            if (flag == INFEASIBLE)
                printf("不能遍历不存在的线性表！\n");
            else if (flag == ERROR)
                printf("线性表是空表。\n");
            else printf("\n");
            getchar(); getchar();
            break;
        case 13:
            printf("请输入文件名称：");
            scanf("%s", FileName);
            flag = SaveList(L, FileName);
            if (flag == ERROR)
                printf("文件打开失败！\n");
            else if (flag == OK)
                printf("线性表的内容已经复制到名称为 %s 的文件中。\n", FileName);
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行进行写文件操作。\n");
            getchar(); getchar();
            break;
        case 14:
            printf("请输入文件名称：");
            scanf("%s", FileName);
            flag = LoadList(L, FileName);
            if (flag == ERROR)
                printf("文件打开失败！\n");
            else if (flag == OK)
                printf("名称为 %s 的文件中的内容已复制到线性表中。\n", FileName);
            else if (flag == INFEASIBLE)
                printf("不能对已存在的线性表进行进行读文件操作。\n");
            else if (flag == OVERFLOW)
                printf("溢出！\n");
            getchar(); getchar();
            break;
        case 15: {char ListName[30] = { '\0' };
               printf("请输入新增线性表的名称：");
               scanf("%s", ListName);
               flag = AddList(Lists, ListName);
               if (flag == OK) printf("成功新增名称为 %s 的线性表。\n", ListName);
               else printf("新增失败！\n");
               getchar(); getchar();
               break;

        }
        case 16:
            printf("请输入想要删除的线性表的名称：");
            scanf("%s", ListName);
            flag = RemoveList(Lists, ListName);
            if (flag == OK)
                printf("成功删除名称为 %s 的线性表。\n", ListName);
            else if (flag == ERROR)
                printf("删除失败！\n");
            getchar(); getchar();
            break;
        case 17: {char ListName[30] = { '\0' };
               printf("请输入想要查找的线性表的名称：");
               scanf("%s", ListName);
               i = LocateList(Lists, ListName);
               if (i == 0)
                   printf("不存在名称为 %s 的线性表。\n", ListName);
               else printf("名称为 %s 的线性表的序号为%d\n", ListName, i);
               getchar(); getchar();
               break;
        }
        case 18:
            flag = ListsTraverse(Lists);
            if (flag == ERROR) printf("线性表的集合为空。\n");
            getchar(); getchar();
            break;
        case 19:
            printf("请输入想要进行操作的线性表的序号（从1开始）：");
            scanf("%d", &i);
            L = ChooseList(L, Lists, i);
            printf("下面可对线性表集合中序号为%d的线性表进行操作。\n", i);
            getchar(); getchar();
            break;
        case 20:
            if (mylist != NULL)
                L = *mylist;
            flag = sortList(L);
            if (flag == OK)
                printf("完成排序\n");
            else
                printf("空表\n");
            getchar(); getchar();
            break;
        case 21:
            if (mylist != NULL)
                L = *mylist;
            if (L == NULL)
            {
                printf("空表无法进行此操作");
                getchar(); getchar();
                break;
            }
            
            L = reverseList(L);
                printf("完成!\n");
            getchar(); getchar();
            break;
        case 22:
            printf("请输入倒数第几个数字：");
            scanf("%d", &e);
            flag = RemoveNthFromEnd(L, e);
            if (flag == OK)
                printf("成功移除！\n");
            else
            {
                printf("表有问题或者输入位置有误");
            }
            getchar(); getchar();
            break;
        case 0:
            break;
        }//end of switch
        printf("\n");
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()






status InitList(LinkList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)//判断是否为空
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    L->data = 0;
    return OK;


    /********** End **********/
}
status DestroyList(LinkList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    LinkList q, p = L;
    while (p != NULL)
    {
        q = p->next;
        free(p);//释放节点
        p = q;
    }
    L = NULL;
    return OK;

    /********** End **********/
}
status ClearList(LinkList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    LinkList q, p = L->next;
    L->next = NULL;
    return OK;

    /********** End **********/
}
status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)//判断第一个节点是否为空即可
    {
        return INFEASIBLE;
    }
    if (L->next != NULL)
        return ERROR;
    return OK;

    /********** End **********/
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    LinkList p;
    p = L;
    int length = 0;
    while (p != NULL)
    {
        p = p->next;
        length++;
    }
    return length - 1;

    /********** End **********/
}
status GetElem(LinkList L, int i, ElemType& e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    int length = 0;
    LinkList p;
    p = L;
    if (i == 0)
        return ERROR;//没有第0个元素
    while (p != NULL)
    {
        length++;
        if (length == i + 1)
        {
            e = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
    /********** End **********/
}
status LocateElem(LinkList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int length = 0;
    if (L == NULL)
        return INFEASIBLE;
    LinkList p;
    p = L;
    while (p != NULL)
    {
        if (p->data == e)
            return length;
        p = p->next;
        length++;
    }
    return ERROR;

    /********** End **********/
}
status PriorElem(LinkList L, ElemType e, ElemType& pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int length = 0;//有一个首节点，所以第一个元素为空
    if (L == NULL)
        return INFEASIBLE;
    LinkList p, q;
    p = L->next;
    q = L;
    while (p != NULL)
    {
        if (p->data == e)//查找到该元素
        {
            if (length == 0)//判断长度是否为0
                return ERROR;
            else
            {
                pre = q->data;
                return OK;
            }

        }
        p = p->next;
        q = q->next;
        length++;
    }
    return ERROR;

    /********** End **********/
}


status NextElem(LinkList L, ElemType e, ElemType& next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int length = 0;//有一个首节点，所以第一个元素为空
    if (L == NULL)
        return INFEASIBLE;
    LinkList p;
    p = L->next;
    while (p != NULL)
    {
        if (p->data == e)
        {
            if (p->next == NULL)//判断后继是否存在
                return ERROR;
            else
            {
                next = p->next->data;
                return OK;
            }

        }
        p = p->next;
        length++;
    }
    return ERROR;

    /********** End **********/
}
status ListInsert(LinkList& L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int length = 0;//有一个首节点，所以第一个元素为空
    if (L == NULL)
        return INFEASIBLE;

    LinkList p, q, cur;
    cur = (LNode*)malloc(sizeof(LNode));
    cur->data = e;
    cur->next = NULL;
    p = L->next;
    q = L;
    while (q != NULL)
    {
        if (length == i - 1)
        {
            q->next = cur;
            cur->next = p;
            return OK;
            break;
        }
        if (p != NULL)
            p = p->next;
        q = q->next;
        length++;
    }
    return ERROR;

    /********** End **********/
}
status ListDelete(LinkList& L, int i, ElemType& e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    int length = 0;
    LinkList p, q;
    p = L;
    q = L->next;
    while (q != NULL && i)
    {
        if (length == i - 1)
        {
            e = q->data;
            p->next = q->next;
            free(q);
            return OK;
        }
        p = p->next;
        q = q->next;
        length++;
    }
    return ERROR;

    /********** End **********/
}
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    LinkList p;
    p = L->next;
    int flag = 0;
    while (p != NULL)
    {
        if (flag)
            printf(" ");
        flag = 1;
        printf("%d", p->data);
        p = p->next;
    }
    return OK;

    /********** End **********/
}
status SaveList(LinkList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (L == NULL)
        return INFEASIBLE;
    FILE* fp = fopen(FileName, "w+");
    LinkList p;
    p = L->next;
    while (p != NULL)
    {
        fprintf(fp, "%d ", p->data);
        p = p->next;
    }
    fclose(fp);
    return OK;

    /********** End 1 **********/
}

status LoadList(LinkList& L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if (L != NULL)
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LinkList));
    FILE* fp = fopen(FileName, "r+");
    int i = 0;
    int data = 0;
    LinkList* head = &L;
    LinkList s;
    s = L;
    while (fscanf(fp, "%d ", &data) != EOF)//读取数据从记事本里面
    {
        LinkList cur;
        cur = (LinkList)malloc(sizeof(LinkList));
        cur->data = data;
        cur->next = NULL;
        s->next = cur;
        s = s->next;
    }
    L = *head;
    return OK;

    /********** End 2 **********/
}

//下面的部分是多个线性表管理的内容
//在Lists中增加一个名称为ListName的空线性表。
status AddList(LISTS& Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++)
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            printf("集合中已存在名称为 %s 的线性表！\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);//复制字串名字
    InitList(Lists.elem[Lists.length].L);//初始化这个表
    Lists.length++;
    int e;
    int x = 1;
    printf("在 %s 线性表中输入元素（以0结束）:\n", ListName);
    scanf("%d", &e);
    while (e)
    {
        ListInsert(Lists.elem[Lists.length - 1].L, x, e); x++;
        scanf("%d", &e);
    }
    return OK;
}

//从Lists中删除一个名称为ListName的线性表
status RemoveList(LISTS& Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            DestroyList(Lists.elem[i].L);//销毁这个表，并且处理掉
            for (int k = i; k < Lists.length - 1; k++)
                Lists.elem[k] = Lists.elem[k + 1];
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

//在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

//遍历Lists中各个线性表
status ListsTraverse(LISTS Lists) {
    if (Lists.length == 0) return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("%s ", Lists.elem[n].name);
        ListTraverse(Lists.elem[n].L);//注意这两个是不一样的
        putchar('\n');
    }
    return OK;
}

//选择一个线性表，输入其序号，后续可对其进行操作
LinkList ChooseList(LinkList& L, LISTS& Lists, int i) {//输入线性表号之后查找
    if (i > Lists.length || i < 1) return ERROR;
    else
    {
        return (Lists.elem[i - 1].L);
    }
}
status sortList(LinkList& L)
{
    if (L == NULL)
        return INFEASIBLE;
    LinkList p, q;
    p = L->next;
    while (p != NULL)
    {
        q = p->next;//比较简单的冒泡排序
        while (q != NULL)
        {
            if (p->data > q->data)
            {
                int temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
            q = q->next;
        }
        p = p->next;
    }
    return OK;
}
LinkList reverseList(LinkList &L)//链表反转
{
    LinkList p = L;
    p = p->next;
    int i = 0;
    int number[1001] = {};//用一个数组存储数据
    while (p != NULL)
    {
        number[i++] = p->data;
        p = p->next;
    }
    LinkList start;
    start = (LinkList)malloc(sizeof(LinkList));
    start->next = NULL;
    p = start;
    for (int j = 0; j < i / 2; j++)
    {
        int temp = number[j];//数组进行反转
        number[j] = number[i - 1 - j];
        number[i - 1 - j] = temp;
    }
    for (int j = 0; j < i; j++)
    {
        LinkList q;
        q = (LinkList)malloc(sizeof(LinkList));//重新交换数值
        q->data = number[j];
        q->next = NULL;
        p->next = q;
        p = q;
    }
    return start;
}
status RemoveNthFromEnd(LinkList& L, int n)
{
    if (ListEmpty(L) || L == NULL)
    {
        return ERROR;
    }
    else
    {
        int length = 0;
        LinkList p;
        p = L->next;
        while (p != NULL)
        {
            p = p->next;
            length++;//记录总长度为length
        }
        if (n > length)
            return ERROR;
        int target = length - n + 1;//正数的第几个元素
        int cur = 0;//标记当前点
        p = L->next;
        LinkList former = L;
        for (int i = 0; i < length; i++)
        {
            cur++;
            if (cur == target)
            {
                former->next = p->next; break;//这里是寻找到当前的那个节点
            }
            p = p->next;
            former = former->next;
        }
    }

    return OK;
}