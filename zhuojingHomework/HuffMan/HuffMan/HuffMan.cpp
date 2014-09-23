// HuffMan.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>

const int codeBitArray[] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };

#define SAFE_DELETE(p) {if(p) {delete p;p=NULL;}}
#define SAFE_DELARR(p) {if(p) {delete []p;p=NULL;}}

struct huffmanNode
{
	char c;
	int weight;
	bool isRight;
	huffmanNode *parent;
	huffmanNode *left, *right;
};

struct huffArrayNode
{
	char c;
	int weight;
	huffmanNode *tree;
};

struct HuffmanTableElement
{
	char c;
	bool *coding;
	char length;
};

struct HuffEndNodeData
{
	char c;
	huffmanNode *leaf;
};

void createHuffmanTable( HuffmanTableElement *phfTable, 
						 const HuffEndNodeData * const phfEndTable, 
						 int wplNum )
{
	huffmanNode *phuffNode;
	// ������б���ĳ��ȣ�����������
	for ( int i=0; i<wplNum; ++i )
	{
		phfTable[i].c = phfEndTable[i].c;
		// ���볤�ȱȲ�����1���������ȼ�1
		phfTable[i].length = -1;

		phuffNode = phfEndTable[i].leaf;
		while ( phuffNode != NULL )
		{
			++phfTable[i].length;

			phuffNode = phuffNode->parent;
		}
	}

	// ��ʼ��ȡÿ���ַ��Ĺ���������
	for ( int j=0; j<wplNum; ++j )
	{
		phfTable[j].coding = new bool[phfTable[j].length];

		phuffNode = phfEndTable[j].leaf;
		for ( int k=phfTable[j].length-1; k>-1; --k )
		{
			phfTable[j].coding[k] = phuffNode->isRight;
			phuffNode = phuffNode->parent;
		}
	}
}

void deleteHuffCodeTable( HuffmanTableElement **pHuffCodeTable, int wplNum )
{
	for ( int i=0; i<wplNum; ++i )
	{
		if ( (*pHuffCodeTable)[i].coding )
		{
			SAFE_DELARR( (*pHuffCodeTable)[i].coding );
		}
	}
	SAFE_DELARR( *pHuffCodeTable );
}

void deleteHuffmanTree( huffmanNode *pRoot )
{
	if( pRoot->left != NULL )
	{
		return deleteHuffmanTree( pRoot->left );
	}
	if ( pRoot->right != NULL )
	{
		return deleteHuffmanTree( pRoot->right );
	}

	SAFE_DELETE( pRoot );
}

int getCodeIndex( HuffmanTableElement *pHuffTable, int wplNum, char c )
{
	for ( int i=0; i<wplNum; ++i )
	{
		if ( pHuffTable[i].c == c )
		{
			return i;
		}
	}

	return -1;
}

void insertionSort( huffArrayNode *hf, int n )
{
	huffArrayNode hfTemp;
	int j = 0;
	for ( int i=1; i<n; ++i )
	{
		hfTemp = hf[i];

		j = i-1;
		while( (j>-1) && (hf[j].weight > hfTemp.weight) )
		{
			hf[j+1] = hf[j];
			--j;
		}

		if ( j < i-1 )
		{
			hf[j+1] = hfTemp;
		}
	}
}

char* getFileExtentsion( const char * const filename )
{
	size_t fnIndex = strlen( filename )-1;
	while ( filename[fnIndex] != '.' )
	{
		--fnIndex;
	}

	return (char *)&(filename[fnIndex]);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if ( argc <= 1 )
	{
		printf( "�������㣡\n" );
		getchar();
		return 0;
	} 
	else
	{
		FILE *fp = fopen( argv[1], "rb" );
		if ( !fp )
		{
			printf( "��Ч���ļ�!\n" );
			return 0;
		}

		// ��ȡ�ļ����ֽ���
		unsigned int fileLen = 0;
		fseek( fp, 0, SEEK_END );
		fileLen = ftell( fp );

		// ��ȡ�ļ�����
		unsigned char *fileContent = new unsigned char[fileLen];
		fseek( fp, 0, SEEK_SET );
		fread( fileContent, sizeof(unsigned char), fileLen, fp );
		fclose( fp );

		// ͳ��0-255��Ȩ��
		int wplArray[256] = {0};
		for ( unsigned int i=0; i<fileLen; ++i )
		{
			++wplArray[fileContent[i]];
		}

		// ����0-255֮����ֵ��ַ���
		int wplNum = 0;
		for ( unsigned int i=0; i<256; ++i )
		{
			if ( wplArray[i] > 0 )
			{
				++wplNum;
			}
		}

		// �����������飬Ϊ��������������׼����
		// ������������ʱ����Ҫ�Ը��ַ���Ȩ�ز�������
		// ����Ϊ���ƶ��������㣬����һ������������
		huffArrayNode *pHuffArray = new huffArrayNode[wplNum];
		int j = 0;
		for ( unsigned int i=0; i<256; ++i )
		{
			if ( wplArray[i] > 0 )
			{
				pHuffArray[j].c = i;
				pHuffArray[j].tree = NULL;
				pHuffArray[j].weight = wplArray[i];
				++j;
			}
		}

		// ��huffArray��������
		insertionSort( pHuffArray, wplNum );

		int firstValidNodeIndex = 0, hufEndTableIndex = 0;
		huffArrayNode hfTemp;
		huffmanNode *pLc = NULL, *pRc = NULL, 
					*pParent = NULL;
		HuffEndNodeData *pHuffEndNodeTable=new HuffEndNodeData[wplNum];
		while( firstValidNodeIndex < wplNum-1 )
		{
			// ����������
			if ( pHuffArray[firstValidNodeIndex].tree == NULL )
			{
				pLc = new huffmanNode;
				pLc->c = pHuffArray[firstValidNodeIndex].c;
				pLc->isRight = false;
				pLc->left = NULL;
				pLc->right = NULL;
				pLc->parent = NULL;
				pLc->weight = pHuffArray[firstValidNodeIndex].weight;

				pHuffEndNodeTable[hufEndTableIndex].c = pLc->c;
				pHuffEndNodeTable[hufEndTableIndex].leaf = pLc;
				++hufEndTableIndex;
			}
			else
			{
				pLc = pHuffArray[firstValidNodeIndex].tree;
				pLc->isRight = false;
			}

			// ����������
			if ( pHuffArray[firstValidNodeIndex+1].tree == NULL )
			{
				pRc = new huffmanNode;
				pRc->c = pHuffArray[firstValidNodeIndex+1].c;
				pRc->isRight = true;
				pRc->left = NULL;
				pRc->right = NULL;
				pRc->parent = NULL;
				pRc->weight = pHuffArray[firstValidNodeIndex+1].weight;

				pHuffEndNodeTable[hufEndTableIndex].c = pRc->c;
				pHuffEndNodeTable[hufEndTableIndex].leaf = pRc;
				++hufEndTableIndex;
			}
			else
			{
				pRc = pHuffArray[firstValidNodeIndex+1].tree;
				pRc->isRight = true;
			}

			pParent = new huffmanNode;
			pParent->c = -1;
			pParent->isRight = false;
			pParent->left = pLc;
			pParent->right = pRc;
			pParent->parent = NULL;
			pParent->weight = pLc->weight + pRc->weight;

			pLc->parent = pParent;
			pRc->parent = pParent;

			++firstValidNodeIndex;
			pHuffArray[firstValidNodeIndex].weight = pParent->weight;
			pHuffArray[firstValidNodeIndex].tree = pParent;

			// �Խڵ����һ�ֲ�������
			int j = firstValidNodeIndex+1;
			hfTemp = pHuffArray[firstValidNodeIndex];
			while ( (j<wplNum) && (pHuffArray[j].weight < hfTemp.weight ) )
			{
				pHuffArray[j-1] = pHuffArray[j];
				++j;
			}

			if ( j > firstValidNodeIndex+1 )
			{
				pHuffArray[j-1] = hfTemp;
			}
		}
		huffmanNode *pRoot = pHuffArray[wplNum-1].tree;
		
		// ���������ļ�,���ļ������һ��.֮ǰ����_huf�� ���ԣ�
		// Դ�ļ������ȼ�5
		char *destFilename = new char[strlen( argv[1] )+5];
		strcpy( destFilename, argv[1] );
		strcpy( getFileExtentsion(destFilename), "_huf" );
		strcat( destFilename, getFileExtentsion(argv[1]) );
		FILE *fDest = fopen( destFilename, "wb" );
		if ( !fDest )
		{
			printf( "�����ļ�����ʧ�ܣ�\n" );
			return 0;
		}
		SAFE_DELETE( destFilename );

		fwrite( &fileLen, sizeof( unsigned int ), 1, fDest  );
		fwrite( &wplNum, sizeof( int ), 1, fDest );
		for ( int i=0; i<wplNum; ++i )
		{
			fwrite( &pHuffArray[i].c, sizeof( char ), 1, fDest );
			fwrite( &pHuffArray[i].weight, sizeof( int ), 1, fDest );
		}
		SAFE_DELARR( pHuffArray );

		// ���ɱ����
		HuffmanTableElement *pHuffCodeTable = new HuffmanTableElement[wplNum];
		createHuffmanTable( pHuffCodeTable, pHuffEndNodeTable, wplNum );
		SAFE_DELARR( pHuffEndNodeTable );

		// д�����������
		// �����ĵ�һ��Ԫ��һ���ǣ��볤��ġ�
		// ��Ϊ�������ǰ���Ҷ�ӽڵ�Ľ���˳���¼Ҷ�ӽڵ�ĵ�ַ
		unsigned int destFileLen = (fileLen%8 ? fileLen/8+1 : fileLen/8)*pHuffCodeTable[0].length;
		destFileLen = destFileLen < fileLen ? destFileLen : fileLen;
		unsigned char *destFileContent = new unsigned char[destFileLen];
		memset( destFileContent, 0, sizeof( unsigned char )*(destFileLen) );

		unsigned int totalMoveBit = 0,
					 totalMoveByte = 0,
					 curMoveBit = 0,
					 curCodeIndex = 0;
		unsigned int fI = 0;
		for ( fI; fI<fileLen; ++fI )
		{
			curCodeIndex = getCodeIndex( pHuffCodeTable, wplNum, fileContent[fI] );
			for ( int j=0; j<pHuffCodeTable[curCodeIndex].length; ++j )
			{
				totalMoveByte = totalMoveBit/8;
				curMoveBit = totalMoveBit%8;

				if ( pHuffCodeTable[curCodeIndex].coding[j] )
				{
					destFileContent[totalMoveByte] |= codeBitArray[curMoveBit];
				}

				++totalMoveBit;
			}
		}
		// д���������
		totalMoveByte += totalMoveBit<=0 ? 0 : 1;
		fwrite( destFileContent, totalMoveByte, sizeof(unsigned char), fDest );
		fwrite( &totalMoveBit, 1, sizeof(unsigned int), fDest );

		fclose( fDest );
		SAFE_DELARR( destFileContent );
		deleteHuffCodeTable( &pHuffCodeTable, wplNum );
		deleteHuffmanTree( pRoot );
		SAFE_DELARR( fileContent );
		return 0;
	}
}

