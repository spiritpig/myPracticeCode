/*
 *  ˵���� ����ͷ�ļ���ʵ���ļ�
 *
 *  ���ڣ� 2014.7.17
 *  ���ߣ� pinkbeen
 */
#include "commonHeader.h"

//---------------------------------------------------------------------------
void output2DArray( const char **a, int h, int w )
{
    for( int i = 0; i < h; ++i )
    {
        for( int j = 0; j < w; ++j )
        {
            cout << a[i][j];
        }
        cout << endl;
    }
}
//---------------------------------------------------------------------------
void gotoxy( const int x, const int y )
{
	COORD pos = { x,y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ),pos );
}
//---------------------------------------------------------------------------
int random( const int max, const int min )
{
	return rand()%( max - min ) + min;
}
