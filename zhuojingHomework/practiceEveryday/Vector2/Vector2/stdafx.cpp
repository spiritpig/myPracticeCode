// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// Vector2.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
//�����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
bool isFloatEqualToZero( float f )
{
	return ( f < precsion ) && 
		( f > -precsion );
}