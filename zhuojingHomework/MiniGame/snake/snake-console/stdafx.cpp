// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// firstConsoleCpp.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
//�����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
int random( int min, int max )
{
	return rand()%(max - min + 1) + min;
}
void gotoXY( const int x, const int y )
{
	COORD pos = { x*2, y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}

void clearInputCache()
{
	int c;
	while( ( c = getchar() ) != '\n' && c != EOF );
}

void changeTextColor( int color )
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}