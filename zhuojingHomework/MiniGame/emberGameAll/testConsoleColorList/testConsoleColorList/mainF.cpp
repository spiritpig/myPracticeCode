#include "stdafx.h"
#include <math.h>

int main(void)
{
	Tab  myTab( 0, 0, GetStdHandle( STD_OUTPUT_HANDLE ) );
	myTab.outputList( true, 4 );

	while ( 1 )
	{
		myTab.moveListPos();
		myTab.updateList( true, 4 );
	}
	return 0;
}