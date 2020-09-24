#include "base.h"


typedef struct TNode *Position1;
typedef Position1 BinTree; /* ���������� */
typedef  char ElementType1;
struct TNode{ /* ����㶨�� */
    ElementType1 Data; /* ������� */
    BinTree Left;     /* ָ�������� */
    BinTree Right;    /* ָ�������� */
};

typedef	 BinTree ElementType2;
typedef struct SNode *PtrToSNode;
struct SNode {
    ElementType2 Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

typedef struct Node *PtrToNode;
struct Node { /* �����еĽ�� */
    ElementType2 Data;
    PtrToNode Next;
};
typedef PtrToNode Position2;
 
struct QNode {
    Position2 Front, Rear;  /* ���е�ͷ��βָ�� */

};
typedef struct QNode *Queue;

//��ջ
Stack CreateStack( ) 
{ /* ����һ����ջ��ͷ��㣬���ظý��ָ�� */
    Stack S;
 
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}
 
int IsEmpty ( Stack S )
{ /* �ж϶�ջS�Ƿ�Ϊ�գ����Ƿ���true�����򷵻�false */
    return ( S->Next == NULL );
}
 
int Push( Stack S, ElementType2 X )
{ /* ��Ԫ��Xѹ���ջS */
    PtrToSNode TmpCell;
 
    TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
    TmpCell->Data = X;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
    return TRUE;
}
 
ElementType2 Pop( Stack S )  
{ /* ɾ�������ض�ջS��ջ��Ԫ�� */
    PtrToSNode FirstCell;
    ElementType2 TopElem;
 
    if( IsEmpty(S) ) {
        printf("��ջ��"); 
        return ERROR;
    }
    else {
        FirstCell = S->Next; 
        TopElem = FirstCell->Data;
        S->Next = FirstCell->Next;
        free(FirstCell);
        return TopElem;
    }
}

//��
void CreateTree(BinTree *T)                          
{           
    char ch;
    scanf("%c",&ch);

    if(ch=='#')
    {
        *T=NULL;
    }
    else
    {
        (*T)=(BinTree)malloc(sizeof(struct TNode));
        if(!(*T))exit(0);
        (*T)->Data=ch;
        CreateTree(&((*T)->Left));
        CreateTree(&((*T)->Right));
    }
}

//����ǵݹ�����㷨
void PreorderTraversal(BinTree BT)
{
	BinTree T=BT;
	Stack S =CreateStack();
	while (T || !IsEmpty(S)){
		while (T){ //һֱ���󲢽���;�Ľڵ�ѹ���ջ
			Push(S,T);
			printf("%c ", T->Data);//���ʴ�ӡ�ڵ�
			T=T->Left;
		}
		if(!IsEmpty(S)){
			T = Pop(S);//�ڵ㵯����ջ
			T = T->Right;//ת���ҽڵ�
		}

	}
}

//����ǵݹ�����㷨
void InorderTraversal(BinTree BT)
{
	BinTree T=BT;
	Stack S =CreateStack();
	while (T || !IsEmpty(S)){
		while (T){ //һֱ���󲢽���;�Ľڵ�ѹ���ջ
			Push(S,T);
			T=T->Left;
		}
		if(!IsEmpty(S)){
			T = Pop(S);//�ڵ㵯����ջ
			printf("%c ", T->Data);//���ʴ�ӡ�ڵ�
			T = T->Right;//ת���ҽڵ�
		}

	}
}

//�������������
void PostOrderTraversal(BinTree BT)
{
	if(BT){
		PostOrderTraversal(BT->Left);
		PostOrderTraversal(BT->Right);
		printf("%c ",BT->Data);
	}

}

//�������
void LevelorderTraversal(BinTree BT)
{
	Status Isempty( Queue Q );
	Queue CreatQueue();
	ElementType2 DeleteQ( Queue Q );
	Status AddQ(Queue Q,ElementType2 X);

	Queue Q;
	BinTree T;
	if(!BT)return;

	Q = CreatQueue(); /* �����ն���Q */
	AddQ( Q, BT );
	while ( !Isempty(Q) ) {
		T = DeleteQ( Q );
		printf("%c ", T->Data); /* ����ȡ�����еĽ�� */
		if ( T->Left )   AddQ( Q, T->Left );
		if ( T->Right )  AddQ( Q, T->Right );
	}

}
//�������Ҷ�ڵ�
void LevelorderTraversalleaves(BinTree BT)
{
	Status Isempty( Queue Q );
	Queue CreatQueue();
	ElementType2 DeleteQ( Queue Q );
	Status AddQ(Queue Q,ElementType2 X);

	Queue Q;
	BinTree T;
	if(!BT)return;

	Q = CreatQueue(); /* �����ն���Q */
	AddQ( Q, BT );
	while ( !Isempty(Q) ) {
		T = DeleteQ( Q );
		if(!T->Left && !T->Right)
		printf("%c ", T->Data); /* ����ȡ�����еĽ�� */
		if ( T->Left )   AddQ( Q, T->Left );
		if ( T->Right )  AddQ( Q, T->Right );
	}

}

//���������Ҷ�ڵ�
void LevelorderTraversalNotleaves(BinTree BT)
{
	Status Isempty( Queue Q );
	Queue CreatQueue();
	ElementType2 DeleteQ( Queue Q );
	Status AddQ(Queue Q,ElementType2 X);

	Queue Q;
	BinTree T;
	if(!BT)return;

	Q = CreatQueue(); /* �����ն���Q */
	AddQ( Q, BT );
	while ( !Isempty(Q) ) {
		T = DeleteQ( Q );
		if(!(!T->Left && !T->Right))
		printf("%c ", T->Data); /* ����ȡ�����еĽ�� */
		if ( T->Left )   AddQ( Q, T->Left );
		if ( T->Right )  AddQ( Q, T->Right );
	}

}
int Max ( int a, int b )
{
    return a > b ? a : b;
}

//�����������
int DeepthTree(BinTree T)
{
	if(!T->Left && !T->Right)
		return 1;
	if(!T->Left && T->Right)
		return DeepthTree(T->Right)+1;
	if(!T->Right && T->Left)
		return DeepthTree(T->Left)+1;
	if (T->Left && T->Right)
		return Max(DeepthTree(T->Left),DeepthTree(T->Right))+1;
	return -1;
}


//����
Queue CreatQueue()
{
	Queue Q;
	Q=(Queue)malloc(sizeof(struct QNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}

Status Isempty( Queue Q )
{
    return ( Q->Front == NULL);
}

ElementType2 DeleteQ( Queue Q )
{
    Position2 FrontCell; 
    ElementType2 FrontElem;
     
    if  ( Isempty(Q) ) {
        printf("���п�");
        return NULL;
    }
    else {
        FrontCell = Q->Front;
        if ( Q->Front == Q->Rear ) /* ������ֻ��һ��Ԫ�� */
            Q->Front = Q->Rear = NULL; /* ɾ���������Ϊ�� */
        else                     
            Q->Front = Q->Front->Next;
        FrontElem = FrontCell->Data;
 
        free( FrontCell );  /* �ͷű�ɾ�����ռ�  */
        return  FrontElem;
    }
}

Status AddQ(Queue Q,ElementType2 X)
{
	Position2 RearCell;
	RearCell=(Position2)malloc(sizeof(struct QNode));
	RearCell->Data = X;
	if(!Q->Front && !Q->Rear)//û��Ԫ��
	Q->Front = Q->Rear = RearCell;
	else {
		Q->Rear->Next= RearCell;
		Q->Rear = Q->Rear->Next;
	}
	return TRUE;

     
    
}








int main()
{
	BinTree T;
	printf("�밴ǰ����������\n");
	CreateTree(&T);
	printf("��ǰ���������\n");
	PreorderTraversal(T);
	printf("\n");
	printf("�������������\n");
	InorderTraversal(T);
	printf("\n");
	printf("�������������\n");
	PostOrderTraversal(T);
	printf("\n");
	printf("����α�������\n");
	LevelorderTraversal(T);
	printf("\n");
	printf("���������Ϊ:");
	printf("%d",DeepthTree(T));
	printf("\n");
	printf("������Ҷ�ڵ�Ϊ:");
	LevelorderTraversalleaves(T);
	printf("\n");
	printf("�����ķ�Ҷ�ڵ�Ϊ:");
	LevelorderTraversalNotleaves(T);
	printf("\n");
	return 0;
}


