#include "stdafx.h"


enum GAME_STATE
{
	STATE_GAME_MENU,				
	STATE_GAME_WORLD,
	STATE_PACK
};

void processGameMenu( const char c, GAME_STATE &gs )
{
	switch( c )
	{
	case 'W': case 'w': 
		{
			printf( "��Ϸ���˵������ƶ�һ\n" );
		}
		break;

	case 'S': case 's':
		{
			printf( "��Ϸ���˵������ƶ�һ\n" );
		}
		break;

	case 'A': case 'a':
		{
			printf( "��Ϸ���˵������ƶ�һ\n" );
		}
		break;

	case 'D': case 'd':
		{
			printf( "��Ϸ���˵������ƶ�һ\n" );
		}
		break;

	case '\r':
		{
			printf( "������Ϸ����\n" );
			gs = STATE_GAME_WORLD;
		}	
		break;
	}
}

bool processGameWorld( const char c, GAME_STATE &gs )
{
	switch( c )
	{
	case 'W': case 'w':
		{
			printf( "��Ϸ���������ƶ�һ\n" );
		}
		break;

	case 'S': case 's':
		{
			printf( "��Ϸ���������ƶ�һ\n" );
		}
		break;

	case 'A': case 'a':
		{
			printf( "��Ϸ���������ƶ�һ\n" );
		}
		break;

	case 'D': case 'd':
		{
			printf( "��Ϸ���������ƶ�һ\n" );
		}
		break;

	case '\r':
		{
			printf( "���뱳������\n" );
			gs = STATE_PACK;
		}	
		break;

	case 27:
		{
			printf( "�˻����˵�\n" );
			gs = STATE_GAME_MENU;
		}	
		break;

	case 'q': case 'Q':
		{
			printf( "�˳���Ϸ\n" );
			return true;
		}
		break;
	}

	return false;
}

void processPack( const char c, GAME_STATE &gs )
{
	switch( c )
	{
	case 'W': case 'w':
		{
			printf( "���������ƶ�һ\n" );
		}
		break;

	case 'S': case 's':
		{
			printf( "���������ƶ�һ\n" );
		}
		break;

	case 'A': case 'a':
		{
			printf( "���������ƶ�һ\n" );
		}
		break;

	case 'D': case 'd':
		{
			printf( "���������ƶ�һ\n" );
		}
		break;

	case 27:
		{
			printf( "�˻���Ϸ����\n" );
			gs = STATE_GAME_WORLD;
		}	
		break;
	}
}

int main( void )
{
	GAME_STATE gs = STATE_GAME_MENU;
	bool isExit = false;
	char c;

	while( !isExit )
	{
		system( "cls" );
		c = _getch();
		
		switch ( gs )
		{
		case STATE_GAME_MENU:
			{
				printf( "����Ϸ���˵���:   " );
				processGameMenu( c, gs );
			}
			break;

		case STATE_GAME_WORLD:
			{
				printf( "����Ϸ������:     " );
				isExit = processGameWorld( c, gs );
			}
			break;

		case STATE_PACK:
			{
				printf( "�ڱ�����:     " );
				processPack( c, gs );
			}
			break;
		}
	}

	return 0;
}