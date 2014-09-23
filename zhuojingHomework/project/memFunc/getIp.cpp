#include "stdafx.h"

union IP
{
	unsigned char sData[4];// sIP
	unsigned int iData;	   // iIP
};

int main( void )
{
	IP myIp={ { 1, 1, 1, 1 } };

	int temp[4] = {0};
	scanf( "%d.%d.%d.%d", &temp[0], &temp[1], &temp[2], &temp[3] );

	for ( int i = 0; i < 4; ++i )
	{
		myIp.sData[i] = temp[i];
	}

	printf( "IP: %d.%d.%d.%d\n", myIp.sData[0], myIp.sData[1],
				   				 myIp.sData[2], myIp.sData[3] );
	printf( "0X%X\n", myIp.iData );

	return 0;
}
