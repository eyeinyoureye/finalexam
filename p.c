#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GRAPh.h"
int convert(const char* str)
{
	int res=0;
	for(int i=0;i<strlen(str);i++)
	{
		res*=10;
        res+=(str[i]-'0');
	}
	return res;
}
int main(int argc,char** argv)
{

    int o;
    if(strcmp(argv[1],"-h")==0)
    	{
    		printf("C-Advanced, HK20152\n");
    		return 0;
    	}
    if(strcmp(argv[1],"-v")==0)
    	o=1;
    if(strcmp(argv[1],"-w")==0)
    	o=2;
    if(strcmp(argv[1],"-p")==0)
    	o=3;
    if(strcmp(argv[1],"-n")==0)
    	o=4;
    if(strcmp(argv[1],"-s")==0)
    	o=5;
	GRAPH* g=(GRAPH*)calloc(1,sizeof(GRAPH));
    FILE* f=fopen(argv[2],"r");
	int v_size,id,e_size,x,y,z;
	char* ip=(char*)calloc(15,sizeof(char));
	fscanf(f,"%d",&v_size);
	for(int i=0;i<v_size;i++)
	{
	    fscanf(f,"%d",&id);
		fscanf(f,"%s",ip);
		addVertex(ip,id,&g);
	}
	fscanf(f,"%d",&e_size);
	for(int i=0;i<e_size;i++)
	{
	    fscanf(f,"%d",&x);
		fscanf(f,"%d",&y);
		fscanf(f,"%d",&z);
		addEdge(x,y,z,&g);
	    addEdge(y,x,z,&g);
    }
    fclose(f);
    JRB root;
    graphNode* node=g->node;
  	
    switch(o)
    {
    	case 1:
    	{
    		while(node!=NULL)
    		{
    			printf("%d ",node->id);
    			printf("%s\n",node->key);
    			node=node->next;
    		}
    		break;
    	}
    	case 2:
    	{
    		int a=convert(argv[3]);
		    int b=convert(argv[4]);
		    printf("%d\n",edgeValue(a,b,g));
		    break;
    	}
    	case 3:
    	{
    		int a=convert(argv[3]);
		    int b=convert(argv[4]);
		    int** res = (int**)calloc(2, sizeof(int*));
			res=dijkstra(a, &g);
			find_pathc(b,res,v_size,g);
			break;

    	}
    	case 4:
    	{
    		int count=0;
			jrb_traverse(root,node->Adjcency)
			{
				count++;
			}
			printf("%d\n",count);
			jrb_traverse(root,node->Adjcency)
			{
				printf("%d ",root->key.i);
				printf("%s ",return_key(root->key.i,g));
				printf("%d\n",edgeValue(node->id,root->key.i,g));
			}
			break;
    	}
    	case 5:
    	{
    		int k=argc-3;
    		printf("%d\n",k);
    		int list[k];
    		for(int i=0;i<k;i++)
    		{
    			list[i]=convert(argv[3+i]);
    		}
    		for(int i=0;i<k;i++)
    		{
    			printf("%d ",list[i]);
    			printf("%s\n",return_key(list[i],g));
    		}
    		int count =0;
    		for(int i=0;i<k;i++)
    			for(int j=i+1;j<k;j++)
    				if(edgeValue(list[i],list[j],g)!=-1)
    					count++;
    	    printf("%d\n",count);
    	    for(int i=0;i<k;i++)
    			for(int j=i+1;j<k;j++)
    				if(edgeValue(list[i],list[j],g)!=-1)
    				{
    					printf("%d %d %d\n",list[i],list[j],edgeValue(list[i],list[j],g));
    				}
    		break;
    	}
    }
    return 0;
}