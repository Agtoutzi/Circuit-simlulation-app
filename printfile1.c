
void printfile1(FILE *k){
	char d; int i;
	printf("printfile1\n");
	for(i=0;i<8;i++){
		d=fgetc(k);
		putchar(d);
	}
	printf("\n");
}