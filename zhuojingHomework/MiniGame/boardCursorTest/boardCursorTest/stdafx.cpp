// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// boardCursorTest.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
//�����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
void gotoXY( int x, int y )
{
	COORD pos = { x*2, y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}

void hideConsoleCursor()
{
	CONSOLE_CURSOR_INFO cci = { 1, false };
	SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cci );
}
