//////////////////////////////////////////////////////////////////////////
//
//	����С��Ϸ
//	by pinkbeen
//  2014.7.21
//
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <cstring>
#include <cctype>
#include <ctime>



//////////////////////////////////////////////////////////////////////////
//
//	������
//
//////////////////////////////////////////////////////////////////////////
#define QUESTION_MAX_NUM 4
#define ANSWER_MAX_NUM   8
// �������ձ�
#define RIGHTANSWER_ONCE			20		// ʹ��һ�δ�����⣬һ���Դ�����
#define RIGHTANSWER_TWICE			14
#define RIGHTANSWER_THIRD			10
#define RIGHTANSWER_FOUTH			7
#define RIGHTANSWER_FIFTH_OR_MORE	5		// ʹ����5�λ��߸������ɴ���



//////////////////////////////////////////////////////////////////////////
//
//	����������
//
//////////////////////////////////////////////////////////////////////////
bool haveDuplicateNum( int a, int b, int c )
{
	if( a == b || 
		b == c ||
		a == c )
	{
		return true;
	}
	return false;
}

void addScore( int *score, int time )
{
	switch( time )
	{
	case 1:
		{
			*score += RIGHTANSWER_ONCE;
		}
		break;

	case 2:
		{
			*score += RIGHTANSWER_TWICE;
		}
		break;

	case 3:
		{
			*score += RIGHTANSWER_THIRD;
		}
		break;

	case 4:
		{
			*score += RIGHTANSWER_FOUTH;
		}
		break;

	case 5: case 6: 
	case 7: case 8:
		{
			*score += RIGHTANSWER_FIFTH_OR_MORE;
		}
		break;
	}

}

//////////////////////////////////////////////////////////////////////////
//
// ��Ϸ���� ������Ϸ
//   ������ ����˼�壬���Ǹ����������û�����ʲô��
//			�û��������ɴλ�����в²⡣
//			ͬʱ������������ʾ�������û����˼���λ��,
//			���˼������֡�
//
//////////////////////////////////////////////////////////////////////////
void guessNumberGame()
{
	int score = 0;
	int qArr[3] = {0};
	int aArr[3] = {0};
	char temp[100] = " ";

	srand( (unsigned)time(NULL) );

	for( int qNum = 0; qNum < QUESTION_MAX_NUM; ++qNum)
	{
		qArr[0] = random( 0, 10 );
		qArr[1] = random( 0, 10 );
		qArr[2] = random( 0, 10 );
		// ����һ�����֣����ظ�
		while ( qArr[1] == qArr[0] )
		{
			qArr[1] = random( 0, 10 );
		} 
		while ( qArr[2] == qArr[1] || qArr[2] == qArr[0] ) 
		{
			qArr[2] = random( 0, 10 );
		}

		// ����г������
		//printf( "ԭ��Ϊ��%d%d%d\n", qArr[0], qArr[1], qArr[2] );

		// �����û����볢��һ������
		for( int aNum = 0; aNum < ANSWER_MAX_NUM; ++aNum )
		{
			// ����һ�����֣����ظ�
			while( true )
			{
				// ��ն�����ַ�
				printf( "������һ����λ������λ����Ϊ0��\n" );
				scanf( "%s", temp );
				while ( getchar() != '\n' );

				// ���û������˹������߷������ַ�ʱ����������
				if( strlen( temp ) > 3 || 
					!isdigit( temp[0] ) || 
					!isdigit( temp[1] ) || 
					!isdigit( temp[2] ) )
				{
					printf( "���벻����Ҫ������������\n" );
				}
				else
				{
					aArr[0] = temp[0] - '0';
					aArr[1] = temp[1] - '0';
					aArr[2] = temp[2] - '0';

					if( haveDuplicateNum( aArr[0], aArr[1], aArr[2] ) )
					{
						printf( "���ظ����֣�����������!\n" );
					}
					else
					{
						break;
					}
				}
			}
			
			// ����λ�õ���ȷ��
			int posRightNum = 0;
			for( int i = 0; i < 3; ++i )
			{
				if( qArr[i] == aArr[i] )
				{
					posRightNum++;
				}
			}

			// �ش���ȷ�ˣ�������һ�ֵĲ���
			if( posRightNum == 3 )
			{
				addScore( &score, aNum+1 );
				printf( "��ϲ�����ˣ���ǰ�ķ�Ϊ%d���������ǰ���ɣ�", score );

				system( "pause" );
				system( "cls" );
				break;
			}

			// �������ֵ���ȷ��
			int numRightNum = 0;
			for( int i = 0; i < 3; ++i )
			{
				for( int j = 0; j < 3; ++j )
				{
					// ƥ����ֱ������ȥ��
					if( qArr[i] == aArr[j] )
					{
						numRightNum++;
						break;
					}
				}
			}

			printf( "��ǰ��%d�⣬��%d�β�����λ�õ���ȷ���ǣ�%d\n", qNum+1, aNum+1, posRightNum );
			printf( "��ǰ��%d�⣬��%d�β��������ֵ���ȷ���ǣ�%d\n\n", qNum+1, aNum+1, numRightNum );
		}

		if( aNum >= QUESTION_MAX_NUM )
		{
			printf( "����ˣ���Ҫ����!\n" );
			getchar();
			system( "cls" );
		}
	}
	// �㱨���
	system( "cls" );
	printf( "���δ����㹲���%d��!\n", score );
}

int _tmain(int argc, _TCHAR* argv[])
{
	guessNumberGame();	

	return 0;
}