#include "stdio.h"

struct kati{

char *name;
char *node1;
char *node2;
char *value;

};


int main(int argc, char *argv[]){

FILE *fp1;
char oneword[100];
char c;
struct kati *pointer;

pointer=(struct kati *)malloc(sizeof(struct kati));

   fp1 = fopen(argv[1],"r");

 //  do {
      c = fscanf(fp1,"%s",oneword); /* got one word from the file */
      printf("%s\n",oneword);       /* display it on the monitor  */
	  pointer->name=(char*)malloc(sizeof(char)*strlen(oneword));
	  strcpy(pointer->name , oneword);
	  c = fscanf(fp1,"%s",oneword); /* got one word from the file */
      printf("%s\n",oneword);       /* display it on the monitor  */
	  pointer->node1=(char*)malloc(sizeof(char)*strlen(oneword));
	  strcpy(pointer->node1 , oneword);
	  c = fscanf(fp1,"%s",oneword); /* got one word from the file */
      printf("%s\n",oneword);       /* display it on the monitor  */
	  pointer->node2=(char*)malloc(sizeof(char)*strlen(oneword));
	  strcpy(pointer->node2 , oneword);
	  c = fscanf(fp1,"%s",oneword); /* got one word from the file */
      printf("%s\n",oneword);       /* display it on the monitor  */
	  pointer->value=(char*)malloc(sizeof(char)*strlen(oneword));
	  strcpy(pointer->value , oneword);
 //  } while (c != EOF);              /* repeat until EOF           */

   fclose(fp1);
		printf("%s\n",pointer->name);
		printf("%s\n",pointer->node1);
		printf("%s\n",pointer->node2);
		printf("%s\n",pointer->value);
}