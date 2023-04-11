#ifndef GRAPH_H_
#define GRAPH_H_

#define MAX_VERTEX_NUM 100

typedef int edgeInfo;
typedef int vertexType;

//adjacent list
struct aedge{
	int avertex;
	struct aedge *next;
	edgeInfo info;
};

struct anode{
	vertexType data;
	struct aedge *first;	
};

struct agraph{
	struct anode Alist[MAX_VERTEX_NUM];
	int  vexnum, edgenum;
};

//orthogonal list

struct oarc{
	int headvex,tailvex;
	struct oarc *hlink, *tlink;
};

struct onode{
	vertexType data;
	struct oarc *firstin, *firstout;
};

struct ograph{
	struct onode Olist[MAX_VERTEX_NUM];
	int vexnum,arcnum;
};

//adjacency multiple list


struct amedge{
	int mark;
	int ivex, jvex;
	struct amedge *ilink, *jlink;
	edgeInfo info;
};

struct amnode{
	vertexType data;
	struct amedge *first;	
};

struct amgraph{
	struct amnode AMlist[MAX_VERTEX_NUM];
	int  vexnum, edgenum;
};

#endif
