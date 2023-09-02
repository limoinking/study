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
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号 
    struct ArcNode* nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode {				//头结点及其数组类型定义
    VertexType data;       	//顶点信息
    ArcNode* firstarc;      	 //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum, arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;

typedef struct {//森林的定义
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
status VerticesSetLessThanK(ALGraph G, KeyType v, int km);//小于k的节点集合
status ShortestPathLength(ALGraph G, KeyType v, KeyType w);//节点中的最短路径使用迪杰斯特拉算法
status ConnectedComponentsNums(ALGraph G, char FileName[]);//连通分量的测试

int flag = 0;
int f[1000] = {};//并查集
int a[20] = { 0 };
char aw[21] = "22.txt";//这个是专用的

ALGraph* mygra = NULL;//这个是处理选图情况
int gf = 0;//查看是否有被选取的图

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
        printf("\n请选择你的操作[0~19]:\n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            i = 0;
            printf("请输入顶点序列，以-1 nil结束：");
            do {
                scanf("%d%s", &V[i].key, V[i].others);
            } while (V[i++].key != -1);
            i = 0;
            printf("请输入关系对序列，以-1 -1结束：");
            do {
                scanf("%d%d", &VR[i][0], &VR[i][1]);
            } while (VR[i++][0] != -1);
            if (CreateCraph(G, V, VR) == OK)
                printf("图创建成功！\n");
            else
                printf("图创建失败！\n");
            getchar(); getchar();
            getchar();
            break;
        case 2:
            if (gf == 0)
            {
                if (DestroyGraph(G) == OK)
                    printf("成功销毁图并释放数据元素的空间。\n");
                else
                    printf("不能对不存在的图进行销毁操作！\n");
            }
            else
            {
                if (DestroyGraph(*mygra) == OK)
                    printf("成功销毁图并释放数据元素的空间。\n");
                else
                    printf("不能对不存在的图进行销毁操作！\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 3:
            printf("请输入想要在图中查找的顶点的关键字：");
            scanf("%d", &e);
            if (gf == 0)
            {
                i = LocateVex(G, e);
                if (i != -1) printf("图中关键字为%d的顶点的位序为%d\n", e, i);
                else
                    printf("图中不存在关键字为%d的顶点！\n", e);
            }
            else
            {
                i = LocateVex(*mygra, e);
                if (i != -1) printf("图中关键字为%d的顶点的位序为%d\n", e, i);
                else
                    printf("图中不存在关键字为%d的顶点！\n", e);
            }
            getchar(); getchar();
            getchar();
            break;
        case 4:
            printf("请输入想要修改的顶点的关键字：");
            scanf("%d", &e);
            printf("将其顶点值修改为：");
            scanf("%d %s", &value.key, value.others);
            if (gf == 0)
            {
                flag1 = PutVex(G, e, value);
                if (flag1 == ERROR)
                    printf("赋值操作失败！\n");
                else if (flag1 == OK)
                    printf("已将关键字为%d的顶点值修改为%d,%s\n", e, value.key, value.others);
            }
            else
            {
                flag1 = PutVex(*mygra, e, value);
                if (flag1 == ERROR)
                    printf("赋值操作失败！\n");
                else if (flag1 == OK)
                    printf("已将关键字为%d的顶点值修改为%d,%s\n", e, value.key, value.others);
            }
            getchar(); getchar();
            getchar();
            break;
        case 5:
            printf("请输入想要查找其第一邻接点的顶点：");
            scanf("%d", &e);
            if (gf == 0)
            {
                i = FirstAdjVex(G, e);
                if (i != -1)
                    printf("顶点%d的第一邻接点的位序为%d\n", e, i);
                else
                    printf("顶点%d没有第一邻接点！\n", e);
            }
            else
            {
                i = FirstAdjVex(*mygra, e);
                if (i != -1)
                    printf("顶点%d的第一邻接点的位序为%d\n", e, i);
                else
                    printf("顶点%d没有第一邻接点！\n", e);
            }
            getchar(); getchar();
            getchar();
            break;
        case 6:
            printf("请输入两个顶点的关键字：");
            scanf("%d %d", &e, &j);
            if (gf == 0)
            {
                i = NextAdjVex(G, e, j);
                if (i != -1)
                    printf("顶点%d相对于顶点%d的下一个邻接顶点为%d %s\n", e, j, G.vertices[i].data.key, G.vertices[i].data.others);
                else printf("无下一邻接顶点！\n");
            }
            else
            {
                i = NextAdjVex(*mygra, e, j);
                if (i != -1)
                    printf("顶点%d相对于顶点%d的下一个邻接顶点为%d %s\n", e, j, (*mygra).vertices[i].data.key, (*mygra).vertices[i].data.others);
                else printf("无下一邻接顶点！\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 7:
            printf("请输入想要插入的顶点值：");
            scanf("%d %s", &value.key, value.others);
            if (gf == 0)
            {
                flag1 = InsertVex(G, value);
                if (flag1 == OK)
                    printf("顶点 %d %s 已成功插入图中\n", value.key, value.others);
                else if (flag == ERROR)
                    printf("插入失败！\n");
            }
            else
            {
                flag1 = InsertVex(*mygra, value);
                if (flag1 == OK)
                    printf("顶点 %d %s 已成功插入图中\n", value.key, value.others);
                else if (flag == ERROR)
                    printf("插入失败！\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 8:
            printf("请输入想要删除的顶点的关键字：");
            scanf("%d", &e);
            
            if (gf == 0)
            {
                flag1 = DeleteVex(G, e);
                if (flag1 == OK)
                    printf("关键字为%d的顶点已从图中删除\n", e);
                else if (flag1 == ERROR)
                    printf("删除失败！\n");
            }
            else
            {
                flag1 = DeleteVex(*mygra, e);
                if (flag1 == OK)
                    printf("关键字为%d的顶点已从图中删除\n", e);
                else if (flag1 == ERROR)
                    printf("删除失败！\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 9:
            printf("请输入想要插入的弧：");
            scanf("%d %d", &e, &j);
            if (gf == 0)
            {
                flag1 = InsertArc(G, e, j);
                if (flag1 == OK)
                    printf("插入成功！\n");
                else if (flag1 == ERROR)
                    printf("插入失败！\n");
            }
            else
            {
                flag1 = InsertArc(*mygra, e, j);
                if (flag1 == OK)
                    printf("插入成功！\n");
                else if (flag1 == ERROR)
                    printf("插入失败！\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 10:
            printf("请输入想要删除的弧：");
            scanf("%d %d", &e, &j);
            if (gf == 0)
            {
                flag1 = DeleteArc(G, e, j);
                if (flag1 == OK)
                    printf("删除成功！\n");
                else if (flag1 == ERROR)
                    printf("删除失败！\n");
            }
            else
            {
                flag1 = DeleteArc(*mygra, e, j);
                if (flag1 == OK)
                    printf("删除成功！\n");
                else if (flag1 == ERROR)
                    printf("删除失败！\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 11:
            for (int m = 0; m < 1000; m++)
                f[m] = 0;
            printf("深度优先搜索遍历：\n");
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
            printf("广度优先搜索遍历：\n");
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
            printf("请输入文件名称：");
            scanf("%s", FileName);
            if (gf == 0)
            {
                flag1 = SaveGraph(G, FileName);
                if (flag1 == ERROR)
                    printf("文件打开失败！\n");
                else if (flag1 == OK)
                    printf("图的内容已经复制到名称为 %s 的文件中。\n", FileName);
            }
            else
            {
                flag1 = SaveGraph(*mygra, FileName);
                if (flag1 == ERROR)
                    printf("文件打开失败！\n");
                else if (flag1 == OK)
                    printf("图的内容已经复制到名称为 %s 的文件中。\n", FileName);
            }
            getchar(); getchar();
            getchar();
            break;
        case 14:
            printf("请输入文件名称：");
            scanf("%s", FileName);
            if (gf == 0)
            {
                flag1 = LoadGraph(G, FileName);
                if (flag1 == ERROR)
                    printf("文件打开失败！\n");
                else if (flag1 == OK)
                    printf("名称为 %s 的文件中的内容已复制到图中。\n", FileName);
                else if (flag1 == INFEASIBLE)
                    printf("不能对已存在的图进行进行读文件操作。\n");
                else if (flag1 == OVERFLOW)
                    printf("溢出！\n");
            }
            else
            {
                flag1 = LoadGraph(*mygra, FileName);
                if (flag1 == ERROR)
                    printf("文件打开失败！\n");
                else if (flag1 == OK)
                    printf("名称为 %s 的文件中的内容已复制到图中。\n", FileName);
                else if (flag1 == INFEASIBLE)
                    printf("不能对已存在的图进行进行读文件操作。\n");
                else if (flag1 == OVERFLOW)
                    printf("溢出！\n");
            }
            getchar(); getchar();
            getchar();
            break;
        case 15: {char ListName[30] = { '\0' };
               printf("请输入新增图的名称：");
               scanf("%s", ListName);
               flag1 = AddGraph(Graphs, ListName);
               if (flag1 == OK) printf("成功新增名称为 %s 的图。\n", ListName);
               else printf("新增失败！\n");
               getchar(); getchar();
               getchar();
               break;
        }
        case 16:
            printf("请输入想要删除的图的名称：");
            scanf("%s", ListName);
            flag1 = RemoveGraph(Graphs, ListName);
            if (flag1 == OK)
                printf("成功删除名称为 %s 的图。\n", ListName);
            else if (flag == ERROR)
                printf("删除失败！\n");
            getchar(); getchar();
            getchar();
            break;
        case 17:
            printf("请输入想要查找的图的名称：");
            scanf("%s", ListName);
            i = LocateGraph(Graphs, ListName);
            if (i == 0)
                printf("不存在名称为 %s 的图。\n", ListName);
            else printf("名称为 %s 的图的序号为%d\n", ListName, i);
            getchar(); getchar();
            getchar();
            break;
        case 18:
            flag1 = GraphsTraverse(Graphs);
            if (flag1 == ERROR) printf("线性表的集合为空。\n");
            getchar(); getchar();
            getchar();
            break;
        case 19:
            printf("请输入想要进行操作的线性表的序号（从0开始）：");
            scanf("%d", &i);
            flag1 = ChooseGraph(Graphs, i);
            if (flag1 == ERROR)
                printf("输入的序号不合法！\n");
            else printf("下面可对线性表集合中序号为%d的线性表进行操作。\n", i);
            getchar(); getchar();
            getchar();
            break;
        case 20:
            printf("请输入该节点对应的关键字的值\n");
            int inn;
            scanf("%d", &inn);
            int kk;
            printf("请输入k的值\n");
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
            printf("请输入两个节点的关键字\n");
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
            //printf("注：本操作需要对图进行不可逆转处理，故需要重新销毁图并输入\n");
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
    printf("欢迎下次再使用本系统！\n");
}//end of main()


//1根据V和VR构造图T并返回OK；如果V和VR不正确，返回ERROR；如果有相同的关键字，返回ERROR。
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
        G.vertices[i].firstarc = (ArcNode*)malloc(sizeof(ArcNode));//寻找第一个在哪里
        if (G.vertices[i].firstarc != NULL) {
            G.vertices[i].firstarc->adjvex = j;
            G.vertices[i].firstarc->nextarc = NULL;
        }
    }
    else
    {
        if (!(p = (ArcNode*)malloc(sizeof(ArcNode))))//如果没有找到进行后序的处理
            return OVERFLOW;
        p->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p;
        p->adjvex = j;
    }
    if (G.vertices[j].firstarc == NULL)//如果第一个指向为空
    {
        G.vertices[j].firstarc = (ArcNode*)malloc(sizeof(ArcNode));
        if (G.vertices[j].firstarc != NULL) {
            G.vertices[j].firstarc->adjvex = i;
            G.vertices[j].firstarc->nextarc = NULL;
        }
    }
    else
    {
        if (!(p = (ArcNode*)malloc(sizeof(ArcNode))))//处理其他的情况
            return OVERFLOW;
        p->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p;
        p->adjvex = i;
    }
    G.arcnum++;//最后别忘了处理变数
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

//2销毁无向图G,删除G的全部顶点和边
status DestroyGraph(ALGraph& G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
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

//3根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
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

//4根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；如果查找失败或关键字不唯一，返回ERROR
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

//5根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
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

//6根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序，查找失败返回-1；
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

//7在图G中插入顶点v，成功返回OK,否则返回ERROR
status InsertVex(ALGraph& G, VertexType v)
{
    if (G.vexnum == 20)//节点数已经满了
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

//8在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
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

//9在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
status InsertArc(ALGraph& G, KeyType v, KeyType w)
{
    int x = -1, y = -1;//需要转换到表中的顺序
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

//10在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
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
    //先处理前面的
    ArcNode** head = &(G.vertices[x].firstarc);//记录头节点位置
    pre = G.vertices[x].firstarc;
    cur = NULL;
    if (pre != NULL)
        cur = pre->nextarc;
    while (pre != NULL)
    {
        if (pre->adjvex == y && pre == *head)//如果是头节点特殊处理
        {
            *head = cur;
            free(pre);
            pre = *head;
            if (pre != NULL)
                cur = pre->nextarc;
            continue;
        }
        if (cur != NULL && cur->adjvex == y)//不是头节点正常处理
        {
            pre->nextarc = cur->nextarc;
            free(cur);
            cur = pre->nextarc;
            continue;
        }
        if (pre != NULL)//最后收尾条件的判断
            pre = pre->nextarc;
        if (cur != NULL)
            cur = cur->nextarc;
    }
    //在处理后面那个

    ArcNode** head1 = &(G.vertices[y].firstarc);
    p = G.vertices[y].firstarc;
    c = NULL;
    if (p != NULL)
        c = p->nextarc;
    while (p != NULL)
    {
        if (p->adjvex == x && p == *head1)//最后处理特殊的那个
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
            p->nextarc = c->nextarc;//还是和前面一样的步骤
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

//11对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
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

//12对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
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
            { visit(G.vertices[p1->adjvex].data); //访问节点
                a[p1->adjvex] = 1; }//节点入栈
            p1 = p1->nextarc;
        }
        i++;
    }
    return OK;
}

//13将图的数据写入到文件FileName中
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE* fp;
    fp = fopen(FileName, "w+");
    if (fp == NULL)
        return ERROR;
    int que[100] = {};
    int n = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);//输入数据
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
                que[j] = temp;//按照大小顺序（在节点矩阵中的相对大小排序
            }
        }
    }
    for (int q = 0; q < G.vexnum; q++)
    {
        int i = 0;
        for (int j = 0; j < G.vexnum; j++)
        {
            if (G.vertices[j].data.key == que[q])
                i = j;//记录当前i对哪一个处理
        }

        while (G.vertices[i].firstarc != NULL && G.vertices[i].firstarc->adjvex != -1)
        {
            int tail = 0;
            ArcNode* p = G.vertices[i].firstarc;

            while (p->nextarc != NULL && p->nextarc->adjvex != -1)
            {
                p = p->nextarc;//寻找最后末尾的元素
            }

            tail = p->adjvex;
            ArcNode* q = G.vertices[tail].firstarc;
            while (q != NULL)
            {
                if (q->adjvex == i)
                {
                    q->adjvex = -1;//看是否找到这个节点，如果找到了就返回下标，没找到就breakl
                    break;
                }
                q = q->nextarc;

            }
            fprintf(fp, "%d %d ", G.vertices[i].data.key, G.vertices[tail].data.key);//最后输入进去这个节点和边
            p->adjvex = -1;
        }

    }
    fprintf(fp, "%d %d ", -1, -1);//最后输入一下该节点的读入结束标志
    fclose(fp);
    return OK;

    /********** End 1 **********/
}

//14读入文件FileName的图数据，创建图的邻接表
status LoadGraph(ALGraph& G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
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
    } while (VR[i++][0] != -1);//数据的读入
    int nv = 0, nvr = 0, x, y;
    ArcNode* l;
    while (V[nv].key != -1) nv++;//节点边的数目
    while (VR[nvr][0] != -1) nvr++;//这些和第一个没啥区别就是多了个读取的过程
    //下面过程就是第一个
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
            if (VR[i][0] == V[j].key) fv = 1;//赋值
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

//15在森林中添加一个图
status AddGraph(GRAPHS& Graphs, char ListName[])
{
    for (int i = 0; i < Graphs.length; i++)
        if (strcmp(Graphs.elem[i].name, ListName) == 0)
        {
            printf("集合中已存在名称为 %s 的图！\n", ListName);
            return ERROR;
        }
    printf("在图 %s 中添加顶点，请输入顶点序列和关系对序列：\n", ListName);
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
        printf("关键字不唯一！"); return ERROR;
    }
}

//16在森林中删除一个图
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

//17在森林中查找一个名称为ListName的图，成功返回逻辑序号，否则返回0
int LocateGraph(GRAPHS& Graphs, char ListName[]) {
    for (int i = 0; i < Graphs.length; i++)
    {
        if (strcmp(Graphs.elem[i].name, ListName) == 0) return i + 1;
    }
    return 0;
}

//18遍历森林中各个图
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

//19选择一个图，输入其序号，后续可对其进行操作
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
    int index = -1;//记录这个节点在图中的位置
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
            index = i;
    }
    if (index == -1)
    {
        return 0;//没有搜到这样的节点
    }
    int dis[1001] = {};
    int mark[1001] = {};//标记这个节点是否被搜索过
    memset(dis, 0x7f, sizeof(dis));
    dis[index] = 0;
    mark[index] = 1;
    ArcNode* cur;
    cur = G.vertices[index].firstarc;//选取这个初始化
    while (cur != NULL)
    {
        int s = 0;
        dis[cur->adjvex] = 1;
        cur = cur->nextarc;//初始化
    }
    for (int i = 0; i < G.vexnum - 1; i++)
    {
        minl = 999;
        int k = -1;
        for (int j = 0; j < G.vexnum; j++)
        {
            if ((!mark[j]) && (dis[j] < minl))//寻找到相邻的最近的没有搜过的边
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
            cur1 = cur1->nextarc;//使用迪杰斯特拉算法更新每个点的值
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
        printf("不存在这样的节点！\n");//判断是否搜索到这个点
    return 1;
    //其中n等于G.venums
}



status ShortestPathLength(ALGraph G, KeyType v, KeyType w)
{
    int index2 = -1;
    int index = -1;//记录这个节点在图中的位置
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
            index = i;
        if (G.vertices[i].data.key == w)
            index2 = i;
    }
    if (index == -1)
    {
        return 0;//没有搜到这样的节点
    }
    int dis[1001] = {};
    int mark[1001] = {};//标记这个节点是否被搜索过
    memset(dis, 0x7f, sizeof(dis));
    dis[index] = 0;
    mark[index] = 1;
    ArcNode* cur;
    cur = G.vertices[index].firstarc;//选取这个初始化
    while (cur != NULL)
    {
        int s = 0;
        dis[cur->adjvex] = 1;
        if (cur->nextarc != NULL)
        {
            cur = cur->nextarc;
            continue;
        }//初始化
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
                minl = dis[j];//同上面的思路，将所有点的情况都处理一边，但是这次考虑了具体是那两个点
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
            if (dis[k] + 1 < dis[cur1->adjvex])//使用最短路径算法进行处理
            {
                dis[cur1->adjvex] = dis[k] + 1;
            }
            cur1 = cur1->nextarc;
        }
    }
    if (dis[index2] != 0)
    {
        printf("到%d %s的距离为%d\n", G.vertices[index2].data.key, G.vertices[index2].data.others, dis[index2]);
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
    int tn = G.vexnum;//tn为连通分量总数
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
        f[i] = i;//并查集的初始化
    }
    i = 0;
    while (fscanf(fp, "%d %d", &v1, &v2) && v1 != -1)
    {

        int in1 = -1, in2 = -1;//记录这两条边所对应的节点的位置
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.vertices[i].data.key == v1)
                in1 = i;
            if (G.vertices[i].data.key == v2)
                in2 = i;
        }
        if (in1 == -1 || in2 == -1)
            return -1;
        if (find(in1) != find(in2))//如果属于同一个并查集，那么就要连通分量不变
            //反之，则要发生变化
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
    
    printf("连通分量的个数为：%d\n", tn);
    *mygra = G;
    return 1;
}