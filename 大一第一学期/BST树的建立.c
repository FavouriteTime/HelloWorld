#include "base.h"

//��ʽ�洢��
typedef int ElementType;
typedef int Status;

typedef struct TNode* Position;
typedef Position BinTree; /* ���������� */

struct TNode { /* ����㶨�� */
	ElementType Data; /* ������� */
	BinTree Left;     /* ָ�������� */
	BinTree Right;    /* ָ�������� */
};

//����������������Сֵ
BinTree Findmin(BinTree BST)
{
	if (!BST) return NULL;//�յĶ���������
	else if (!BST->Left)
		return BST;
	else
		return Findmin(BST->Left);
}

//�����������������ֵ
BinTree Findmax(BinTree BST)
{
	if (!BST) return NULL;//�յĶ���������
	else if (!BST->Right)
		return BST;
	else
		return Findmin(BST->Right);
}

//�����������Ĳ���
BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST) {//��ԭ��Ϊ�գ����ɲ�����һ���ڵ�Ķ���������
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = BST->Right = NULL;
	}
	else {//��������Ԫ�ص�λ��
		if (X < BST->Data)
			BST->Left = Insert(BST->Left, X);//�ݹ����������
		else if (X > BST->Data)
			BST->Right = Insert(BST->Right, X);//�ݹ����������
		else;
	}
	return BST;
}

//������������ɾ�� 
BinTree Delete(BinTree BST, ElementType X, int* count)
{
	Position Tmp;
	if (!BST)printf("δ�ҵ�Ҫɾ����Ԫ��");
	else {
		(*count)++;
		if (X < BST->Data)
			BST->Left = Delete(BST->Left, X, count);//���������ݹ�ɾ��
		else if (X > BST->Data)
			BST->Right = Delete(BST->Right, X, count);//���������ݹ�ɾ��
		else {//BST����Ҫɾ���Ľڵ�
			if (BST->Left && BST->Right) {//�����ɾ���Ľڵ������������ӽڵ�
				//��������������С��Ԫ�����ɾ�����
				Tmp = Findmin(BST->Right);
				BST->Data = Tmp->Data;
				BST->Right = Delete(BST->Right, BST->Data,count);
			}
			else {//��ɾ�������һ�������ӽ��
				Tmp = BST;
				if (!BST->Left)
					BST = BST->Right;
				else
					BST = BST->Left;
				free(Tmp);
			}

		}

	}
	return BST;
}

//�������������
void InOrderTraversal(BinTree BT)
{
	if (BT) {
		InOrderTraversal(BT->Left);
		printf("%d,", BT->Data);
		InOrderTraversal(BT->Right);
	}

}

int Tree_seek(BinTree BT, ElementType X, Position* Node)
{
	if (!BT) {
		*Node = NULL;
		return 0;
	}
	if (BT->Data == X) {
		*Node = BT;
		return 1;
	}
	else {
		if (X < BT->Data)
			return Tree_seek(BT->Left, X, Node) + 1;
		else
			return Tree_seek(BT->Right, X, Node) + 1;
	}
}


int main()
{
	int nums[50] = { 241,267,934,300,969,724,478,758,762,664,
		305,345,281,227,561,691,795,942,227,836,
		591,404,902,353,492,582,821,516,718,895,
		847,326,571,538,469,912,267,899,435,494,
		903,811,322,933,273,864,941,711,453,668 };
	int num, i,count;
	BinTree BST = NULL;
	Position Node;

	printf("BST���������������£�\n");
	for (i = 0; i < 50; i++) {
		BST = Insert(BST, nums[i]);
	}
	InOrderTraversal(BST);

	printf("\n��������ҵ����֣�\n");
	scanf("%d", &num);
	count = Tree_seek(BST, num, &Node);
	if (Node) {
		printf("���ҳɹ������Ҵ���Ϊ��%d\n", count);
	}
	else printf("����ʧ��");

	printf("������ɾ�������֣�\n");
	scanf("%d", &num);
	count = 0;
	BST = Delete(BST, num, &count);
	if(!BST)printf("���ҳɹ������Ҵ���Ϊ��%d", count);
	printf("BST��ɾ������������������£�\n");
	InOrderTraversal(BST);
}