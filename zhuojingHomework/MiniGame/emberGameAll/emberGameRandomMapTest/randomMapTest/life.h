/*
 *  ˵���� life�࣬ ����һ���ɹ����ƶ�������
 *          ��Ϊ��������ǵĹ�������
 *
 *  ���ڣ� 2014.7.25
 *  ���ߣ� pinkbeen
 */
#include "commonHeader.h"

#ifndef LIFE
#define LIFE

struct lifeInfo
{
public:
	int atk, def;
	int hp, mp;
	int isDefense;

	float defPercent; // �����ʣ��ڷ�����̬�����ֵܵ����˺��ٷֱȡ�
	Point pos;

	char name[20];

public:

	/**
	 *	 ���캯��  
	 *
	 */
	lifeInfo( int iatk, 
			  int idef, 
			  int ihp, 
			  int imp, 
			  const char *iname );
	lifeInfo( const char *iname );
};

// ��������ǵĻ�����Ϣ
class life
{
protected:
	lifeInfo state;
	char model[5][6];									// ���ļ��ж�ȡ�ַ���ģ��
	Point modelSize;

	void initModel();

public:

	/**
	 *	 ���캯��  
	 *
	 */
	life( const lifeInfo &li,
		  const char *iname, 
		  const char *modelFileName );
	life( const char *iname, const char *modelFileName );

	/**
	 *	  ��ĳ����������й���
     *
     *	  ����
     *          l   ����Ҫ�����Ķ��� 
	 */
	virtual void attack( life &l );

	/**
	 *	  ���������������Ŀ��������
     *
	 */
	virtual void defense();

	/**
	 *	  ��������ܵķ�Ӧ������
     *	  ���ǣ���ͬ�����������ܵķ�ʽ�ǲ�ͬ��
     *
	 */
	virtual void runAway() = 0;


	// void releaseSkill(); ���Ǽ���
    
	/**
	 *	  ���ļ��ж�ȡģ����Ϣ
     *
     *	  ����
     *          filename   ģ���ļ��� 
	 *
	 *	  ģ���ļ�ͳһΪ5��5��
	 */
	void readModelFromFile( const char *filename );

	/**
	 *	  ����ģ��
     *
	 *	  ģ���ļ�ͳһΪ5��5��
	 */
	void drawModel( const int startX, const int startY );

	const Point& getModelSize()
	{
		return modelSize;
	}
};

#endif	// LIFE
