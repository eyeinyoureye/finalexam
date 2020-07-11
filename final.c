#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPh.h"

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
			printf("Hello World\n");
			break;
		}

		case 2:
		{
			FILE* fp = fopen(argv[1], "r");
			MAP* map = NULL;
			char* str = (char*)calloc(20, sizeof(char));
			int a;
			int product_quantity;

			fscanf(fp, "%d", &product_quantity);

			for (int i = 0; i < product_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				insertMap_str(str, a, &map);
			}

			fclose(fp);

			while(map != NULL)
			{
				printf("%s: %d\n", map -> value.s, map -> key);
				map = map -> next;
			}
			break;
		}

		case 3:
		{
			FILE* fp = fopen(argv[2], "r");
			MAP* map = NULL;
			char* str = (char*)calloc(20, sizeof(char));
			int a;
			int product_quantity;
			int storage_quantity;
			int x, y;

			fscanf(fp, "%d", &product_quantity);

			for (int i = 0; i < product_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				insertMap_str(str, a, &map);
			}

			fclose(fp);

			fp = fopen(argv[1], "r");
			GRAPH* graph = (GRAPH*)calloc(1, sizeof(GRAPH));

			fscanf(fp, "%d", &storage_quantity);

			for (int i = 0; i < storage_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				addVertex(str, a, &graph);

				for (int j = 0; j < product_quantity; ++j)
				{
					fscanf(fp, "%d", &x);
					fscanf(fp, "%d", &y);

					addInfor(a, x, y, &graph);
				}
			}
			int count = 0;

			// while(map != NULL)
			// {
			// 	printf("%s.\n", map -> value.s);
			// 	map = map -> next;
			// }

			graphNode* tmp = graph -> node;

			while(tmp != NULL)
			{
				printf("%s\n", tmp -> key);
				PAIR* tmp2 = tmp -> product;

				while(tmp2 != NULL)
				{
					printf("%s: %d\n", find_int(tmp2 -> key, &map) -> value.s, tmp2 -> value);
					tmp2 = tmp2 -> next;
				}

				if(count != storage_quantity - 1)
				{
					++count;
					printf("------------------\n");
				}

				tmp = tmp -> next;
			}
			break;
		}

		/*case 4:
		{
			FILE* fp = fopen(argv[2], "r");
			MAP* map = NULL;
			char* str = (char*)calloc(20, sizeof(char));
			int a;
			int product_quantity;
			int storage_quantity;
			int edge;
			int x, y, z;

			fscanf(fp, "%d", &product_quantity);

			for (int i = 0; i < product_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				insertMap_str(str, a, &map);
			}

			fclose(fp);

			fp = fopen(argv[1], "r");
			GRAPH* graph = (GRAPH*)calloc(1, sizeof(GRAPH));

			fscanf(fp, "%d", &storage_quantity);

			for (int i = 0; i < storage_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				addVertex(str, a, &graph);

				for (int j = 0; j < product_quantity; ++j)
				{
					fscanf(fp, "%d", &x);
					fscanf(fp, "%d", &y);

					addInfor(a, x, y, &graph);
				}
			}

			fscanf(fp, "%d", &edge);

			for (int i = 0; i < edge; ++i)
			{
				fscanf(fp, "%d", &x);
				fscanf(fp, "%d", &y);
				fscanf(fp, "%d", &z);

				addEdge(x, y, z, &graph);
				addEdge(y, x, z, &graph);
			}
		}*/

		case 5:
		{
			FILE* fp = fopen(argv[2], "r");
			MAP* map = NULL;
			char* str = (char*)calloc(20, sizeof(char));
			int a;
			int product_quantity;
			int storage_quantity;
			int edge;
			int x, y, z;

			fscanf(fp, "%d", &product_quantity);

			for (int i = 0; i < product_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				insertMap_str(str, a, &map);
			}

			fclose(fp);

			fp = fopen(argv[1], "r");
			GRAPH* graph = (GRAPH*)calloc(1, sizeof(GRAPH));

			fscanf(fp, "%d", &storage_quantity);

			for (int i = 0; i < storage_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				addVertex(str, a, &graph);

				for (int j = 0; j < product_quantity; ++j)
				{
					fscanf(fp, "%d", &x);
					fscanf(fp, "%d", &y);

					addInfor(a, x, y, &graph);
				}
			}

			fscanf(fp, "%d", &edge);

			for (int i = 0; i < edge; ++i)
			{
				fscanf(fp, "%d", &x);
				fscanf(fp, "%d", &y);
				fscanf(fp, "%d", &z);

				addEdge(x, y, z, &graph);
				addEdge(y, x, z, &graph);
			}

			x = convert(argv[3]);
			y = convert(argv[4]);

			graphNode* res = findVertex(y, &graph);

			PAIR* res2 = res -> product;

			if(res != NULL)
			{
				printf("%s\n", res -> key);

				res2 = findPair(x, &res2);

				if(res2 != NULL)
					printf("%s %d\n", find_int(res2 -> key, &map) -> value.s, res2 -> value);
			}

			printf("---Cac kho ke la:\n");

			JRB tmp;

			jrb_traverse(tmp, res -> Adjcency)
			{
				graphNode* res3 = findVertex(tmp -> key.i, &graph);

				if(res3 != NULL)
				{
					printf("%s\n", res3 -> key);

					res2 = findPair(x, &(res3 -> product));

					if(res2 != NULL)
						printf("%s %d\n", find_int(res2 -> key, &map) -> value.s, res2 -> value);
				}
			}

			break;
		}

		case 7:
		{
			FILE* fp = fopen(argv[2], "r");
			MAP* map = NULL;
			char* str = (char*)calloc(20, sizeof(char));
			int a;
			int product_quantity;
			int storage_quantity;
			int edge;
			int x, y, z;

			fscanf(fp, "%d", &product_quantity);

			for (int i = 0; i < product_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				insertMap_str(str, a, &map);
			}

			fclose(fp);


			fp = fopen(argv[1], "r");
			GRAPH* graph = (GRAPH*)calloc(1, sizeof(GRAPH));

			fscanf(fp, "%d", &storage_quantity);

			for (int i = 0; i < storage_quantity; ++i)
			{
				fscanf(fp, "%s", str);
				fscanf(fp, "%d", &a);

				addVertex(str, a, &graph);

				for (int j = 0; j < product_quantity; ++j)
				{
					fscanf(fp, "%d", &x);
					fscanf(fp, "%d", &y);
					addInfor(a, x, y, &graph);
				}

			}


			fscanf(fp, "%d", &edge);

			for (int i = 0; i < edge; ++i)
			{
				fscanf(fp, "%d", &x);
				fscanf(fp, "%d", &y);
				fscanf(fp, "%d", &z);

				addEdge(x, y, z, &graph);
				addEdge(y, x, z, &graph);
			}

			x = convert(argv[3]);	//loai sp
			y = convert(argv[4]);	//so luong dat hang
			z = convert(argv[5]);	//cua hang gan nhat
			int t = convert(argv[6]);	//cua hang tiep can kiem tra


			graphNode* res = findVertex(z, &graph);
			PAIR* res2 = findPair(x, &(res -> product));

			if(res2 -> value < y)
			{
				graphNode* res3 = findVertex(t, &graph);
				if(findPair(x, &(res3 -> product)) -> value + res2 -> value < y)
				{
					printf("Dat hang khong thanh cong\n");
				}else{
					int** res = (int**)calloc(2, sizeof(int*));
					for (int i = 0; i < 2; ++i)
						*(res + i) = (int*)calloc(graph -> size, sizeof(int));

					res = dijkstra(z, &graph);

					printf("Dat hang thanh cong\n");
					float time = 30 + (float)res[0][t-1] / 30 * 60;
					printf("Thoi gian giao hang la %d gio %d phut\n", (int)(time / 60), (int)time % 60);
				}
			}else{
				printf("Dat thanh cong\n");
				printf("Thoi gian giao hang la 30 phut\n");
			}

			break;
		}
		
	}
}