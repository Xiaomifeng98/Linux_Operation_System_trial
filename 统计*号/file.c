#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp;
	int num=0;
	int  i,j,n,ch;
	char buf[10000],aid[20];

	fp=fopen("test.txt","r");
	if(fp==NULL)
	{
		printf("open file error!\n");
		return 1;
	}
	
	i=0;
	while((ch=fgetc(fp))!=EOF)
	  buf[i++]=ch;
	buf[i]='\0';
	fclose(fp);

	fp=fopen("test.txt","w");
	n=0;
	for(i=0;i<strlen(buf);i++)
	{
		fputc(buf[i],fp);
		if(buf[i]=='*')
		{
			n++;
			if(buf[i+1]!='*')
			{
				sprintf(aid,"num=%d",n);
				for(j=0;j<strlen(aid);j++)
					fputc(aid[j],fp);
				n=0;
			}
		}
	}
	fclose(fp);
	return 0;

}

