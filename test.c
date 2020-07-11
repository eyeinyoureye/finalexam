#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPh.h"

int convert(char* str)
{
	int res = 0;

	for (int i = 0; i < strlen(str); ++i)
	{
		res *= 10;
		res += (str[i] - '0');
	}

	return res;
}

int main()
{
	// FILE* fp = fopen("input.txt", "r");

	GRAPH* graph = (GRAPH*)calloc(1, sizeof(GRAPH));
	
	// //TH1:
	// char v1[1], v2[1];
	// int dis;

	// while(feof(fp) == 0)
	// {
	// 	fscanf(fp, "%s", v1);
	// 	fscanf(fp, "%s", v2);
	// 	fscanf(fp, "%d", &dis);

	// 	addVertex(v1, (int)(v1[0] - 'A' + 1), &graph);
	// 	addVertex(v2, (int)(v2[0] - 'A' + 1), &graph);
	// 	addEdge((int)(v1[0] - 'A' + 1), (int)(v2[0] - 'A' + 1), dis, &graph);
	// }

	//TH2:
	int dis;
	char str[100];

	FILE* fp = fopen("input.txt", "r");

	while(fgets(str, 100, fp))
	{
		if(feof(fp) == 0) 
			str[strlen(str) - 1] = '\0';

		char* s1 = (char*)calloc(100, sizeof(char));
		char* s2 = (char*)calloc(100, sizeof(char));
		char* las = (char*)calloc(100, sizeof(char));

		strcpy(s1, str);
		int i = 0;

		for (i = 0;; ++i)
		{
			if(str[i] == ' ' || str[i] == '\0')
			{
				s1[i] = '\0';
				break;
			}
		}

		addVertex(s1, 0, &graph);
		int new_id1 = return_id(s1, graph);

		int j = i + 1;
		++i;
		int node = 1;
		int num = 0;

		while(str[i-1] != '\0')
		{
			strcpy(s2, str + j);
			if(str[i] == ' ' || str[i] == '\0')
			{
				s2[i - j] = '\0';
				j = i + 1;
				// if(node)
				// {
					// node = 0;
					// num = 1;
					strcpy(las, s2);
					addVertex(s2, 0, &graph);
					int new_id = return_id(s2, graph);
					addEdge(new_id1, new_id, 1, &graph);

				// }else{
				// 	node = 1;
				// 	num = 0;
				// 	dis = convert(s2);
				// 	addEdge((int)(s1[0] - 'A' + 1), (int)(las[0] - 'A' + 1), dis, &graph);
				// }
			}

			++i;
		}
	}

	topo(graph);
}