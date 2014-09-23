/*
 *  ˵���� emberManager�࣬ ������emberС��Ϸ�Ĺ�����Ա
 *
 *  ���ڣ� 2014.7.31
 *  ���ߣ� pinkbeen
 */
#ifndef EMBER_MANAGER
#define EMBER_MANAGER

#include "commonHeader.h"

class emberManager
{
	emberMap	myMap;
	monster		evil;
	player		ember;
	bool		isFight;
	Tab			fightTab;

	/**
	 *	  ���ƹ�������ǵ�ս������
     *
     *	  ����
     *	        plName				��ҵ�����
     *	        plModelFileName		���ģ���ļ�������
	 *	        monName				���������
	 *	        monModelFileName	����ģ���ļ�������
	 */
	void drawFightScene( const player &pl,
						 const monster &mon );
public:

	/**
	 *	  ���캯��
     *
     *	  ����
	 *			plLi				��ҵ���Ϣ
     *	        plName				��ҵ�����
     *	        plModelFileName		���ģ���ļ�������
	 *			monLi				�������Ϣ
	 *	        monName				���������
	 *	        monModelFileName	����ģ���ļ�������
	 */
	emberManager( const lifeInfo &plLi, const char *plName, 
				  const char *plModelFileName, 
				  const lifeInfo &monLi, const char *monName, 
				  const char *monModelFileName );

	/**
	 *	  ���캯��
     *
     *	  ����
     *	        plName				��ҵ�����
     *	        plModelFileName		���ģ���ļ�������
	 *	        monName				���������
	 *	        monModelFileName	����ģ���ļ�������
	 */
	emberManager( const char *plName, 
				  const char *plModelFileName, 
				  const char *monName, 
				  const char *monModelFileName );

	/**
	 *	  ��������
	 *
	 */
	~emberManager()
	{
	}

	void update();
	void processInput();
	void draw_scene();
};

#endif // EMBER_MANAGER end