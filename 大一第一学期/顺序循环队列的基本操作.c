#include <stdio.h>
#include <malloc.h>

#define false 0;
#define true 1;

typedef int Position;
typedef char ElementType;
struct QNode {
    ElementType *Data;     /* �洢Ԫ�ص����� */
    Position Front, Rear;  /* ���е�ͷ��βָ�� */
    int MaxSize;           /* ����������� */
};
typedef struct QNode *Queue;

//����(��ʼ��)����Q
Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

//�ж϶���Q�Ƿ�Ϊ��
int IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}
//�ж϶���Q�Ƿ�Ϊ��
int IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}

//���
int AddQ( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) {
        printf("������");
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

//����
ElementType DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) { 
        printf("���п�");
        return ' ';
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}

//���������Ԫ�صĸ���
int countQ( Queue Q)
{
	return (Q->Rear+Q->MaxSize-Q->Front)%Q->MaxSize;
}

int main()
{
	int i;
	char a;
	Queue Q;
	Q=CreateQueue(20);
	printf("��������Ԫ�أ�������10�������\n");
	for(i=0;i<10;i++){
		scanf("%c",&a);
		if(!AddQ(Q,a))return 1;
	}
	getchar();//��ȡ�س�
	a=DeleteQ(Q);
	printf("%c\n",a);
	printf("%d\n",countQ(Q));
	for(i=0;i<4;i++){
		scanf("%c",&a);
		AddQ(Q,a);
	}
	while (!IsEmpty(Q))
	{
		a=DeleteQ(Q);
		printf("%c",a);
	}
	printf("\n");
	return 0;
}


