//////////////////////////////////////////////////////////////////////////
//
//
//	 ��������Rock-Paper-Scissors
//
//	 by pinkbeen 
//
//	 2014.7.25
// 
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ctime>

// ���ƺ궨��
#define ROCK	"ʯͷ"
#define PAPER	"��"
#define SCISSOR	"����"
#define ERROR	"ERROR"

// ��������
const int ROCK_ID = 1;
const int PAPER_ID = 2;
const int SCISSOR_ID = 3;
const int ERROR_ID = -1;

const int LEFT_WIN = 1;
const int RIGHT_WIN = -1;
const int DRAW = 0;

void outputHeader( const char *name )
{
	printf( " -----------------------------------------------------------------------------\n" );
	printf( "!                                                                   \n" );
	printf( "!                           %s                        \n",name );
	printf( "!                                                                   \n" );
	printf( " -----------------------------------------------------------------------------\n" );
}

void mapHandIdToHandStr( const int &handId )
{
	if( handId == ROCK_ID  )
	{
		printf( "%s ",ROCK );
	}
	else
	if( handId == PAPER_ID )
	{
		printf( "%s ",PAPER );
	}
	else
	if( handId == SCISSOR_ID )
	{
		printf( "%s ",SCISSOR );
	}
	else
	{
		printf( "%s ",ERROR );
	}
}

// ����-1��hand2ʤ��
// ����1��hand1ʤ��
// ����0��ƽ��
int calcRes( int hand1, int hand2 )
{
	if( hand1 == hand2 )
	{
		return DRAW;
	}
	else
	if( hand1 -hand2 == 1 ||
		hand1 - hand2 == -2 )
	{
		return LEFT_WIN;
	}
	else
	{
		return RIGHT_WIN;
	}
}

void rps()
{
	srand( ( unsigned int )time( NULL ) );

	outputHeader("����ʯͷ��!");

	int comHandId = random( 4, 1 );
	int plHandId, res;
	printf( "�������������(ʯͷ1\\��2\\����3): " );
	scanf( "%d", &plHandId );

	while( 1 )
	{
		printf( "\n" );
		printf( "��ң� " );
		mapHandIdToHandStr( plHandId );

		printf( " ���ԣ� " );
		mapHandIdToHandStr( comHandId );

		printf( "\n" );
		res = calcRes( plHandId, comHandId );

		if( res == DRAW )
		{
			printf( "\t���ƽ��\n" );
			printf( "�������µ�����(ʯͷ1\\��2\\����3): " );
			scanf( "%d", &plHandId );
			comHandId = random( 4, 1 );
		}
		else
		if( res == RIGHT_WIN )
		{
			printf( "\t���Ի�ʤ!\n" );
			break;
		}
		else
		if( res == LEFT_WIN )
		{
			printf( "\t��һ�ʤ!\n" );
			break;
		}		
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	rps();		

	return 0;
}