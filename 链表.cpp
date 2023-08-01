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
typedef int ElemType; //����Ԫ�����Ͷ���
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode {  //��������ʽ�ṹ�����Ķ���
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;

typedef struct {  //���Ա�Ĺ������
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
        printf("\n��ѡ����Ĳ���[0~19]:\n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            if (InitList(L) == OK)
                printf("���Ա����ɹ���\n");
            else
                printf("���Ա���ʧ�ܣ�\n");
            getchar(); getchar();
            break;
        case 2:
            if (DestroyList(L) == OK)
                printf("�ɹ��������Ա��ͷ�����Ԫ�صĿռ䡣\n");
            else
                printf("���ܶԲ����ڵ����Ա�������ٲ�����\n");
            getchar(); getchar();
            break;
        case 3:
            if (ClearList(L) == OK)
                printf("�ɹ�ɾ�����Ա������е�Ԫ�ء�\n");
            else
                printf("���ܶԲ����ڵ����Ա������ղ�����\n");
            getchar(); getchar();
            break;
        case 4:
            flag = ListEmpty(L);
            if (flag == TRUE)
                printf("���Ա�Ϊ�ա�\n");
            else if (flag == ERROR)
                printf("���Ա�ǿա�\n");
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա��пա�\n");
            getchar(); getchar();
            break;
        case 5:
            length = ListLength(L);
            if (length >= 0)
                printf("���Ա�ĳ���Ϊ%d��\n", length);
            else
                printf("���ܶԲ����ڵ����Ա��󳤣�\n");
            getchar(); getchar();
            break;
        case 6:
            printf("��������Ҫ�����Ա��л�ȡ��Ԫ�ص���ţ�");
            scanf("%d", &i);
            flag = GetElem(L, i, e);
            if (flag == OK)
                printf("���Ա��е�%d��Ԫ��Ϊ%d��\n", i, e);
            else if (flag == ERROR)
                printf("�������Ų��Ϸ���\n");
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա���д˲�����\n");
            getchar(); getchar();
            break;
        case 7:
            printf("��������Ҫ�����Ա��в��ҵ�Ԫ�أ�");
            scanf("%d", &e);
            flag = LocateElem(L, e);
            if (flag == 0)
                printf("���Ա��в�����%d���Ԫ�ء�\n", e);
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա���д˲�����\n");
            else
                printf("Ԫ��%d�����Ա��е����Ϊ%d\n", e, flag);
            getchar(); getchar();
            break;
        case 8:
            printf("��������Ҫ�����Ա��в�����ǰ����Ԫ�أ�");
            scanf("%d", &e);
            flag = PriorElem(L, e, pre);
            if (flag == OK)
                printf("Ԫ��%d�����Ա��е�ǰ��Ϊ%d��\n", e, pre);
            else if (flag == ERROR)
                printf("Ԫ��%d�����Ա���û��ǰ����\n", e);
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա���д˲�����\n");
            getchar(); getchar();
            break;
        case 9:
            printf("��������Ҫ�����Ա��в������̵�Ԫ�أ�");
            scanf("%d", &e);
            flag = NextElem(L, e, next);
            if (flag == OK)
                printf("Ԫ��%d�����Ա��еĺ��Ϊ%d��\n", e, next);
            else if (flag == ERROR)
                printf("Ԫ��%d�����Ա���û�к�̡�\n", e);
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա���д˲�����\n");
            getchar(); getchar();
            break;
        case 10:
            printf("��������Ҫ�����Ԫ�أ�");
            scanf("%d", &e);
            printf("��������Ҫ�����λ��(ĳһ��λ��֮ǰ����");
            scanf("%d", &i);
            flag = ListInsert(L, i, e);
            if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա���в��룡\n");
            else if (flag == ERROR)
                printf("����λ�ò���ȷ��\n");
            else
                printf("Ԫ���Ѳ������Ա��С�\n");
            getchar(); getchar();
            break;
        case 11:
            printf("��������Ҫɾ����Ԫ�ص���ţ�");
            scanf("%d", &i);
            flag = ListDelete(L, i, e);
            if (flag == OK)
                printf("���Ϊ%d��Ԫ��%d�Ѿ������Ա���ɾ����\n", i, e);
            else if (flag == ERROR)
                printf("ɾ��λ�ò���ȷ��\n");
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա����ɾ����\n");
            getchar(); getchar();
            break;
        case 12:
            flag = ListTraverse(L);
            if (flag == INFEASIBLE)
                printf("���ܱ��������ڵ����Ա�\n");
            else if (flag == ERROR)
                printf("���Ա��ǿձ�\n");
            else printf("\n");
            getchar(); getchar();
            break;
        case 13:
            printf("�������ļ����ƣ�");
            scanf("%s", FileName);
            flag = SaveList(L, FileName);
            if (flag == ERROR)
                printf("�ļ���ʧ�ܣ�\n");
            else if (flag == OK)
                printf("���Ա�������Ѿ����Ƶ�����Ϊ %s ���ļ��С�\n", FileName);
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա���н���д�ļ�������\n");
            getchar(); getchar();
            break;
        case 14:
            printf("�������ļ����ƣ�");
            scanf("%s", FileName);
            flag = LoadList(L, FileName);
            if (flag == ERROR)
                printf("�ļ���ʧ�ܣ�\n");
            else if (flag == OK)
                printf("����Ϊ %s ���ļ��е������Ѹ��Ƶ����Ա��С�\n", FileName);
            else if (flag == INFEASIBLE)
                printf("���ܶ��Ѵ��ڵ����Ա���н��ж��ļ�������\n");
            else if (flag == OVERFLOW)
                printf("�����\n");
            getchar(); getchar();
            break;
        case 15: {char ListName[30] = { '\0' };
               printf("�������������Ա�����ƣ�");
               scanf("%s", ListName);
               flag = AddList(Lists, ListName);
               if (flag == OK) printf("�ɹ���������Ϊ %s �����Ա�\n", ListName);
               else printf("����ʧ�ܣ�\n");
               getchar(); getchar();
               break;

        }
        case 16:
            printf("��������Ҫɾ�������Ա�����ƣ�");
            scanf("%s", ListName);
            flag = RemoveList(Lists, ListName);
            if (flag == OK)
                printf("�ɹ�ɾ������Ϊ %s �����Ա�\n", ListName);
            else if (flag == ERROR)
                printf("ɾ��ʧ�ܣ�\n");
            getchar(); getchar();
            break;
        case 17: {char ListName[30] = { '\0' };
               printf("��������Ҫ���ҵ����Ա�����ƣ�");
               scanf("%s", ListName);
               i = LocateList(Lists, ListName);
               if (i == 0)
                   printf("����������Ϊ %s �����Ա�\n", ListName);
               else printf("����Ϊ %s �����Ա�����Ϊ%d\n", ListName, i);
               getchar(); getchar();
               break;
        }
        case 18:
            flag = ListsTraverse(Lists);
            if (flag == ERROR) printf("���Ա�ļ���Ϊ�ա�\n");
            getchar(); getchar();
            break;
        case 19:
            printf("��������Ҫ���в��������Ա����ţ���1��ʼ����");
            scanf("%d", &i);
            L = ChooseList(L, Lists, i);
            printf("����ɶ����Ա��������Ϊ%d�����Ա���в�����\n", i);
            getchar(); getchar();
            break;
        case 20:
            if (mylist != NULL)
                L = *mylist;
            flag = sortList(L);
            if (flag == OK)
                printf("�������\n");
            else
                printf("�ձ�\n");
            getchar(); getchar();
            break;
        case 21:
            if (mylist != NULL)
                L = *mylist;
            if (L == NULL)
            {
                printf("�ձ��޷����д˲���");
                getchar(); getchar();
                break;
            }
            
            L = reverseList(L);
                printf("���!\n");
            getchar(); getchar();
            break;
        case 22:
            printf("�����뵹���ڼ������֣�");
            scanf("%d", &e);
            flag = RemoveNthFromEnd(L, e);
            if (flag == OK)
                printf("�ɹ��Ƴ���\n");
            else
            {
                printf("���������������λ������");
            }
            getchar(); getchar();
            break;
        case 0:
            break;
        }//end of switch
        printf("\n");
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()






status InitList(LinkList& L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L != NULL)//�ж��Ƿ�Ϊ��
        return INFEASIBLE;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    L->data = 0;
    return OK;


    /********** End **********/
}
status DestroyList(LinkList& L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    LinkList q, p = L;
    while (p != NULL)
    {
        q = p->next;
        free(p);//�ͷŽڵ�
        p = q;
    }
    L = NULL;
    return OK;

    /********** End **********/
}
status ClearList(LinkList& L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    LinkList q, p = L->next;
    L->next = NULL;
    return OK;

    /********** End **********/
}
status ListEmpty(LinkList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L == NULL)//�жϵ�һ���ڵ��Ƿ�Ϊ�ռ���
    {
        return INFEASIBLE;
    }
    if (L->next != NULL)
        return ERROR;
    return OK;

    /********** End **********/
}

int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    int length = 0;
    LinkList p;
    p = L;
    if (i == 0)
        return ERROR;//û�е�0��Ԫ��
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int length = 0;//��һ���׽ڵ㣬���Ե�һ��Ԫ��Ϊ��
    if (L == NULL)
        return INFEASIBLE;
    LinkList p, q;
    p = L->next;
    q = L;
    while (p != NULL)
    {
        if (p->data == e)//���ҵ���Ԫ��
        {
            if (length == 0)//�жϳ����Ƿ�Ϊ0
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int length = 0;//��һ���׽ڵ㣬���Ե�һ��Ԫ��Ϊ��
    if (L == NULL)
        return INFEASIBLE;
    LinkList p;
    p = L->next;
    while (p != NULL)
    {
        if (p->data == e)
        {
            if (p->next == NULL)//�жϺ���Ƿ����
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int length = 0;//��һ���׽ڵ㣬���Ե�һ��Ԫ��Ϊ��
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
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
    while (fscanf(fp, "%d ", &data) != EOF)//��ȡ���ݴӼ��±�����
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

//����Ĳ����Ƕ�����Ա���������
//��Lists������һ������ΪListName�Ŀ����Ա�
status AddList(LISTS& Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++)
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            printf("�������Ѵ�������Ϊ %s �����Ա�\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);//�����ִ�����
    InitList(Lists.elem[Lists.length].L);//��ʼ�������
    Lists.length++;
    int e;
    int x = 1;
    printf("�� %s ���Ա�������Ԫ�أ���0������:\n", ListName);
    scanf("%d", &e);
    while (e)
    {
        ListInsert(Lists.elem[Lists.length - 1].L, x, e); x++;
        scanf("%d", &e);
    }
    return OK;
}

//��Lists��ɾ��һ������ΪListName�����Ա�
status RemoveList(LISTS& Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            DestroyList(Lists.elem[i].L);//������������Ҵ����
            for (int k = i; k < Lists.length - 1; k++)
                Lists.elem[k] = Lists.elem[k + 1];
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

//��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
int LocateList(LISTS Lists, char ListName[]) {
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

//����Lists�и������Ա�
status ListsTraverse(LISTS Lists) {
    if (Lists.length == 0) return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("%s ", Lists.elem[n].name);
        ListTraverse(Lists.elem[n].L);//ע���������ǲ�һ����
        putchar('\n');
    }
    return OK;
}

//ѡ��һ�����Ա���������ţ������ɶ�����в���
LinkList ChooseList(LinkList& L, LISTS& Lists, int i) {//�������Ա��֮�����
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
        q = p->next;//�Ƚϼ򵥵�ð������
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
LinkList reverseList(LinkList &L)//����ת
{
    LinkList p = L;
    p = p->next;
    int i = 0;
    int number[1001] = {};//��һ������洢����
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
        int temp = number[j];//������з�ת
        number[j] = number[i - 1 - j];
        number[i - 1 - j] = temp;
    }
    for (int j = 0; j < i; j++)
    {
        LinkList q;
        q = (LinkList)malloc(sizeof(LinkList));//���½�����ֵ
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
            length++;//��¼�ܳ���Ϊlength
        }
        if (n > length)
            return ERROR;
        int target = length - n + 1;//�����ĵڼ���Ԫ��
        int cur = 0;//��ǵ�ǰ��
        p = L->next;
        LinkList former = L;
        for (int i = 0; i < length; i++)
        {
            cur++;
            if (cur == target)
            {
                former->next = p->next; break;//������Ѱ�ҵ���ǰ���Ǹ��ڵ�
            }
            p = p->next;
            former = former->next;
        }
    }

    return OK;
}