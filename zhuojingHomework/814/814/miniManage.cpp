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
	// ������˶���ʱ�䣬ʱ�䵽�˾ͽ�����һ�׶�
	elpasedTime = GetTickCount() - startTime;
	if( elpasedTime >= STAGE_DURATION[curStage] )
	{
		++curStage;
		// ���һ���׶ζ������ˣ��Ǹý�����Ϸ��
		if( curStage >= MAX_STAGE )
		{
			isRun = false;

			system( "cls" );
			printf( "��ϲͨ��!\n" );
			system( "pause" );

			return;
		}
		else
		{
			startTime = GetTickCount();

			system( "cls" );
			printf( "��%d�׶�!\n", curStage+1 );
			system( "pause" );
		}
	}

	int rollNum = rand()%MONSTER_FINDPATH_BASE;
	vector2 monPos = monster.getPos(),
		  fmPos = fireMan.getPos();

	int nextDir = -1;

	// ���Ҫ�����������Թ���Ѱ·���ʵĻ���
	// С�ڵ��ڵ�ǰ�׶ε�Ѱ·���ʣ����ù���
	// ����һ�㣬ͨ��Ѱ·����ȡ��һ����λ��
	if( (float)rollNum/MONSTER_FINDPATH_BASE < MONSTER_FINDPATH_PERCENT[curStage] )
	{
		// ��������ǵ������·��
		// ��dirMap�ͻ��¼�ӹ��ﵽ���ǵ�·��
		// ��Ϊ��dirMap�м�¼���ǵ�ǰ�㵽ǰһ�����
		// ����
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
	// ���ӵ�������λ���غ�ʱ�����Ǿ�û��Ҫ���ӵ���
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