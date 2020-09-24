#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

struct student
{
	int score;
	struct student *next;//ָ����
};
typedef struct student * Linklist;
//�������������
void Creatlist(Linklist head)
{
	int count = 1,i=0;//count��������,i��������
	int score,temp=-1;
	Linklist q;
	Linklist p;
	q = head;//��ָ����г�ʼ��
	printf("�������%d��ͬѧ�ĳɼ�:",count);
	scanf("%d",&score);
	temp=score;
	while(score!=-1){
		if(score!=-1&&score>=temp){
			p=(struct student*)malloc(sizeof(struct student));
			if(!p){printf("�����ڴ�ʧ��");exit(1);}
			p->score = score;
			q->next = p;
			q=p;	//����
			count++;
			temp=score;
		}
		else if(score<temp)printf("�����������������\n");
		printf("�������%d��ͬѧ�ĳɼ�:",count);
		scanf("%d",&score);
	}
	q->next =NULL;//��β
}
//�ϲ��������������
Linklist combine_list(struct student *head1,struct student *head2)
{
	Linklist p1,p2,head3,p=NULL,q=NULL;

	p1=head1->next;
	p2=head2->next;
	head3=(Linklist)malloc(sizeof(struct student));
	if(!head3){printf("�����ڴ�ʧ��");exit(1);}
	q=head3;

	//��С�������뵽�ϲ���������
	while(p1&&p2){
		p=(Linklist)malloc(sizeof(struct student));
		if(!p){printf("�����ڴ�ʧ��");exit(1);}
		if(p1->score<p2->score){
			p->score=p1->score;
			q->next=p;
			q=q->next;
			p1=p1->next;
		}
		else
		{
			p->score=p2->score;
			q->next=p;
			q=q->next;
			p2=p2->next;
		}
	}
	//������һ��������βʱ����һ����������ݽӵ���β
	if(p1==NULL)p->next=p2;
	else p->next=p1;
	return head3;
}
//�������
void pri_list(struct student *head)
{
	int i=1;
	struct student *p=head->next;
	while(p){
		printf("��%d���˵ĳɼ�Ϊ%d\n",i++,p->score);
		p = p->next;
	}
}

void freelist(Linklist head)
{
	Linklist q=head,p=head->next;
	while(q->next){
		free(q);
		q=p;
		if(p->next)
			p->next;
	}
	free(q);
}

void main()
{
	Linklist list1,list2,list3,p;
	list1 = (struct student *)malloc(sizeof(struct student));
	if(!list1){printf("�����ڴ�ʧ��");exit(1);}
	list2 = (struct student *)malloc(sizeof(struct student));
	if(!list2){printf("�����ڴ�ʧ��");exit(1);}
	printf("������һ������\n");
	Creatlist(list1);
	printf("�����ڶ�������\n");
	Creatlist(list2);
	list3=combine_list(list1,list2);
	pri_list(list3);
	freelist(list1);
	freelist(list2);
	freelist(list3);
}