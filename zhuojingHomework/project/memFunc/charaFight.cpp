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
		printf( "%s 已死亡！\n", beAttacker.name );
	}
	else
	{
		// 为了少存储一个变量，我们将输出语句分为两段
		printf( "%s 伤害了 %s（物理攻击）, %s 的hp由 %d", 
			attacker.name, beAttacker.name, beAttacker.name, beAttacker.hp );

		int curDamage = 1;
		// 计算新的hp值
		if( !beAttacker.isDef )
		{
			curDamage = attacker.atk - beAttacker.def;
		}
		beAttacker.hp = beAttacker.hp - curDamage;


		// 修正被攻击者HP为负数的情况
		if( beAttacker.hp < 0 )
		{
			beAttacker.hp = 0;
			beAttacker.isDead = true;
		}
		printf( "变为%d\n", beAttacker.hp );

		// 取消防御姿态产生的特效
		if( attacker.isDef )
		{
			attacker.isDef = false;
			printf( "由于 %s 进行了攻击，所以防御状态解除\n" );
		}
	}
}

void defense( character &defender )
{
	defender.isDef = true;
	// 为了少存储一个变量，我们将输出语句分为两段
	printf( "%s 进入防御姿态，所有物理攻击伤害将变为1\n",  defender.name );
}

void heal( character &beHealer, character &healer )
{
	if(  healer.mp < HEAL_MP_RECUDE )
	{
		printf( "%s 的魔法值不足了，无法为 %s 治疗",
			healer.name, beHealer.name );
		return;
	}

	// 治疗的过程
	printf( "%s 为 %s 治疗, %s 的hp由 %d", 
		healer.name, beHealer.name, beHealer.name, beHealer.hp );
	beHealer.hp += healer.mAtk * HEAL_RATIO;

	healer.mp -= HEAL_MP_RECUDE;
	if( healer.mp < 0 )
	{
		healer.mp = 0;
	}

	// 修正hp值
	if( beHealer.hp > beHealer.maxHp )
	{
		beHealer.hp = beHealer.maxHp;
	}
	printf( "变为%d\n", beHealer.hp );
}

void lookupInfo( const character &victim, const character &peeper )
{
	printf( "%s 偷看 %s 的信息\n", peeper.name, victim.name );

	// 受害者的具体信息
	printf( "\t最大生命值： %d\n", victim.maxHp );
	printf( "\t生命值： %d\n", victim.hp );
	printf( "\t魔法值： %d\n", victim.hp );
	printf( "\t攻击力： %d\n", victim.atk );
	printf( "\t防御力： %d\n", victim.def );
	printf( "\t魔法攻击力： %d\n", victim.mAtk );

	if( victim.isDef )
	{
		printf( "\t处于防御状态\n" );
	}
	else
	{
		printf( "\t未处于防御状态\n" );
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
//	大地图定义区
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

#define MONSTER_DRAW_CHAR	"⊕"
#define TRAP_HIT_DRAW_CHAR	"◎"
#define SPACE_DRAW_CHAR		"  "
#define HERO_DRAW_CHAR		"の"
#define WALL_DRAW_CHAR		"▇"

struct GameInfo
{
	char data[MAP_SIZE][MAP_SIZE];

	pos heroPos;
	character hero, monster, trapObj;
};


//////////////////////////////////////////////////////////////////////////
//
//	函数声明区
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
//	函数定义区
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
	// 检测这个位置是否已经有怪物了
	while( gi.data[y][x] != SPACE_CHAR )
	{
		x = random( 1, MAP_SIZE-2 );
		y = random( 1, MAP_SIZE-2 );
	}
	gi.data[y][x] = (char)flag;
}

void initMap( GameInfo &gi )
{
	// 初始化地图的基本字符
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
	// 生成怪物
	for( int i = 0; i < monNum; ++i )
	{
		putObjOnMap( gi, MONSTER_CHAR );
	}

	int trapNum = random( 10, 20 );
	// 生成陷阱
	for( int i = 0; i < monNum; ++i )
	{
		putObjOnMap( gi, TRAP_CHAR );
	}
	
	// 为了储存主角的坐标同时不希望，家中putObjOnMap函数的开销
	// 单独写一遍，put的过程
	int x = random( 1, MAP_SIZE-2 ),
		y = random( 1, MAP_SIZE-2 );
	// 检测这个位置是否已经有怪物了
	while( gi.data[y][x] != SPACE_CHAR )
	{
		x = random( 1, MAP_SIZE-2 );
		y = random( 1, MAP_SIZE-2 );
	}
	gi.heroPos.x = x;
	gi.heroPos.y = y;

	// 为怪物和主角赋值
	assignCharacter( gi.hero, 1000, 1000, 
					200, 200, 50, 40, "小呆" ); 
	assignCharacter( gi.monster, 200, 200,
					100, 70, 20, 20, "哥布林" ); 
	assignCharacter( gi.trapObj, 1, 1,
					1, 100, 0, 0, "爆炸陷阱" ); 
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

	// 如果是有效的位置，就改变角色的位置。
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
	printf( "遇到怪物了,开始战斗\n" );
	// gi中的怪物信息，我们只作为读取之用，并不作为
	// 真正的怪物
	character monster;
	assignCharacter( monster, gi.monster );

	while ( !gi.hero.isDead &&
			!monster.isDead )
	{
		// 停顿让互相攻击的感觉更加真实
		Sleep( 1000 );
		physicalAttack( gi.hero, monster );
		Sleep( 1000 );
		physicalAttack( monster, gi.hero );
	}

	if( !gi.hero.isDead )
	{
		printf( "%s获胜\n", gi.hero.name );
		// 既然怪物已经死掉了，那就将地图中的这个位置清空
		gi.data[gi.heroPos.y][gi.heroPos.x] = MONSTER_DEAD_CHAR;
	}
	else
	{
		printf( "%s失败了，游戏结束\n", gi.hero.name );
	}

	system( "pause" );
}

void processHitTrap( GameInfo &gi )
{
	system( "cls" );
	printf( "踩到陷阱了\n" );

	character trap;
	assignCharacter( trap, gi.trapObj );
	// 陷阱对人的伤害我们用物理攻击进行模拟
	Sleep( 1000 );
	physicalAttack( gi.hero, trap );

	if( !gi.hero.isDead )
	{
		// 既然怪物已经死掉了，那就将地图中的这个位置清空
		gi.data[gi.heroPos.y][gi.heroPos.x] = TRAP_HIT_CHAR;
	}
	else
	{
		printf( "%s失败了，游戏结束\n", gi.hero.name );
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
	character hero = { 1000, 1000, 200, 200, 50, 40, "小呆", false, false }, 
			monster = { 200, 200, 100, 100, 20, 20, "哥布林", false, false }, 
			woman =  { 400, 400, 500, 100, 100, 200, "医生MM", false, false };

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