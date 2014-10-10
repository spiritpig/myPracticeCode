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
	// ����ıȽϺ��������ݶ�Ϊ����ѻ�С���ѣ���������ֵ
	// �����ʱ��left > right ����1
	// С����ʱ��left < right ����1
	int _compare( const aStarNode * const left, const aStarNode * const right );
	void _resize();

	aStarNode **m_Data;
	size_t m_Size;
	size_t m_Capacity; 
	bool m_IsMax;
};

#endif	// END HEAP
