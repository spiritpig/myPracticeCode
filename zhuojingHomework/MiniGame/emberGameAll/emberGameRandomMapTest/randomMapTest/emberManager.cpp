/*
 *  说明： emberManager类的实现文件
 *
 *  日期： 2014.7.31
 *  作者： pinkbeen
 */

#include "commonHeader.h"

//---------------------------------------------------------------------------
emberManager::emberManager( const lifeInfo &plLi, const char *plName, 
						    const char *plModelFileName, 
							const lifeInfo &monLi, const char *monName, 
							const char *monModelFileName )
			:	ember( plLi, plName, plModelFileName ),
				evil( monLi, monName, monModelFileName ),
				isFight( false ), 
				fightTab( 0, 9, GetStdHandle( STD_OUTPUT_HANDLE ) )
{
	ember.setPos( myMap.getCurMapCenter().x, 
				  myMap.getCurMapCenter().y );
}
//---------------------------------------------------------------------------
emberManager::emberManager( const char *plName, 
						    const char *plModelFileName, 
							const char *monName, 
							const char *monModelFileName )
			:	ember( plName, plModelFileName ),
				evil( monName, monModelFileName ),
				isFight( false ),
				fightTab( 0, 8, GetStdHandle( STD_OUTPUT_HANDLE ) )
{
	ember.setPos( myMap.getCurMapCenter().x, 
				  myMap.getCurMapCenter().y );
}
//---------------------------------------------------------------------------
void emberManager::update()
{
	processInput();
	// 绘制合适的场景
	if( isFight )
	{
		drawFightScene( ember, evil );
		isFight = false;
	}
	else
	{
		draw_scene();
	}
}
//---------------------------------------------------------------------------
void emberManager::processInput()
{
	// 重置方向
	char dir = ' ';
	if( kbhit() )
	{
		dir = getch();

		int res = ember.move( myMap.getMap(), dir );
		if( res == MOVEABLE )
		{
			myMap.setHeroPos( ember.getPos() );
			myMap.moveMap( dir );
		}
		// 当碰到了怪物时，进入战斗画面
		else
		if( res == HIT_MONSTER )
		{
			isFight = true;
		}
		// 碰到了建筑物，显示建筑物内部的情况
		else
		if( res == HIT_ROOM )
		{
			/////////////
			/////////////
			/////////////
		}
	}
}
//---------------------------------------------------------------------------
void emberManager::draw_scene()
{
	// 输出地图
	myMap.draw();

	/////////////
	/////////////
	/////////////
}
//---------------------------------------------------------------------------
void emberManager::drawFightScene( const player &pl, const monster &mon )
{
	system( "cls" );
	printf( "进入战斗！！！\n" );
	system( "pause" );

	// 输出战斗画面
	system( "cls" );
	// 输出血条
	for( int i = 0; i < 2; ++i )
	{
		for ( int j = 0; j < 20; ++j )
		{
			printf( "-" );
		}
		printf( "\n" );
	}

	// 输出模型
	ember.drawModel( 2, 3 );
	// 控制下一个模型的输出区域
	evil.drawModel( ember.getModelSize().x + 6, 3 );

	// 输出选项卡
	fightTab.outputList( false, 1 );

	int tabNum = 0, fightInfoOffsetY = 0;
	while ( 1 )
	{
		tabNum = fightTab.moveListPos();
		fightTab.updateList( false, 1 );

		switch( tabNum )
		{
		case TABNUM_DEFENSE:
			{
				gotoxy( FIGHTINFO_START_OFFSETX, 
					FIGHTINFO_START_OFFSETY + fightInfoOffsetY );
				ember.defense();
				printf( "防御" );
				++fightInfoOffsetY;
			}
			break;

		case TABNUM_ATTACK:
			{
				gotoxy( FIGHTINFO_START_OFFSETX, 
					FIGHTINFO_START_OFFSETY + fightInfoOffsetY );
				ember.attack( evil );
				printf( "攻击" );
				++fightInfoOffsetY;
			}
			break;

		case TABNUM_RUNAWAY:
			{
				printf( "\n\n" );
				system( "pause" );
				return;
			}
			break;
		}

		fightInfoOffsetY %= FIGHTINFO_MAX_LINE;
	}

	return;
}
//---------------------------------------------------------------------------
