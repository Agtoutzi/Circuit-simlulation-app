#include <stdio.h>

void printfile1(FILE *k){
	char d; int i;
	printf("printfile1\n");
	for(i=0;i<4;i++){
		d=fgetc(k);
		putchar(d);
	}
}
void printfile2(FILE *k){
	char d;
	printf("printfile2\n");
	while(!feof(k)){
		d=fgetc(k);
		putchar(d);
	}
}


int main(int argc, char *argv[]){
	FILE *f;
	char c;
	f = fopen(argv[1],"w");
	do {
		c = getchar();
		fputc(c,f);
	}while(c != '~'); 
	fflush(f); fclose(f);

	f = fopen(argv[1],"r");
	printfile1(f);
	printfile2(f);
	fclose(f);
}