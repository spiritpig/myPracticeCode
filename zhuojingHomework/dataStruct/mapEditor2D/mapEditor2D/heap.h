#include "AllDefine.h"

#ifndef HEAP
#define HEAP

#define MAX( a, b ) ( (a > b) ? (a) : (b) )
#define SAFE_DELARR(p) {if(p) {delete []p;p=0;}}

struct aStarNode
{
	char mapFlag;
	POINT pos;
	aStarNode *pParent;
	int F,G,H;

	aStarNode();
};

class heap
{
public:
	heap(bool isMax = true);
	~heap(void);

	void add( const aStarNode *data );
	bool remove_Top( aStarNode **data );
	bool isEmpty();
	void setEmpty();

private:
	// 特殊的比较函数，根据堆为大根堆或小根堆，决定返回值
	// 大根堆时，left > right 返回1
	// 小根堆时，left < right 返回1
	int _compare( const aStarNode * const left, const aStarNode * const right );
	void _resize();

	aStarNode **m_Data;
	size_t m_Size;
	size_t m_Capacity; 
	bool m_IsMax;
};

#endif	// END HEAP
