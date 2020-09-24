#include "base.h"



typedef int ElementType;

void ShellSort(ElementType A[], int N,int* count)
{ /* ϣ������ - ��Sedgewick�������� */
	int Si, D, P, i;
	ElementType Tmp;
	/* ����ֻ�г�һС�������� */
	int Sedgewick[] = { 929, 505, 209, 109, 41, 19, 5, 1 };

	(*count)=0;

	for (Si = 0; Sedgewick[Si] >= N; Si++)
		; /* ��ʼ������Sedgewick[Si]���ܳ����������г��� */

	for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si],(*count)++)
		for (P = D; P < N; P++) { /* ��������*/
			Tmp = A[P];
			for (i = P; i >= D && A[i - D] > Tmp; i -= D)
				A[i] = A[i - D];
			A[i] = Tmp;
		}
}

int* Create_randnum(int count, int min, int max)
{//�������һ������Ϊcount����Χ��min��max֮�������
	int* nums = (int*)malloc(sizeof(int) * count);
	int i;
	for (i = 0; i < count; i++)
		nums[i] = rand(time(0)) % (max - min) + min;
	return nums;
}

void Print_nums(int* nums, int count)
{//�������ǰcount������ӡ�����ͷ�����
	int i;
	for (i = 0; i < count; i++) {
		printf("%-5d", nums[i]);
		if (i % 10 == 9)printf("\n");
		else printf(",");
	}
	free(nums);
}

/* �������� */
void Swap(ElementType* a, ElementType* b)
{
	ElementType temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);
	/* ��ʱA[Left] <= A[Center] <= A[Right] */
	Swap(&A[Center], &A[Right - 1]); /* ����׼Pivot�ص��ұ�*/
	/* ֻ��Ҫ����A[Left+1] �� A[Right-2] */
	return  A[Right - 1];  /* ���ػ�׼Pivot */
}

void InsertionSort(ElementType A[], int count)
{
	int  i, j;
	for (i = 0; i < count; i++)
		for (j = 0; j < count-1; j++)
			if (A[j] > A[j + 1]) {
				Swap(A + j, A + (j + 1));
			}
}

void Qsort(ElementType A[], int Left, int Right,int* count)
{ /* ���ĵݹ麯�� */
	int Pivot, Cutoff=5, Low, High;
	(*count)++;

	if (Cutoff <= Right - Left) { /* �������Ԫ�س�ֶ࣬������� */
		Pivot = Median3(A, Left, Right); /* ѡ��׼ */
		Low = Left; High = Right - 1;
		while (1) { /*�������бȻ�׼С���Ƶ���׼��ߣ�����Ƶ��ұ�*/
			while (A[++Low] < Pivot);
			while (A[--High] > Pivot);
			if (Low < High) Swap(&A[Low], &A[High]);
			else break;
		}
		Swap(&A[Low], &A[Right - 1]);   /* ����׼������ȷ��λ�� */
		Qsort(A, Left, Low - 1,count);    /* �ݹ������ */
		Qsort(A, Low + 1, Right,count);   /* �ݹ����ұ� */
	}
	else InsertionSort(A + Left, Right - Left + 1); /* Ԫ��̫�٣��ü����� */
}

void QuickSort(ElementType A[], int N,int* count)
{ /* ͳһ�ӿ� */
	(*count)=0;
	Qsort(A, 0, N - 1,count);
}

//������
void PercDown(ElementType A[], int p, int N)
{ /* �ı����4.24��PercDown( MaxHeap H, int p )    */
	/* ��N��Ԫ�ص���������A[p]Ϊ�����Ӷѵ���Ϊ���� */
	int Parent, Child;
	ElementType X;

	X = A[p]; /* ȡ��������ŵ�ֵ */
	for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
		Child = Parent * 2 + 1;
		if ((Child != N - 1) && (A[Child] < A[Child + 1]))
			Child++;  /* Childָ�������ӽ��Ľϴ��� */
		if (X >= A[Child]) break; /* �ҵ��˺���λ�� */
		else  /* ����X */
			A[Parent] = A[Child];
	}
	A[Parent] = X;
}

void HeapSort(ElementType A[], int N,int* count)
{ /* ������ */
	int i;
	*(count)=0;
	for (i = N / 2 - 1; i >= 0; i--)/* �������� */
		PercDown(A, i, N);

	for (i = N - 1; i > 0; i--,(*count)++) {
		/* ɾ�����Ѷ� */
		Swap(&A[0], &A[i]); 
		PercDown(A, 0, i);
	}
}






int main()
{
	int* nums;
	int count=0;

	printf("ϣ������\n");
	nums = Create_randnum(100, 200, 1000);

	ShellSort(nums, 100,&count);
	printf("ִ��ϣ������Ĵ���Ϊ��%d\n",count);
	Print_nums(nums, 100);
	printf("\n");

	printf("��������\n");
	nums = Create_randnum(200, 200, 10000);

	QuickSort(nums, 200,&count);
	printf("ִ�п�������Ĵ���Ϊ��%d\n",count);
	Print_nums(nums, 200);
	printf("\n");

	printf("������\n");
	nums = Create_randnum(500, 200, 100000);

	HeapSort(nums, 500,&count);
	printf("ִ�ж�����Ĵ���Ϊ��%d\n",count);
	Print_nums(nums, 500);


}