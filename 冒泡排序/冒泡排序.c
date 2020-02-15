#include<stdio.h>
#include<string.h>
int main(void)
{
	int n = 0,i,j;
	int t,s[100];
	printf("输入一串数组，以数字9999结束：\n");
	for(i = 0;i < 100;i++)
	{
		scanf("%d",&s[i]);
		if(s[i] == 9999)
			break;
		else
			n++;
	}
	for(i = 1;i <= n-1;i++)
	{
		for(j = 0;j< n-1;j++)
		{
			if(s[j] > s[j+1])
			{
				t = s[j];
				s[j] = s[j+1];
				s[j+1] = t;
			}
		}
	}
	printf("排序后的数组为：\n");
	for(i = 0;i <= n-1;i++)
	{
		printf("%d   ",s[i]);
	}
	printf("\n");
	return 0;
}
