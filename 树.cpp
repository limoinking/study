#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<stdlib.h>
#include<string.h>
#include <iostream>
using namespace std;
#pragma warning(disable:4996)//������vs��ᾯ�������
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
} TElemType; //������������Ͷ���

typedef struct BiTNode {  //����������Ķ���
    TElemType  data;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;

typedef struct {//ɭ�ֵĶ���
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
BiTree lower(BiTree root, int q, int p);//q,p����ΪҪ���ҵĽڵ�
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
        printf("\n��ѡ����Ĳ���[0~19]:\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1: {
            printf("��������������Ķ���������������У�\n");
            flag = 0; num = 0; i = 0;
            do {
                scanf("%d%s", &definition[i].key, definition[i].others);
            } while (definition[i++].key != -1);
            flag1 = CreateBiTree(T, definition);
            if (flag1 == OK)
                printf("�����������ɹ���\n");
            else if (flag1 == ERROR)
                printf("�ؼ��ֲ�Ψһ\n");
            else if (flag1 == OVERFLOW)
                printf("�����\n");
            getchar(); getchar();
            getchar();
            break;

        }
        case 2:
            if (DestroyBiTree(T) == OK)
                printf("�ɹ���ն��������ͷ�����Ԫ�صĿռ䡣\n");
            else
                printf("���ܶԲ����ڵĶ������������ٲ�����\n");
            T = NULL;
            getchar(); getchar();
            getchar();
            break;
        case 3:
            depth = 0;
            BiTreeDepth(T);
            printf("�����������Ϊ%d\n", depth);
            getchar(); getchar();
            getchar();
            break;
        case 4:
            T1 = NULL;
            printf("��������Ҫ���ҵĽ��Ĺؼ��֣�");
            scanf("%d", &e);
            LocateNode(T, e);
            if (T1) printf("�ؼ���Ϊ%d�Ľ��%d, %s\n", e, T1->data.key, T1->data.others);
            else printf("����ʧ�ܣ������ڹؼ���Ϊ%d�Ľ��\n", e);
            getchar(); getchar();
            getchar();
            break;
        case 5:
            flag = 0; T1 = NULL;
            printf("��������Ҫ�޸ĵĽ��Ĺؼ��֣�");
            scanf("%d", &e);
            printf("������ֵ�޸�Ϊ��");
            scanf("%d %s", &value.key, value.others);
            flag1 = Assign(T, e, value);
            if (flag1 == ERROR)
                printf("��ֵ����ʧ�ܣ�\n");
            else if (flag1 == OK)
                printf("�ѽ��ؼ���Ϊ%d�Ľ��ֵ�޸�Ϊ %d,%s\n", e, value.key, value.others);
            getchar(); getchar();
            getchar();
            break;
        case 6:
            T1 = NULL; T2 = NULL;
            flag = 0;
            printf("��������Ҫ�Ӷ������л���ֵܽ��Ĺؼ��֣�");
            scanf("%d", &e);
            GetSibling(T, e);
            if (T2) printf("�ؼ���Ϊ%d�Ľ����ֵܽ��Ϊ%d,%s\n", e, T2->data.key, T2->data.others);
            else printf("�ؼ���Ϊ%d�Ľ�����ֵܽ��\n", e);
            getchar(); getchar();
            getchar();
            break;
        case 7:
            flag = 0, _flag = 0;
            T1 = NULL;
            printf("�����������ĸ��׵����֣�");
            scanf("%d", &e);
            printf("��������Ϊ ����(0)/�Һ���(1)/���ڵ�(-1)��");
            scanf("%d", &LR);
            printf("�������ֵ��");
            scanf("%d %s", &value.key, value.others);
            flag1 = InsertNode(T, e, LR, value);
            if (flag1 == OK)
                printf("����ɹ���\n");
            else if (flag1 == ERROR && _flag == 1)
                printf("�������ؼ����ظ�������ʧ�ܣ�\n");
            else if (flag1 == ERROR && flag == 0)
                printf("�޷��ҵ����׽�㣬����ʧ�ܣ�\n");
            getchar(); getchar();
            getchar();
            break;
        case 8:
            flag = 0; LR = 0; deg = 0; _flag = 0;
            T1 = NULL; T2 = NULL;
            printf("��������Ҫ���߶�������ɾ���Ľ�����֣�");
            scanf("%d", &e);
            flag1 = DeleteNode(T, e);
            if (flag1 == OK)
                printf("���ؼ���Ϊ%d�Ľ���ѴӶ�������ɾ����\n", e);
            else if (flag1 == ERROR)
                printf("�������в����йؼ���Ϊ%d�Ľ�㣬ɾ��ʧ�ܣ�\n", e);
            getchar(); getchar();
            getchar();
            break;
        case 9:
            printf("���������������\n");
            flag1 = PreOrderTraverse(T, visit);
            if (flag1 != OK)
                printf("���ܱ��������ڵĶ�������\n");
            else printf("\n");
            getchar(); getchar();
            getchar();
            break;
        case 10:
            printf("���������������\n");
            flag1 = InOrderTraverse(T, visit);
            if (flag1 != OK)
                printf("���ܱ��������ڵĶ�������\n");
            else printf("\n");
            getchar(); getchar();
            getchar();
            break;
        case 11:
            printf("���������������\n");
            flag1 = PostOrderTraverse(T, visit);
            if (flag1 != OK)
                printf("���ܱ��������ڵĶ�������\n");
            else printf("\n");
            getchar(); getchar();
            getchar();
            break;
        case 12:
            printf("���������������\n");
            for (i = 0; i < 100; i++)
                A[i] = NULL;
            i = 0; j = 1;
            flag1 = LevelOrderTraverse(T, visit);
            if (flag1 != OK)
                printf("���ܱ��������ڵĶ�������\n");
            else printf("\n");
            getchar(); getchar();
            getchar();
            break;
        case 13:
            printf("�������ļ����ƣ�");
            scanf("%s", FileName);
            flag1 = SaveBiTree(T, FileName);
            if (flag1 == ERROR)
                printf("�ļ���ʧ�ܣ�\n");
            else if (flag1 == OK)
                printf("�������������Ѿ����Ƶ�����Ϊ %s ���ļ��С�\n", FileName);
            else if (flag1 == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա���н���д�ļ�������\n");
            getchar(); getchar();
            getchar();
            break;
        case 14:
            i = 0; flag = 0; num = 0;
            printf("�������ļ����ƣ�");
            scanf("%s", FileName);
            flag1 = LoadBiTree(T, FileName);
            if (flag1 == ERROR)
                printf("�ļ���ʧ�ܣ�\n");
            else if (flag1 == OK)
                printf("����Ϊ %s ���ļ��е������Ѹ��Ƶ����Ա��С�\n", FileName);
            else if (flag1 == INFEASIBLE)
                printf("���ܶ��Ѵ��ڵ����Ա���н��ж��ļ�������\n");
            else if (flag1 == OVERFLOW)
                printf("�����\n");
            getchar(); getchar();
            getchar();
            break;
        case 15:
            i = 0; flag = 0; num = 0;
            printf("���������������������ƣ�");
            scanf("%s", ListName);
            flag1 = AddTree(Trees, ListName);
            if (flag1 == OK) printf("�ɹ���������Ϊ %s �Ķ�������\n", ListName);
            else printf("����ʧ�ܣ�\n");
            getchar(); getchar();
            getchar();
            break;
        case 16:
            printf("��������Ҫɾ���Ķ����������ƣ�");
            scanf("%s", ListName);
            flag1 = RemoveTree(Trees, ListName,T);
            if (flag1 == OK)
                printf("�ɹ�ɾ������Ϊ %s �Ķ�������\n", ListName);
            else if (flag1 == ERROR)
                printf("ɾ��ʧ�ܣ�\n");
            getchar(); getchar();
            getchar();
            break;
        case 17:
            flag1 = 0;
            printf("��������Ҫ���ҵĶ����������ƣ�");
            scanf("%s", ListName);
            flag1 = LocateTree(Trees, ListName);
            if (flag1 == 0)
                printf("����������Ϊ %s �Ķ�������\n", ListName);
            else printf("����Ϊ %s �Ķ����������Ϊ%d\n", ListName, flag1);
            getchar(); getchar();
            getchar();
            break;
        case 18:
            printf("�������ɭ���и�����������\n");
            flag1 = TreesTraverse(Trees);
            if (flag1 == ERROR) printf("ɭ��Ϊ�ա�\n");
            getchar(); getchar();
            getchar();
            break;
        case 19:

            printf("��������Ҫ���в����Ķ���������ţ���1��ʼ����");
            scanf("%d", &e);
            flag1 = ChooseTree(T, Trees, e);
            if (flag1 == ERROR)
                printf("�������Ų��Ϸ���\n");
            else printf("����ɶ�ɭ�������Ϊ%d�Ķ��������в�����\n", e);
            getchar(); getchar();
            getchar();
            break;
        case 20:
            flag1 = InvertTree(T);
            if (flag1 == -1)
                printf("���ܶԿ������в���");
            else
                printf("�Ѿ�����������ɡ�");
            getchar(); getchar();
            getchar();
            break;
        case 21:
            flag1 = MaxPathSum(T);
            if (flag1 == 0)
                printf("������");
            else
                printf("��ó���Ϊ%d\n", flag1);
            getchar(); getchar();
            getchar();
            break;
        case 22:
            BiTree sa;
            int p, q;
            printf("������Ҫ���ҵ������ڵ������ֵ��");
            scanf("%d %d", &p, &q);
            sa = lower(T,p,q);
            if (sa == NULL)
                printf("û�й������ȣ�");
            else
                printf("���������Ϊ%d %s\n", sa->data.key, sa->data.others);
            getchar(); getchar();
            getchar();
            break;
        case 23:
            if (T == NULL)
            {
                printf("������������\n");
            }
            if (BiTreeEmpty(T) == TRUE)
            {
                printf("������Ϊ��\n");
            }
            else
            {
                printf("��������Ϊ��\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 24:
            if (ClearBiTree(T) == OK)
            {
                printf("�������ɹ����\n");
            }
            else
            {
                printf("������������\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 0:
            break;
        }//end of switch
        printf("\n");
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()


//1���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK���������ͬ�Ĺؼ��֣�����ERROR��
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

//2�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
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

//3�������T�����
void Traverse(BiTree T, int i)
{
    i++;
    if (depth < i) depth = i;
    if (T->lchild) { Traverse(T->lchild, i); }//ȡȫ�ֱ���������
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

//4���ҽ��
BiTNode* LocateNode(BiTree T, KeyType e)
{
    if (T == NULL) return NULL;
    if (T->data.key == e) T1 = T;
    else
    {
        if (T->lchild) LocateNode(T->lchild, e);//ͬ��Ҳ��Ѱ�ҵĹ���
        if (T->rchild) LocateNode(T->rchild, e);
    }
    return T1;
}

//5ʵ�ֽ�㸳ֵ����������ͨ������������������ʵ�ֱ�������
void check(BiTree& T, KeyType e, TElemType value)
{
    if (flag == 1)
        return;
    else
    {
        if (e != value.key && T->data.key == value.key) flag = 1;//Ѱ�ҽڵ�Ĺ���
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

//6ʵ�ֻ���ֵܽ��
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

//7�����㡣��������ͨ������������������ʵ�ֱ�������
void Check(BiTree& T, KeyType e)//�ҵ����׽�� flag==1��ʾ�ҵ��˹ؼ���Ϊe�ĸ��׽�� ��ʹT1ָ��ָ���ҵ��Ľ��
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
void _Check(BiTree& T, TElemType c)//�ж���������Ƿ��йؼ����ظ� �����������ԭ�н���йؼ����ظ���_flag==1;
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
    if (_flag == 1) return ERROR;//�������ؼ����ظ���ֱ�ӷ��ش���
    if (LR == -1)//�������Ǹ��ڵ㣬���ÿ���flag��ֵ��
    {
        BiTree t = (BiTNode*)malloc(sizeof(BiTNode));
        t->rchild = T;
        T = t;
        T->data = c;
        T->lchild = NULL;
        return OK;
    }
    if (flag == 0) return ERROR;//�ڲ����㲻�Ǹ��ڵ������£�û���ҵ��丸�ף�ֱ�ӷ��ش���
    else
    {
        BiTree t = (BiTNode*)malloc(sizeof(BiTNode));//������������봢��ռ䡣
        if (LR == 0)//�������Ϊ���׽�������
        {
            if (T1->lchild == NULL) t->rchild = NULL;
            else t->rchild = T1->lchild;
            t->lchild = NULL;
            T1->lchild = t;
            t->data = c;
            return OK;
        }
        else if (LR == 1)//�������Ϊ���׽����Һ���
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

//8ɾ����㡣��������ͨ������������������ʵ�ֱ�������
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
//����д��ɾ���ڵ����
int flag8 = 0;//�տ�ʼ��ʱ�򣬼�����û��ΪΪȷ���Ľڵ�
int swi8 = 1;//������������Ƶ�һ���ڵ�������

int fin8 = 0;//������������Ѱ�������������Ҷ˽ڵ��
status check_no8(BiTree T, KeyType e)
{
    if (T->data.key == e && !flag8)
        flag8 = 1;//����ҵ�������ڵ㣬��ô���Է���1
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
//ɾ����㡣��������ͨ������������������ʵ�ֱ�������
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int du = 0;//�ܵĶ���
    if (T != NULL && T->lchild != NULL)
        du++;
    if (T != NULL && T->rchild != NULL)
        du++;
    if (check_no8(T, e) != 1 && swi8)
    {
        return ERROR;//û�������Ľڵ�
    }
    if (T->data.key == e && swi8)//��һ���ڵ���Ŀ��ڵ�
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
        pre = T;//��ǰ��Ľڵ�Ϊpre
    swi8 = 0;
    //������������ģ�������һ�����
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
//9�������������T
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

//10�������������T
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

//11�������������T
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

//12�������������T
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

//13���������Ľ������д�뵽�ļ�FileName��

status SaveBiTree(BiTree T, char FileName[])
//���������Ľ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
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
////14�����ļ�FileName�Ľ�����ݣ�����������
status LoadBiTree(BiTree& T, char FileName[])
//�����ļ�FileName�Ľ�����ݣ�����������
{
    // �������ﲹ����룬��ɱ�������
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

//15��ɭ�������һ����
status AddTree(TREES& Trees, char ListName[])
{
    for (int i = 0; i < Trees.length; i++)
        if (strcmp(Trees.elem[i].name, ListName) == 0)
        {
            printf("�������Ѵ�������Ϊ %s �Ķ�������\n", ListName);
            return ERROR;
        }
    TElemType definition[100] = { 0 };//����Ƚϼ򵥣����Ƕ������Ӧ��
    printf("�ڶ����� %s ����ӽ�㣬��������������Ķ���������������У�\n", ListName);
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
        printf("�ؼ��ֲ�Ψһ��"); return ERROR;
    }
}

//16��ɭ����ɾ��һ����
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

//17��ɭ���в���һ������ΪListName�Ķ��������ɹ������߼���ţ����򷵻�0
int LocateTree(TREES Trees, char ListName[]) {
    for (int i = 0; i < Trees.length; i++)
    {
        if (strcmp(Trees.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

//18����ɭ���и���������
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

//19ѡ��һ������������������ţ������ɶ�����в���
status ChooseTree(BiTree& T, TREES& Trees, int x) {
    if (x > Trees.length || x < 1) return ERROR;
    else
    {
        T = Trees.elem[x-1].T;
    }
    return OK;
}
//20��ת������
status InvertTree(BiTree& T)
{
    if (T == NULL)
        return INFEASIBLE;//���ú��������˼·
    InvertTree(T->lchild);//�������������ϱ���
    InvertTree(T->rchild);
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    return OK;
}

//21�Զ������еĽڵ������·����
status MaxPathSum(BiTree T)//keyΪ��ǰֵ��depΪ���
{
    if (T == NULL)
        return 0;//���ΪNULL�ͷ���0
    int lef = MaxPathSum(T->lchild);//���������������ֵ����
    int right = MaxPathSum(T->rchild);
    return T->data.key + max(lef, right);//���������������������Ǹ�һ��
    //�е���dp��˼�룬������һֱ�����ߣ��ߵ����õ����ֵ;
}
//22�󹫹�����
BiTree lower(BiTree root, int q, int p)//q,p����ΪҪ���ҵĽڵ�
{
    if (root == NULL || root->data.key == q || root->data.key == p)//����ǿսڵ��ֱ�ӷ��ؾ��У������Ŀ��ڵ�ͷ���Ŀ��ڵ�
        return root;
    BiTree left = lower(root->lchild, p, q);//�ҳ�����ߵ�Ŀ��ڵ�
    BiTree right = lower(root->rchild, p, q);//�ҳ����ұߵ�Ŀ��ڵ�
    if (left != NULL && right != NULL) return root;//��������ҵ���Ŀ��ڵ㣬��ô��˵���ҵ���

    if (left == NULL && right != NULL) return right;//�������У��ͷ�����ߵ�
    else if (left != NULL && right == NULL) return left;//�ұ��оͷ����ұߵ�
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
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
    // �������ﲹ����룬��ɱ�������
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