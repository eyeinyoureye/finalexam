#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MAP.h"

void insertMap_str(char* _val, int _key, MAP** root)
{
	if(*root == NULL)
	{
		*root = (MAP*)calloc(1, sizeof(MAP));
		(*root) -> value.s = (char*)calloc(MAX, sizeof(char));

		strcpy((*root) -> value.s, _val);
		(*root) -> key = _key;
	}else{
		MAP* new = (MAP*)calloc(1, sizeof(MAP));
		new -> value.s = (char*)calloc(MAX, sizeof(char));
		strcpy(new -> value.s, _val);
		new -> key = _key;

		MAP* current = *root;
		MAP* previous = NULL;

		while(current != NULL)
		{
			if(current -> key > new -> key)
				break;

			previous = current;
			current = current -> next;
		}

		if(previous == NULL)
		{
			new -> next = *root;
			*root = new;
		}else{
			previous -> next = new;
			new -> next = current;
		}
	}
}

void insertMap_int(int _key, int _value, int addition_value, MAP** root)
{
	if(*root == NULL)
	{
		*root = (MAP*)calloc(1, sizeof(MAP));
		(*root) -> value.i = _value;
		(*root) -> key = _key;
	}else{
		MAP* current = *root;
		MAP* previous = NULL;
		MAP* new = (MAP*)calloc(1, sizeof(MAP));

		new -> key = _key;
		new -> value.i = _value;

		while(current != NULL)
		{
			if(current -> key > _key)
				break;

			previous = current;
			current = current -> next;
		}

		if(previous == NULL)
		{
			new -> next = *root;
			*root = new;
		}else{
			new -> next = current;
			previous -> next = new;
		}
	}
}

void Remove(int _key, MAP** root)
{
	if(*root != NULL)
	{
		MAP* current = *root;
		MAP* previous = NULL;

		while(current != NULL)
		{
			if(current -> key == _key
				)
				break;

			previous = current;
			current = current -> next;
		}

		if(current != NULL)
		{
			if(previous != NULL)
			{
				previous -> next = current -> next;
			}else{
				*root = (*root) -> next;
			}
		}
	}
}

MAP* find_str(char* _key, MAP** root)
{
	MAP* current = *root;

	while(current != NULL)
	{
		if(strcmp(current -> value.s, _key) == 0)
			break;

		current = current -> next;
	}

	return current;
}

MAP* find_int(int _key, MAP** root)
{
	MAP* current = *root;

	while(current != NULL)
	{
		if(current -> key == _key)
			break;

		current = current -> next;
	}

	return current;
}