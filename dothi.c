#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GRAPh.h"

void menu()
{
	printf("Menu:\n1.Matric\n2.Vertex's Adjcency .\n3.List of Castles\n4.Shortest way\n");

}
int main()
{
	FILE* cc=fopen("dothi.txt","r");
	int v_size,e_size;
	int x,y,z;
	int walk[8]={0,0,0,0,0,0,0,0};
	GRAPH* tmp=(GRAPH*)calloc(1,sizeof(GRAPH));
	fscanf(cc,"%d",&v_size);
	fscanf(cc,"%d",&e_size);
	for(int i=0;i<e_size;i++)
	{
		fscanf(cc,"%d",&x);
		fscanf(cc,"%d",&y);
		fscanf(cc,"%d",&z);
		if(z<50)
		{
			walk[x-1]++;
			walk[y-1]++;
		}
		addVertex("#",x,&tmp);
		addVertex("#",y,&tmp);
		addEdge(x,y,z,&tmp);
		addEdge(y,x,z,&tmp);
	}
	fclose(cc);
	int choice=0;
	while(choice!=6)
	{
		menu();
		printf("\nEnter your choice:\n");
		scanf("%d",&choice);
		while(choice<1||choice>6)
		{
			printf("Error. Choose again\n");
			scanf("%d",&choice);
		}
		switch(choice)
		{
			case 1:
			{
				printf("Matric of Vertex\n");
				int a[v_size+1][v_size+1];
				for(int i=0;i<v_size;i++)
					for (int j = 0; j < v_size; ++j)
					{
						a[i][j]=0;
					}
				graphNode* cur = tmp -> node;
				JRB lag;
				while(cur!=NULL)
				{
					jrb_traverse(lag,cur->Adjcency)
					{
						a[cur -> id -1 ][lag->key.i-1]=lag->val.i;
					}
					cur=cur->next;
				}
				for (int i = 0; i <=v_size; ++i)
				{
					printf("%d\t",i);
				}
				printf("\n");
				for(int i=0;i<v_size;i++)
				{
					printf("%d\t",i+1);
					for (int j = 0; j < v_size; ++j)
					{
						printf("%d\t",a[i][j]);
					}
					printf("\n");
				}
				break;
			}
			case 2:
			{
				graphNode* cur = tmp -> node;
				JRB lag;
				while(cur!=NULL)
				{
					printf("Castle %d:\t",cur->id);
				    jrb_traverse(lag,cur->Adjcency)
				    {
				    	printf("%d\t",lag->key.i);
				    }	
				    printf("\n");
				    cur=cur->next;				
				}
				break;				
			}
			case 3:
			{
				printf("list of castle can walk to:\n");
				for(int i=0;i<v_size;i++)
					if(walk[i]==0)
						printf("Castle %d\t",i+1);
				printf("\n");
			    printf("list of mode castle:\n");
			    graphNode* cur = tmp -> node;
			    int max=0;
			    while(cur!=NULL)
			    {
			    	if(cur->in_degree>max)
			    		max=cur->in_degree;
			    	cur=cur->next;
			    }
			    cur = tmp -> node;
			    while(cur!=NULL)
			    {
			    	if(cur->in_degree==max)
			    		printf("Castle %d\t",cur->id);
			    	cur=cur->next;
			    }
			    printf("\n");
			    break;
			}
			case 4:
			{
				int s,e;
				printf("enter the start castle:\n");
				scanf("%d",&s);
				printf("enter the end Castle:\n");
				scanf("%d",&e);
				int** res = (int**)calloc(2, sizeof(int*));
				res=dijkstra(s, &tmp);
				find_path(e, res, v_size);
				break;
			}
		}
	}
} 