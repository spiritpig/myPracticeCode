// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// firstConsoleCpp.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
//�����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

int random( int min, int max )
{
	return rand()%( max - min + 1 ) + min;
}

// �ƶ�����̨���
void gotoxy( int x, int y )
{
	COORD pos = { 2*x, y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}
