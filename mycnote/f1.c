#include<stdio.h>

int main(int argc,char *argv[]) {

	FILE* fp;
	fp = fopen("tet.txt", "w");
	fprintf(fp, "atai  \t %d \n", 10);
	fclose(fp);

	

	return 0;

}