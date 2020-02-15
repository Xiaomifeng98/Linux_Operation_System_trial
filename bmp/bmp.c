#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	long width,height;

	fp=fopen("1.bmp","rb");
	if(fp==NULL)
	{
		printf("Open bmp failed!\n");
		return 1;
	}
	
	fseek(fp,18L,SEEK_SET);
	fread(&width,sizeof(char),4,fp);
	fseek(fp,22L,SEEK_SET);
	fread(&height,sizeof(char),4,fp);
	printf("BMP 宽为 %ld\n",width);
	printf("BMP 高为 %ld\n",height);

	fclose(fp);
	return 0;
}

