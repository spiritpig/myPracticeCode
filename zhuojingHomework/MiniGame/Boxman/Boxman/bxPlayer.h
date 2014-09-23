#ifndef BXPLAYER_AFX
#define BXPLAYER_AFX

class bxPlayer
{
public:
	bxPlayer();
	void init( int x, int y, int boxNum,
				bxBox *boxes );
	void update( MAPDATA md, char dir );
	void draw();

	const point & getPos()
	{
		return m_Pos;
	}

	const point & getPrevPos()
	{
		return m_PrevPos;
	}

private:
	void _processInput( MAPDATA md, char dir );
	bool _isBox( int px, int py );

	bxBox *m_Boxes;
	int m_BoxNum;
	point m_Pos, m_PrevPos;
};

#endif // END BXPLAYER_AFX