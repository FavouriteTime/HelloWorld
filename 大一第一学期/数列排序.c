void series_rank(int *p,int n,int m)	//*pָ�����е�ָ�루���У���n��
{
	int i,j,temp;
	for(i=0;i<n;i++)
		for(j=0;j<m-1;j++)
			if(p[j]>p[j+1])
				temp=p[j],p[j]=p[j+1],p[j+1]=temp;
}
