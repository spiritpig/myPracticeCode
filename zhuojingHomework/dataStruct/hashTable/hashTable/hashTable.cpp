// hashTable.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "myHashTable.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	myHashTable mht;

	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zs", 15, false, "�²۴���" );
	mht.add( "zw", 1623, false, "�²۴���" );

	int age = -1;
	bool sex = false;
	char *desc = new char[100];
	if ( mht.find( "zw", age, sex, &desc ) )
	{
		printf( "zs, age: %d, sex :%d, desc : %s \n", age, sex, desc );
	}

	SAFE_DELETE( desc );
	return 0;
}

