#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100

int main()
{
	FILE *fp;
	char string[SIZE];
	char ch[SIZE];
	char test[SIZE];
	int count = 0;
	fp = fopen("test.txt","r+");
	
	while(fgets(string, SIZE, fp) != NULL)
	{
		count = strlen(string) - 1;		//计算这一行的长度
		
		/*输出最开始的这一行*/
		//printf("mmmmmmm%s", string);
		
		//printf("%d",count);
		
		/*将这一行与“haofana”连接起来*/
		string[count] = '\0';
		strcat(ch, string);
		strcat(ch,"Q\n");	
		
		//printf("%s", ch);
		//************************************这里之前将字符串拼接没问题
		
		/*将文件指针放到行首*/
		for(int i = 0; i <= count; i++)	
		{
			fseek(fp, -1L, 1);
		}
		
		/*输出把指针往前移动后，之后的字符串*/
		//fgets(test, SIZE, fp);
		//printf("%s", test);
		//************************************这里之前将文件指针向前移动没有问题
		
		/*将这一行重新写入，副加上了行尾的一些数据*/
		fputs(ch,fp);
		
		/*重新计算这一行的长度，使得让文件指针到行尾*/
		fgets(string, SIZE, fp);
		count = strlen(string) - 1;
		
		/**/
//		printf("%d",count);
		
		/*将文件指针方回到行尾*/
		for(int i = 0; i < count; i++)
		{
			fseek(fp, 1L, 1);
		}
		
		printf("%s", string);
		
		/*测试：输出这一行*/
//		printf("%s", ch);
		
		/*用于清除数据*/
		strcpy(ch, "");
	}
	count = 0;
	
	fclose(fp);
	return 0;
}

/*
int main()
{
	FILE *fp;
	char s;
	int count = -2;
	fp = fopen("test.txt", "r+");
	
	while(!feof(fp))
	{
		count++;
		s = fgetc(fp); 
		if(s == '\n')
		{
			fseek(fp, -2L, 1);
			fprintf(fp,"%d\n",count);
			//printf("这一行有%d个“*”",count);
			count = -2;
		}
		putchar(s);
	}
	fclose(fp);

	//printf("使用fgets()函数读取到的字符为：%c\n", s);	
	return 0;
}*/
