//
// ������: sameWithMe
//
//	by pinkbben
//
//	2014.7.26
//

#include "stdafx.h"

void outputHeader( char *name )
{
	printf( " -----------------------------------------------------------------------------\n" );
	printf( "!                                                                   \n" );
	printf( "!                           %s                        \n",name );
	printf( "!                                                                   \n" );
	printf( " -----------------------------------------------------------------------------\n" );
}


void sameWithMe()
{
	bool isEqual = true;
	int comNum = 0, plNum = 0;
	int score = 0, curMaxTime = MAX_TIME;
	newTimer myTimer( curMaxTime );

	outputHeader( "SameWithMe!" );
	printf( "ÿ���������һ����λ��ʱ����Ҷ���Ҫ��һ��ʱ����������ͬ��ֵ��\n" );
	printf( "��󣬵�����������ʱ�������ܵ÷֣�\n" );

	// ��ͣһ�� 
	system( "pause" );
	system( "cls" );
	myTimer.moveTimer();

	while( isEqual )	
	{
		comNum = random( 1000, 100 );

		printf( "%d\n",comNum );
		scanf( "%d",&plNum );
		
		// ���û���������Ժ󣬼��㻨�˶���ʱ��
		// ��ʱ�и�
		if( myTimer.isOutOfTime() || plNum != comNum )
		{
			printf( "��Ϸ������\n" );
			printf( "�����ܷ�Ϊ:%d\n", score );

			system( "pause" );
			system( "cls" );
			break;
		}
		else
		{
			printf( "��ϲ�� ��һ�ּ�����ʼ\n" );

			system( "pause" );
			system( "cls" );

			// ���ü�ʱ��
			myTimer.moveTimer();
			curMaxTime -= ONE_TIME_OFFSET;
			myTimer.setMT( curMaxTime  );

			score += 10;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand( ( unsigned int )time(NULL) );
	sameWithMe();

	return 0;
}