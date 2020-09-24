#include "base.h"


#define MaxVertexNum 100	/* ��󶥵�����Ϊ100 */
#define INFINITY 65535		/* ����Ϊ˫�ֽ��޷������������ֵ65535*/
typedef int Vertex;			/* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;		/* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;      /* ����洢������������Ϊ�ַ��� */
typedef	 int ElementType;

Vertex Visited[MaxVertexNum] = { FALSE };//��Ƕ����Ƿ���ʹ�������

typedef struct Node* PtrToNode;
struct Node { /* �����еĽ�� */
	ElementType Data;
	PtrToNode Next;
};
typedef PtrToNode Position;

struct QNode {
	Position Front, Rear;  /* ���е�ͷ��βָ�� */
};
typedef struct QNode* Queue;

Queue CreatQueue()
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}

Status IsEmpty(Queue Q)
{
	return (Q->Front == NULL);
}

ElementType DeleteQ(Queue Q)
{
	Position FrontCell;
	ElementType FrontElem;

	if (IsEmpty(Q)) {
		printf("���п�");
		return ERROR;
	}
	else {
		FrontCell = Q->Front;
		if (Q->Front == Q->Rear) /* ������ֻ��һ��Ԫ�� */
			Q->Front = Q->Rear = NULL; /* ɾ���������Ϊ�� */
		else
			Q->Front = Q->Front->Next;
		FrontElem = FrontCell->Data;

		free(FrontCell);  /* �ͷű�ɾ�����ռ�  */
		return  FrontElem;
	}
}

Status AddQ(Queue Q, ElementType X)
{
	Position RearCell;
	RearCell = (Position)malloc(sizeof(struct QNode));
	RearCell->Data = X;
	if (!Q->Front && !Q->Rear)//û��Ԫ��
		Q->Front = Q->Rear = RearCell;
	else {
		Q->Rear->Next = RearCell;
		Q->Rear = Q->Rear->Next;
	}

	return 1;
}

/* �ߵĶ��� */
typedef struct ENode* PtrToENode;
struct ENode {
	Vertex V1, V2;      /* �����<V1, V2> */
	WeightType Weight;  /* Ȩ�� */
};
typedef PtrToENode Edge;

/* �ڽӾ���ͼ���Ķ��� */
typedef struct GNode1* PtrToGNode;
struct GNode1 {
	int Nv;     /* ������ */
	int Ne;     /* ����  */
	WeightType G[MaxVertexNum][MaxVertexNum];/* �ڽӾ��� */
	DataType Data[MaxVertexNum];    /* �涥������� */
	/* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
};
typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */

MGraph CreateGraph(int VertexNum)
{/* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode1));/*����ͼ*/
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӾ��� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}

void Visit(Vertex V)
{
	printf("���ڷ��ʶ���%d\n", V);
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* ����� <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* ��������ͼ����Ҫ�����<V2, V1> */
	Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int Nv, i;

	scanf("%d", &Nv);/* ���붥����� */
	Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	scanf("%d", &(Graph->Ne));   /* ������� */
	if (Graph->Ne != 0) {/*����б�*/
		E = (Edge)malloc(sizeof(struct ENode));/*�����߽ڵ�*/
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i < Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge(Graph, E);
		}
	}

	return Graph;
}

Status IsEdge(MGraph Graph, Vertex V, Vertex W)
{
	return Graph->G[V][W] < INFINITY ? TRUE : FALSE;
}

void DFS(MGraph Graph, Vertex V)
{/* ��VΪ��������ڽӱ�洢��ͼGraph����DFS���� */
	Vertex W;


	Visit(V);
	Visited[V] = TRUE;

	for (W = 0; W < Graph->Nv; W++) {
		if (!Visited[W] && IsEdge(Graph, V, W)) {
			DFS(Graph, W);
		}
	}
}

void DFS_1(MGraph Graph, Vertex V)
{
	DFS(Graph, V);
	memset(Visited, 0, MaxVertexNum);
}

void BFS(MGraph Graph, Vertex V)
{ /* ��SΪ��������ڽӾ���洢��ͼGraph����BFS���� */
	Queue Q;
	Vertex  temp, W;

	Q = CreatQueue();/* �����ն���, MaxSizeΪ�ⲿ����ĳ��� */
	/* ���ʶ���S���˴��ɸ��ݾ��������Ҫ��д */

	Visit(V);
	Visited[V] = TRUE; /* ���S�ѷ��� */
	AddQ(Q, V);/* V����� */

	while (!IsEmpty(Q)) {
		temp = DeleteQ(Q);/* ����temp */

		for (W = 0; W < Graph->Nv; W++) {/* ��ͼ�е�ÿ������W */
			/* ��W��V���ڽӵ㲢��δ���ʹ� */
			if (!Visited[W] && IsEdge(Graph, temp, W)) {
				Visit(W);
				Visited[W] = TRUE;/* ���W�ѷ��� */
				AddQ(Q, W);/* W����� */
			}
		}
	}
	memset(Visited, 0, MaxVertexNum);
}

Vertex FindMinDist(MGraph Graph, WeightType dist[])
{ /* ����δ����¼������dist��С�� */
	Vertex MinV, V;
	WeightType MinDist = INFINITY;

	for (V = 0; V < Graph->Nv; V++) {
		if (dist[V] != 0 && dist[V] < MinDist) {
			/* ��Vδ����¼����dist[V]��С */
			MinDist = dist[V]; /* ������С���� */
			MinV = V; /* ���¶�Ӧ���� */
		}
	}
	if (MinDist < INFINITY) /* ���ҵ���Сdist */
		return MinV; /* ���ض�Ӧ�Ķ����±� */
	else return ERROR;  /* �������Ķ��㲻���ڣ�����-1��Ϊ��� */
}






/* �ڽӵ�Ķ��� */
typedef struct AdjVNode* PtrToAdjVNode;
struct AdjVNode {
	Vertex AdjV;        /* �ڽӵ��±� */
	WeightType Weight;  /* ��Ȩ�� */
	PtrToAdjVNode Next;    /* ָ����һ���ڽӵ��ָ�� */
};

/* �����ͷ���Ķ��� */
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;/* �߱�ͷָ�� */
	DataType Data;            /* �涥������� */
} AdjList[MaxVertexNum];    /* AdjList���ڽӱ����� */

/* ͼ���Ķ��� */
typedef struct GNode2* PtrToGNode2;
struct GNode2 {
	int Nv;     /* ������ */
	int Ne;     /* ����   */
	AdjList G;  /* �ڽӱ� */
};
typedef PtrToGNode2 LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */

LGraph CreateGraph2(int VertexNum)
{/* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(struct GNode1));/* ����ͼ */
	Graph->Nv = VertexNum;
	/* ��ʼ���ڽӱ�ͷָ�� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;

	return Graph;
}

void InsertEdge2(LGraph Graph, Edge E)
{/*���߲���ͼ��*/
	PtrToAdjVNode NewNode;
	/* ����� <V1, V2> */
	/* ΪV2�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V2;
	NewNode->Weight = E->Weight;
	/* ��V2����V1�ı�ͷ(ͷ�巨) */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;

	/* ��������ͼ����Ҫ����� <V2, V1> */
	/* ΪV1�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->AdjV = E->V1;
	NewNode->Weight = E->Weight;
	/* ��V1����V2�ı�ͷ */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph2()
{
	LGraph Graph;
	Edge E;
	int Nv, i;

	scanf("%d", &(Nv));   /* ���붥����� */
	Graph = CreateGraph2(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */

	scanf("%d", &(Graph->Ne));   /* ������� */
	if (Graph->Ne != 0) { /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i < Graph->Ne; i++) {
			scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdge2(Graph, E);
		}
	}

	return Graph;
}

/* �ڽӱ�洢��ͼ - DFS */
void Visit2(Vertex V)
{
	printf("���ڷ��ʶ���%d\n", V);
}

/* Visited[]Ϊȫ�ֱ������Ѿ���ʼ��ΪFALSE */
void DFS2(LGraph Graph, Vertex V)
{/* ��VΪ��������ڽӱ�洢��ͼGraph����DFS���� */
	PtrToAdjVNode W;


	Visit2(V);/* ���ʵ�V������ */
	Visited[V] = TRUE; /* ���V�ѷ��� */

	for (W = Graph->G[V].FirstEdge; W; W = W->Next)/* ��V��ÿ���ڽӵ�W->AdjV */
		if (!Visited[W->AdjV]) {/* ��W->AdjVδ������ */
			DFS2(Graph, W->AdjV);/* ��ݹ����֮ */
		}
}

void DFS_2(LGraph Graph, Vertex V)
{
	DFS2(Graph, V);
	memset(Visited, 0, MaxVertexNum);
}

void BFS2(LGraph Graph, Vertex V)
{
	PtrToAdjVNode W;
	Vertex temp;
	Vertex visited[MaxVertexNum] = { FALSE };
	Queue Q;

	Q = CreatQueue();

	Visit2(V);
	visited[V] = TRUE;
	AddQ(Q, V);//���ýڵ����
	while (!IsEmpty(Q)) {//�����в�Ϊ��
		temp = DeleteQ(Q);//����
		for (W = Graph->G[temp].FirstEdge; W; W = W->Next)/* �Գ��ӵĶ����ÿ���ڽӵ�W->AdjV */
			if (!visited[W->AdjV]) {
				Visit2(W->AdjV);
				visited[W->AdjV] = TRUE;
				AddQ(Q, W->AdjV);
			}
	}
	memset(Visited, 0, MaxVertexNum);
}



int Prim(MGraph Graph, LGraph* MST)
{ /* ����С����������Ϊ�ڽӱ�洢��ͼMST��������СȨ�غ� */
	WeightType dist[MaxVertexNum], TotalWeight;
	Vertex parent[MaxVertexNum], V, W;
	int VCount;
	Edge E;

	/* ��ʼ����Ĭ�ϳ�ʼ���±���0 */
	for (V = 0; V < Graph->Nv; V++) {
		/* ���������V��Wû��ֱ�ӵıߣ���Graph->G[V][W]����ΪINFINITY */
		dist[V] = Graph->G[0][V];
		parent[V] = 0; /* ���Ҷ������ж���ĸ���㶼�ǳ�ʼ��0 */
	}
	/* �����������ж��㵫û�бߵ�ͼ��ע�����ڽӱ�汾 */
	*MST = CreateGraph2(Graph->Nv);
	TotalWeight = 0; /* ��ʼ��Ȩ�غ�     */
	VCount = 0;;/* ��ʼ����¼�Ķ����� */
	(*MST)->Ne = 0;/* ��ʼ����¼�ı��� */
	E = (Edge)malloc(sizeof(struct ENode)); /* �����յı߽�� */

	/* ����ʼ��0��¼��MST */
	dist[0] = 0;
	VCount++;
	parent[0] = -1; /* ��ǰ������0 */

	while (1) {
		V = FindMinDist(Graph, dist);
		/* V = δ����¼������dist��С�� */
		if (V == ERROR) /* ��������V������ */
			break;   /* �㷨���� */

		/* ��V����Ӧ�ı�<parent[V], V>��¼��MST */
		E->V1 = parent[V];
		E->V2 = V;
		E->Weight = dist[V];
		InsertEdge2(*MST, E);
		TotalWeight += dist[V];
		dist[V] = 0;
		(*MST)->Ne++;
		VCount++;

		for (W = 0; W < Graph->Nv; W++) /* ��ͼ�е�ÿ������W */
			if (dist[W] != 0 && Graph->G[V][W] < INFINITY) {
				/* ��W��V���ڽӵ㲢��δ����¼ */
				if (Graph->G[V][W] < dist[W]) {
					/* ����¼Vʹ��dist[W]��С */
					dist[W] = Graph->G[V][W]; /* ����dist[W] */
					parent[W] = V; /* ������ */
				}
			}
	} /* while����*/
	if (VCount < Graph->Nv) /* MST���յĶ��㲻��|V|�� */
		TotalWeight = ERROR;
	return TotalWeight;   /* �㷨ִ����ϣ�������СȨ�غͻ������ */
}




int main()
{
	MGraph Mgraph;
	LGraph Lgraph, Mintree;
	Vertex V1, V2;
	printf("������ͼ1��\n");
	Mgraph = BuildGraph();
	printf("������ͼ2��\n");
	Lgraph = BuildGraph2();

	//�ڽӾ���
	printf("�ڽӾ���ʵ�֣�\n");
	printf("���������ͼ1����㣺");
	scanf("%d", &V1);
	printf("DFS����������£�\n");
	DFS_1(Mgraph, V1);
	printf("\n");
	printf("BFS����������£�\n");
	BFS(Mgraph, V1);
	printf("\n");
	printf("��ͼ����С������BFS����������£�\n");
	Prim(Mgraph, &Mintree);
	DFS_2(Mintree, 0);
	printf("\n");

	//�ڽӱ�
	printf("�ڽӱ�ʵ�֣�\n");
	printf("���������ͼ2����㣺");
	scanf("%d", &V2);
	printf("DFS����������£�\n");
	DFS_2(Lgraph, V2);
	printf("\n");
	printf("BFS����������£�\n");
	BFS2(Lgraph, V2);

}