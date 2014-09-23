#include "stdafx.h"

#ifndef BXMANAGER_AFX
#define BXMANAGER_AFX

class bxManager
{
public:
	bxManager();
	~bxManager();

	void init( const char *filename = "map.dat" );
	void update();
	void draw();
	void drawMap();
	void gameLoop();

private:
	void _redrawPos( const point &p );

	// ���ļ��ж�ȡ������
	// ��Щ���ݰ����� ��ͼ���֣�����λ�ã����λ��
	// Ŀ��ص㲢����Ҫ��¼��
	void _fillDataFromFile( const char *filename );
	bool _isWin();

	bool isRun;

	char **m_MapData;
	int m_MapCel, m_MapRow;
	int m_BoxNum, m_FinishedBoxNum;

	bxBox *m_Boxes;
	bxPlayer m_Hero;
};

#endif // END BXMANAGER_AFX