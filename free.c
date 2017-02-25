#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"
#include "mna.h"
#include "options.h"
#include "mna-sparse.h"
#include "csparse.h"
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_linalg.h>

//analamvanei na eleutherwsei olo to xwro sti mnimi pou exei desmeusei to programma

void freeAllmem(){

  
	//eleutherwnoume tous pinakes mna
	gsl_permutation_free(p);
	gsl_vector_free(B);
	gsl_matrix_free(A);
	gsl_vector_free(x);
	gsl_matrix_free(C);

	//free csparse matrices 
	cs_spfree(C_sparse);
	cs_spfree(E_sparse);
	
	//free double arrays
	free(B_sparse);
	free(x_sparse);

	//eleutherwnoume tis listes twn stoixeiwn tou kyklwmatos
	VoltT *nodeV, *nodeVtobefreed;
	AmperT *nodeI, *nodeItobefreed;
	ResistanceT *nodeR, *nodeRtobefreed;
	CapacitorT *nodeC, *nodeCtobefreed;
	InductorT *nodeL, *nodeLtobefreed;
	DiodeT *nodeD, *nodeDtobefreed;
	MosT *nodeM, *nodeMtobefreed;
	BjtT *nodeB, *nodeBtobefreed;
	struct PWL *Pwl,*Pwltobefreed;

	nodeV=rootV;
	while(nodeV!=NULL){
		nodeVtobefreed=nodeV;
		nodeV=nodeV->next;
		if(nodeVtobefreed->exp!=NULL)free(nodeVtobefreed->exp);
		if(nodeVtobefreed->sin!=NULL)free(nodeVtobefreed->sin);
		if(nodeVtobefreed->pulse!=NULL)free(nodeVtobefreed->pulse);
		Pwl=nodeVtobefreed->pwl;
		while(Pwl!=NULL){
		  Pwltobefreed=Pwl;
		  Pwl=Pwl->next;
		  free(Pwltobefreed);
		}
		free(nodeVtobefreed->name);
		free(nodeVtobefreed->node1);
		free(nodeVtobefreed->node2);
		free(nodeVtobefreed);
	}

	nodeI=rootI;
	while(nodeI!=NULL){
		nodeItobefreed=nodeI;
		nodeI=nodeI->next;
		if(nodeItobefreed->exp!=NULL)free(nodeItobefreed->exp);
		if(nodeItobefreed->sin!=NULL)free(nodeItobefreed->sin);
		if(nodeItobefreed->pulse!=NULL)free(nodeItobefreed->pulse);
		Pwl=nodeItobefreed->pwl;
		while(Pwl!=NULL){
		  Pwltobefreed=Pwl;
		  Pwl=Pwl->next;
		  free(Pwltobefreed);
		}
		free(nodeItobefreed->name);
		free(nodeItobefreed->node1);
		free(nodeItobefreed->node2);
		free(nodeItobefreed);
	}

	nodeR=rootR;
	while(nodeR!=NULL){
		nodeRtobefreed=nodeR;
		nodeR=nodeR->next;
		free(nodeRtobefreed->name);
		free(nodeRtobefreed->node1);
		free(nodeRtobefreed->node2);
		free(nodeRtobefreed);
	}

	nodeC=rootC;
	while(nodeC!=NULL){
		nodeCtobefreed=nodeC;
		nodeC=nodeC->next;
		free(nodeCtobefreed->name);
		free(nodeCtobefreed->node1);
		free(nodeCtobefreed->node2);
		free(nodeCtobefreed);
	}

	nodeL=rootL;
	while(nodeL!=NULL){
		nodeLtobefreed=nodeL;
		nodeL=nodeL->next;
		free(nodeLtobefreed->name);
		free(nodeLtobefreed->node1);
		free(nodeLtobefreed->node2);
		free(nodeLtobefreed);
	}

	nodeD=rootD;
	while(nodeD!=NULL){
		nodeDtobefreed=nodeD;
		nodeD=nodeD->next;
		free(nodeDtobefreed->name);
		free(nodeDtobefreed->node1);
		free(nodeDtobefreed->node2);
		if(nodeDtobefreed->modelname!=NULL)free(nodeDtobefreed->modelname);
		free(nodeDtobefreed);
	}

	nodeM=rootM;
	while(nodeM!=NULL){
		nodeMtobefreed=nodeM;
		nodeM=nodeM->next;
		free(nodeMtobefreed->name);
		free(nodeMtobefreed->D);
		free(nodeMtobefreed->G);
		free(nodeMtobefreed->S);
		free(nodeMtobefreed->B);
		if(nodeMtobefreed->modelname!=NULL)free(nodeMtobefreed->modelname);
		free(nodeMtobefreed);
	}

	nodeB=rootB;
	while(nodeB!=NULL){
		nodeBtobefreed=nodeB;
		nodeB=nodeB->next;
		free(nodeBtobefreed->name);
		free(nodeBtobefreed->C);
		free(nodeBtobefreed->B);
		free(nodeBtobefreed->E);
		if(nodeMtobefreed->modelname!=NULL)free(nodeBtobefreed->modelname);
		free(nodeBtobefreed);
	};
	
	//eleutherwnoume tous hash tables
	int i;
	entry_t *temp;
	entry_t *current = NULL;
	for(i=0;i<hashtable->size;i++){
		current = hashtable->table[i];
		while(current != NULL) {
			temp=current;
			current = current->next;
			free(temp);
		}
	}
	free(hashtable->table);
	free(hashtable);

	
	
	//eleutherwnoume tis ypoloipes metavlites pou exoume desmeusei
	free(plot_nodes);
	for(i=0;i<plot_size;i++){
	  free(plot_names[i]);
	}

}
