#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct PolyNode {
	double coef;	//ϵ��
	int expon;	//ָ��
	struct PolyNode *link;	//ָ����һ���ڵ��ָ��
};
typedef struct PolyNode* Polynomial;
Polynomial P1,P2;

//�����ڱ���������Ҫ�ı䵱ǰ������ʽβ��ָ���ֵ
//���Ժ������ݽ������ǽڵ�ָ��ĵ�ַ��*pRearָ��β��
void Attach(double c,int e,Polynomial *pRear)
{	
	Polynomial p;

	p=(Polynomial)malloc(sizeof(struct PolyNode));
	p->coef =c;
	p->expon = e;
	p->link=NULL;
	//��pָ����½ڵ���뵽��ǰ������ʽ��β��ĺ���
	(*pRear)->link = p;
	(*pRear)=p;//����
}

//�����ָ��������뵽���ʵ�λ��
void InsertPoly(Polynomial head,Polynomial node)
{
	Polynomial q,p;
	q=head;
	p=head->link;
	while (p)
	{
		if(node->expon<=p->expon)break;
		p=p->link;
		q=q->link;
	}
	//�������ҵ�����λ��
	node->link=q->link;
	q->link=node;
}

//����ʽ����ָ������
void OrderPoly(Polynomial head)
{
	Polynomial q,p;
	q=head->link;
	p=q;
	head->link=NULL;
	while ((p))
	{
		p=p->link;q->link=NULL;//��ȡ�ڵ�
		InsertPoly(head,q);
		q=p;
	}
}

//��������ʽ��������
Polynomial ReadPoly()
{
	int N,e;
	double c;
	Polynomial Rear,P,t;
	P = (Polynomial)malloc(sizeof(struct PolyNode));//����սڵ�
	P ->link = NULL;
	Rear = P;
	printf("���������ʽ������");
	scanf("%d",&N);
	if(N<=0)return NULL;
	while(N--){
		printf("������ϵ����ָ��:");
		scanf("%lf %d",&c,&e);
		Attach(c,e, &Rear);
	}
	OrderPoly(P);
	t = P;P = P->link;free(t);//ɾ����ʱͷ���
	return P;
}

//�Ƚ�ָ����С
int Compare(int a,int b)
{
	if(a<b)return 1;
	if(b<a)return -1;
	return 0;
}

//����ʽ�ӷ�
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

//����ʽ����
Polynomial PolySub (Polynomial p1,Polynomial p2)
{
	Polynomial front,rear,temp;
	int sub;
	rear=(Polynomial)malloc(sizeof(struct PolyNode));
	front = rear;//��front��¼�������ʽ����ͷ���
	while(p1&&p2)
		switch(Compare(p1->expon,p2->expon)){
		case 1:
			Attach(p1->coef,p1->expon,&rear);
			p1=p1->link;
			break;
		case -1:
			Attach(-p2->coef,p2->expon,&rear);
			p2=p2->link;
			break;
		case 0:
			sub =p1->coef-p2->coef;
			if(sub)Attach(sub,p1->expon,&rear);
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

//�������ʽ
void PrintPoly(Polynomial p)
{
	if(!p){
		printf("0 0\n");
		return;
	}

	while(p){
		printf("%.2lf %d ",p->coef,p->expon);
		p = p ->link;
	}
	printf("\n");
}

void main()
{
	int sel;
	Polynomial p1,p2,ps;
	p1=ReadPoly();
	p2=ReadPoly();
	while(1){
		printf("��ѡ����е�����:0-�ӷ�,1-����\n");
		scanf("%d",&sel);
		if(sel==1){
			ps=PolySub(p1,p2);
			break;
		}
		if(sel==0) {
			ps=PolyAdd(p1,p2);
			break;
		}
	}
	PrintPoly(ps);
}