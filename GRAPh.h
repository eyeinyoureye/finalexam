#include "jrb.h"
#include "jval.h"
#include "MAP.h"

#ifndef _graphNode_
#define _graphNode_

#define MAX 50
#define INF 1e6

typedef struct GRAPH
{
	struct graphNode* node;	//đỉnh đồ thị
	int size;	//số đỉnh có trong đồ thị
}GRAPH;

typedef struct graphNode //một đỉnh của đồ thị
{
	int id;	//id bắt đầu từ 1
	char* key;	//tên đỉnh
	int in_degree;
	int out_degree;

	JRB Adjcency;	//danh sách các đỉnh kề
	struct graphNode* next; 

	//tùy vào yêu cầu đề bài
	struct PAIR* product;
}graphNode;

typedef struct PAIR //cấu trúc lưu giá trị theo khóa tùy ý
{
	int key;
	int value;

	struct PAIR* next;
}PAIR;

typedef struct QUEUE
{
	int value;

	struct QUEUE* next;
}QUEUE;

//hàm thêm đỉnh vào đồ thị
void addVertex(char* _key, int _id, GRAPH** graph);

//hàm thêm cạnh vào đồ thị (có hướng)
void addEdge(int _id1, int _id2, int weight, GRAPH** graph);

//hàm trả về ma trận 2 x (số đỉnh), trong đó hàng 1 là khoảng cách, hàng 2 là truy vết
int** dijkstra(int _begin, GRAPH** graph);
void find_path(int _end, int** path, int size);

//In ra topo của đồ thị
void topo(GRAPH* graph);

//trả về đỉnh trong đồ thị có id = _id
graphNode* findVertex(int _id, GRAPH** graph);

//trả về đỉnh trong đồ thị có key =_key
graphNode* findVertexc(const char* _key,GRAPH** graph);

//trả về cấu trúc PAIR có key = _key
PAIR* findPair(int _key, PAIR** pair);

//tùy vào yêu cầu đề bài mà bổ sung thêm hàm
void addInfor(int _store_id, int _product_id, int quantity, GRAPH** graph);
int return_id(const char* _key, GRAPH* graph);
char* return_key(int _id, GRAPH* graph);
//tra ve trọng số của cạnh
int edgeValue(int _id1, int _id2, GRAPH* graph);
//tra ve doan duong di ngan nhat the ten
void find_pathc(int _end, int** path, int size, GRAPH* graph);

#endif