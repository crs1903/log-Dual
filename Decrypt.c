#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include"DEC.h"

int main(int argc, char** argv)
{	
	unsigned char *r = (unsigned char*)malloc(16),f[20],Key[17];
	FILE *fp,*fq;
	long l,t,size;
	float per;
	if(argc < 2)
	{
		printf("Enter The Filename to decrypt in the following format :\n\n\n ./enc <filename>\n");
		return 0;
	}
	fp = fopen(argv[1],"rb+");
	printf("Enter the key :\n");
	scanf("%16[^\n]s",Key);
	sprintf(Key,"%16s",Key);

	fseek(fp,0,SEEK_END);
	l = ftell(fp);
	printf("size of file : %ld\n\n",l);
	fseek(fp,0,SEEK_SET);
	t = l>>4;
	while(t-->0)
	{
		fread(r,1,16,fp);
		fseek(fp,-16,SEEK_CUR);
		r = logDual_DEC(r,Key);
		fwrite(r,1,16,fp);
		if(t%100==0)
		{
			size = l-(t<<4);
			per = (100.0*size)/l;
			printf("Progress : %8.2f%%\r",per);
			fflush(stdout);
		}
	}
	printf("Progress : %8.2f%% Completed !!\n",100.0);
	fclose(fp);
}
