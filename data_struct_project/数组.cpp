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
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct {  //˳���˳��ṹ���Ķ���
    ElemType* elem;
    int length;
    int listsize;
}SqList;
typedef struct {  //���Ա�Ĺ������
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
        printf("    ��ѡ����Ĳ���[0~22]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            //printf("\n----IntiList���ܴ�ʵ�֣�\n");
            if (InitList(L) == OK) printf("���Ա����ɹ���\n");
            else printf("���Ա���ʧ�ܣ�\n");
            getchar(); getchar();
            break;
        case 2:
            if (mylist != NULL)
                L = *mylist;
            if (DestroyList(L) == OK)
                printf("�ɹ��������Ա��ͷ�����Ԫ�صĿռ䡣\n");
            else
                printf("���ܶԲ����ڵ����Ա�������ٲ�����\n");
            getchar(); getchar();
            break;
        case 3:
            if (mylist != NULL)
                L = *mylist;
            if (ClearList(L) == OK)
                printf("�ɹ�ɾ�����Ա������е�Ԫ�ء�\n");
            else
                printf("���ܶԲ����ڵ����Ա������ղ�����\n");
            getchar(); getchar();
            break;
        case 4:
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
            length = ListLength(L);
            if (length >= 0)
                printf("���Ա�ĳ���Ϊ%d��\n", length);
            else
                printf("���ܶԲ����ڵ����Ա��󳤣�\n");
            getchar(); getchar();
            break;
        case 6:
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
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
            if (mylist != NULL)
                L = *mylist;
            printf("��������Ҫɾ����Ԫ�ص���ţ�");
            scanf("%d", &i);
            flag = ListDelete(L, i, e);
            if (flag == OK)
                printf("���Ϊ%d��Ԫ��%d�Ѿ������Ա���ɾ����\n", i, e);
            else if (flag == ERROR)
                printf("ɾ��λ�ò���ȷ��");
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա����ɾ����\n");
            getchar(); getchar();
            break;

        case 12:
            if (mylist != NULL)
                L = *mylist;
            flag = ListTraverse(L);
            if (flag == INFEASIBLE)
                printf("���ܱ��������ڵ����Ա�\n");
            else if (flag == ERROR)
                printf("���Ա��ǿձ�\n");
            else printf("\n");
            getchar(); getchar();
            break;
        
        case 13:
            if (mylist != NULL)
                L = *mylist;
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
        {char ListName[30] = { '\0' };
        printf("�������������Ա�����ƣ�");
        scanf("%s", ListName);
        flag = AddList(Lists, ListName);
        if (flag == OK) 
        { 
            printf("�ɹ���������Ϊ %s �����Ա�\n", ListName);
            printf("����������������Ա������:");
            scanf("%d", &e);
            while (e)
            {
                ListInsert(Lists.elem[Lists.length - 1].L, Lists.elem[Lists.length - 1].L.length + 1, e);
                scanf("%d", &e);
            }
            printf("�ɹ�������ֵ����Ա�!");
        }
        else printf("����ʧ�ܣ�\n");
        
        getchar(); getchar();
        break;
        }
        case 15:
            printf("��������Ҫɾ�������Ա�����ƣ�");
            scanf("%s", ListName);
            flag = RemoveList(Lists, ListName);
            if (flag == OK)
                printf("�ɹ�ɾ������Ϊ %s �����Ա�\n", ListName);
            else if (flag == ERROR)
                printf("ɾ��ʧ�ܣ�\n");
            getchar(); getchar();
            break;
        case 16:
        {char ListName[30] = { '\0' };
        printf("��������Ҫ���ҵ����Ա�����ƣ�");
        scanf("%s", ListName);
        i = LocateList(Lists, ListName);
        if (i == 0)
            printf("����������Ϊ %s �����Ա�\n", ListName);
        else printf("����Ϊ %s �����Ա�����Ϊ%d\n", ListName, i);
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
            printf("�������ļ����ƣ�");
            scanf("%s", FileName);
            flag = LoadList(L, FileName);
            if (flag == ERROR)
                printf("�ļ���ȡʧ�ܣ�\n");
            else if (flag == OK)
                printf("���Ա�����ݶ�ȡΪ����Ϊ %s ���ļ��С�\n", FileName);
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ����Ա���н����ļ�������\n");
            getchar(); getchar();
            break;
        case 19:
            if (mylist != NULL)
                L = *mylist;
            q = sortList(L);
            if (q == INFEASIBLE)
                printf("�ձ�");
            if (q == OK)
                printf("�Ѿ���ɸ�ֵ��");
            getchar(); getchar();
            break;
        case 20:

            printf("������ѡ��ı�\n");
            scanf("%s", fe);
            i = 0;
            for (i; i < Lists.length; i++)
            {
                if (strcmp(fe, Lists.elem[i].name) == 0)
                {
                    L = Lists.elem[i].L;
                    printf("�Ѿ�ѡȡ���ñ�");
                }
            }
            if (i == Lists.length - 1)
                printf("û�������ı�");
            getchar(); getchar();
            break;
        case 21:
            printf("��������ĺ�Ϊ:\n");
            scanf("%d", &e);
            printf("�������������Ϊ%d���������\n", e);
            if (L.elem == NULL)
            {
                printf("���Ա�����\n");
            }
            else
            {
                i = SubArrayNum(L, e);
                printf("��Ϊ%d�����������Ϊ��%d\n", e, i);
            }
            getchar(); getchar();
            break;
        case 22:
            if (L.elem == NULL)
            {
                printf("���Ա�Ϊ��\n");
            }
            else
            {
                e = MaxSubArray(L);
                printf("�����������������������Ϊ%d\n", e);
            }
            getchar(); getchar();
            break;
        case 0:
            break;
        }//end of switch
    }//end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}//end of main()
//�����Ǵ���ʵ�ֹ���
status InitList(SqList& L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L.length > 0 && L.elem)
        return INFEASIBLE;
    L.elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);//����ռ�
    L.length = 0;//��ʼ������
    L.listsize = LIST_INIT_SIZE;
    return OK;


    /********** End **********/
}
status DestroyList(SqList& L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    L.length = 0;
    return OK;

    /********** End **********/
}
status ListEmpty(SqList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    else
        return L.length;

    /********** End **********/
}
status GetElem(SqList L, int i, ElemType& e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE����-1����
{
    // �������ﲹ����룬��ɱ�������
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
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)
        {
            if (i == 0)//�鿴���Ƿ�Ϊ��һ��Ԫ��
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
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L.elem == NULL)
        return INFEASIBLE;
    for (int i = 0; i < L.length; i++)
    {
        if (L.elem[i] == e)//�鿴���Ƿ�Ϊ���һ��Ԫ��
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    /********** Begin *********/
    if (L.elem == NULL) return INFEASIBLE;//������
    if (i <= 0 || i > L.length + 1) return ERROR;//����λ��Խ��
    int after = i - 1;
    if (L.length == L.listsize)
    {
        ElemType* newbase = NULL;
        newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));//����ռ�
        L.elem = newbase;//����ָ��
        L.listsize += LISTINCREMENT;//������󳤶���չ
    }
    for (int j = L.length - 1; j >= after; j--)
    {
        L.elem[j + 1] = L.elem[j];
    }
    L.elem[after] = e;
    L.length++;//Ԫ�ظ���+1
    return OK;
    /********** End **********/
}
status ListDelete(SqList& L, int i, ElemType& e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (!L.elem)
        return INFEASIBLE;
    if (i >= L.length || i == 0)//���ɾ��λ���Ƿ�Ϸ�
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
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    /********** Begin *********/

    if (L.elem == NULL) return INFEASIBLE;//������
    for (int j = 0; j <= L.length - 1; j++)
    {
        j == L.length - 1 ? printf("%d", L.elem[j]) : printf("%d ", L.elem[j]);

    }
    return OK;
    /********** End **********/
}
status  SaveList(SqList L, char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (!L.elem)
        return INFEASIBLE;
    FILE* fp = fopen(FileName, "w+");//���ݵĶ�ȡ
    for (int i = 0; i < L.length; i++)
    {
        fprintf(fp, "%d ", L.elem[i]);
    }
    fclose(fp);//һ�����Ź�
    return OK;
    /********** End **********/
}
status  LoadList(SqList& L, char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if (L.elem)
        return INFEASIBLE;
    L.elem = (ElemType*)malloc(sizeof(ElemType) * 100);
    FILE* fp = fopen(FileName, "r+");//����д��
    int i = 0;
    while (fscanf(fp, "%d ", &(L.elem[i++])) != EOF);
    L.length = i - 1;
    fclose(fp);
    return OK;
    /********** End **********/
}
status AddList(LISTS& Lists, char ListName[])
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    Lists.elem[Lists.length].L.elem = NULL;//���ӱ�Ϊ��
    InitList(Lists.elem[Lists.length].L);//����һ�����ӱ�
    int i;
    //�����ַ������Ƹ�LIST
    for (i = 0; ListName[i] != '\0'; i++)
    {
        Lists.elem[Lists.length].name[i] = ListName[i];
    }
    Lists.elem[Lists.length].name[i] = '\0';
    //�����ַ������Ƹ�LIST
    Lists.length++;//����+1
    return OK;
    /********** End **********/
}
status RemoveList(LISTS& Lists, char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
    if (Lists.length == 0)
    {
        printf("�ñ�Ϊ�ձ�!�밴�س�����,");
        return 0;//�ձ�ֱ�ӷ���δ֪
    }
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i, j, flag = 0;
    for (j = 0; j < Lists.length; j++)//���������ӱ�
    {
        for (i = 0; ListName[i] != '\0'; i++)//�ж�����һһ��Ӧ
        {
            if (Lists.elem[j].name[i] != ListName[i]) break;
        }
        if (ListName[i] == '\0')
        {
            flag = 1;
            break;
        }
    }
    //�ж������Ƿ���ͬ
    if (flag == 1)
    {
        Lists.elem[j].L.elem = NULL;
        Lists.elem[j].L.elem = Lists.elem[j + 1].L.elem;//����Ԫ�ظı�
        Lists.elem[j].L.length = Lists.elem[j + 1].L.length;//���ȸı�
        //���ָı�
        for (i = 0; Lists.elem[j + 1].name[i] != '\0'; i++)
        {
            Lists.elem[j].name[i] = Lists.elem[j + 1].name[i];
        }
        Lists.elem[j].name[i] = '\0';
        //
        Lists.length--;
        return OK;
    }
    else return INFEASIBLE;//ɾ��ʧ��
    /********** End **********/
}
int LocateList(LISTS Lists, char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
    if (Lists.length == 0)
    {
        printf("�ñ�Ϊ�ձ�!�밴�س�����,");
        return 0;//�ձ�ֱ�ӷ���δ֪
    }
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int i, j, flag = 0;
    for (j = 0; j < Lists.length; j++)//���������ӱ�
    {
        for (i = 0; ListName[i] != '\0'; i++)//�ҵ���Ѱ����
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
        printf("�ñ��ڲ���Ԫ��Ϊ:");
        for (int k = 0; k < Lists.elem[j].L.length; k++)
        {
            printf("%d ", Lists.elem[j].L.elem[k]);
        }
        printf("\n");
        return j + 1; 
    }
    //���ҵ��ͷ���λ��
    else return 0;//û�ҵ��ͷ���-1
    /********** End **********/
}
status ShowList(LISTS Lists)
{
    if (Lists.length == 0)
    {
        printf("�ñ�Ϊ�ձ�!�밴�س�����");
        return 0;//�ձ�ֱ�ӷ���δ֪
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
    int m = 0;//����
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
        m++;//������©��һ��
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
