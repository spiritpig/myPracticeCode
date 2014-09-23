/*
 *  ˵���� emberManager���ʵ���ļ�
 *
 *  ���ڣ� 2014.7.31
 *  ���ߣ� pinkbeen
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
	// ���ƺ��ʵĳ���
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
	// ���÷���
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
		// �������˹���ʱ������ս������
		else
		if( res == HIT_MONSTER )
		{
			isFight = true;
		}
		// �����˽������ʾ�������ڲ������
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
	// �����ͼ
	myMap.draw();

	/////////////
	/////////////
	/////////////
}
//---------------------------------------------------------------------------
void emberManager::drawFightScene( const player &pl, const monster &mon )
{
	system( "cls" );
	printf( "����ս��������\n" );
	system( "pause" );

	// ���ս������
	system( "cls" );
	// ���Ѫ��
	for( int i = 0; i < 2; ++i )
	{
		for ( int j = 0; j < 20; ++j )
		{
			printf( "-" );
		}
		printf( "\n" );
	}

	// ���ģ��
	ember.drawModel( 2, 3 );
	// ������һ��ģ�͵��������
	evil.drawModel( ember.getModelSize().x + 6, 3 );

	// ���ѡ�
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
				printf( "����" );
				++fightInfoOffsetY;
			}
			break;

		case TABNUM_ATTACK:
			{
				gotoxy( FIGHTINFO_START_OFFSETX, 
					FIGHTINFO_START_OFFSETY + fightInfoOffsetY );
				ember.attack( evil );
				printf( "����" );
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
