/* Linear Table On Sequence Structure */
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <algorithm>
#include <iostream>
using namespace std;
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
typedef struct {  //顺序表（顺序结构）的定义
    ElemType* elem;
    int length;
    int listsize;
}SqList;
typedef struct {  //线性表的管理表定义
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;


/*-----page 19 on textbook ---------*/
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType& e);
int LocateElem(SqList L, ElemType e);
status PriorElem(SqList L, ElemType e, ElemType& pre);
status NextElem(SqList L, ElemType e, ElemType& next);
status ListInsert(SqList& L, int i, ElemType e);
status ListDelete(SqList& L, int i, ElemType& e);
status ListTraverse(SqList L);
status  SaveList(SqList L, char FileName[]);
status  LoadList(SqList& L, char FileName[]);
status AddList(LISTS& Lists, char ListName[]);
status RemoveList(LISTS& Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
status ShowList(LISTS Lists);
status sortList(SqList& L);
status SubArrayNum(SqList L, ElemType k);
status MaxSubArray(SqList L);



int main(void) {
    SqList L;
    LISTS Lists;
    Lists.length = 0;
    for (int i = 0; i < 10; i++)
        Lists.elem[i].L.elem = NULL;
    int op = 1, flag, length, i, e, pre, next;
    char FileName[30] = { '\0' };
    char ListName[30] = { '\0' };
    L.elem = NULL;
    int q = 0;
    SqList* mylist = NULL;
    char fe[100] = {};
    while (op) {
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       2. DestroyList\n");
        printf("    	  3. ClearList      4. ListEmpty\n");
        printf("    	  5. ListLength     6. GetElem  \n");
        printf("    	  7.LocateElem      8.PriorElem\n");
        printf("    	  9. NextElem       10. ListInsert\n");
        printf("    	  11. ListDelete    12. ListTraverse\n");
        printf("    	  13. SaveList      14. AddList\n");
        printf("    	  15. RemoveList    16. LocateList\n");
        printf("          17. ShowList      18.LoadList\n");
        printf("          19.sort           20.ChooseList\n");
        printf("          21.SubArrayNum    22.MaxSubArray");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~22]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            //printf("\n----IntiList功能待实现！\n");
            if (InitList(L) == OK) printf("线性表创建成功！\n");
            else printf("线性表创建失败！\n");
            getchar(); getchar();
            break;
        case 2:
            if (mylist != NULL)
                L = *mylist;
            if (DestroyList(L) == OK)
                printf("成功销毁线性表并释放数据元素的空间。\n");
            else
                printf("不能对不存在的线性表进行销毁操作！\n");
            getchar(); getchar();
            break;
        case 3:
            if (mylist != NULL)
                L = *mylist;
            if (ClearList(L) == OK)
                printf("成功删除线性表中所有的元素。\n");
            else
                printf("不能对不存在的线性表进行清空操作！\n");
            getchar(); getchar();
            break;
        case 4:
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
            length = ListLength(L);
            if (length >= 0)
                printf("线性表的长度为%d。\n", length);
            else
                printf("不能对不存在的线性表求长！\n");
            getchar(); getchar();
            break;
        case 6:
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
            printf("请输入想要删除的元素的序号：");
            scanf("%d", &i);
            flag = ListDelete(L, i, e);
            if (flag == OK)
                printf("序号为%d的元素%d已经从线性表中删除。\n", i, e);
            else if (flag == ERROR)
                printf("删除位置不正确！");
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行删除！\n");
            getchar(); getchar();
            break;

        case 12:
            if (mylist != NULL)
                L = *mylist;
            flag = ListTraverse(L);
            if (flag == INFEASIBLE)
                printf("不能遍历不存在的线性表！\n");
            else if (flag == ERROR)
                printf("线性表是空表。\n");
            else printf("\n");
            getchar(); getchar();
            break;
        
        case 13:
            if (mylist != NULL)
                L = *mylist;
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
        {char ListName[30] = { '\0' };
        printf("请输入新增线性表的名称：");
        scanf("%s", ListName);
        flag = AddList(Lists, ListName);
        if (flag == OK) 
        { 
            printf("成功新增名称为 %s 的线性表。\n", ListName);
            printf("接下来请输入该线性表的数字:");
            scanf("%d", &e);
            while (e)
            {
                ListInsert(Lists.elem[Lists.length - 1].L, Lists.elem[Lists.length - 1].L.length + 1, e);
                scanf("%d", &e);
            }
            printf("成功添加数字到线性表!");
        }
        else printf("新增失败！\n");
        
        getchar(); getchar();
        break;
        }
        case 15:
            printf("请输入想要删除的线性表的名称：");
            scanf("%s", ListName);
            flag = RemoveList(Lists, ListName);
            if (flag == OK)
                printf("成功删除名称为 %s 的线性表。\n", ListName);
            else if (flag == ERROR)
                printf("删除失败！\n");
            getchar(); getchar();
            break;
        case 16:
        {char ListName[30] = { '\0' };
        printf("请输入想要查找的线性表的名称：");
        scanf("%s", ListName);
        i = LocateList(Lists, ListName);
        if (i == 0)
            printf("不存在名称为 %s 的线性表。\n", ListName);
        else printf("名称为 %s 的线性表的序号为%d\n", ListName, i);
        getchar(); getchar();
        break;
        }
        case 17:
            ShowList(Lists);
            getchar(); getchar();
            break;
        case 18:
            if (mylist != NULL)
                L = *mylist;
            printf("请输入文件名称：");
            scanf("%s", FileName);
            flag = LoadList(L, FileName);
            if (flag == ERROR)
                printf("文件读取失败！\n");
            else if (flag == OK)
                printf("线性表的内容读取为名称为 %s 的文件中。\n", FileName);
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行进行文件操作。\n");
            getchar(); getchar();
            break;
        case 19:
            if (mylist != NULL)
                L = *mylist;
            q = sortList(L);
            if (q == INFEASIBLE)
                printf("空表！");
            if (q == OK)
                printf("已经完成赋值！");
            getchar(); getchar();
            break;
        case 20:

            printf("请输入选择的表\n");
            scanf("%s", fe);
            i = 0;
            for (i; i < Lists.length; i++)
            {
                if (strcmp(fe, Lists.elem[i].name) == 0)
                {
                    L = Lists.elem[i].L;
                    printf("已经选取到该表！");
                }
            }
            if (i == Lists.length - 1)
                printf("没有这样的表");
            getchar(); getchar();
            break;
        case 21:
            printf("查找数组的和为:\n");
            scanf("%d", &e);
            printf("即将查找数组和为%d的数组个数\n", e);
            if (L.elem == NULL)
            {
                printf("线性表不存在\n");
            }
            else
            {
                i = SubArrayNum(L, e);
                printf("和为%d的字数组个数为：%d\n", e, i);
            }
            getchar(); getchar();
            break;
        case 22:
            if (L.elem == NULL)
            {
                printf("线性表为空\n");
            }
            else
            {
                e = MaxSubArray(L);
                printf("该线性组的最大连续子数组和为%d\n", e);
            }
            getchar(); getchar();
            break;
        case 0:
            break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}//end of main()
//下面是代码实现过程
status InitList(SqList& L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.length > 0 && L.elem)
        return INFEASIBLE;
    L.elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);//分配空间
    L.length = 0;//初始化长度
    L.listsize = LIST_INIT_SIZE;
    return OK;


    /********** End **********/
}
status DestroyList(SqList& L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;

    /********** End **********/
}
status ClearList(SqList& L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    L.length = 0;
    return OK;

    /********** End **********/
}
status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL && L.length == 0)
        return INFEASIBLE;
    else if (L.length == 0)
        return OK;
    else
        return ERROR;

    /********** End **********/
}
status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    else
        return L.length;

    /********** End **********/
}
status GetElem(SqList L, int i, ElemType& e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    else if (i - 1 > L.length || i == 0)
        return ERROR;
    else
    {
        e = L.elem[i - 1];
        return OK;
    }

    /********** End **********/
}
int LocateElem(SqList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
            return i + 1;
    }
    return ERROR;


    /********** End **********/
}
status PriorElem(SqList L, ElemType e, ElemType& pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
        {
            if (i == 0)//查看其是否为第一个元素
                return ERROR;
            else
                pre = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}
status NextElem(SqList L, ElemType e, ElemType& next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)//查看其是否为最后一个元素
        {
            if (i == L.length - 1)
                return ERROR;
            else
                next = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR;

    /********** End **********/
}
status ListInsert(SqList& L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/
    if (L.elem == NULL) return INFEASIBLE;//表不存在
    if (i <= 0 || i > L.length + 1) return ERROR;//插入位置越界
    int after = i - 1;
    if (L.length == L.listsize)
    {
        ElemType* newbase = NULL;
        newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));//扩大空间
        L.elem = newbase;//重新指向
        L.listsize += LISTINCREMENT;//数组最大长度扩展
    }
    for (int j = L.length - 1; j >= after; j--)
    {
        L.elem[j + 1] = L.elem[j];
    }
    L.elem[after] = e;
    L.length++;//元素个数+1
    return OK;
    /********** End **********/
}
status ListDelete(SqList& L, int i, ElemType& e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L.elem)
        return INFEASIBLE;
    if (i >= L.length || i == 0)//检测删除位置是否合法
        return ERROR;
    e = L.elem[i - 1];
    for (int j = i - 1; j < L.length; j++)
    {
        L.elem[j] = L.elem[j + 1];
    }
    L.length--;
    return OK;

    /********** End **********/
}
status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    /********** Begin *********/

    if (L.elem == NULL) return INFEASIBLE;//表不存在
    for (int j = 0; j <= L.length - 1; j++)
    {
        j == L.length - 1 ? printf("%d", L.elem[j]) : printf("%d ", L.elem[j]);

    }
    return OK;
    /********** End **********/
}
status  SaveList(SqList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (!L.elem)
        return INFEASIBLE;
    FILE* fp = fopen(FileName, "w+");//数据的读取
    for (int i = 0; i < L.length; i++)
    {
        fprintf(fp, "%d ", L.elem[i]);
    }
    fclose(fp);//一定记着关
    return OK;
    /********** End **********/
}
status  LoadList(SqList& L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L.elem)
        return INFEASIBLE;
    L.elem = (ElemType*)malloc(sizeof(ElemType) * 100);
    FILE* fp = fopen(FileName, "r+");//数据写入
    int i = 0;
    while (fscanf(fp, "%d ", &(L.elem[i++])) != EOF);
    L.length = i - 1;
    fclose(fp);
    return OK;
    /********** End **********/
}
status AddList(LISTS& Lists, char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    Lists.elem[Lists.length].L.elem = NULL;//新子表为空
    InitList(Lists.elem[Lists.length].L);//创建一个新子表
    int i;
    //名字字符串复制给LIST
    for (i = 0; ListName[i] != '\0'; i++)
    {
        Lists.elem[Lists.length].name[i] = ListName[i];
    }
    Lists.elem[Lists.length].name[i] = '\0';
    //名字字符串复制给LIST
    Lists.length++;//长度+1
    return OK;
    /********** End **********/
}
status RemoveList(LISTS& Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    if (Lists.length == 0)
    {
        printf("该表为空表!请按回车继续,");
        return 0;//空表直接返回未知
    }
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i, j, flag = 0;
    for (j = 0; j < Lists.length; j++)//遍历所有子表
    {
        for (i = 0; ListName[i] != '\0'; i++)//判断名字一一对应
        {
            if (Lists.elem[j].name[i] != ListName[i]) break;
        }
        if (ListName[i] == '\0')
        {
            flag = 1;
            break;
        }
    }
    //判断名字是否相同
    if (flag == 1)
    {
        Lists.elem[j].L.elem = NULL;
        Lists.elem[j].L.elem = Lists.elem[j + 1].L.elem;//数组元素改变
        Lists.elem[j].L.length = Lists.elem[j + 1].L.length;//长度改变
        //名字改变
        for (i = 0; Lists.elem[j + 1].name[i] != '\0'; i++)
        {
            Lists.elem[j].name[i] = Lists.elem[j + 1].name[i];
        }
        Lists.elem[j].name[i] = '\0';
        //
        Lists.length--;
        return OK;
    }
    else return INFEASIBLE;//删除失败
    /********** End **********/
}
int LocateList(LISTS Lists, char ListName[])
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
    if (Lists.length == 0)
    {
        printf("该表为空表!请按回车继续,");
        return 0;//空表直接返回未知
    }
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i, j, flag = 0;
    for (j = 0; j < Lists.length; j++)//遍历所有子表
    {
        for (i = 0; ListName[i] != '\0'; i++)//找到所寻名字
        {
            if (Lists.elem[j].name[i] != ListName[i]) break;
        }
        if (ListName[i] == '\0')
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1) 
    {
        printf("该表内部的元素为:");
        for (int k = 0; k < Lists.elem[j].L.length; k++)
        {
            printf("%d ", Lists.elem[j].L.elem[k]);
        }
        printf("\n");
        return j + 1; 
    }
    //当找到就返回位置
    else return 0;//没找到就返回-1
    /********** End **********/
}
status ShowList(LISTS Lists)
{
    if (Lists.length == 0)
    {
        printf("该表为空表!请按回车继续");
        return 0;//空表直接返回未知
    }
    for (int i = 0; i < Lists.length; i++)
    {
        printf("%s ", Lists.elem[i].name);
        for (int j = 0; j < Lists.elem[i].L.length; j++)
        {
            printf("%d ", Lists.elem[i].L.elem[j]);
        }
        printf("\n");
    }
    return 1;
}
status sortList(SqList& L)
{
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length - 1; i++)
    {
        for (int j = i + 1; j < L.length; j++)
        {
            if (L.elem[i] > L.elem[j])
            {
                int temp = L.elem[i];
                L.elem[i] = L.elem[j];
                L.elem[j] = temp;
            }
        }
    }
    return OK;
}

status SubArrayNum(SqList L, ElemType k)
{
    int sum[30];
    int m = 0;//计数
    sum[0] = L.elem[0];

    for (int i = 1; i < L.length; i++) {
        sum[i] = sum[i - 1] + L.elem[i];
        if (sum[i] == k)
            m++;
    }
    for (int p = 0; p < L.length - 1; p++)
        for (int q = p + 1; q < L.length; q++) {
            if ((sum[q] - sum[p]) == k)
                m++;
        }

    if (sum[0] == k)
        m++;//加上遗漏的一项
    return m;
}

status MaxSubArray(SqList L)
{
    if (L.elem == NULL) return INFEASIBLE;
    else {

        int* sum = (int*)malloc(L.length * sizeof(int));
        sum[0] = L.elem[0];
        int i, maxl = L.elem[0];
        for (i = 1; i < L.length; i++)
        {
            sum[i] = (sum[i - 1] + L.elem[i] > L.elem[i] ? sum[i - 1] + L.elem[i] : L.elem[i]);
            if (maxl < sum[i]) maxl = sum[i];
        }
        return maxl;
    }
}
