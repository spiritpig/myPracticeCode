#include "stdafx.h"

bool isvector2Same( const vector2 &a, const vector2 &b )
{
	return (a.x == b.x) &&
		   (a.y == b.y);
}

miniManage::miniManage()
: monster( ROW+1 )
{
	curStage = 0;
	isRun = true;
	elpasedTime = 0;
	startTime = GetTickCount();
}

miniManage::~miniManage()
{
}

void miniManage::update()
{
	// 计算过了多少时间，时间到了就进入下一阶段
	elpasedTime = GetTickCount() - startTime;
	if( elpasedTime >= STAGE_DURATION[curStage] )
	{
		++curStage;
		// 最后一个阶段都结束了，是该结束游戏了
		if( curStage >= MAX_STAGE )
		{
			isRun = false;

			system( "cls" );
			printf( "恭喜通关!\n" );
			system( "pause" );

			return;
		}
		else
		{
			startTime = GetTickCount();

			system( "cls" );
			printf( "第%d阶段!\n", curStage+1 );
			system( "pause" );
		}
	}

	int rollNum = rand()%MONSTER_FINDPATH_BASE;
	vector2 monPos = monster.getPos(),
		  fmPos = fireMan.getPos();

	int nextDir = -1;

	// 如果要出来的数除以怪物寻路几率的基数
	// 小于等于当前阶段的寻路几率，则让怪物
	// 聪明一点，通过寻路器获取下一步的位置
	if( (float)rollNum/MONSTER_FINDPATH_BASE < MONSTER_FINDPATH_PERCENT[curStage] )
	{
		// 计算从主角到怪物的路径
		// 则dirMap就会记录从怪物到主角的路径
		// 因为，dirMap中记录的是当前点到前一个点的
		// 方向
		pfGuy.findPath( myMap.getMapData(), 
			fmPos, monPos );

		p2DArray dirMap = pfGuy.getDirMap();
		nextDir = dirMap[monPos.x][monPos.y];
	}
	monster.walk( myMap.getMapData(), nextDir );

	if( isEvilHitPlayer() ||
		monster.isBulletHitPlayer( fmPos ))
	{
		isRun = false;
	}
}

void miniManage::render()
{
	// 当子弹与怪物的位置重合时，我们就没必要画子弹了
	bool isCover = isvector2Same( monster.getPos(), monster.getBulletPos() );

	myMap.setPlayerData( fireMan.getPos() );
	myMap.setEvilData( monster.getPos() );
	if( !isCover )
	{
		myMap.setBulletData( monster.getBulletPos() );
	}

	myMap.draw();

	myMap.clearPlayerData( fireMan.getPos() );
	myMap.clearEvilData( monster.getPos() );
	if ( !isCover )
	{
		myMap.clearBulletData( monster.getBulletPos() );
	}
}

void miniManage::processInput()
{
	if ( _kbhit() )
	{
		char inputC = _getch();

		switch( inputC )
		{
		case 27:
			{
				isRun = false;
			}
			break;

		default:
			{
				fireMan.walk( myMap.getMapData(), inputC );
			}
			break;
		}
	}
}

void miniManage::gameLoop()
{
	while( isRun )
	{
		system( "cls" );

		update();
		processInput();
		render();
	}
}

bool miniManage::isEvilHitPlayer()
{
	return (fireMan.getPos().x == monster.getPos().x) &&
		   (fireMan.getPos().y == monster.getPos().y);
}