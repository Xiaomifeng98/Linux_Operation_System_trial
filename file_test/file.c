#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	FILE *fp1,*fp2;
	char *username;
	char *newPassword;
	username = "温庆峰";
	newPassword = "522";
	fp1 = fopen("user.txt","r");
	if(fp1 == NULL){
		perror("Fail to open file");
		return 0;
	}
	fp2 = fopen("user2.txt","w+");
	if(fp2 ==  NULL){
		perror("Fail to open file");
		return 0;
	}

	while(1){
		char _username[100];
		char _password[100];
		char _telphone[100];
		char _useremail[100];
		int ret = fscanf(fp1, "%[^:]:%[^:]:%[^:]:%s\n", _username, _password, _telphone, _useremail);
		if(ret == EOF){
			break;
		}


		printf("-----------------\n");
		printf("%s\n", username);
		printf("%s\n", _username);
		printf("|||||||||||||||||\n");

		if(strcmp(username, _username) == 0){
			fprintf(fp2, "%s:%s:%s:%s\n", _username, newPassword, _useremail, _telphone);
			continue;
		}
		fprintf(fp2, "%s:%s:%s:%s\n", _username, _password, _useremail, _telphone);
	}

	fclose(fp1);
	fclose(fp2);
	system("rm user.txt");
	system("mv user2.txt user.txt");
//	free(username);
//	free(newPassword);

	return 0;
}
