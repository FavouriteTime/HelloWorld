#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void main()
{
	double n;
	long double result,left,right,x;
	printf("��ţ�ٷ��ƽ���x3-4x+1=0�ĸ�\n");
	printf("�����뾫׼�ȣ�");
	scanf_s("%lf",&n);
	left=0;right=1;
	printf("f(0)=1\n");
	printf("f(1)=-1\n");
	result=1;
	while(fabs(result)>n)
	{
		x=(left+right)/2;
		result=pow(x,3)-4*x+1;
		if(result<0)right=x;
		else left=x;
		printf("f(%lf)=%lf\n",x,result);
	}
	system("pause");
}
