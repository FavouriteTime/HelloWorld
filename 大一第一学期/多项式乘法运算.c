#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct PolyNode {
	int coef;	//ϵ��
	int expon;	//ָ��
	struct PolyNode *link;	//ָ����һ���ڵ��ָ��
};
typedef struct PolyNode* Polynomial;

int Compare(int a,int b)
{
	if(a>b)return 1;
	if(b>a)return -1;
	return 0;
}

void Attach(int c,int e,Polynomial *pRear)
{	//�����ڱ���������Ҫ�ı䵱ǰ������ʽβ��ָ���ֵ
	//���Ժ������ݽ������ǽڵ�ָ��ĵ�ַ��*pRearָ��β��
	Polynomial p;

	p=(Polynomial)malloc(sizeof(struct PolyNode));
	p->coef =c;
	p->expon = e;
	p->link=NULL;
	//��pָ����½ڵ���뵽��ǰ������ʽ��β��ĺ���
	(*pRear)->link = p;
	(*pRear)=p;//����
}
//����û�п�ͷ���Ķ���ʽ����
Polynomial ReadPoly()
{
	int N,c,e;
	Polynomial Rear,P,t;
	P = (Polynomial)malloc(sizeof(struct PolyNode));//����սڵ�
	P ->link = NULL;
	Rear = P;
	printf("���������ʽ������");
	scanf("%d",&N);
	if(N<=0)return;
	while(N--){
		printf("������ϵ����ָ��");
		scanf("%d %d",&c,&e);
		Attach(c,e, &Rear);
	}
	t = P;P = P->link;free(t);//ɾ����ʱͷ���
	return P;
}

Polynomial PolyAdd (Polynomial p1,Polynomial p2)
{
	Polynomial front,rear,temp;
	int sum;
	rear=(Polynomial)malloc(sizeof(struct PolyNode));
	front = rear;//��front��¼�������ʽ����ͷ���
	while(p1&&p2)
		switch(Compare(p1->expon,p2->expon)){
		case 1:
			Attach(p1->coef,p1->expon,&rear);
			p1=p1->link;
			break;
		case -1:
			Attach(p2->coef,p2->expon,&rear);
			p2=p2->link;
			break;
		case 0:
			sum =p1->coef+p2->coef;
			if(sum)Attach(sum,p1->expon,&rear);
			p1=p1->link;
			p2=p2->link;
			break;
	}
	//��δ���������һ������ʽ�����нڵ�һ�θ��Ƶ��������ʽ��ȥ
	for(;p1;p1=p1->link)Attach(p1->coef,p1->expon,&rear);
	for(;p2;p2=p1->link)Attach(p2->coef,p2->expon,&rear);
	rear->link=NULL;
	temp=front;
	front = front->link;
	free(temp);
	return front;
}

Polynomial PolyMul(Polynomial p1,Polynomial p2)
{
	Polynomial p,Rear,t1,t2,t;
	int c,e;
	t1=p1;t2=p2;
	if(!p1||p2)return NULL;
	p = (Polynomial)malloc(sizeof(struct PolyNode));p->link = NULL;
	Rear = p;
	while(t2){	//����p1�ĵ�һ���p2�ȵ�����p
		Attach(t1->coef*t2->coef,t1->expon+t2->expon,&Rear);
		t2=t2->link;
	}
	t1->link;
	while (t1)
	{
		t2=p2;Rear = p;
		while (t2)
		{
			c=t1->coef*t2->coef;
			e=t1->expon+t2->expon;
			while(Rear->link && Rear->link->expon>e)
				Rear=Rear->link;
			if(Rear->link&&Rear->link->expon==e)
				if(Rear->link->coef+c)
					Rear->link->coef+=c;
				else{
					t = Rear->link;
					Rear->link=t->link;
					free(t);
				}
			else{
				t=(Polynomial)malloc(sizeof(struct PolyNode));
				t->coef=c;t->expon=e;
				t->link = Rear->link;
				Rear->link =t;Rear=t;
			}

		}
		t1=t1->link;
	}
	t2 = p;p=p->link;free(t2);

	return p;
}

void PrintPoly(Polynomial p)
{//�������ʽ
	if(!p){
		printf("0 0\n");
		return;
	}

	while(p){
		printf("%d %d ",p->coef,p->expon);
		p = p ->link;
	}
	printf("\n");
}


void main()
{
	Polynomial p1,p2,pp,ps;
	p1=ReadPoly();
	p2=ReadPoly();
	pp = PolyMul(p1,p2);
	PrintPoly(pp);
	ps = PolyAdd(p1,p2);
	PrintPoly(ps);
}
