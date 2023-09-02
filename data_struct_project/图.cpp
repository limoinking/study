#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#pragma warning(disable:6031)
#pragma warning(disable:6385)
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
    int adjvex;              //����λ�ñ�� 
    struct ArcNode* nextarc;	   //��һ������ָ��
} ArcNode;
typedef struct VNode {				//ͷ��㼰���������Ͷ���
    VertexType data;       	//������Ϣ
    ArcNode* firstarc;      	 //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
    AdjList vertices;     	 //ͷ�������
    int vexnum, arcnum;   	  //������������
    GraphKind  kind;        //ͼ������
} ALGraph;

typedef struct {//ɭ�ֵĶ���
    struct {
        char name[30];
        ALGraph G;
    }elem[10];
    int length;
    int listsize;
}GRAPHS;


status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph& G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph& G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph& G, VertexType v);
status DeleteVex(ALGraph& G, KeyType v);
status InsertArc(ALGraph& G, KeyType v, KeyType w);
status DeleteArc(ALGraph& G, KeyType v, KeyType w);
status DFSTraverse(ALGraph& G, void (*visit)(VertexType));
status BFSTraverse(ALGraph& G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph& G, char FileName[]);
status AddGraph(GRAPHS& Graphs, char ListName[]);
status RemoveGraph(GRAPHS& Graphs, char ListName[]);
int LocateGraph(GRAPHS& Graphs, char ListName[]);
status GraphsTraverse(GRAPHS& Graphs);
status ChooseGraph(GRAPHS& Graphs, int x);
status VerticesSetLessThanK(ALGraph G, KeyType v, int km);//С��k�Ľڵ㼯��
status ShortestPathLength(ALGraph G, KeyType v, KeyType w);//�ڵ��е����·��ʹ�õϽ�˹�����㷨
status ConnectedComponentsNums(ALGraph G, char FileName[]);//��ͨ�����Ĳ���

int flag = 0;
int f[1000] = {};//���鼯
int a[20] = { 0 };
char aw[21] = "22.txt";//�����ר�õ�

ALGraph* mygra = NULL;//����Ǵ���ѡͼ���
int gf = 0;//�鿴�Ƿ��б�ѡȡ��ͼ

void visit(VertexType v)
{
    printf(" %d %s", v.key, v.others);
}
int main(void)
{
    ALGraph G;
    G.vexnum = 0;
    GRAPHS Graphs;
    Graphs.length = 0;
    VertexType value;
    VertexType V[30] = {};
    KeyType VR[100][2] = {};
    int i = 0, j;
    int op = 1, length, e, pre, next, flag1 = 0;
    char FileName[30] = { '\0' };
    char ListName[30] = { '\0' };
    
    while (op) {
        system("cls");	printf("\n\n");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("------------------------------------------------\n");
        printf("     1. CreateGraph            2. DestroyGraph\n");
        printf("     3. LocateVex              4. PutVex\n");
        printf("     5. FirstAdjVex            6. NextAdjVex\n");
        printf("     7. InsertVex              8. DeleteVex\n");
        printf("     9. InsertArc              10.DeleteArc\n");
        printf("     11.DFSTraverse            12.BFSTraverse\n");
        printf("     13.SaveGraph              14.LoadGraph\n");
        printf("     15.AddGraph               16.RemoveGraph\n");
        printf("     17.LocateGraph            18.GraphsTraverse\n");
        printf("     19.ChooseGraph            20.VerticesSetLessThanK\n");
        printf("     21.ShortestPathLength     22.ConnectedComponentsNums\n");
        printf("     0. Exit\n");
        printf("------------------------------------------------\n");
        printf("\n��ѡ����Ĳ���[0~19]:\n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            i = 0;
            printf("�����붥�����У���-1 nil������");
            do {
                scanf("%d%s", &V[i].key, V[i].others);
            } while (V[i++].key != -1);
            i = 0;
            printf("�������ϵ�����У���-1 -1������");
            do {
                scanf("%d%d", &VR[i][0], &VR[i][1]);
            } while (VR[i++][0] != -1);
            if (CreateCraph(G, V, VR) == OK)
                printf("ͼ�����ɹ���\n");
            else
                printf("ͼ����ʧ�ܣ�\n");
            getchar(); getchar();
            getchar();
            break;
        case 2:
            if (gf == 0)
            {
                if (DestroyGraph(G) == OK)
                    printf("�ɹ�����ͼ���ͷ�����Ԫ�صĿռ䡣\n");
                else
                    printf("���ܶԲ����ڵ�ͼ�������ٲ�����\n");
            }
            else
            {
                if (DestroyGraph(*mygra) == OK)
                    printf("�ɹ�����ͼ���ͷ�����Ԫ�صĿռ䡣\n");
                else
                    printf("���ܶԲ����ڵ�ͼ�������ٲ�����\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 3:
            printf("��������Ҫ��ͼ�в��ҵĶ���Ĺؼ��֣�");
            scanf("%d", &e);
            if (gf == 0)
            {
                i = LocateVex(G, e);
                if (i != -1) printf("ͼ�йؼ���Ϊ%d�Ķ����λ��Ϊ%d\n", e, i);
                else
                    printf("ͼ�в����ڹؼ���Ϊ%d�Ķ��㣡\n", e);
            }
            else
            {
                i = LocateVex(*mygra, e);
                if (i != -1) printf("ͼ�йؼ���Ϊ%d�Ķ����λ��Ϊ%d\n", e, i);
                else
                    printf("ͼ�в����ڹؼ���Ϊ%d�Ķ��㣡\n", e);
            }
            getchar(); getchar();
            getchar();
            break;
        case 4:
            printf("��������Ҫ�޸ĵĶ���Ĺؼ��֣�");
            scanf("%d", &e);
            printf("���䶥��ֵ�޸�Ϊ��");
            scanf("%d %s", &value.key, value.others);
            if (gf == 0)
            {
                flag1 = PutVex(G, e, value);
                if (flag1 == ERROR)
                    printf("��ֵ����ʧ�ܣ�\n");
                else if (flag1 == OK)
                    printf("�ѽ��ؼ���Ϊ%d�Ķ���ֵ�޸�Ϊ%d,%s\n", e, value.key, value.others);
            }
            else
            {
                flag1 = PutVex(*mygra, e, value);
                if (flag1 == ERROR)
                    printf("��ֵ����ʧ�ܣ�\n");
                else if (flag1 == OK)
                    printf("�ѽ��ؼ���Ϊ%d�Ķ���ֵ�޸�Ϊ%d,%s\n", e, value.key, value.others);
            }
            getchar(); getchar();
            getchar();
            break;
        case 5:
            printf("��������Ҫ�������һ�ڽӵ�Ķ��㣺");
            scanf("%d", &e);
            if (gf == 0)
            {
                i = FirstAdjVex(G, e);
                if (i != -1)
                    printf("����%d�ĵ�һ�ڽӵ��λ��Ϊ%d\n", e, i);
                else
                    printf("����%dû�е�һ�ڽӵ㣡\n", e);
            }
            else
            {
                i = FirstAdjVex(*mygra, e);
                if (i != -1)
                    printf("����%d�ĵ�һ�ڽӵ��λ��Ϊ%d\n", e, i);
                else
                    printf("����%dû�е�һ�ڽӵ㣡\n", e);
            }
            getchar(); getchar();
            getchar();
            break;
        case 6:
            printf("��������������Ĺؼ��֣�");
            scanf("%d %d", &e, &j);
            if (gf == 0)
            {
                i = NextAdjVex(G, e, j);
                if (i != -1)
                    printf("����%d����ڶ���%d����һ���ڽӶ���Ϊ%d %s\n", e, j, G.vertices[i].data.key, G.vertices[i].data.others);
                else printf("����һ�ڽӶ��㣡\n");
            }
            else
            {
                i = NextAdjVex(*mygra, e, j);
                if (i != -1)
                    printf("����%d����ڶ���%d����һ���ڽӶ���Ϊ%d %s\n", e, j, (*mygra).vertices[i].data.key, (*mygra).vertices[i].data.others);
                else printf("����һ�ڽӶ��㣡\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 7:
            printf("��������Ҫ����Ķ���ֵ��");
            scanf("%d %s", &value.key, value.others);
            if (gf == 0)
            {
                flag1 = InsertVex(G, value);
                if (flag1 == OK)
                    printf("���� %d %s �ѳɹ�����ͼ��\n", value.key, value.others);
                else if (flag == ERROR)
                    printf("����ʧ�ܣ�\n");
            }
            else
            {
                flag1 = InsertVex(*mygra, value);
                if (flag1 == OK)
                    printf("���� %d %s �ѳɹ�����ͼ��\n", value.key, value.others);
                else if (flag == ERROR)
                    printf("����ʧ�ܣ�\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 8:
            printf("��������Ҫɾ���Ķ���Ĺؼ��֣�");
            scanf("%d", &e);
            
            if (gf == 0)
            {
                flag1 = DeleteVex(G, e);
                if (flag1 == OK)
                    printf("�ؼ���Ϊ%d�Ķ����Ѵ�ͼ��ɾ��\n", e);
                else if (flag1 == ERROR)
                    printf("ɾ��ʧ�ܣ�\n");
            }
            else
            {
                flag1 = DeleteVex(*mygra, e);
                if (flag1 == OK)
                    printf("�ؼ���Ϊ%d�Ķ����Ѵ�ͼ��ɾ��\n", e);
                else if (flag1 == ERROR)
                    printf("ɾ��ʧ�ܣ�\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 9:
            printf("��������Ҫ����Ļ���");
            scanf("%d %d", &e, &j);
            if (gf == 0)
            {
                flag1 = InsertArc(G, e, j);
                if (flag1 == OK)
                    printf("����ɹ���\n");
                else if (flag1 == ERROR)
                    printf("����ʧ�ܣ�\n");
            }
            else
            {
                flag1 = InsertArc(*mygra, e, j);
                if (flag1 == OK)
                    printf("����ɹ���\n");
                else if (flag1 == ERROR)
                    printf("����ʧ�ܣ�\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 10:
            printf("��������Ҫɾ���Ļ���");
            scanf("%d %d", &e, &j);
            if (gf == 0)
            {
                flag1 = DeleteArc(G, e, j);
                if (flag1 == OK)
                    printf("ɾ���ɹ���\n");
                else if (flag1 == ERROR)
                    printf("ɾ��ʧ�ܣ�\n");
            }
            else
            {
                flag1 = DeleteArc(*mygra, e, j);
                if (flag1 == OK)
                    printf("ɾ���ɹ���\n");
                else if (flag1 == ERROR)
                    printf("ɾ��ʧ�ܣ�\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 11:
            for (int m = 0; m < 1000; m++)
                f[m] = 0;
            printf("�����������������\n");
            if (gf == 0)
            {
                DFSTraverse(G, visit);
                printf("\n");
            }
            else
            {
                DFSTraverse(*mygra, visit);
                printf("\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 12:
            for (int m = 0; m < 20; m++)
                a[m] = 0;
            printf("�����������������\n");
            if (gf == 0)
            {
                BFSTraverse(G, visit);
                printf("\n");
            }
            else
            {
                BFSTraverse(*mygra, visit);
                printf("\n");
            }

            getchar(); getchar();
            getchar();
            break;
        case 13:
            printf("�������ļ����ƣ�");
            scanf("%s", FileName);
            if (gf == 0)
            {
                flag1 = SaveGraph(G, FileName);
                if (flag1 == ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else if (flag1 == OK)
                    printf("ͼ�������Ѿ����Ƶ�����Ϊ %s ���ļ��С�\n", FileName);
            }
            else
            {
                flag1 = SaveGraph(*mygra, FileName);
                if (flag1 == ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else if (flag1 == OK)
                    printf("ͼ�������Ѿ����Ƶ�����Ϊ %s ���ļ��С�\n", FileName);
            }
            getchar(); getchar();
            getchar();
            break;
        case 14:
            printf("�������ļ����ƣ�");
            scanf("%s", FileName);
            if (gf == 0)
            {
                flag1 = LoadGraph(G, FileName);
                if (flag1 == ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else if (flag1 == OK)
                    printf("����Ϊ %s ���ļ��е������Ѹ��Ƶ�ͼ�С�\n", FileName);
                else if (flag1 == INFEASIBLE)
                    printf("���ܶ��Ѵ��ڵ�ͼ���н��ж��ļ�������\n");
                else if (flag1 == OVERFLOW)
                    printf("�����\n");
            }
            else
            {
                flag1 = LoadGraph(*mygra, FileName);
                if (flag1 == ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else if (flag1 == OK)
                    printf("����Ϊ %s ���ļ��е������Ѹ��Ƶ�ͼ�С�\n", FileName);
                else if (flag1 == INFEASIBLE)
                    printf("���ܶ��Ѵ��ڵ�ͼ���н��ж��ļ�������\n");
                else if (flag1 == OVERFLOW)
                    printf("�����\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 15: {char ListName[30] = { '\0' };
               printf("����������ͼ�����ƣ�");
               scanf("%s", ListName);
               flag1 = AddGraph(Graphs, ListName);
               if (flag1 == OK) printf("�ɹ���������Ϊ %s ��ͼ��\n", ListName);
               else printf("����ʧ�ܣ�\n");
               getchar(); getchar();
               getchar();
               break;
        }
        case 16:
            printf("��������Ҫɾ����ͼ�����ƣ�");
            scanf("%s", ListName);
            flag1 = RemoveGraph(Graphs, ListName);
            if (flag1 == OK)
                printf("�ɹ�ɾ������Ϊ %s ��ͼ��\n", ListName);
            else if (flag == ERROR)
                printf("ɾ��ʧ�ܣ�\n");
            getchar(); getchar();
            getchar();
            break;
        case 17:
            printf("��������Ҫ���ҵ�ͼ�����ƣ�");
            scanf("%s", ListName);
            i = LocateGraph(Graphs, ListName);
            if (i == 0)
                printf("����������Ϊ %s ��ͼ��\n", ListName);
            else printf("����Ϊ %s ��ͼ�����Ϊ%d\n", ListName, i);
            getchar(); getchar();
            getchar();
            break;
        case 18:
            flag1 = GraphsTraverse(Graphs);
            if (flag1 == ERROR) printf("���Ա�ļ���Ϊ�ա�\n");
            getchar(); getchar();
            getchar();
            break;
        case 19:
            printf("��������Ҫ���в��������Ա����ţ���0��ʼ����");
            scanf("%d", &i);
            flag1 = ChooseGraph(Graphs, i);
            if (flag1 == ERROR)
                printf("�������Ų��Ϸ���\n");
            else printf("����ɶ����Ա��������Ϊ%d�����Ա���в�����\n", i);
            getchar(); getchar();
            getchar();
            break;
        case 20:
            printf("������ýڵ��Ӧ�Ĺؼ��ֵ�ֵ\n");
            int inn;
            scanf("%d", &inn);
            int kk;
            printf("������k��ֵ\n");
            scanf("%d", &kk);
            if (gf == 0)
            {
                VerticesSetLessThanK(G, inn, kk);
            }
            else
                VerticesSetLessThanK(*mygra, inn, kk);
            getchar(); getchar();
            getchar();
            break;
        case 21:
            printf("�����������ڵ�Ĺؼ���\n");
            int v1, v2;
            scanf("%d %d", &v1, &v2);
            if (gf == 0)
                ShortestPathLength(G, v1, v2);
            else
                ShortestPathLength(*mygra, v1, v2);
            getchar(); getchar();
            getchar();
            break;
        case 22:
            //printf("ע����������Ҫ��ͼ���в�����ת��������Ҫ��������ͼ������\n");
            if (gf == 0)
                ConnectedComponentsNums(G, aw);
            else
                ConnectedComponentsNums(*mygra, aw);
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


//1����V��VR����ͼT������OK�����V��VR����ȷ������ERROR���������ͬ�Ĺؼ��֣�����ERROR��
int check(VertexType V[], KeyType VR[][2])
{
    if (V[0].key == -1) return 1;
    for (int i = 0; V[i].key != -1; i++)
    {
        if (i >= 20) return 1;
        for (int j = i + 1; V[j].key != -1; j++)
            if (V[i].key == V[j].key)
                return 1;
    }
    for (int i = 0; VR[i][0] != -1; i++)
        for (int j = i + 1; VR[j][0] != -1; j++)
            if (VR[i][0] == VR[j][0] && VR[i][1] == VR[j][1])
                return 1;
    return 0;
}
status insert(ALGraph& G, int x, int y)
{
    ArcNode* p = NULL; ArcNode* p1 = NULL;
    int i = 21, j = 21;
    for (int k = 0; k < G.vexnum; k++)
    {
        if (x == G.vertices[k].data.key) i = k;
        if (y == G.vertices[k].data.key) j = k;
    }
    if (i == 21 || j == 21) return ERROR;
    if (G.vertices[i].firstarc == NULL)
    {
        G.vertices[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));//Ѱ�ҵ�һ��������
        if (G.vertices[i].firstarc != NULL) {
            G.vertices[i].firstarc->adjvex = j;
            G.vertices[i].firstarc->nextarc = NULL;
        }
    }
    else
    {
        if (!(p = (ArcNode*)malloc(sizeof(ArcNode))))//���û���ҵ����к���Ĵ���
            return OVERFLOW;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
        p->adjvex = j;
    }
    if (G.vertices[j].firstarc == NULL)//�����һ��ָ��Ϊ��
    {
        G.vertices[j].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
        if (G.vertices[j].firstarc != NULL) {
            G.vertices[j].firstarc->adjvex = i;
            G.vertices[j].firstarc->nextarc = NULL;
        }
    }
    else
    {
        if (!(p = (ArcNode*)malloc(sizeof(ArcNode))))//�������������
            return OVERFLOW;
        p->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p;
        p->adjvex = i;
    }
    G.arcnum++;//�������˴������
    return OK;
}
status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2])
{
    flag = check(V, VR);
    if (flag == 1) return ERROR;
    else
    {
        int i = 0;
        for (i = 0; V[i].key != -1; i++)
        {
            G.vertices[i].data.key = V[i].key;
            strcpy(G.vertices[i].data.others, V[i].others);
            G.vertices[i].firstarc = NULL;
        }
        G.vexnum = i;
        G.arcnum = 0;
        for (i = 0; VR[i][0] != -1; i++)
            insert(G, VR[i][0], VR[i][1]);
        return OK;
    }
}

//2��������ͼG,ɾ��G��ȫ������ͱ�
status DestroyGraph(ALGraph& G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    ArcNode* cur, * p, * q;
    VNode curnode;
    for (int i = 0; i < G.vexnum; i++)
    {
        curnode = G.vertices[i];
        p = curnode.firstarc;
        while (p != NULL && p->nextarc != NULL)
        {
            q = p->nextarc;
            p->nextarc = q->nextarc;
            free(q);
        }
        if (p != NULL)
            free(p);
        curnode.firstarc = NULL;
    }
    G.arcnum = 0;
    G.vexnum = 0;
    return 1;
    /********** End **********/
}

//3����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
int LocateVex(ALGraph G, KeyType u)
{
    int i = 0;
    while (i < G.vexnum)
    {
        if (u == G.vertices[i].data.key) return i;
        i++;
    }
    return -1;
}

//4����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK���������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
status PutVex(ALGraph& G, KeyType u, VertexType value)
{
    int i = 0, num = -1;
    while (i < G.vexnum)
    {
        if (u == G.vertices[i].data.key) num = i;
        if (value.key == G.vertices[i].data.key && value.key != u) return ERROR;
        i++;
    }
    if (num == -1) return ERROR;
    G.vertices[num].data = value;
    return OK;
}

//5����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ�򣬷��򷵻�-1��
int FirstAdjVex(ALGraph G, KeyType u)
{
    int i = 0, num = -1;
    while (i < G.vexnum)
    {
        if (u == G.vertices[i].data.key)
        {
            num = i; break;
        }
        i++;
    }
    if (num == -1 || G.vertices[num].firstarc == NULL) return -1;
    else return G.vertices[num].firstarc->adjvex;
}

//6����u��ͼG�в��Ҷ��㣬���ҳɹ����ض���v���ڽӶ��������w����һ�ڽӶ����λ�򣬲���ʧ�ܷ���-1��
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
    int x = -1, y = -1;
    for (int j = 0; j < G.vexnum; j++) {
        if (G.vertices[j].data.key == v) x = j;
    }
    for (int j = 0; j < G.vexnum; j++)
    {
        if (G.vertices[j].data.key == w)
            y = j;
    }
    if (x == -1 || y == -1)
        return -1;
    ArcNode* cur;
    cur = G.vertices[x].firstarc;
    int flg = 0;
    while (cur != NULL)
    {
        if (cur->adjvex == y)
        {
            flg = 1;
            break;
        }
        cur = cur->nextarc;
    }
    if (flg == 0)
        return -1;
    if (cur->nextarc == NULL)
        return -1;
    else
        return cur->nextarc->adjvex;

}

//7��ͼG�в��붥��v���ɹ�����OK,���򷵻�ERROR
status InsertVex(ALGraph& G, VertexType v)
{
    if (G.vexnum == 20)//�ڵ����Ѿ�����
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (v.key == G.vertices[i].data.key)
            return ERROR;
    }
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

//8��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
status DeleteVex(ALGraph& G, KeyType v)
{
    int i = 0, num = -1;
    while (i < G.vexnum) {
        if (v == G.vertices[i].data.key) num = i;
        i++;
    }
    if (num == -1) return ERROR;
    if (num != -1 && G.vexnum == 1) return ERROR;
    ArcNode* p1, * p2;
    for (i = 0; i < G.vexnum; i++)
    {
        p1 = G.vertices[i].firstarc;
        p2 = p1;
        if (p1 == NULL) continue;
        if (i == num)
        {
            do {
                p2 = p1;
                p1 = p1->nextarc;
                free(p2);
            } while (p1);
            G.vertices[i].firstarc = NULL;
            continue;
        }
        else
        {
            if (p1->adjvex == num)
            {
                G.vertices[i].firstarc = p1->nextarc; free(p1); G.arcnum--;
            }
            else
            {
                p1 = p1->nextarc;
                while (p1)
                {
                    if (p1->adjvex == num) { p2->nextarc = p1->nextarc; free(p1); G.arcnum--; break; }
                    else { p1 = p1->nextarc; p2 = p2->nextarc; }
                }
            }
        }
    }
    for (i = num; i < G.vexnum; i++)
        G.vertices[i] = G.vertices[i + 1];
    G.vexnum--;
    for (i = 0; i < G.vexnum; i++)
    {
        p1 = G.vertices[i].firstarc;
        while (p1)
        {
            if (p1->adjvex > num) p1->adjvex--;
            p1 = p1->nextarc;
        }
    }
    return OK;
}

//9��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
status InsertArc(ALGraph& G, KeyType v, KeyType w)
{
    int x = -1, y = -1;//��Ҫת�������е�˳��
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
            x = i;
        if (G.vertices[i].data.key == w)
            y = i;
    }
    if (x == -1 || y == -1)
    {
        return ERROR;
    }
    ArcNode* che;
    che = G.vertices[x].firstarc;
    while (che != NULL)
    {
        if (che->adjvex == y)
            return ERROR;
        che = che->nextarc;
    }
    ArcNode* qian, * hou;
    qian = G.vertices[x].firstarc;
    hou = G.vertices[y].firstarc;
    ArcNode* lq, * lh;
    lq = (ArcNode*)malloc(sizeof(ArcNode));
    lq->adjvex = y;
    lq->nextarc = G.vertices[x].firstarc;
    G.vertices[x].firstarc = lq;
    lh = (ArcNode*)malloc(sizeof(ArcNode));
    lh->adjvex = x;
    lh->nextarc = G.vertices[y].firstarc;
    G.vertices[y].firstarc = lh;
    G.arcnum++;
    return OK;
}

//10��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
status DeleteArc(ALGraph& G, KeyType v, KeyType w)
{
    int x = -1, y = -1;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
            x = i;
        if (G.vertices[i].data.key == w)
            y = i;
    }
    if (x == -1 || y == -1)
    {
        return ERROR;
    }
    ArcNode* che;
    che = G.vertices[x].firstarc;
    int fl = 0;
    while (che != NULL)
    {
        if (che->adjvex == y)
            fl = 1;
        che = che->nextarc;
    }
    if (fl == 0)
        return ERROR;
    ArcNode* p, * c, * cur = NULL, * pre = NULL;
    //�ȴ���ǰ���
    ArcNode** head = &(G.vertices[x].firstarc);//��¼ͷ�ڵ�λ��
    pre = G.vertices[x].firstarc;
    cur = NULL;
    if (pre != NULL)
        cur = pre->nextarc;
    while (pre != NULL)
    {
        if (pre->adjvex == y && pre == *head)//�����ͷ�ڵ����⴦��
        {
            *head = cur;
            free(pre);
            pre = *head;
            if (pre != NULL)
                cur = pre->nextarc;
            continue;
        }
        if (cur != NULL && cur->adjvex == y)//����ͷ�ڵ���������
        {
            pre->nextarc = cur->nextarc;
            free(cur);
            cur = pre->nextarc;
            continue;
        }
        if (pre != NULL)//�����β�������ж�
            pre = pre->nextarc;
        if (cur != NULL)
            cur = cur->nextarc;
    }
    //�ڴ�������Ǹ�

    ArcNode** head1 = &(G.vertices[y].firstarc);
    p = G.vertices[y].firstarc;
    c = NULL;
    if (p != NULL)
        c = p->nextarc;
    while (p != NULL)
    {
        if (p->adjvex == x && p == *head1)//�����������Ǹ�
        {
            *head1 = c;
            free(p);
            p = *head1;
            if (p != NULL)
                c = p->nextarc;
            continue;
        }
        if (c != NULL && c->adjvex == x)
        {
            p->nextarc = c->nextarc;//���Ǻ�ǰ��һ���Ĳ���
            free(c);
            c = p->nextarc;
            continue;
        }
        if (p != NULL)
            p = p->nextarc;
        if (c != NULL)
            c = c->nextarc;
    }
    G.arcnum--;
    return OK;
}

//11��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
void DFS(ALGraph& G, int num, void (*visit)(VertexType))
{
    if (f[num]) return;
    ArcNode* p = NULL;
    f[num] = 1;
    visit(G.vertices[num].data);
    p = G.vertices[num].firstarc;
    while (p) {
        num = p->adjvex;
        DFS(G, num, visit);
        p = p->nextarc;
    }
    return;
}
status DFSTraverse(ALGraph& G, void (*visit)(VertexType))
{
    int i;
    for (i = 0; i < G.vexnum; i++) {
        DFS(G, i, visit);
    }
    return OK;
}

//12��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
status BFSTraverse(ALGraph& G, void (*visit)(VertexType))
{
    int i = 0;
    ArcNode* p1;
    while (i < G.vexnum)
    {
        if (a[i] == 0) { visit(G.vertices[i].data); a[i] = 1; }
        p1 = G.vertices[i].firstarc;
        while (p1 != NULL)
        {
            if (a[p1->adjvex] == 0) 
            { visit(G.vertices[p1->adjvex].data); //���ʽڵ�
                a[p1->adjvex] = 1; }//�ڵ���ջ
            p1 = p1->nextarc;
        }
        i++;
    }
    return OK;
}

//13��ͼ������д�뵽�ļ�FileName��
status SaveGraph(ALGraph G, char FileName[])
//��ͼ������д�뵽�ļ�FileName��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
    FILE* fp;
    fp = fopen(FileName, "w+");
    if (fp == NULL)
        return ERROR;
    int que[100] = {};
    int n = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);//��������
        que[n++] = G.vertices[i].data.key;
    }
    fprintf(fp, "%d %s ", -1, "nil");
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (que[i] > que[j])
            {
                int temp = que[i];
                que[i] = que[j];
                que[j] = temp;//���մ�С˳���ڽڵ�����е���Դ�С����
            }
        }
    }
    for (int q = 0; q < G.vexnum; q++)
    {
        int i = 0;
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.vertices[j].data.key == que[q])
                i = j;//��¼��ǰi����һ������
        }

        while (G.vertices[i].firstarc != NULL && G.vertices[i].firstarc->adjvex != -1)
        {
            int tail = 0;
            ArcNode* p = G.vertices[i].firstarc;

            while (p->nextarc != NULL && p->nextarc->adjvex != -1)
            {
                p = p->nextarc;//Ѱ�����ĩβ��Ԫ��
            }

            tail = p->adjvex;
            ArcNode* q = G.vertices[tail].firstarc;
            while (q != NULL)
            {
                if (q->adjvex == i)
                {
                    q->adjvex = -1;//���Ƿ��ҵ�����ڵ㣬����ҵ��˾ͷ����±꣬û�ҵ���breakl
                    break;
                }
                q = q->nextarc;

            }
            fprintf(fp, "%d %d ", G.vertices[i].data.key, G.vertices[tail].data.key);//��������ȥ����ڵ�ͱ�
            p->adjvex = -1;
        }

    }
    fprintf(fp, "%d %d ", -1, -1);//�������һ�¸ýڵ�Ķ��������־
    fclose(fp);
    return OK;

    /********** End 1 **********/
}

//14�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
status LoadGraph(ALGraph& G, char FileName[])
//�����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    VertexType V[100] = {};
    KeyType VR[100][2] = {};
    FILE* fp;
    fp = fopen(FileName, "r+");
    int i = 0;
    do {
        fscanf(fp, "%d %s", &V[i].key, V[i].others);
    } while (V[i++].key != -1);
    i = 0;
    do {
        fscanf(fp, "%d %d", &VR[i][0], &VR[i][1]);
    } while (VR[i++][0] != -1);//���ݵĶ���
    int nv = 0, nvr = 0, x, y;
    ArcNode* l;
    while (V[nv].key != -1) nv++;//�ڵ�ߵ���Ŀ
    while (VR[nvr][0] != -1) nvr++;//��Щ�͵�һ��ûɶ������Ƕ��˸���ȡ�Ĺ���
    //������̾��ǵ�һ��
    if (nv > MAX_VERTEX_NUM || nv == 0) return ERROR;
    G.vexnum = nv;
    G.arcnum = nvr;
    G.kind = UDG;
    for (int i = 0; i < nv - 1; i++) {
        for (int j = i + 1; j < nv; j++) {
            if (V[i].key == V[j].key) return ERROR;
        }
    }
    for (int i = 0; i < nvr; i++) {
        int fv = 0, fvr = 0;
        for (int j = 0; j < nv; j++) {
            if (VR[i][0] == V[j].key) fv = 1;//��ֵ
            if (VR[i][1] == V[j].key) fvr = 1;
        }
        if (fv == 0 || fvr == 0) return ERROR;
    }
    for (int i = 0; i < nv; i++) {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
    }
    for (int i = 0; i < nvr; i++) {
        if (VR[i][0] == VR[i][1]) continue;
        int j;
        for (j = 0; j < i; j++) {
            if ((VR[i][0] == VR[j][0] && VR[i][1] == VR[j][1]) || (VR[i][0] == VR[j][1] && VR[i][1] == VR[j][0])) break;
        }
        if (j != i) continue;
        for (j = 0; j < nv; j++) {
            if (V[j].key == VR[i][0]) x = j;
        }
        for (j = 0; j < nv; j++) {
            if (V[j].key == VR[i][1]) y = j;
        }
        l = (ArcNode*)malloc(sizeof(ArcNode));
        l->adjvex = y;
        l->nextarc = G.vertices[x].firstarc;
        G.vertices[x].firstarc = l;
        l = (ArcNode*)malloc(sizeof(ArcNode));
        l->adjvex = x;
        l->nextarc = G.vertices[y].firstarc;
        G.vertices[y].firstarc = l;
    }
    return OK;

    /********** End 2 **********/
}

//15��ɭ�������һ��ͼ
status AddGraph(GRAPHS& Graphs, char ListName[])
{
    for (int i = 0; i < Graphs.length; i++)
        if (strcmp(Graphs.elem[i].name, ListName) == 0)
        {
            printf("�������Ѵ�������Ϊ %s ��ͼ��\n", ListName);
            return ERROR;
        }
    printf("��ͼ %s ����Ӷ��㣬�����붥�����к͹�ϵ�����У�\n", ListName);
    int i;
    VertexType V[30] = {};
    KeyType VR[100][2] = {};
    i = 0;
    do {
        scanf("%d%s", &V[i].key, V[i].others);
    } while (V[i++].key != -1);
    i = 0;
    do {
        scanf("%d%d", &VR[i][0], &VR[i][1]);
    } while (VR[i++][0] != -1);
    flag = 0;
    Graphs.elem[Graphs.length].G.vexnum = 0;
    int a = CreateCraph(Graphs.elem[Graphs.length].G, V, VR);
    if (a == OK) {
        strcpy(Graphs.elem[Graphs.length].name, ListName);
        Graphs.length++;
        return OK;
    }
    else if (a == ERROR) {
        printf("�ؼ��ֲ�Ψһ��"); return ERROR;
    }
}

//16��ɭ����ɾ��һ��ͼ
status RemoveGraph(GRAPHS& Graphs, char ListName[])
{
    for (int i = 0; i < Graphs.length; i++)
    {
        if (strcmp(Graphs.elem[i].name, ListName) == 0)
        {
            DestroyGraph(Graphs.elem[i].G);
            for (int k = i; k < Graphs.length - 1; k++)
                Graphs.elem[k] = Graphs.elem[k + 1];
            Graphs.length--;
            return OK;
        }
    }
    return ERROR;
}

//17��ɭ���в���һ������ΪListName��ͼ���ɹ������߼���ţ����򷵻�0
int LocateGraph(GRAPHS& Graphs, char ListName[]) {
    for (int i = 0; i < Graphs.length; i++)
    {
        if (strcmp(Graphs.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

//18����ɭ���и���ͼ
status GraphsTraverse(GRAPHS& Graphs) {
    if (Graphs.length == 0) return ERROR;
    for (int n = 0; n < Graphs.length; n++)
    {
        for (int m = 0; m < 20; m++)
            a[m] = 0;
        printf("%s ", Graphs.elem[n].name);
        BFSTraverse(Graphs.elem[n].G, visit);
        putchar('\n');
    }
    return OK;
}

//19ѡ��һ��ͼ����������ţ������ɶ�����в���
status ChooseGraph(GRAPHS& Graphs, int x) {
    if (x > Graphs.length || x < 0) return ERROR;
    else
    {
        mygra = &(Graphs.elem[x].G);
        gf = 1;
    }
    return OK;
}



int minl;
status VerticesSetLessThanK(ALGraph G, KeyType v, int km)
{
    int index = -1;//��¼����ڵ���ͼ�е�λ��
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
            index = i;
    }
    if (index == -1)
    {
        return 0;//û���ѵ������Ľڵ�
    }
    int dis[1001] = {};
    int mark[1001] = {};//�������ڵ��Ƿ�������
    memset(dis, 0x7f, sizeof(dis));
    dis[index] = 0;
    mark[index] = 1;
    ArcNode* cur;
    cur = G.vertices[index].firstarc;//ѡȡ�����ʼ��
    while (cur != NULL)
    {
        int s = 0;
        dis[cur->adjvex] = 1;
        cur = cur->nextarc;//��ʼ��
    }
    for (int i = 0; i < G.vexnum - 1; i++)
    {
        minl = 999;
        int k = -1;
        for (int j = 0; j < G.vexnum; j++)
        {
            if ((!mark[j]) && (dis[j] < minl))//Ѱ�ҵ����ڵ������û���ѹ��ı�
            {
                minl = dis[j];
                k = j;
            }
        }
        if (k == -1)
            break;
        mark[k] = 1;
        ArcNode* cur1;
        cur1 = G.vertices[k].firstarc;
        while (cur1 != NULL)
        {
            if (dis[k] + 1 < dis[cur1->adjvex])
            {
                dis[cur1->adjvex] = dis[k] + 1;
            }
            cur1 = cur1->nextarc;//ʹ�õϽ�˹�����㷨����ÿ�����ֵ
        }
    }
    int flag = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (dis[i] < km)
        {
            printf("%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
            flag = 1;
        }
    }
    if (flag == 0)
        printf("�����������Ľڵ㣡\n");//�ж��Ƿ������������
    return 1;
    //����n����G.venums
}



status ShortestPathLength(ALGraph G, KeyType v, KeyType w)
{
    int index2 = -1;
    int index = -1;//��¼����ڵ���ͼ�е�λ��
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
            index = i;
        if (G.vertices[i].data.key == w)
            index2 = i;
    }
    if (index == -1)
    {
        return 0;//û���ѵ������Ľڵ�
    }
    int dis[1001] = {};
    int mark[1001] = {};//�������ڵ��Ƿ�������
    memset(dis, 0x7f, sizeof(dis));
    dis[index] = 0;
    mark[index] = 1;
    ArcNode* cur;
    cur = G.vertices[index].firstarc;//ѡȡ�����ʼ��
    while (cur != NULL)
    {
        int s = 0;
        dis[cur->adjvex] = 1;
        if (cur->nextarc != NULL)
        {
            cur = cur->nextarc;
            continue;
        }//��ʼ��
        break;
    }
    for (int i = 0; i < G.vexnum - 1; i++)
    {
        minl = 999;
        int k = -1;
        for (int j = 0; j < G.vexnum; j++)
        {
            if ((!mark[j]) && (dis[j] < minl))
            {
                minl = dis[j];//ͬ�����˼·�������е�����������һ�ߣ�������ο����˾�������������
                k = j;
            }
        }
        if (k == -1)
            break;
        mark[k] = 1;
        ArcNode* cur1;
        cur1 = G.vertices[k].firstarc;
        while (cur1 != NULL)
        {
            if (dis[k] + 1 < dis[cur1->adjvex])//ʹ�����·���㷨���д���
            {
                dis[cur1->adjvex] = dis[k] + 1;
            }
            cur1 = cur1->nextarc;
        }
    }
    if (dis[index2] != 0)
    {
        printf("��%d %s�ľ���Ϊ%d\n", G.vertices[index2].data.key, G.vertices[index2].data.others, dis[index2]);
    }
    return 1;
}




int find(int x)
{
    if (x == f[x])
        return x;
    else
    {
        f[x] = find(f[x]);
        return f[x];
    }
}
void merge(int p, int q)
{
    int x = find(p);
    int y = find(q);
    f[x] = y;
}
status ConnectedComponentsNums(ALGraph G, char FileName[])
{
    int tn = G.vexnum;//tnΪ��ͨ��������
    VertexType V[100] = {};
    KeyType VR[100][2] = {};
    int v1, v2;
    SaveGraph(G, FileName);
    FILE* fp;
    fp = fopen(FileName, "r+");
    int i = 0;
    do {
        fscanf(fp, "%d %s", &V[i].key, V[i].others);
    } while (V[i++].key != -1);
    for (int i = 0; i < G.vexnum; i++)
    {
        f[i] = i;//���鼯�ĳ�ʼ��
    }
    i = 0;
    while (fscanf(fp, "%d %d", &v1, &v2) && v1 != -1)
    {

        int in1 = -1, in2 = -1;//��¼������������Ӧ�Ľڵ��λ��
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.vertices[i].data.key == v1)
                in1 = i;
            if (G.vertices[i].data.key == v2)
                in2 = i;
        }
        if (in1 == -1 || in2 == -1)
            return -1;
        if (find(in1) != find(in2))//�������ͬһ�����鼯����ô��Ҫ��ͨ��������
            //��֮����Ҫ�����仯
        {
            tn--;
            merge(in1, in2);
        }
        else
        {
            merge(in1, in2);
        }

    }
    LoadGraph(G,FileName);
    
    printf("��ͨ�����ĸ���Ϊ��%d\n", tn);
    *mygra = G;
    return 1;
}