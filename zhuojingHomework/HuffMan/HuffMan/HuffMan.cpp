// HuffMan.cpp : 定义控制台应用程序的入口点。
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
	// 求出所有编码的长度，并储存起来
	for ( int i=0; i<wplNum; ++i )
	{
		phfTable[i].c = phfEndTable[i].c;
		// 编码长度比层数少1，所以事先减1
		phfTable[i].length = -1;

		phuffNode = phfEndTable[i].leaf;
		while ( phuffNode != NULL )
		{
			++phfTable[i].length;

			phuffNode = phuffNode->parent;
		}
	}

	// 开始读取每个字符的哈弗曼编码
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
		printf( "参数不足！\n" );
		getchar();
		return 0;
	} 
	else
	{
		FILE *fp = fopen( argv[1], "rb" );
		if ( !fp )
		{
			printf( "无效的文件!\n" );
			return 0;
		}

		// 获取文件的字节数
		unsigned int fileLen = 0;
		fseek( fp, 0, SEEK_END );
		fileLen = ftell( fp );

		// 读取文件内容
		unsigned char *fileContent = new unsigned char[fileLen];
		fseek( fp, 0, SEEK_SET );
		fread( fileContent, sizeof(unsigned char), fileLen, fp );
		fclose( fp );

		// 统计0-255的权重
		int wplArray[256] = {0};
		for ( unsigned int i=0; i<fileLen; ++i )
		{
			++wplArray[fileContent[i]];
		}

		// 计算0-255之间出现的字符数
		int wplNum = 0;
		for ( unsigned int i=0; i<256; ++i )
		{
			if ( wplArray[i] > 0 )
			{
				++wplNum;
			}
		}

		// 填充哈弗曼数组，为建立哈弗曼树做准备，
		// 建立哈弗曼树时，需要对各字符的权重不断排序
		// 所以为了移动起来方便，建立一个哈弗曼数组
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

		// 对huffArray进行排序
		insertionSort( pHuffArray, wplNum );

		int firstValidNodeIndex = 0, hufEndTableIndex = 0;
		huffArrayNode hfTemp;
		huffmanNode *pLc = NULL, *pRc = NULL, 
					*pParent = NULL;
		HuffEndNodeData *pHuffEndNodeTable=new HuffEndNodeData[wplNum];
		while( firstValidNodeIndex < wplNum-1 )
		{
			// 建立左子树
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

			// 建立右子树
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

			// 对节点进行一轮插入排序
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
		
		// 创建编码文件,在文件名最后一个.之前插入_huf。 所以，
		// 源文件名长度加5
		char *destFilename = new char[strlen( argv[1] )+5];
		strcpy( destFilename, argv[1] );
		strcpy( getFileExtentsion(destFilename), "_huf" );
		strcat( destFilename, getFileExtentsion(argv[1]) );
		FILE *fDest = fopen( destFilename, "wb" );
		if ( !fDest )
		{
			printf( "编码文件创建失败！\n" );
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

		// 生成编码表
		HuffmanTableElement *pHuffCodeTable = new HuffmanTableElement[wplNum];
		createHuffmanTable( pHuffCodeTable, pHuffEndNodeTable, wplNum );
		SAFE_DELARR( pHuffEndNodeTable );

		// 写入编码后的内容
		// 编码表的第一个元素一定是，码长最长的。
		// 因为，我们是按照叶子节点的建立顺序记录叶子节点的地址
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
		// 写入编码内容
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

