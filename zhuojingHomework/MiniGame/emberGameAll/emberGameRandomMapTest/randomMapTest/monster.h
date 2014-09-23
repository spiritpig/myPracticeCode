/*
 *  ˵���� monster�࣬ ����һ������
 *
 *  ���ڣ� 2014.7.31
 *  ���ߣ� pinkbeen
 */

#ifndef MONSTER_M
#define MONSTER_M

#include "commonHeader.h"

class monster : public life
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
	monster( const lifeInfo &li, const char *name, 
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
	monster( const char *name, const char *modelFileName )
		: life( name, modelFileName )
	{}

	/**
	 *	  ��������
     *
	 */
	~monster()
	{
	}


	/**
	 *	  �����������ڳ�����ҽ�ɫ
     *
	 */
	void taunt()
	{
	}

	/**
	 *	  ���ܺ��������������
     *
	 */
	void runAway()
	{
	}
};

#endif	// MONSTER_M end