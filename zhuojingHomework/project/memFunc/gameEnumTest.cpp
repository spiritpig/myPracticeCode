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
			printf( "游戏主菜单向上移动一\n" );
		}
		break;

	case 'S': case 's':
		{
			printf( "游戏主菜单向下移动一\n" );
		}
		break;

	case 'A': case 'a':
		{
			printf( "游戏主菜单向左移动一\n" );
		}
		break;

	case 'D': case 'd':
		{
			printf( "游戏主菜单向右移动一\n" );
		}
		break;

	case '\r':
		{
			printf( "进入游戏世界\n" );
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
			printf( "游戏世界向上移动一\n" );
		}
		break;

	case 'S': case 's':
		{
			printf( "游戏世界向下移动一\n" );
		}
		break;

	case 'A': case 'a':
		{
			printf( "游戏世界向左移动一\n" );
		}
		break;

	case 'D': case 'd':
		{
			printf( "游戏世界向右移动一\n" );
		}
		break;

	case '\r':
		{
			printf( "进入背包界面\n" );
			gs = STATE_PACK;
		}	
		break;

	case 27:
		{
			printf( "退回主菜单\n" );
			gs = STATE_GAME_MENU;
		}	
		break;

	case 'q': case 'Q':
		{
			printf( "退出游戏\n" );
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
			printf( "背包向上移动一\n" );
		}
		break;

	case 'S': case 's':
		{
			printf( "背包向下移动一\n" );
		}
		break;

	case 'A': case 'a':
		{
			printf( "背包向左移动一\n" );
		}
		break;

	case 'D': case 'd':
		{
			printf( "背包向右移动一\n" );
		}
		break;

	case 27:
		{
			printf( "退回游戏世界\n" );
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
				printf( "在游戏主菜单中:   " );
				processGameMenu( c, gs );
			}
			break;

		case STATE_GAME_WORLD:
			{
				printf( "在游戏世界中:     " );
				isExit = processGameWorld( c, gs );
			}
			break;

		case STATE_PACK:
			{
				printf( "在背包中:     " );
				processPack( c, gs );
			}
			break;
		}
	}

	return 0;
}