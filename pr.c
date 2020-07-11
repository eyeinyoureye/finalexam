#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GRAPh.h"
// char* synchro(const char* str)
// {
// 	char* res=(char*)calloc(20,sizeof(char));
// 	for(int i =0; i < strlen(str); ++i)
// 	{
// 		if(str[i]>='A'&&str[i]<='Z')
// 		    res[i]=str[i]+32;
// 	    else
// 	    	res[i]=str[i];
// 	}
// 	res[strlen(str)]='\0';
// 	return res;
// }
int convert(const char* str)
{
	int res = 0;

	for (int i = 0; i < strlen(str); ++i)
	{
		res *= 10;
		res += str[i] - '0';
	}


	return res;
}
int main(int argc, const char* argv[])
{
	switch(argc)
	{
		case 1:
		{
			printf("No program is running\n");
			break;
		}
		case 2:
		{
			// char* tmp =synchro(argv[1]);
			if(strcmp(argv[1],"help")==0)
				printf("Supported command: help, i2n, n2i, cc, cr, odg, rel.\n");
			else
				if(strcmp(argv[1],"about")==0)
					printf("C advanced 20142 final exam.\n");
				else
					printf("code error\n");
		    break;
		}
		case 3:
		{
			printf("No program is running\n");
			break;
		}
		case 4:
		{
			GRAPH* g=(GRAPH*)calloc(1,sizeof(GRAPH));
			FILE* f=fopen(argv[2],"r");
			int v_size,e_size,x,y,id;
			char* name=(char*)calloc(20,sizeof(char));
			fscanf(f,"%d",&v_size);
			fscanf(f,"%d",&e_size);
			for(int i = 0; i < v_size; ++i)
			{
				fscanf(f,"%s",name);
				fscanf(f,"%d",&id);
				addVertex(name,id,&g);
			}
			for (int i = 0; i < e_size; ++i)
			{
				fscanf(f,"%d",&x);
				fscanf(f,"%d",&y);
				addEdge(x,y,0,&g);
			}
			fclose(f);
			//char* tmp =synchro(argv[1]);
			if(strcmp(argv[1],"i2n")==0)
			{
				int a= convert(argv[3]);
				printf("%s\n",return_key(a,g));
			}
			else
				if(strcmp(argv[1],"n2i")==0)
				{
					printf("%d\n",return_id(argv[3],g));
				} 
				else
					if(strcmp(argv[1],"odg")==0)
					{
						int a=convert(argv[3]);
						graphNode* root=g->node;
     	    		    while(root!=NULL)
     	    		    {
     	    		    	if(root->out_degree>a)
     	    		    		printf("%s\n",root->key);
     	    			
     	    			    root=root ->next;
     	    		    }

					}
				    else
				    	if(strcmp(argv[1],"rel")==0)
				    	{
				    		int a=convert(argv[3]);
				    		int* list=realloc(list,sizeof(int));
				    		int count=0;
				    		graphNode* node=findVertex(a,&g);
				    		JRB node1,node2;
				    		jrb_traverse(node1,node->Adjcency)
				    		{
				    			int ch=0;
				    			for(int i=0;i<count;i++)
				    				if(node1->key.i==list[i])
				    					ch=1;
				    		    if(ch==0)
				    		    {
				    		    	printf("%s\n",return_key(node1->key.i,g));
				    			    list[count++]=node1->key.i;
				    			    list=realloc(list,(count+1)*sizeof(int));
				    		    }				    			
				    			graphNode* root=findVertex(node1->key.i,&g);
				    			jrb_traverse(node2,root->Adjcency)
				    			{
				    				int ck=0;
				    				for(int i=0;i<count;i++)
				    					if(node2->key.i==list[i])
				    						ck=1;
				    				if(ck==0)
				    				{
				    					printf("%s\n",return_key(node2->key.i,g));
				    					list[count++]=node2->key.i;
				    			        list=realloc(list,(count+1)*sizeof(int));
				    				}
				    			}
				    		}
				    	}
				    	else
				    	    printf("code error\n");
			break;               
		}
		case 5:
		{
			GRAPH* g=(GRAPH*)calloc(1,sizeof(GRAPH));
			FILE* f=fopen(argv[2],"r");
			int v_size,e_size,x,y,id;
			char* name=(char*)calloc(20,sizeof(char));
			fscanf(f,"%d",&v_size);
			fscanf(f,"%d",&e_size);
			for(int i = 0; i < v_size; ++i)
			{
				fscanf(f,"%s",name);
				fscanf(f,"%d",&id);
				addVertex(name,id,&g);
			}
			for (int i = 0; i < e_size; ++i)
			{
				fscanf(f,"%d",&x);
				fscanf(f,"%d",&y);
				addEdge(x,y,0,&g);
			}
			fclose(f);
			if(strcmp(argv[1],"cc")==0)
			{
				int a = convert(argv[3]);
			    int b = convert(argv[4]);
			    graphNode* root=findVertex(a,&g);
			    JRB root1;
			    int count[v_size];
			    for(int i =0;i<v_size;i++)
				    count[i]=0;
			    int c=0;
			    jrb_traverse(root1,root ->Adjcency)
			    {
				    count[c++]=root1 ->key.i;
			    }
			    root=findVertex(b,&g);
			    jrb_traverse(root1,root ->Adjcency)
			    {
				    for(int i=0;i<c;i++)
					    if(count[i]==root1->key.i)
						    printf("%s\n",return_key(count[i],g));
			    }
			     
     	    }
     	    else 
     	    {
     	    	if(strcmp(argv[1],"cr")==0)
     	    	{
     	    		JRB root1;
     	    		int a = convert(argv[3]);
			        int b = convert(argv[4]);
			        int count=0;
     	    		graphNode* root=g->node;
     	    		while(root!=NULL)
     	    		{
     	    			count=0;
     	    			jrb_traverse(root1,root->Adjcency)
     	    			{
     	    				if(root1->key.i==a)
     	    					count++;
     	    				if(root1->key.i==b)
     	    					count++;
     	    			}
     	    			if(count==2)
     	    				printf("%s\n",return_key(root->id,g));
     	    			root=root ->next;
     	    		}

     	    	}
     	    	else
     	    		printf("code error\n");
     	    }
			break;
		}
		
	}
	return 0;
}