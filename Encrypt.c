#include<string.h>
#include <stdlib.h>
#include"ENC.h"

int main(int argc, char** argv)
{	
	unsigned char *r = (unsigned char*)malloc(16),f[20],Key[17];
	FILE *fp,*fq;
	long l,t,size;
	float per;
	if(argc < 2)
	{
		printf("Enter The Filename to encrypt in the following format :\n\n\n ./enc <filename>\n");
		return 0;
	}
	fp = fopen(argv[1],"rb+");
	printf("Enter a key :\n");
	scanf("%16[^\n]s",Key);
	sprintf(Key,"%16s",Key);
	
	fseek(fp,0,SEEK_END);
	l = ftell(fp);
	printf("size of file : %ld\n\n\n",l);

	fseek(fp,0,SEEK_SET);
	t=l>>4;
	while(t-->0)
	{
		fread(r,1,16,fp);
		fseek(fp,-16,SEEK_CUR);
		r = logDual(r,Key);
		fwrite(r,1,16,fp);
		if(t%100==0)
		{
			size = l-(t<<4);
			per = (100.0*size)/l;
			printf("Progress : %8.2f%%\r",per);
			fflush(stdout);
		}
	}
	if(l&15L != 0L)
	{
		memset(r,' ',16);
		t = fread(r,1,l&15L,fp);
		fseek(fp,-t,SEEK_CUR);
		r = logDual(r,Key);
		fwrite(r,1,16,fp);
	}
	printf("Progress : %8.2f%% Completed !!\n",100.0);
	fclose(fp);
}	
