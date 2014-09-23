/*
 *  说明： life类的实现文件
 *
 *  日期： 2014.7.25
 *  作者： pinkbeen
 */
#include "commonHeader.h"

//---------------------------------------------------------------------------
lifeInfo::lifeInfo( int iatk, int idef, int ihp, int imp, const char *iname )
: atk( iatk ), def( idef ), hp( ihp ), 
	mp( imp ), defPercent( 0.7f ), isDefense( 0 )

{ 
	strcpy( name, iname );
	pos.x = 0;
	pos.y = 0;
}
//---------------------------------------------------------------------------
lifeInfo::lifeInfo( const char *iname )
: atk(0), def(0), hp(0), mp(0),
	defPercent( 0.7f ), isDefense( 0 )
{
	strcpy( name, iname );
	pos.x = 0;
	pos.y = 0;
}

//////////////////////////////////////////////////////////////////////////
//
//		life类成员函数，定义
//
//////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
life::life( const lifeInfo &li, 
			const char *iname, 
			const char *modelFileName )
			: state( li.atk, li.def, li.hp, li.mp, iname )
{
	modelSize.y = 5;
	modelSize.x = 5;

	readModelFromFile( modelFileName );
}
//---------------------------------------------------------------------------
life::life( const char *iname, 
		    const char *modelFileName )
			: state( 0, 0, 0, 0, iname )
{
	modelSize.y = 5;
	modelSize.x = 5;

	readModelFromFile( modelFileName );
}
//---------------------------------------------------------------------------
// 文件第一行会记录模型的高度，模型的宽度
void life::readModelFromFile( const char *filename )
{
	FILE *fp;
	fp  = fopen( filename, "r" );

	if( !fp )
	{
		printf( "%s打开出错！\n", filename );

		// 如果文件打开出错了，就填充空的吧。
		initModel();

		return;
	}

	int i = 0;
	while( !feof( fp ) )
	{
		// 由于temp中会把换行符也读取进来
		fgets( model[i], 100, fp );
		model[i][modelSize.x] = '\0';

		++i;
	}

	fclose( fp );
}
//---------------------------------------------------------------------------
void life::attack( life &l )
{
	// 不能同时进攻和防御
	state.isDefense = 0;

	float damPercent = 1 - l.state.defPercent * l.state.isDefense;

	l.state.hp -= (int)( state.atk * damPercent )- l.state.def;

	// 为负则置0
	l.state.hp = l.state.hp < 0 ? 0 : l.state.hp;
	printf( "evil hp: %d, hero hp : %d", l.state.hp, state.hp );
}
//---------------------------------------------------------------------------
// 防御模式下，防御值提升。
void life::defense()
{
	state.isDefense = 1;
}
//---------------------------------------------------------------------------
void life::initModel()
{
	for ( int i = 0; i < modelSize.y; ++i )
	{
		for ( int j = 0; j < modelSize.x; ++j )
		{
			model[i][j] = '*';
		}
	}
}
//---------------------------------------------------------------------------
void life::drawModel( const int startX, const int startY )
{
	for ( int i = 0; i < modelSize.y; ++i )
	{
		gotoxy( startX, startY + i );
		for ( int j = 0; j < modelSize.x; ++j )
		{
			printf( "%c",model[i][j] );
		}
	}
}
