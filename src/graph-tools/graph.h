#ifndef GRAPH_H_
#define GRAPH_H_

#define MAX_VERTEX_NUM 100

typedef int edgeInfo;
typedef int vertexType;

//adjacent list
typedef struct aedge{
	int avertex;
	struct aedge *next;
	edgeInfo info;
}AEDGE;

typedef struct anode{
	vertexType data;
	AEDGE *first;	
}ANODE;

typedef struct agraph{
	ANODE Alist[MAX_VERTEX_NUM];
	int  vexnum, edgenum;
}AGRAPH;

//orthogonal list

typedef struct oarc{
	int headvex,tailvex;
	struct oarc *hlink, *tlink;
}

typedef struct onode{
	vertexType data;
	OARC *firstin, *firstout;
}ONODE;

typedef struct ograph{
	ONODE Olist[MAX_VERTEX_NUM];
	int vexnum,arcnum;
}

//adjacency multiple list


typedef struct amedge{
	int mark;
	int ivex, jvex;
	struct amedge *ilink, *jlink;
	edgeInfo info;
}AMEDGE;

typedef struct amnode{
	vertexType data;
	AMEDGE *first;	
}AMNODE;

typedef struct amgraph{
	AMNODE AMlist[MAX_VERTEX_NUM];
	int  vexnum, edgenum;
}AMGRAPH;

#endif
