#include "stdafx.h"

#ifndef MYHASHTABLE
#define MYHASHTABLE

#define MAX_REPEAT_INFO 10
#define MAX_ONE_TABLE_LEN 256

#define SAFE_DELETE(p) {if(p) {delete p;p=NULL;}}
#define SAFE_DELARR(p) {if(p) {delete []p;p=NULL;}}

struct info
{
	int age;
	bool sex;
	char *pDesc;
};

struct hashTableNode
{
	info *pInfo[MAX_REPEAT_INFO];
	int finalValidInfoId;
	hashTableNode *next;

	hashTableNode()
	{
		memset( pInfo, 0, sizeof( pInfo ) );
		next = NULL;
		finalValidInfoId = -1;
	}

	~hashTableNode()
	{
		for ( int i=0; i<=finalValidInfoId; ++i )
		{
			if ( pInfo[i] != NULL )
			{
				SAFE_DELARR( pInfo[i]->pDesc );
			}
			SAFE_DELETE( pInfo[i] );
		}
	}
};

class myHashTable
{
public:
	myHashTable(void);
	~myHashTable(void);

	void add( const char * const name, int age, bool sex, const char * const desc );
	bool find( const char * const name, int &age, bool &sex, char ** desc );

private:
	void _add( hashTableNode *pSubTable, int index, const char * const name, 
		int age, bool sex, const char * const desc );
	bool _find( hashTableNode *pSubTable, int index, const char * const name, 
		int &age, bool &sex, char **desc );
	void _deleteHashTable( hashTableNode *pTable );

	hashTableNode *m_pTable;
};

#endif	// END MYHASHTABLE
