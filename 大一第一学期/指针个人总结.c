#include<stdio.h>
void main()
{
	int array[4][5]={0};
	int i,j,k=0;
	for(i = 0;i < 4; i++)
	{
		for(j = 0;j < 5; j++){
			array[i][j]=k++;
		}

	}

	printf("*(array+1):%p\n",*(array+1));
	printf("array+1:%p\n",array+1);
	printf("array[1]::%p\n",array[1]);
	printf("&array[1][0]:%p\n",&array[1][0]);
	printf("array[1][0]:%p\n",array[1][0]);
	printf("array[1]+2:%p\n",array[1]+2);
	printf("&array[1]+2:%p\n",&array[1]+2);
	printf("*(array[1]+2):%p\n",*(array[1]+2));
	printf("array[1][2]:%p\n",array[1][2]);
	printf("ָ�����ָ�������к��е�ԭ��\n");
	printf("ȡֵ�����ȡһ��ָ��ʱ����ʾ��һ��ָ���λ��\n");
	printf("ȡֵ�����ȡһ��ָ��ʱ����ʾ��ȡ��ַ�ı�����ֵ\n");
	printf("��ָ��û��ѡ��һ����ַ�ĵز�(����������������)\n��ʾ������ָ������ĵ�һ���ĵ�ַ������ָ�����ĵ�ַ\n");
	printf("��ȡ����Ϊ�еĵ�һ����ַ������Ϊ�еĵ�һ����ַ\n");
}