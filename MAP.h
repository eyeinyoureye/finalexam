#include "jval.h"

#ifndef _MAP_
#define _MAP_

#define MAX 50

typedef struct MAP
{
	Jval value;
	int key;

	struct MAP* next;
}MAP;

void insertMap_str(char* _key, int _id, MAP** root);
void insertMap_int(int _key, int _value, int addition_value, MAP** root);
void Remove(int _key, MAP** root);
MAP* find_str(char* _key, MAP** root);
MAP* find_int(int _key, MAP** root);

#endif