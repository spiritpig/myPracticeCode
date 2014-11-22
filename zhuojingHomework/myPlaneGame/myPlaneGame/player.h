#include "commonHeader.h"

#ifndef PLAYER_AFX
#define PLAYER_AFX

class player
{
public:
	player(void);
	~player(void);

	void init();
	void update( float mapLen );
	void render( float mapLen );

private:
	void _processInput( float mapLen );
	void _adjustBulletPos( bulletState &blState, float mapLen );
	void _adjustDaodanPos( daodanState &ddState, float mapLen );

private:
	Sgge *m_pSgge;
	
	// 玩家数据集
	PSTEXTURE m_pPLTextrue;
	SggeSprite *m_pPLSpr;
	float m_plHeadScalePercent;
	playerState m_plData;

	// 子弹数据集
	PSTEXTURE m_pBLTextrue;
	SggeSprite *m_pBLSpr;
	bulletState m_blData[BULLET_ROW_NUM][BULLET_CEL_NUM];
	vector2d m_blPosOffset;
	float m_blSpaceTime;
	float m_blScalePercent;	

	// 导弹数据集合
	PSTEXTURE m_pDDTexture;
	SggeSprite *m_pDDSpr;
	daodanState m_ddData[MAX_DAODAN_NUM];
	vector2d m_ddPosOffset;
	float m_ddSpaceTime;
	float m_ddScalePercent;
};

#endif // END PLAYER_AFX