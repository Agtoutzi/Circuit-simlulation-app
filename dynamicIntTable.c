#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"

int TableID(char *  string){

int *plot_nodes;                           // einai o pinakas pou apothikeuontai ta ids


int fid;                                          //einai to id pou exei ginei integer otan to exw parei se string apo hashtable
char *gt_id;                                   // einai to string pou epistrefei o hash table
int i=0,counterT=0;                         // i gia ton pinaka  counter T o counter pou epistrefei i sunartisi

	plot_nodes= (int *)malloc(sizeof(int)) ;
		
	gt_id=ht_get(hashtable, string);
	fid=atoi (gt_id);

	plot_nodes[i]=fid;
	i++;
	counterT++;

return counterT;

}