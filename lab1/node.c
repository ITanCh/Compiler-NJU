#include"node.h"
extern int yylineno;
/*init a Node and allocate space for it*/
Node* initNode(char *name,char *value)
{
	Node *node= malloc(sizeof(Node));
	node->row=yylineno;
	strcpy(node->name,name);
	strcpy(node->value,value);
	node->children=NULL;
	node->next=NULL;
	return node;
}

/*give father a child*/
void addChild(Node* f,Node* c)
{
	if(f!=NULL&&c!=NULL)
	{
		c->next=f->children;
		f->children=c;
		f->row=c->row;		//update the row of father node
	}
}

/*print the whole tree*/
void printTree(Node* r,int count)
{
	if(r==NULL)return;
	if(r->children==NULL)		//it's a token
	{	
		int i=0;		
		for(;i<count;i++)	// retract 
		{
			printf("  ");
		}
		//not all nodes need to print value
		if(strcmp(r->name,"TYPE")==0||strcmp(r->name,"INT")==0||strcmp(r->name,"FLOAT")==0||strcmp(r->name,"ID")==0)
		{
			if(strcmp(r->name,"INT")==0)
				printf("%s: %d\n",r->name,atoi(r->value));
			else if(strcmp(r->name,"FLOAT")==0)
				printf("%s: %f\n",r->name,atof(r->value));
			else
				printf("%s: %s\n",r->name,r->value);

		}
		else
		{
			printf("%s\n",r->name);
		}
	}
	else 				//non-terminal
	{
		int i=0;
		for(;i<count;i++)
		{
			printf("  ");
		}
		printf("%s(%d)\n",r->name,r->row);
		Node *p=r->children;
		//traverse the child nodes
		while(p!=NULL){
			printTree(p,count+1);
			Node* temp=p;
			p=p->next;
			free(temp);
			temp=NULL;
		}
	}
	return;
}
