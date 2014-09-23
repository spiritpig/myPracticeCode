/*
 *  ˵���� player�࣬ ����һ�����
 *
 *  ���ڣ� 2014.7.31
 *  ���ߣ� pinkbeen
 */
#ifndef PLAYER
#define PLAYER

#include "life.h"

class player : public life
{
public:
	/**
	 *	  ���캯��
     *
     *	  ����
     *	        li              ���������Ϣ
     *	        name            �����������
     *	        modelFileName   ģ���ļ�������
	 */
	player( const lifeInfo &li, const char *name, 
			const char *modelFileName )
		: life( li, name, modelFileName )
	{}

	/**
	 *	  ���캯��
     *
     *	  ����
     *	        name            �����������
     *	        modelFileName   ģ���ļ�������
	 */
	player( const char *name, const char *modelFileName )
		: life( name, modelFileName )
	{}

	
	/**
	 *	  ��������
	 *
	 */
	~player()
	{
	}

	/**
	 *	  ���ǿ������ʵ���ʱ������ս��
     *
	 */
	void runAway(){}

	/**
	 *	  ��ײ��ⲿ��
     *
     *	  ����
     *          pos         ��Ҫ���ĵ��λ��
     *          mapData     ��ͼ����
	 */
	bool isHitBuilding( const Point &pos, 
						const char * const mapData );
	bool isHitBuildingRoom( const Point &pos, 
							const char * const mapData );
	bool isHitGrass( const Point &pos, 
					 const char * const mapData );
	bool isHitRock( const Point &pos, 
					const char * const mapData );
	bool isHitMonster( const Point &pos, 
					   const char * const mapData );
	bool isHitBorder( const Point &pos, 
					  const char * const mapData );

	/**
	 *	  �����ƶ�
     *
     *	  ����
     *          mapData     ��ͼ���� 
     *          dir         ��Ҫ�ƶ��ķ���
     *
     *	  ����ֵ
     *          ������Ŀ�����
     *          CANNOT_MOVEABLE  �����ƶ������
     *          MOVEABLE         ���ƶ������
     *          HIT_ROOM         ��������
     *          HIT_MONSTER	     �����˹���
     *
	 */
	int move( const char * const mapData, char dir );


    //////////////////////////////////////////////////////////////////////
    //
    //  getter �� setter
    //
    //////////////////////////////////////////////////////////////////////
	void setPos( const int &x, const int &y )
	{
		state.pos.x = x;
		state.pos.y = y;
	}

	const Point & getPos()
	{
		return state.pos;
	}
};

#endif // PLAYER
