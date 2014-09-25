#include "StdAfx.h"
#include ".\myhashtable.h"

myHashTable::myHashTable(void)
{
	m_pTable = new hashTableNode[MAX_ONE_TABLE_LEN];
}

myHashTable::~myHashTable(void)
{
	_deleteHashTable( m_pTable );
}

void myHashTable::add( const char * const name, int age, bool sex, 
					   const char * const desc )
{
	static size_t nameLen;
	nameLen = strlen(name);

	if ( (name == NULL) || 
		 (nameLen <= 0) ||
		 (nameLen > 3) )
	{
		return;
	}

	static unsigned int nameCode = (unsigned char)name[0];
	//  名字长度为1时
	if ( nameLen == 1 )
	{
		++m_pTable[nameCode].finalValidInfoId;
		if ( m_pTable[nameCode].finalValidInfoId < MAX_REPEAT_INFO )
		{
			m_pTable[nameCode].pInfo[m_pTable[nameCode].finalValidInfoId] = new info;
			m_pTable[nameCode].pInfo[m_pTable[nameCode].finalValidInfoId]->age = age;
			m_pTable[nameCode].pInfo[m_pTable[nameCode].finalValidInfoId]->sex = sex;
			m_pTable[nameCode].pInfo[m_pTable[nameCode].finalValidInfoId]->pDesc 
				= new char[strlen(desc)+1];
			strcpy( m_pTable[nameCode].pInfo[m_pTable[nameCode].finalValidInfoId]->pDesc
				, desc );
		}
	}
	else
	{
		if ( m_pTable[nameCode].next == NULL )
		{
			m_pTable[nameCode].next = new hashTableNode[MAX_ONE_TABLE_LEN];
		}
		_add( m_pTable[nameCode].next, 1, name, age, sex, desc );
	}
}

bool myHashTable::find( const char * const name, int &age, bool &sex, char **desc )
{
	static size_t nameLen;
	nameLen = strlen(name);

	if ( (name == NULL) || 
		(nameLen <= 0) ||
		(nameLen > 3) )
	{
		return false;
	}

	static unsigned int nameCode = (unsigned char)name[0];
	//  名字长度为1时
	if ( nameLen == 1 )
	{
		if ( m_pTable[nameCode].finalValidInfoId > -1 )
		{
// 			age = m_pTable[nameCode].pInfo[m_pTable[nameCode].finalValidInfoId]->age;
// 			sex = m_pTable[nameCode].pInfo[m_pTable[nameCode].finalValidInfoId]->sex;
// 			*desc = m_pTable[nameCode].pInfo[m_pTable[nameCode].finalValidInfoId]->pDesc;
			age = m_pTable[nameCode].pInfo[0]->age;
			sex = m_pTable[nameCode].pInfo[0]->sex;
			strcpy( *desc, m_pTable[nameCode].pInfo[0]->pDesc );
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ( m_pTable[nameCode].next != NULL )
		{
			return _find( m_pTable[nameCode].next, 1, name, age, sex, desc );
		}
		else
		{
			return false;
		}
	}
}

void myHashTable::_add( hashTableNode *pSubTable, int index, const char * const name, 
					   int age, bool sex, const char * const desc )
{
	unsigned int nameCode = (unsigned char)name[index];
	if ( name[index+1] == '\0' )
	{
		++pSubTable[nameCode].finalValidInfoId;
		if ( pSubTable[nameCode].finalValidInfoId < MAX_REPEAT_INFO )
		{
			pSubTable[nameCode].pInfo[pSubTable[nameCode].finalValidInfoId] = new info;
			pSubTable[nameCode].pInfo[pSubTable[nameCode].finalValidInfoId]->age = age;
			pSubTable[nameCode].pInfo[pSubTable[nameCode].finalValidInfoId]->sex = sex;
			pSubTable[nameCode].pInfo[pSubTable[nameCode].finalValidInfoId]->pDesc 
				= new char[strlen(desc)+1];
			strcpy( pSubTable[nameCode].pInfo[pSubTable[nameCode].finalValidInfoId]->pDesc
				, desc );
		}
	}
	else
	{
		if ( pSubTable[nameCode].next == NULL )
		{
			pSubTable[nameCode].next = new hashTableNode[MAX_ONE_TABLE_LEN];
		}
		_add( pSubTable[nameCode].next, index+1, name, age, sex, desc );
	}
}

bool myHashTable::_find( hashTableNode *pSubTable, int index, const char * const name, 
						int &age, bool &sex, char **desc )
{
	unsigned int nameCode = (unsigned char)name[index];
	if ( name[index+1] == '\0' )
	{
		if ( pSubTable[nameCode].finalValidInfoId > -1 )
		{
			age = pSubTable[nameCode].pInfo[0]->age;
			sex = pSubTable[nameCode].pInfo[0]->sex;
			strcpy( *desc, pSubTable[nameCode].pInfo[0]->pDesc );

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ( pSubTable[nameCode].next != NULL )
		{
			return _find( pSubTable[nameCode].next, index+1, name, age, sex, desc );
		}
		else
		{
			return false;
		}
	}
}

void myHashTable::_deleteHashTable( hashTableNode *pTable )
{
	for ( int i=0; i<MAX_ONE_TABLE_LEN; ++i )
	{
		if ( pTable[i].next != NULL )
		{
			_deleteHashTable( pTable[i].next );
		}
	}
	SAFE_DELARR( pTable );
}