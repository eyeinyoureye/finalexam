#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GRAPH.h"

graphNode* vertexExistedId(int _id, GRAPH** graph)
{
	graphNode* current = (*graph) -> node;
	while(current != NULL)
	{
		if(current -> id == _id)
			return current;

		current = current -> next;
	}

	return NULL;
}

graphNode* vertexExistedKey(char* _key, GRAPH** graph)
{
	graphNode* current = (*graph) -> node;

	while(current != NULL)
	{
		// printf("%s\t", current -> key);
		if(strcmp(current -> key, _key) == 0)
			return current;

		current = current -> next;
	}

	return NULL;
}

void addPair(int _key, int _value, PAIR** root)
{
	PAIR* current = *root;

	while(current != NULL)
	{
		if(current -> key == _key)
		{
			current -> value = _value;
			break;
		}

		current = current -> next;
	}

	if(current == NULL)
	{
		PAIR* new = (PAIR*)calloc(1, sizeof(PAIR));

		new -> key = _key;
		new -> value = _value;

		new -> next = *root;
		*root = new;
	}
}

graphNode* findVertex(int _id, GRAPH** graph)
{
	graphNode* current = (*graph) -> node;

	while(current != NULL)
	{
		if(current -> id == _id)
			return current;

		current = current -> next;
	}

	return NULL;
}
graphNode* findVertexc(const char* _key, GRAPH** graph)
{
	graphNode* current = (*graph) -> node;

	while(current != NULL)
	{
		if(strcmp(current -> key,_key)==0)
			return current;

		current = current -> next;
	}

	return NULL;
}

PAIR* findPair(int _key, PAIR** pair)
{
	PAIR* tmp = *pair;

	while(tmp != NULL)
	{
		if(tmp -> key == _key)
			break;

		tmp = tmp -> next;
	}

	return tmp;
}

void enQueue(int _value, QUEUE** queue)
{
	if(*queue == NULL)
	{
		*queue = (QUEUE*)calloc(1, sizeof(QUEUE));
		(*queue) -> value = _value;
	}else{
		QUEUE* current = *queue;
		QUEUE* previous = NULL;
		QUEUE* new = (QUEUE*)calloc(1, sizeof(QUEUE));

		new -> value = _value;

		while(current != NULL)
		{
			previous = current;
			current = current -> next;
		}

		previous -> next = new;
	}
}

void addVertex(char* _key, int _id, GRAPH** graph)
{
	graphNode* new = NULL;

	if(_id == 0)
	{
		new = vertexExistedKey(_key, graph);
	}
	else
	{
		new = vertexExistedId(_id, graph);
	}

	if(new == NULL)
	{
		new = (graphNode*)calloc(1, sizeof(graphNode));
		new -> key = (char*)calloc(MAX, sizeof(char));
		strcpy(new -> key, _key);
		new -> Adjcency = make_jrb();


		//tùy yêu cầu đề bài
		// new -> reverse_Adjcency = make_jrb();


		if((*graph) -> node == NULL)
		{
			new -> id = 1;
			(*graph) -> node = new;
		}else{
			graphNode* current = (*graph) -> node;
			graphNode* previous = NULL;

			while(current != NULL)
			{
				previous = current;
				current = current -> next;
			}

			previous -> next = new;

			if(_id == 0)
				new -> id = previous -> id + 1;
			else
				new -> id = _id;
		}

		++((*graph) -> size);
	}
}

void addEdge(int id1, int id2, int weight, GRAPH** graph)
{
	graphNode* node1 = vertexExistedId(id1, graph);
	graphNode* node2 = vertexExistedId(id2, graph);

	++(node1 -> out_degree);
	++(node2 -> in_degree);

	jrb_insert_int(node1 -> Adjcency, id2, new_jval_i(weight));

	//tùy yêu cầu của đề bài
	// jrb_insert_int(node2 -> reverse_Adjcency, id1, new_jval_i(weight));
}

int not_in_list(int n, int* list, int size)
{
	for (int i = 0; i < size; ++i)
		if(list[i] == n)
			return 0;

	return 1;
}

int** dijkstra(int _begin, GRAPH** graph)
{
	QUEUE* queue = NULL;
	PAIR* pair = NULL;
	int* list = NULL;
	int l_size = 1;
	int** res = (int**)calloc(2, sizeof(int*));


	for (int i = 0; i < 2; ++i)
		*(res + i) = (int*)calloc((*graph) -> size, sizeof(int));
	
	for (int i = 0; i < (*graph) -> size; ++i)
		res[1][i] = -1;

	graphNode* temp = (*graph) -> node;
	while(temp != NULL)
	{
		addPair(temp ->  id, INF, &pair);
		temp = temp -> next;
	}
	free(temp);

	addPair(_begin, 0, &pair);

	int q_size = 0;
	graphNode* node = findVertex(_begin, graph);

	if(node != NULL)
	{
		enQueue(_begin, &queue);
		list = realloc(list, sizeof(int));
		list[l_size - 1] = _begin;
		++q_size;
	}

	while(q_size != 0)
	{
		MAP* tmp = NULL;

		JRB ad;
		PAIR* a = findPair(queue -> value, &pair);
		graphNode* node2 = findVertex(queue -> value, graph);

		list = realloc(list, (++l_size) * sizeof(int));
		list[l_size - 1] = queue -> value;

		jrb_traverse(ad, node2 -> Adjcency)
		{
			PAIR* b = findPair(ad -> key.i, &pair);
			//JRB c = jrb_find_int(node2 -> Adjcency, ad -> key.i);	//đỉnh kề vs node2

			if((a -> value) + (ad -> val.i) < b -> value)
			{
				addPair(b -> key, (a -> value) + (ad -> val.i), &pair);
				res[1][b -> key - 1] = a -> key - 1;
			}

			if(not_in_list(ad -> key.i, list, l_size))
			{
				insertMap_int(b -> value, b -> key, 0, &tmp);
				++q_size;
			}
		}

		while(tmp != NULL)
		{
			enQueue(tmp -> value.i, &queue);
			tmp = tmp -> next;
		}

		queue = queue -> next;
		--q_size;
	}

	while(pair != NULL)
	{
		res[0][pair -> key - 1] = pair -> value;
		pair = pair -> next;
	}

	free(list);
	free(pair);
	free(queue);

	return res;
}

void find_path(int _end, int** path, int size)
{
	int* way = NULL;
	int s_size = 0;
	if(path[0][_end - 1] != 0)
	{
		int next = path[1][_end - 1];

		printf("%d\n", path[0][_end - 1]);
		way = realloc(way, (++s_size) * sizeof(int));
		way[s_size - 1] = _end - 1;

		do
		{
			way = realloc(way, (++s_size) * sizeof(int));
			way[s_size - 1] = next;
			next = path[1][next];
		}while(next != -1);

		for (int i = s_size - 1; i > 0; --i)
		{
			printf("%d -> ", way[i] + 1);
		}
		printf("%d\n", way[0] + 1);
	}
}

char* f(int n, GRAPH* graph)
{
	graphNode* tmp_node = graph -> node;

	while(tmp_node != NULL)
	{
		if(tmp_node -> id == n)
			return tmp_node -> key;

		tmp_node = tmp_node -> next;
	}

	return NULL;
}

void topo(GRAPH* graph)
{
	int DAG = 0;
	QUEUE* queue = NULL;
	int q_size = 0;
	graphNode* head = graph -> node;

	int* list = NULL;
	int l_size = 0;
	int* res = NULL;
	int r_size = 0;

	while(head != NULL)
	{
		if(head -> in_degree == 0)
		{
			DAG = 1;
			enQueue(head -> id, &queue);
			list = realloc(list, (++l_size) * sizeof(int));
			list[l_size - 1] = head -> id;
			++q_size;
		}
		head = head -> next;
	}

	while(q_size != 0)
	{
		graphNode* node = vertexExistedId(queue -> value, &graph);
		if(node != NULL)
		{
			JRB tmp;

			jrb_traverse(tmp, node -> Adjcency)
			{
				graphNode* tmp2 = vertexExistedId(tmp -> key.i, &graph);
				if(tmp2 != NULL && not_in_list(tmp2 -> id, list, l_size))
				{
					if(tmp2 -> in_degree == 1)
					{
						enQueue(tmp2 -> id, &queue);
						++q_size;
						list = realloc(list, (++l_size) * sizeof(int));
						list[l_size - 1] = tmp2 -> id;
					}
					--(tmp2 -> in_degree);
				}
			}
		}

		res = realloc(res, (++r_size) * sizeof(int));
		res[r_size - 1] = queue -> value;
		queue = queue -> next;
		--q_size;
	}

	head = graph -> node;

	while(head != NULL)
	{
		if(head -> in_degree != 0)
		{
			printf("%d\n", head -> id);
			DAG = 0;
			break;
		}

		head = head -> next;
	}

	if(DAG)
		for (int i = 0; i < r_size; ++i)
			printf("%-10s", f(res[i], graph));
		else
			printf("not DAG graph!");
	printf("\n");
}

void addInfor(int _store_id, int _product_id, int quantity, GRAPH** graph)
{
	graphNode* node = vertexExistedId(_store_id, graph);

	if(node != NULL)
	{
		PAIR* current = node -> product;

		if(current == NULL)
		{
			node -> product = (PAIR*)calloc(1, sizeof(PAIR));
			node -> product -> key = _product_id;
			node -> product -> value = quantity;
		}else{
			while(current != NULL)
			{
				if(current -> key == _product_id)
				{
					current -> value = quantity;
					break;
				}

				current = current -> next;
			}

			if(current == NULL)
			{
				PAIR* new = (PAIR*)calloc(1, sizeof(PAIR));
				new -> key = _product_id;
				new -> value = quantity;

				PAIR* current_product = node -> product;
				PAIR* previous_product = NULL;

				while(current_product != NULL)
				{
					previous_product = current_product;
					current_product = current_product -> next;
				}

				previous_product -> next = new;
			}
		}
	}
}
char* return_key(int _id,GRAPH* graph)
{
	graphNode* current = graph -> node;

	while(current != NULL)
	{
		if(current ->id==_id)
			return current -> key;

		current = current -> next;
	}

	return NULL;

}

int return_id(const char* _key, GRAPH* graph)
{
	graphNode* current = graph -> node;

	while(current != NULL)
	{
		if(strcmp(current -> key, _key) == 0)
			return current -> id;

		current = current -> next;
	}

	return -1;
}