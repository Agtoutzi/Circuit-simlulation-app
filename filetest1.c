#include <stdio.h>
#include "printfile1.c"
#include <math.h>

double convertStringToDouble(char* string){

	int negative=1;
	int negativeExp=1;
	int i=0,j=0,exponent=0;
	char c;
	int d;
	double res = 0;
	
	if(string[i]=='-'){
		negative=-1;
		i++;
	}
	
	while((string[i] )!= '.'){
		res = res*10 +(string[i] - '0');
		i++;
	}
	i++;
	
	j=-1;
	while(string[i] != 'e'){
		d = string[i] - '0';
		res = res + (double)d*(pow(10,j));	
		j--;
		i++;
	}
	
	res=res*negative;
	
	printf("res = %f\n",res);
	i++;
	printf("character = %c\n",string[i]);
	
	if(string[i]=='-'){negativeExp=-1;i++;}
	if(string[i]=='+'){i++;}
	printf("character = %c\n",string[i]);
	
	while((string[i] )!= '\0'){
		exponent = exponent*10 +(string[i] - '0');
		i++;
		printf("current exponent = %d\n",exponent);
	}
	
	exponent=exponent*negativeExp;
	printf("total exponent = %d\n",exponent);
	res=res*(pow(10,exponent));
	
	return(res);
}


void printfile2(FILE *k){
	char d[100];
	double v;
	printf("printfile2\n");
	while(!feof(k)){
		//d=fgetc(k);
		//putchar(d);
		fscanf(k,"%s",d);
		printf("%s\n",d);
		v=convertStringToDouble(d);
		printf("%e\n",v);
		
		printf("\n");
		printf("\n");
		printf("\n");
	}
}


int main(int argc, char *argv[]){

	FILE *f;
	
	f = fopen(argv[1],"r");
//	printfile1(f);
	printfile2(f);
	fclose(f);

}