// homework-825-duotai.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class role
{
public:
	virtual void render() = 0;
	virtual void update() = 0;

	int getY()
	{
		return y;
	}

protected:
	int x, y;
};

class hero : public role
{
public:
	hero();

	virtual void render();
	virtual void update();
};

hero::hero()
{
	x = 50;
	y = 50;
}

void hero::render()
{
	printf( "音箱在%d,%d处\n", x, y );
}

void hero::update()
{
	if( _kbhit() )
	{
		char dir = _getch();

		switch ( dir )
		{
		case 'w': case 'W':
			{
				--x;
			}
			break;

		case 's': case 'S':
			{
				++x;
			}	
			break;

		case 'a': case 'A':
			{
				--y;
			}
			break;

		case 'd': case 'D':
			{
				++y;
			}
			break;
		}
	}
}

class evil : public role
{
public:
	evil();

	virtual void render();
	virtual void update();

	void setId( int id )
	{
		eId = id;
	}

private:
	int eId;
};

evil::evil()
{
	x = 50;
	y = 200;

	eId = 0;
}

void evil::render()
{
	printf( "%d个 怪物在 %d,%d\n", eId, x, y );
}

void evil::update()
{
	if( rand()%2 )
	{
		--y;
	}
	else
	{
		++y;
	}
}

void selectSort( role **pRole, int n )
{
	role *swapR;
	for ( int i=0; i<n-1; ++i )
	{
		for ( int j=i+1; j<n; ++j )
		{
			if( pRole[i]->getY() < pRole[j]->getY() )
			{
				swapR = pRole[i];
				pRole[i] = pRole[j];
				pRole[j] = swapR;
			}
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	role *pRole[6];

	evil npc[5];
	hero man;
	for ( int i=0; i<5; ++i )
	{
		npc[i].setId( i );
		pRole[i] = &npc[i];
	}
	pRole[5] = &man;

	while (1)
	{
		selectSort( pRole, 6 );

		Sleep( 20 );
		system( "cls" );
		for ( int i=0; i<6; ++i )
		{
			pRole[i]->update();
			pRole[i]->render();
		}
	}

	return 0;
}

