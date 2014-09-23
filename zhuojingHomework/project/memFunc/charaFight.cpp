#include "stdafx.h"

#define HEAL_RATIO 2
#define HEAL_MP_RECUDE  20

struct character
{
	int maxHp;
	int hp;
	int mp;
	int atk;
	int def;
	int mAtk;
	char name[12];

	bool isDef;
	bool isDead;
};



void physicalAttack( character &beAttacker, character &attacker )
{
	if( beAttacker.isDead )
	{
		printf( "%s ��������\n", beAttacker.name );
	}
	else
	{
		// Ϊ���ٴ洢һ�����������ǽ��������Ϊ����
		printf( "%s �˺��� %s����������, %s ��hp�� %d", 
			attacker.name, beAttacker.name, beAttacker.name, beAttacker.hp );

		int curDamage = 1;
		// �����µ�hpֵ
		if( !beAttacker.isDef )
		{
			curDamage = attacker.atk - beAttacker.def;
		}
		beAttacker.hp = beAttacker.hp - curDamage;


		// ������������HPΪ���������
		if( beAttacker.hp < 0 )
		{
			beAttacker.hp = 0;
			beAttacker.isDead = true;
		}
		printf( "��Ϊ%d\n", beAttacker.hp );

		// ȡ��������̬��������Ч
		if( attacker.isDef )
		{
			attacker.isDef = false;
			printf( "���� %s �����˹��������Է���״̬���\n" );
		}
	}
}

void defense( character &defender )
{
	defender.isDef = true;
	// Ϊ���ٴ洢һ�����������ǽ��������Ϊ����
	printf( "%s ���������̬�������������˺�����Ϊ1\n",  defender.name );
}

void heal( character &beHealer, character &healer )
{
	if(  healer.mp < HEAL_MP_RECUDE )
	{
		printf( "%s ��ħ��ֵ�����ˣ��޷�Ϊ %s ����",
			healer.name, beHealer.name );
		return;
	}

	// ���ƵĹ���
	printf( "%s Ϊ %s ����, %s ��hp�� %d", 
		healer.name, beHealer.name, beHealer.name, beHealer.hp );
	beHealer.hp += healer.mAtk * HEAL_RATIO;

	healer.mp -= HEAL_MP_RECUDE;
	if( healer.mp < 0 )
	{
		healer.mp = 0;
	}

	// ����hpֵ
	if( beHealer.hp > beHealer.maxHp )
	{
		beHealer.hp = beHealer.maxHp;
	}
	printf( "��Ϊ%d\n", beHealer.hp );
}

void lookupInfo( const character &victim, const character &peeper )
{
	printf( "%s ͵�� %s ����Ϣ\n", peeper.name, victim.name );

	// �ܺ��ߵľ�����Ϣ
	printf( "\t�������ֵ�� %d\n", victim.maxHp );
	printf( "\t����ֵ�� %d\n", victim.hp );
	printf( "\tħ��ֵ�� %d\n", victim.hp );
	printf( "\t�������� %d\n", victim.atk );
	printf( "\t�������� %d\n", victim.def );
	printf( "\tħ���������� %d\n", victim.mAtk );

	if( victim.isDef )
	{
		printf( "\t���ڷ���״̬\n" );
	}
	else
	{
		printf( "\tδ���ڷ���״̬\n" );
	}
}


void assignCharacter( character &ch1, const character &ch2 )
{
	ch1.atk = ch2.atk;
	ch1.def = ch2.def;
	ch1.hp = ch2.hp;
	ch1.mp = ch2.mp;
	ch1.mAtk = ch2.mAtk;
	ch1.maxHp = ch2.maxHp;

	strcpy( ch1.name, ch2.name );
	ch1.isDef = false;
	ch1.isDead = false;
}

void assignCharacter( character &ch1, const int &maxHp,
					  const int &hp,  const int &mp,
					  const int &atk, const int &def, 
					  const int &mAtk, const char *name )
{
	ch1.atk = atk;
	ch1.def = def;
	ch1.hp = hp;
	ch1.mp = mp;
	ch1.mAtk = mAtk;
	ch1.maxHp = maxHp;

	strcpy( ch1.name, name );  
	ch1.isDef = false;
	ch1.isDead = false;
}
//////////////////////////////////////////////////////////////////////////
//
//	���ͼ������
//
//////////////////////////////////////////////////////////////////////////
#define MAP_SIZE 20
#define MONSTER_CHAR	'M'
#define MONSTER_DEAD_CHAR 'D'
#define TRAP_CHAR		'T'
#define TRAP_HIT_CHAR	'I'
#define SPACE_CHAR		' '
#define HERO_CHAR		'H'
#define WALL_CHAR		'*'

#define MONSTER_DRAW_CHAR	"��"
#define TRAP_HIT_DRAW_CHAR	"��"
#define SPACE_DRAW_CHAR		"  "
#define HERO_DRAW_CHAR		"��"
#define WALL_DRAW_CHAR		"�~"

struct GameInfo
{
	char data[MAP_SIZE][MAP_SIZE];

	pos heroPos;
	character hero, monster, trapObj;
};


//////////////////////////////////////////////////////////////////////////
//
//	����������
//
//////////////////////////////////////////////////////////////////////////
bool isValidPos( const pos &p );
void initMap( GameInfo &gi );
void initGame( GameInfo &gi );
void move( pos &charaPos, char dir );
void collisionDetection( GameInfo &gi );
void processHitTrap( GameInfo &gi );
void processHitMonster( GameInfo &gi );
void putObjOnMap( GameInfo &gi, const int flag );
void draw( GameInfo &gi );
void drawHero( pos heroPos );
void drawMap( GameInfo &gi );




//////////////////////////////////////////////////////////////////////////
//
//	����������
//
//////////////////////////////////////////////////////////////////////////
bool isValidPos( const pos &p )
{
	return p.x > 0 && p.x < MAP_SIZE-1 &&
		   p.y > 0 && p.y < MAP_SIZE-1;
}

void putObjOnMap( GameInfo &gi, const int flag )
{
	int x = random( 1, MAP_SIZE-2 ),
		y = random( 1, MAP_SIZE-2 );
	// ������λ���Ƿ��Ѿ��й�����
	while( gi.data[y][x] != SPACE_CHAR )
	{
		x = random( 1, MAP_SIZE-2 );
		y = random( 1, MAP_SIZE-2 );
	}
	gi.data[y][x] = (char)flag;
}

void initMap( GameInfo &gi )
{
	// ��ʼ����ͼ�Ļ����ַ�
	for( int i = 0; i < MAP_SIZE; ++i )
	{
		for( int j = 0; j < MAP_SIZE; ++j )
		{
			if( i == 0 || j == 0 ||
				i == MAP_SIZE - 1 ||
				j == MAP_SIZE - 1 )
			{
				gi.data[i][j] = WALL_CHAR;
			}
			else
			{
				gi.data[i][j] = SPACE_CHAR;
			}
		}
	}
}

void initGame( GameInfo &gi )
{
	initMap( gi );

	int monNum = random( 10, 20 );
	// ���ɹ���
	for( int i = 0; i < monNum; ++i )
	{
		putObjOnMap( gi, MONSTER_CHAR );
	}

	int trapNum = random( 10, 20 );
	// ��������
	for( int i = 0; i < monNum; ++i )
	{
		putObjOnMap( gi, TRAP_CHAR );
	}
	
	// Ϊ�˴������ǵ�����ͬʱ��ϣ��������putObjOnMap�����Ŀ���
	// ����дһ�飬put�Ĺ���
	int x = random( 1, MAP_SIZE-2 ),
		y = random( 1, MAP_SIZE-2 );
	// ������λ���Ƿ��Ѿ��й�����
	while( gi.data[y][x] != SPACE_CHAR )
	{
		x = random( 1, MAP_SIZE-2 );
		y = random( 1, MAP_SIZE-2 );
	}
	gi.heroPos.x = x;
	gi.heroPos.y = y;

	// Ϊ��������Ǹ�ֵ
	assignCharacter( gi.hero, 1000, 1000, 
					200, 200, 50, 40, "С��" ); 
	assignCharacter( gi.monster, 200, 200,
					100, 70, 20, 20, "�粼��" ); 
	assignCharacter( gi.trapObj, 1, 1,
					1, 100, 0, 0, "��ը����" ); 
}

void move( pos &charaPos, char dir )
{
	pos p = { charaPos.x, charaPos.y };
	switch (dir)
	{
	case 'W': case 'w':
		{
			p.y -= 1;
		}
		break;

	case 'S': case 's':
		{
			p.y += 1;
		}
		break;

	case 'A': case 'a':
		{
			p.x -= 1;
		}
		break;

	case 'D': case 'd':
		{
			p.x += 1;
		}
		break;
	}

	// �������Ч��λ�ã��͸ı��ɫ��λ�á�
	if( isValidPos( p ) )
	{
		charaPos.x = p.x;
		charaPos.y = p.y;
	}
}

void collisionDetection( GameInfo &gi )
{
	switch( gi.data[gi.heroPos.y][gi.heroPos.x] )
	{
	case MONSTER_CHAR:
		{
			processHitMonster( gi );
		}
		break;

	case TRAP_CHAR:
		{
			processHitTrap( gi );
		}
		break;
	}
}

void processHitMonster( GameInfo &gi )
{
	system( "cls" );
	printf( "����������,��ʼս��\n" );
	// gi�еĹ�����Ϣ������ֻ��Ϊ��ȡ֮�ã�������Ϊ
	// �����Ĺ���
	character monster;
	assignCharacter( monster, gi.monster );

	while ( !gi.hero.isDead &&
			!monster.isDead )
	{
		// ͣ���û��๥���ĸо�������ʵ
		Sleep( 1000 );
		physicalAttack( gi.hero, monster );
		Sleep( 1000 );
		physicalAttack( monster, gi.hero );
	}

	if( !gi.hero.isDead )
	{
		printf( "%s��ʤ\n", gi.hero.name );
		// ��Ȼ�����Ѿ������ˣ��Ǿͽ���ͼ�е����λ�����
		gi.data[gi.heroPos.y][gi.heroPos.x] = MONSTER_DEAD_CHAR;
	}
	else
	{
		printf( "%sʧ���ˣ���Ϸ����\n", gi.hero.name );
	}

	system( "pause" );
}

void processHitTrap( GameInfo &gi )
{
	system( "cls" );
	printf( "�ȵ�������\n" );

	character trap;
	assignCharacter( trap, gi.trapObj );
	// ������˵��˺�����������������ģ��
	Sleep( 1000 );
	physicalAttack( gi.hero, trap );

	if( !gi.hero.isDead )
	{
		// ��Ȼ�����Ѿ������ˣ��Ǿͽ���ͼ�е����λ�����
		gi.data[gi.heroPos.y][gi.heroPos.x] = TRAP_HIT_CHAR;
	}
	else
	{
		printf( "%sʧ���ˣ���Ϸ����\n", gi.hero.name );
	}

	system( "pause" );
}

void drawHero( pos heroPos )
{
	gotoxy( heroPos.x, heroPos.y );
	printf( "%s", HERO_DRAW_CHAR );
}

void drawMap( GameInfo &gi )
{
	for ( int i = 0; i < MAP_SIZE; ++i )
	{
		for ( int j = 0; j < MAP_SIZE; ++j )
		{

			switch( gi.data[i][j] )
			{
			case SPACE_CHAR: 
			case TRAP_CHAR:
			case MONSTER_DEAD_CHAR:
				{
					printf( "%s", SPACE_DRAW_CHAR );
				}
				break;

			case WALL_CHAR:
				{
					printf( "%s", WALL_DRAW_CHAR );
				}
				break;

			case MONSTER_CHAR:
				{
					printf( "%s", MONSTER_DRAW_CHAR );
				}
				break;

			case TRAP_HIT_CHAR:
				{
					printf( "%s", TRAP_HIT_DRAW_CHAR );
				}
				break;

			default:
				break;
			}
		}
		printf( "\n" );
	}
}

void draw( GameInfo &gi )
{
	drawMap( gi );
	drawHero( gi.heroPos );
}

int main( void )
{
	character hero = { 1000, 1000, 200, 200, 50, 40, "С��", false, false }, 
			monster = { 200, 200, 100, 100, 20, 20, "�粼��", false, false }, 
			woman =  { 400, 400, 500, 100, 100, 200, "ҽ��MM", false, false };

	srand( ( unsigned )time( NULL ) );
	//physicalAttack( monster, hero );
	//physicalAttack( hero, monster );

	//defense( hero );
	//physicalAttack( hero, monster );

	//heal( hero, woman );

	//lookupInfo( monster, hero );

	GameInfo gi;
	initGame( gi );
	draw( gi );

	while ( !gi.hero.isDead )
	{
		Sleep( 200 );
		system( "cls" );

		if( kbhit() )
		{
			char dir = getch();
			move( gi.heroPos, dir );
			collisionDetection( gi );
		}
		
		draw( gi );
	}

	gotoxy( 0, MAP_SIZE + 2 );
	return 0;
}