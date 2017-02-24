#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "CircLib.h"
#include "hash.h"
#include "mna.h"
#include "options.h"
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


	//eleutherwnoume tis listes twn stoixeiwn tou kyklwmatos
	VoltT *nodeV, *nodeVtobefreed;
	AmperT *nodeI, *nodeItobefreed;
	ResistanceT *nodeR, *nodeRtobefreed;
	CapacitorT *nodeC, *nodeCtobefreed;
	InductorT *nodeL, *nodeLtobefreed;
	DiodeT *nodeD, *nodeDtobefreed;
	MosT *nodeM, *nodeMtobefreed;
	BjtT *nodeB, *nodeBtobefreed;

	nodeV=rootV;
	while(nodeV!=NULL){
		nodeVtobefreed=nodeV;
		nodeV=nodeV->next;
		free(nodeVtobefreed);
	}

	nodeI=rootI;
	while(nodeI!=NULL){
		nodeItobefreed=nodeI;
		nodeI=nodeI->next;
		free(nodeItobefreed);
	}

	nodeR=rootR;
	while(nodeR!=NULL){
		nodeRtobefreed=nodeR;
		nodeR=nodeR->next;
		free(nodeRtobefreed);
	}

	nodeC=rootC;
	while(nodeC!=NULL){
		nodeCtobefreed=nodeC;
		nodeC=nodeC->next;
		free(nodeCtobefreed);
	}

	nodeL=rootL;
	while(nodeL!=NULL){
		nodeLtobefreed=nodeL;
		nodeL=nodeL->next;
		free(nodeLtobefreed);
	}

	nodeD=rootD;
	while(nodeD!=NULL){
		nodeDtobefreed=nodeD;
		nodeD=nodeD->next;
		free(nodeDtobefreed);
	}

	nodeM=rootM;
	while(nodeM!=NULL){
		nodeMtobefreed=nodeM;
		nodeM=nodeM->next;
		free(nodeMtobefreed);
	}

	nodeB=rootB;
	while(nodeB!=NULL){
		nodeBtobefreed=nodeB;
		nodeB=nodeB->next;
		free(nodeBtobefreed);
	};
	
	//eleutherwnoume tous hash tables
	
	
	
	//eleutherwnoume tis ypoloipes metavlites pou exoume desmeusei
	free(plot_nodes);
  
}