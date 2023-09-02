#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
#pragma warning(disable:4996)//处理在vs里会警告的问题
#pragma warning(disable:6031)

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int KeyType;
typedef struct {
    KeyType  key;
    char others[20];
} TElemType; //二叉树结点类型定义

typedef struct BiTNode {  //二叉链表结点的定义
    TElemType  data;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

typedef struct {//森林的定义
    struct {
        char name[30];
        BiTree T;
    }elem[10];
    int length;
    int listsize;
}TREES;


status CreateBiTree(BiTree& T, TElemType definition[]);
status DestroyBiTree(BiTree& T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, KeyType e);
status Assign(BiTree& T, KeyType e, TElemType value);
BiTNode* GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree& T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree& T, char FileName[]);
status AddTree(TREES& Trees, char ListName[]);
status RemoveTree(TREES& Trees, char ListName[],BiTree &T);
int LocateTree(TREES Trees, char ListName[]);
status TreesTraverse(TREES Trees);
status ChooseTree(BiTree& T, TREES& Trees, int x);
status InvertTree(BiTree& T);
status MaxPathSum(BiTree T);
BiTree lower(BiTree root, int q, int p);//q,p两个为要查找的节点
status BiTreeEmpty(BiTree T);
status ClearBiTree(BiTree& T);


void visit(BiTree T)
{
    printf(" %d,%s", T->data.key, T->data.others);
}

int flag = 0, _flag = 0, num = 0;
int depth = 0, i = 0, j = 1;
int deg = 0, LR = 0;
BiTree T1, T2;
BiTree A[100];
FILE* fpo;
int total = 1;
int flag13 = 0;
int main(void)
{
    int op = 1, length, e, pre, next, flag1;
    char FileName[30] = { '\0' };
    char ListName[30] = { '\0' };
    TElemType value;
    TElemType definition[100] = { 0 };
    BiTree T = NULL;
    TREES Trees;
    Trees.length = 0;
    while (op) {
        system("cls");	printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("------------------------------------------------\n");
        printf("     1. CreateBiTree      2. DestroyBiTree\n");
        printf("     3. BiTreeDepth       4. LocateNode\n");
        printf("     5. Assign            6. GetSibling\n");
        printf("     7. InsertNode        8. DeleteNode\n");
        printf("     9. PreOrderTraverse  10.InOrderTraverse\n");
        printf("     11.PostOrderTraverse 12.LevelOrderTraverse\n");
        printf("     13.SaveBiTree        14.LoadBiTree\n");
        printf("     15.AddBiTree         16.RemoveBiTree\n");
        printf("     17.LocateBiTree      18.TreesTraverse\n");
        printf("     19.ChooseTree        20.InvertTree\n");
        printf("     21.MaxPathSum        22.LowestCommonAncestor\n");
        printf("     23.BiTreeEmpty       24.ClearBiTree\n");
        printf("     0. Exit\n");
        printf("------------------------------------------------\n");
        printf("\n请选择你的操作[0~19]:\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1: {
            printf("请输入带空子树的二叉树先序遍历序列：\n");
            flag = 0; num = 0; i = 0;
            do {
                scanf("%d%s", &definition[i].key, definition[i].others);
            } while (definition[i++].key != -1);
            flag1 = CreateBiTree(T, definition);
            if (flag1 == OK)
                printf("二叉树创建成功！\n");
            else if (flag1 == ERROR)
                printf("关键字不唯一\n");
            else if (flag1 == OVERFLOW)
                printf("溢出！\n");
            getchar(); getchar();
            getchar();
            break;

        }
        case 2:
            if (DestroyBiTree(T) == OK)
                printf("成功清空二叉树并释放数据元素的空间。\n");
            else
                printf("不能对不存在的二叉树进行销毁操作！\n");
            T = NULL;
            getchar(); getchar();
            getchar();
            break;
        case 3:
            depth = 0;
            BiTreeDepth(T);
            printf("二叉树的深度为%d\n", depth);
            getchar(); getchar();
            getchar();
            break;
        case 4:
            T1 = NULL;
            printf("请输入想要查找的结点的关键字：");
            scanf("%d", &e);
            LocateNode(T, e);
            if (T1) printf("关键字为%d的结点%d, %s\n", e, T1->data.key, T1->data.others);
            else printf("查找失败，不存在关键字为%d的结点\n", e);
            getchar(); getchar();
            getchar();
            break;
        case 5:
            flag = 0; T1 = NULL;
            printf("请输入想要修改的结点的关键字：");
            scanf("%d", &e);
            printf("将其结点值修改为：");
            scanf("%d %s", &value.key, value.others);
            flag1 = Assign(T, e, value);
            if (flag1 == ERROR)
                printf("赋值操作失败！\n");
            else if (flag1 == OK)
                printf("已将关键字为%d的结点值修改为 %d,%s\n", e, value.key, value.others);
            getchar(); getchar();
            getchar();
            break;
        case 6:
            T1 = NULL; T2 = NULL;
            flag = 0;
            printf("请输入想要从二叉树中获得兄弟结点的关键字：");
            scanf("%d", &e);
            GetSibling(T, e);
            if (T2) printf("关键字为%d的结点的兄弟结点为%d,%s\n", e, T2->data.key, T2->data.others);
            else printf("关键字为%d的结点无兄弟结点\n", e);
            getchar(); getchar();
            getchar();
            break;
        case 7:
            flag = 0, _flag = 0;
            T1 = NULL;
            printf("请输入插入结点的父亲的数字：");
            scanf("%d", &e);
            printf("插入结点作为 左孩子(0)/右孩子(1)/根节点(-1)：");
            scanf("%d", &LR);
            printf("插入结点的值：");
            scanf("%d %s", &value.key, value.others);
            flag1 = InsertNode(T, e, LR, value);
            if (flag1 == OK)
                printf("插入成功！\n");
            else if (flag1 == ERROR && _flag == 1)
                printf("新增结点关键字重复，插入失败！\n");
            else if (flag1 == ERROR && flag == 0)
                printf("无法找到父亲结点，插入失败！\n");
            getchar(); getchar();
            getchar();
            break;
        case 8:
            flag = 0; LR = 0; deg = 0; _flag = 0;
            T1 = NULL; T2 = NULL;
            printf("请输入想要在线二叉树中删除的结点数字：");
            scanf("%d", &e);
            flag1 = DeleteNode(T, e);
            if (flag1 == OK)
                printf("结点关键字为%d的结点已从二叉树中删除。\n", e);
            else if (flag1 == ERROR)
                printf("二叉树中不含有关键字为%d的结点，删除失败！\n", e);
            getchar(); getchar();
            getchar();
            break;
        case 9:
            printf("先序遍历二叉树：\n");
            flag1 = PreOrderTraverse(T, visit);
            if (flag1 != OK)
                printf("不能遍历不存在的二叉树！\n");
            else printf("\n");
            getchar(); getchar();
            getchar();
            break;
        case 10:
            printf("中序遍历二叉树：\n");
            flag1 = InOrderTraverse(T, visit);
            if (flag1 != OK)
                printf("不能遍历不存在的二叉树！\n");
            else printf("\n");
            getchar(); getchar();
            getchar();
            break;
        case 11:
            printf("后序遍历二叉树：\n");
            flag1 = PostOrderTraverse(T, visit);
            if (flag1 != OK)
                printf("不能遍历不存在的二叉树！\n");
            else printf("\n");
            getchar(); getchar();
            getchar();
            break;
        case 12:
            printf("层序遍历二叉树：\n");
            for (i = 0; i < 100; i++)
                A[i] = NULL;
            i = 0; j = 1;
            flag1 = LevelOrderTraverse(T, visit);
            if (flag1 != OK)
                printf("不能遍历不存在的二叉树！\n");
            else printf("\n");
            getchar(); getchar();
            getchar();
            break;
        case 13:
            printf("请输入文件名称：");
            scanf("%s", FileName);
            flag1 = SaveBiTree(T, FileName);
            if (flag1 == ERROR)
                printf("文件打开失败！\n");
            else if (flag1 == OK)
                printf("二叉树的内容已经复制到名称为 %s 的文件中。\n", FileName);
            else if (flag1 == INFEASIBLE)
                printf("不能对不存在的线性表进行进行写文件操作。\n");
            getchar(); getchar();
            getchar();
            break;
        case 14:
            i = 0; flag = 0; num = 0;
            printf("请输入文件名称：");
            scanf("%s", FileName);
            flag1 = LoadBiTree(T, FileName);
            if (flag1 == ERROR)
                printf("文件打开失败！\n");
            else if (flag1 == OK)
                printf("名称为 %s 的文件中的内容已复制到线性表中。\n", FileName);
            else if (flag1 == INFEASIBLE)
                printf("不能对已存在的线性表进行进行读文件操作。\n");
            else if (flag1 == OVERFLOW)
                printf("溢出！\n");
            getchar(); getchar();
            getchar();
            break;
        case 15:
            i = 0; flag = 0; num = 0;
            printf("请输入新增二叉树的名称：");
            scanf("%s", ListName);
            flag1 = AddTree(Trees, ListName);
            if (flag1 == OK) printf("成功新增名称为 %s 的二叉树。\n", ListName);
            else printf("新增失败！\n");
            getchar(); getchar();
            getchar();
            break;
        case 16:
            printf("请输入想要删除的二叉树的名称：");
            scanf("%s", ListName);
            flag1 = RemoveTree(Trees, ListName,T);
            if (flag1 == OK)
                printf("成功删除名称为 %s 的二叉树。\n", ListName);
            else if (flag1 == ERROR)
                printf("删除失败！\n");
            getchar(); getchar();
            getchar();
            break;
        case 17:
            flag1 = 0;
            printf("请输入想要查找的二叉树的名称：");
            scanf("%s", ListName);
            flag1 = LocateTree(Trees, ListName);
            if (flag1 == 0)
                printf("不存在名称为 %s 的二叉树。\n", ListName);
            else printf("名称为 %s 的二叉树的序号为%d\n", ListName, flag1);
            getchar(); getchar();
            getchar();
            break;
        case 18:
            printf("先序遍历森林中各个二叉树：\n");
            flag1 = TreesTraverse(Trees);
            if (flag1 == ERROR) printf("森林为空。\n");
            getchar(); getchar();
            getchar();
            break;
        case 19:

            printf("请输入想要进行操作的二叉树的序号（从1开始）：");
            scanf("%d", &e);
            flag1 = ChooseTree(T, Trees, e);
            if (flag1 == ERROR)
                printf("输入的序号不合法！\n");
            else printf("下面可对森林中序号为%d的二叉树进行操作。\n", e);
            getchar(); getchar();
            getchar();
            break;
        case 20:
            flag1 = InvertTree(T);
            if (flag1 == -1)
                printf("不能对空树进行操作");
            else
                printf("已经对树操作完成。");
            getchar(); getchar();
            getchar();
            break;
        case 21:
            flag1 = MaxPathSum(T);
            if (flag1 == 0)
                printf("树有误");
            else
                printf("求得长度为%d\n", flag1);
            getchar(); getchar();
            getchar();
            break;
        case 22:
            BiTree sa;
            int p, q;
            printf("请输入要查找的两个节点的数字值：");
            scanf("%d %d", &p, &q);
            sa = lower(T,p,q);
            if (sa == NULL)
                printf("没有公共祖先！");
            else
                printf("最近的祖先为%d %s\n", sa->data.key, sa->data.others);
            getchar(); getchar();
            getchar();
            break;
        case 23:
            if (T == NULL)
            {
                printf("二叉树不存在\n");
            }
            if (BiTreeEmpty(T) == TRUE)
            {
                printf("二叉树为空\n");
            }
            else
            {
                printf("二叉树不为空\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 24:
            if (ClearBiTree(T) == OK)
            {
                printf("二叉树成功清空\n");
            }
            else
            {
                printf("二叉树不存在\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 0:
            break;
        }//end of switch
        printf("\n");
    }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()


//1根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，如果有相同的关键字，返回ERROR。
status CreateBiTree(BiTree& T, TElemType definition[])
{
    if (flag == 0)
    {
        int i = 0;
        int j = 0;
        for (i = 0; definition[i].key != -1; i++)
        {
            if (definition[i].key == 0) i++;
            if (definition[i].key == -1) { flag = 1; break; }
            for (j = i + 1; definition[j].key != -1; j++)
            {
                if (definition[j].key != 0)
                {
                    if (definition[i].key == definition[j].key)
                        return ERROR;
                }
            }
        }
        flag = 1;
    }
    if (flag == 1)
    {
        if (definition[num].key == 0) { T = NULL; num++; }
        else
        {
            if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
                return OVERFLOW;
            T->data = definition[num];
            num++;
            CreateBiTree(T->lchild, definition);
            CreateBiTree(T->rchild, definition);
        }
        return OK;
    }
}

//2将二叉树设置成空，并删除所有结点，释放结点空间
status DestroyBiTree(BiTree& T)
{
    if (T == NULL) return ERROR;
    else {
        if (T->lchild != NULL) ClearBiTree(T->lchild);
        if (T->rchild != NULL) ClearBiTree(T->rchild);
        if (T->lchild == NULL && T->rchild == NULL) { free(T); T = NULL; return OK; }
    }
    return OK;
}

//3求二叉树T的深度
void Traverse(BiTree T, int i)
{
    i++;
    if (depth < i) depth = i;
    if (T->lchild) { Traverse(T->lchild, i); }//取全局变量来遍历
    if (T->rchild) { Traverse(T->rchild, i); }
    i--;
}
int BiTreeDepth(BiTree T)
{
    if (T != NULL)
    {
        Traverse(T, 0);
        return depth;
    }
    else return 0;
}

//4查找结点
BiTNode* LocateNode(BiTree T, KeyType e)
{
    if (T == NULL) return NULL;
    if (T->data.key == e) T1 = T;
    else
    {
        if (T->lchild) LocateNode(T->lchild, e);//同样也是寻找的过程
        if (T->rchild) LocateNode(T->rchild, e);
    }
    return T1;
}

//5实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
void check(BiTree& T, KeyType e, TElemType value)
{
    if (flag == 1)
        return;
    else
    {
        if (e != value.key && T->data.key == value.key) flag = 1;//寻找节点的过程
        if (e == T->data.key) T1 = T;
        else
        {
            if (T->lchild) check(T->lchild, e, value);
            if (T->rchild) check(T->rchild, e, value);
        }
    }
}
status Assign(BiTree& T, KeyType e, TElemType value)
{
    if (T == NULL) return ERROR;
    T1 = T;
    if (flag == 0) check(T, e, value);
    if (flag == 1) return ERROR;
    else flag = -1;
    if (T1 == T && T->data.key != value.key) return ERROR;
    T1->data = value; return OK;
}

//6实现获得兄弟结点
void _GetSibling(BiTree T, KeyType e, BiTNode* T1)
{
    if (flag == 1) return;
    else
    {
        if (T1->lchild && flag == 0)
        {
            if (T1->lchild->data.key == e) { T2 = T1->rchild; flag = 1; return; }
            else _GetSibling(T, e, T1->lchild);
        }
        if (T1->rchild && flag == 0)
        {
            if (T1->rchild->data.key == e) { T2 = T1->lchild; flag = 1; return; }
            else _GetSibling(T, e, T1->rchild);
        }
    }
}
BiTNode* GetSibling(BiTree T, KeyType e)
{
    T1 = T;
    if (T1)
    {
        _GetSibling(T, e, T1);
        return T2;
    }
    else return ERROR;
}

//7插入结点。此题允许通过增加其它函数辅助实现本关任务
void Check(BiTree& T, KeyType e)//找到父亲结点 flag==1表示找到了关键字为e的父亲结点 且使T1指针指向被找到的结点
{
    if (flag == 1) return;
    else
    {
        if (T->data.key == e)
        {
            T1 = T; flag = 1; return;
        }
        if (T->lchild && flag == 0) Check(T->lchild, e);
        if (T->rchild && flag == 0) Check(T->rchild, e);
    }

}
void _Check(BiTree& T, TElemType c)//判断新增结点是否有关键字重复 如新增结点与原有结点有关键字重复则_flag==1;
{
    if (_flag == 1) return;
    else
    {
        if (T->data.key == c.key)
        {
            _flag = 1; return;
        }
        if (T->lchild && _flag == 0) _Check(T->lchild, c);
        if (T->rchild && _flag == 0) _Check(T->rchild, c);
    }
}
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c)
{
    Check(T, e); _Check(T, c);
    if (_flag == 1) return ERROR;//新增结点关键字重复，直接返回错误。
    if (LR == -1)//插入结点是根节点，不用考虑flag的值。
    {
        BiTree t = (BiTNode*)malloc(sizeof(BiTNode));
        t->rchild = T;
        T = t;
        T->data = c;
        T->lchild = NULL;
        return OK;
    }
    if (flag == 0) return ERROR;//在插入结点不是根节点的情况下，没有找到其父亲，直接返回错误。
    else
    {
        BiTree t = (BiTNode*)malloc(sizeof(BiTNode));//给新增结点申请储存空间。
        if (LR == 0)//新增结点为父亲结点的左孩子
        {
            if (T1->lchild == NULL) t->rchild = NULL;
            else t->rchild = T1->lchild;
            t->lchild = NULL;
            T1->lchild = t;
            t->data = c;
            return OK;
        }
        else if (LR == 1)//新增结点为父亲结点的右孩子
        {
            if (T1->rchild == NULL) t->rchild = NULL;
            else t->rchild = T1->rchild;
            t->lchild = NULL;
            T1->rchild = t;
            t->data = c;
            return OK;
        }
    }
}

//8删除结点。此题允许通过增加其它函数辅助实现本关任务
void Check1(BiTree& T, KeyType e)
{
    if (flag == 1) return;
    else
    {
        if (T->lchild && T->lchild->data.key == e)
        {
            T1 = T; flag = 1; LR = -1; return;
        }
        if (T->rchild && T->rchild->data.key == e)
        {
            T1 = T; flag = 1; LR = 1; return;
        }
        if (T->lchild && flag == 0) Check1(T->lchild, e);
        if (T->rchild && flag == 0) Check1(T->rchild, e);
    }

}
//重新写的删除节点代码
int flag8 = 0;//刚开始的时候，假设其没有为为确定的节点
int swi8 = 1;//这个是用来控制第一个节点的问题的

int fin8 = 0;//这是用来控制寻找最左子树最右端节点的
status check_no8(BiTree T, KeyType e)
{
    if (T->data.key == e && !flag8)
        flag8 = 1;//如果找到了这个节点，那么可以返回1
    if (T->lchild != NULL && !flag8)
    {
        check_no8(T->lchild, e);
    }
    if (T->rchild != NULL && !flag8)
    {
        check_no8(T->rchild, e);
    }
    return flag8;

}

BiTree FindNode8(BiTree T)
{
    if (T->rchild == NULL && !fin8)
    {
        fin8 = 1;
        return T;
    }
    if (T->rchild != NULL && !fin8)
    {
        FindNode8(T->rchild);
    }
}



BiTree pre;
status DeleteNode(BiTree& T, KeyType e)
//删除结点。此题允许通过增加其它函数辅助实现本关任务
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int du = 0;//总的度数
    if (T != NULL && T->lchild != NULL)
        du++;
    if (T != NULL && T->rchild != NULL)
        du++;
    if (check_no8(T, e) != 1 && swi8)
    {
        return ERROR;//没有这样的节点
    }
    if (T->data.key == e && swi8)//第一个节点是目标节点
    {
        BiTree s;
        if (du == 0)
        {
            free(T);
            T = NULL;
            return OK;
        }
        if (du == 1)
        {

            if (T->lchild != NULL)
            {
                s = T->lchild;
                free(T);
                T = s;
            }
            else
            {
                s = T->rchild;
                free(T);
                T = s;
            }
            return OK;
        }
        if (du == 2)
        {
            BiTree head;
            head = T->lchild;
            s = FindNode8(T->lchild);
            s->rchild = T->rchild;
            free(T);
            T = head;
            return OK;
        }

    }
    if (swi8)
        pre = T;//最前面的节点为pre
    swi8 = 0;
    //讨论完了特殊的，该讨论一般的了
    BiTree save;
    BiTree head;
    if (T->data.key == e)
    {
        if (du == 0)
        {
            if (pre->lchild == T)
            {
                free(T);
                pre->lchild = NULL;
            }
            if (pre->rchild == T)
            {
                free(T);
                pre->rchild = NULL;
            }

            return OK;
        }
        if (du == 1)
        {
            if (pre->lchild == T)
            {
                if (T->lchild != NULL)
                {
                    pre->lchild = T->lchild;
                    free(T);
                    return OK;
                }
                if (T->rchild != NULL)
                {
                    BiTree c = T;
                    pre->lchild = T->rchild;
                    free(c);
                    return OK;
                }
            }
            if (pre->rchild == T)
            {
                if (T->lchild != NULL)
                {
                    pre->rchild = T->lchild;
                    free(T);
                    return OK;
                }
                if (T->rchild != NULL)
                {
                    pre->rchild = T->rchild;
                    free(T);
                    return OK;
                }
            }
        }
        if (du == 2)
        {
            head = T->lchild;
            save = FindNode8(T->lchild);
            save->rchild = T->rchild;
            free(T);
            T = head;
            return OK;
        }
    }
    if (T->lchild != NULL)
    {
        pre = T;
        DeleteNode(T->lchild, e);
    }
    if (T->rchild != NULL)
    {
        pre = T;
        DeleteNode(T->rchild, e);
    }
    return OK;
    /********** End **********/
}
//9先序遍历二叉树T
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T == NULL) return ERROR;
    else
    {
        visit(T);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return OK;
}

//10中序遍历二叉树T
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T == NULL) return ERROR;
    else
    {
        InOrderTraverse(T->lchild, visit);
        visit(T);
        InOrderTraverse(T->rchild, visit);
    }
    return OK;
}

//11后序遍历二叉树T
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T == NULL) return ERROR;
    else
    {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T);
    }
    return OK;
}

//12按层遍历二叉树T
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    A[0] = T;
    if (T == NULL) return ERROR;
    else
    {
        visit(T); i++;
        if (T->lchild) { A[j] = T->lchild; j++; }
        if (T->rchild) { A[j] = T->rchild; j++; }
        LevelOrderTraverse(A[i], visit);
        return OK;
    }
}

//13将二叉树的结点数据写入到文件FileName中

status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (flag13 == 0)
    {
        fpo = fopen(FileName, "w+");
        flag13 = 1;
    }
    if (T == NULL)
    {
        fprintf(fpo, "%d %s ", 0, "null");

    }
    else
    {
        fprintf(fpo, "%d %s ", total++, T->data.others);
    }
    if (T != NULL)
    {
        SaveBiTree(T->lchild, FileName);
        SaveBiTree(T->rchild, FileName);
    }
    return OK;

    /********** End 1 **********/
}
////14读入文件FileName的结点数据，创建二叉树
status LoadBiTree(BiTree& T, char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    TElemType definition[100] = {};
    fprintf(fpo, "%d %s ", -1, "null");
    fclose(fpo);
    fpo = fopen(FileName, "r+");
    int i = 0;
    do {
        fscanf(fpo, "%d %s", &definition[i].key, definition[i].others);
    } while (definition[i++].key != -1);
    CreateBiTree(T, definition);
    return OK;

    /********** End 2 **********/
}

//15在森林中添加一棵树
status AddTree(TREES& Trees, char ListName[])
{
    for (int i = 0; i < Trees.length; i++)
        if (strcmp(Trees.elem[i].name, ListName) == 0)
        {
            printf("集合中已存在名称为 %s 的二叉树！\n", ListName);
            return ERROR;
        }
    TElemType definition[100] = { 0 };//这个比较简单，就是多表管理的应用
    printf("在二叉树 %s 中添加结点，请输入带空子树的二叉树先序遍历序列：\n", ListName);
    do {
        scanf("%d %s", &definition[i].key, definition[i].others);
    } while (definition[i++].key != -1);
    int a = CreateBiTree(Trees.elem[Trees.length].T, definition);
    if (a == OK) {
        strcpy(Trees.elem[Trees.length].name, ListName);
        Trees.length++;
        return OK;
    }
    else if (a == ERROR) {
        printf("关键字不唯一！"); return ERROR;
    }
}

//16在森林中删除一棵树
status RemoveTree(TREES& Trees, char ListName[],BiTree &T)
{
    for (int i = 0; i < Trees.length; i++)
    {
        if (strcmp(Trees.elem[i].name, ListName) == 0)
        {
            if (T == Trees.elem[i].T)
                T = NULL;
            for (int k = i; k < Trees.length - 1; k++)
                Trees.elem[k] = Trees.elem[k + 1];
            Trees.length--;
            return OK;
        }
    }
    return ERROR;
}

//17在森林中查找一个名称为ListName的二叉树，成功返回逻辑序号，否则返回0
int LocateTree(TREES Trees, char ListName[]) {
    for (int i = 0; i < Trees.length; i++)
    {
        if (strcmp(Trees.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

//18遍历森林中各个二叉树
status TreesTraverse(TREES Trees) {
    if (Trees.length == 0) return ERROR;
    for (int n = 0; n < Trees.length; n++)
    {
        printf("%s ", Trees.elem[n].name);
        PreOrderTraverse(Trees.elem[n].T, visit);
        putchar('\n');
    }
    return OK;
}

//19选择一个二叉树，输入其序号，后续可对其进行操作
status ChooseTree(BiTree& T, TREES& Trees, int x) {
    if (x > Trees.length || x < 1) return ERROR;
    else
    {
        T = Trees.elem[x-1].T;
    }
    return OK;
}
//20反转二叉树
status InvertTree(BiTree& T)
{
    if (T == NULL)
        return INFEASIBLE;//采用后序遍历的思路
    InvertTree(T->lchild);//从下面依次向上遍历
    InvertTree(T->rchild);
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    return OK;
}

//21对二叉树中的节点求最大路径和
status MaxPathSum(BiTree T)//key为当前值，dep为深度
{
    if (T == NULL)
        return 0;//如果为NULL就返回0
    int lef = MaxPathSum(T->lchild);//将左右子树的最大值返回
    int right = MaxPathSum(T->rchild);
    return T->data.key + max(lef, right);//最后求出左右子树中最大的那个一个
    //有点像dp的思想，从下面一直网上走，走到最后得到最大值;
}
//22求公共祖先
BiTree lower(BiTree root, int q, int p)//q,p两个为要查找的节点
{
    if (root == NULL || root->data.key == q || root->data.key == p)//如果是空节点就直接返回就行，如果是目标节点就返回目标节点
        return root;
    BiTree left = lower(root->lchild, p, q);//找出在左边的目标节点
    BiTree right = lower(root->rchild, p, q);//找出在右边的目标节点
    if (left != NULL && right != NULL) return root;//如果左右找到了目标节点，那么就说明找到了

    if (left == NULL && right != NULL) return right;//如果左边有，就返回左边的
    else if (left != NULL && right == NULL) return left;//右边有就返回右边的
    else { //  (left == NULL && right == NULL)
        return NULL;
    }
}

status BiTreeEmpty(BiTree T)
{
    if (T->data.key == -1)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

status ClearBiTree(BiTree& T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (T == NULL)
        return ERROR;
    if (T)
    {
        T->data.key = -1;
        memset(T->data.others, '\0', 20);
        if (T->lchild != NULL)
            ClearBiTree(T->lchild);
        if (T->rchild != NULL)
            ClearBiTree(T->rchild);
    }
    return OK;
    /********** End **********/
}