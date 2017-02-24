void CreateNode(char *string){

	NodeT *temp=rootN;

	while(temp!=NULL){
		if(strcmp(string,temp->name)){return();}
	}

	temp = (NodeT*) malloc(sizeof(NodeT));
	temp->name=(char*)malloc(sizeof(char)*(strlen(string)+1));
	strcpy(temp->name ,string);

	temp->code=NodeCounter;
	NodeCounter++;
	
	temp->next=rootN;
	rootN=temp;
	

}