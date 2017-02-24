#include <stdio.h>


void convertType(char* value)
{
   int i = 0;
   char ch;
   double ret = 0;
   
   while((ch = value[i] )!= '\n')
   {
      ret = ret*10 +(ch - '0');
      ++i;
   }
   printf("%f",ret);//or %f..what is the control string for double?
}



int main(int argc, char *argv[]){

	FILE *f;
	char c[100];
	char *d;
	double e1;
	
	f = fopen(argv[1],"r");
	// printf("debugg1\n");
	// fgetc(f);
	// printf("debugg2\n");
	fscanf(f,"%e",e1);
	// printf("debugg3\n");
	// d=c;
	printf("%e",e1);
//	convertType(d);
	fclose(f);


}