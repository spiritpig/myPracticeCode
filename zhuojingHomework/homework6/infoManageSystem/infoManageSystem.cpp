// infoManageSystem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct Data
{
	int num;
	int age;
	int year;
	int moth;
	int day;
	bool sex;
	char name[20];
	char zy[30];
	Data * Next;
};

struct FileData
{
	Data *pTail;	/* 指向最后一个元素的位置，方便插入元素 */
	Data *pHead;	/* 指向系统的头部，也就是头结点 */
};

//////////////////////////////////////////////////////////////////////////
//
// 函数前向声明
//
//////////////////////////////////////////////////////////////////////////
void createFileData(FileData *);							// 完成FileData的初始化(无数据的状态)
bool addData(FileData *, Data *);							// 向FileData中，添加数据
bool removeData(FileData *, int);							// 从FileData中，移除数据，以学号查询
bool removeData(FileData *, char *);						// 从FileData中，移除数据，以性命查询
bool findStuInfo(FileData *, int);							// 以学生的学号从FileData中，查找信息
bool findStuInfo(FileData *, char *);						// 以学生的名字从FileData中，查找信息
void deleteFileData(FileData *);							// 删除一个FileData
void displayAllData(FileData *);							// 显示所有的学生信息
void saveInfoIntoFile(FileData *);							// 储存当前的学生数据到文件中，方便下次的读取
void readInfoFromFile(FILE *, FileData *);					// 从文件中读取学生数据
bool isFileDataHaveData(FileData *);						// 检测FileData中是否已有数据

void showSystemDescription(FileData *);						// 显示关于系统本身的描述
void systemFunction_AddData(FileData *);					// 显示添加学生信息功能的描述
void systemFunction_RemoveData(FileData *);					// 显示移除学生信息功能的描述
void systemFunction_DisplayAllData(FileData *);				// 显示显示学生信息功能的描述
void systemFunction_FindStuInfo(FileData *);				// 显示查询学生功能的描述


//////////////////////////////////////////////////////////////////////////
//
// 函数的定义
//
//////////////////////////////////////////////////////////////////////////
void createFileData( FileData *pFd )
{
	Data *pHead = new Data();
	pHead->Next = NULL;

	// 为系统结构的变量赋初始值
	pFd->pHead = pHead;
	// 由于最开始没有数据，所以，pTail指向pHead
	pFd->pTail = pHead;
}

bool addData( FileData *pFd, Data *newData )
{ 
	if( !pFd )
	{
		return false;
	}

	Data *pCur = pFd->pHead->Next;
	bool isDuplicateData = false;

	while( pCur != NULL )
	{
		//  检测学号是否重复，重复的学号是不允许的。
		//  因为，它是一个唯一的标识符，不允许重复。
		if( pCur->num == newData->num )
		{
			isDuplicateData = true;
		}

		pCur = pCur->Next;
	}
	
	// 不重复才产生插入操作
	if( !isDuplicateData )
	{
		// 将新的节点链接到尾部去， 然后，将pTail指向新的尾巴
		pFd->pTail->Next = newData;
		pFd->pTail = newData;

		return true;
	}
	else
	{
		return false;
	}
}

bool removeData( FileData *pFd, int num )
{
	if( !isFileDataHaveData(pFd) )
	{
		return false;
	}

	Data *pCur = pFd->pHead->Next, 
		 *pPrev = pFd->pHead;
	while( pCur != NULL )
	{
		if( pCur->num == num )
		{
			// 将pCur从链中去除
			pPrev->Next = pCur->Next;
			return true;
		}
		pPrev = pCur;
		pCur = pCur->Next;
	}

	return false;
}

bool removeData( FileData *pFd, char *name )
{
	if( !isFileDataHaveData(pFd) )
	{
		return false;
	}


	Data *pCur = pFd->pHead->Next, 
		*pPrev = pFd->pHead;
	while( pCur != NULL )
	{
		if( pCur->name == name )
		{
			// 将pCur从链中去除
			pPrev->Next = pCur->Next;
			return true;
		}
		pPrev = pCur;
		pCur = pCur->Next;
	}

	return false;
}

// 查找学生信息，重载以学号查找
bool findStuInfo( FileData *pFd, int num )
{
	if( !isFileDataHaveData(pFd) )
	{
		return false;
	}

	Data *pCur = pFd->pHead->Next;
	while( pCur != NULL )
	{
		// 匹配学号，一旦查找到则输出该同学的
		// 完整信息
		if( pCur->num == num )
		{
			printf( "%d\t%d\t%d\\%d\\%d\t%d\t%s\t%s\n",
				pCur->num, pCur->age, pCur->year, 
				pCur->moth, pCur->day, pCur->sex,
				pCur->name, pCur->zy );

			return true;
		}

		pCur = pCur->Next;
	}

	return false;
}

// 查找学生信息，重载以名字查找
bool findStuInfo( FileData *pFd, char *name )
{
	if( !isFileDataHaveData( pFd ) )
	{
		return false;
	}

	Data *pCur = pFd->pHead->Next;
	while( pCur != NULL )
	{
		// 匹配姓名， 一旦查找到则输出该同学的
		// 完整信息
		if( strcmp( pCur->name, name ) )
		{
			printf( "%d\t%d\t%d\\%d\\%d\t%d\t%s\t%s\n",
				pCur->num, pCur->age, pCur->year, 
				pCur->moth, pCur->day, pCur->sex,
				pCur->name, pCur->zy );

			return true;
		}

		pCur = pCur->Next;
	}

	return false;
}

bool isFileDataHaveData( FileData *pFd )
{
	if( !( pFd->pHead->Next ) )
	{
		return false;
	}
	return true;

}

void displayAllData( FileData *pFd )
{
	if( !isFileDataHaveData( pFd ) )
	{
		printf( "系统中，无学生信息！\n" );
		return;
	}

	Data *pCur = pFd->pHead->Next;

	printf( "--------------------------学生信息表--------------------------\n\n" );
	printf( "学号\t年龄\t出生年月日\t性别\t名字\t专业\n" );
	while( pCur != NULL )
	{
		printf( "%d\t%d\t%d\\%d\\%d\t%d\t%s\t%s\n",
				pCur->num, pCur->age, pCur->year, 
				pCur->moth, pCur->day, pCur->sex,
				pCur->name, pCur->zy );

		pCur = pCur->Next;
	}
	printf( "\n" );
	printf( "--------------------------   结束   --------------------------\n" );
}

void deleteFileData( FileData *pFd )
{
	if( !pFd )
	{
		return;
	}

	Data *pCur = pFd->pHead->Next;
	Data *pNext;

	// 由于头部，并没有字符串数据，所以，需要先删除掉
	// 然后，其他的节点再统一的删除。
	delete pFd->pHead;

	while( pCur != NULL )
	{
		pNext = pCur->Next;

		// 删除所有动态分配出来的数据
		delete pCur;

		pCur = pNext;
	}
}	

void saveInfoIntoFile( FileData *pFd )
{
	// 对于没有数据的FileData没有存储的必要
	if( !isFileDataHaveData( pFd ) )
	{
		return;
	}

	int num = 0;

	// 使用二进制文件储存，不易被提取数据
	FILE *file;
	file = fopen( "ssi.dat", "wb" );

	Data *pCur = pFd->pHead->Next;
	while( pCur != NULL )
	{
		fwrite( pCur, sizeof(Data), 1, file );
		pCur = pCur->Next;
		++num;
	}

	printf( "储存了%d条记录\n", num );
}


void readInfoFromFile( FILE *fp, FileData *pFd )
{
	if( !fp )
	{
		return;
	}

	// 若fd为空，我们创建一个新的FileData
	if( !( pFd->pHead ) )
	{
		return;
	}

	int num = 0;
	while( !feof( fp ) )
	{
		Data *temp = new Data();
		temp->Next = NULL;

		if( !fread( temp, sizeof(Data), 1, fp ) )
		{
			break;
		}

		// 移动节点
		pFd->pTail->Next = temp;
		pFd->pTail = pFd->pTail->Next;

		num++;
	}

	printf( "读取了%d条记录\n", num );
}

void showSystemDescription()
{
	printf( " -------------------------------------------------------------------\n" );
	printf( "!                                                                   !\n" );
	printf( "!                           学生信息管理系统                        !\n" );
	printf( "!                                                                   !\n" );
	printf( " -------------------------------------------------------------------\n" );

	// 功能说明;
	printf( "输入数字键选择对应的操作,输入q(Q)退出系统：\n" );
	printf( "1、添加学生信息\n" );
	printf( "2、删除学生信息\n" );
	printf( "3、显示所有学生信息\n" );
	printf( "4、查询学生信息\n" );
}

void systemFunction_AddData( FileData *pFd )
{
	if( !pFd )
	{
		return;
	}

	Data *newData = new Data();
	newData->Next = NULL;

	// 输入信息数据
	printf( "请输入学生的 学号,年龄,出生年, 月, 日, 性别(0为男/1为女), 名字, 专业: \n" );
	printf( "逗号分隔开的数据请用空格隔开\n" );

	scanf( "%d", &(newData->num)  );
	scanf( "%d", &(newData->age)  );
	scanf( "%d", &(newData->year) );
	scanf( "%d", &(newData->moth) );
	scanf( "%d", &(newData->day)  );
	scanf( "%d", &(newData->sex)  );
	scanf( "%s",  newData->name   );
	scanf( "%s",  newData->zy     );
	
	// 完成最终的插入
	bool isSuccess = addData( pFd, newData );

	if( isSuccess )
	{
		printf( "插入成功!!!!!!!!!!!!!!!! \n" );
	}
	else
	{
		printf( "插入失败!!!!!!!!!!!!!!!! \n" );
	}
}

void systemFunction_RemoveData( FileData *pFd )
{
	if( !isFileDataHaveData( pFd ) )
	{
		return;
	}

	printf( "请输入要删除的学生学号或者姓名：\n" );

	char temp[30] = " ";
	scanf( "%s", temp );
	// atoi在失败时，会返回0，所以我们将用这个值进行检测
	int tempNum = atoi(temp);	

	bool isSuccess = false;
	// 根据输入的数据选择调用哪一种重载类型
	if( tempNum != 0 )
	{
		isSuccess = removeData( pFd, tempNum );
	}
	else
	{
		isSuccess = removeData( pFd, temp );
	}

	// 报告删除的情况
	if( isSuccess )
	{
		printf( "删除成功!!!!!!!!!!!!!!!! \n" );
	}
	else
	{
		printf( "删除失败!!!!!!!!!!!!!!!! \n" );
	}
}


void systemFunction_DisplayAllData( FileData *pFd )
{
	displayAllData( pFd );
}

void systemFunction_FindStuInfo( FileData *pFd )
{
	if( !isFileDataHaveData( pFd ) )
	{
		return;
	}

	printf( "请输入要删除的学生学号或者姓名：\n" );

	char temp[30] = " ";
	scanf( "%s", temp );
	// atoi在失败时，会返回0，所以我们将用这个值进行检测
	int tempNum = atoi(temp);	

	bool isSuccess = false;
	// 根据输入的数据选择调用哪一种重载类型
	if( tempNum != 0 )
	{
		isSuccess = findStuInfo( pFd, tempNum );
	}
	else
	{
		isSuccess = findStuInfo( pFd, temp );
	}

	// 报告删除的情况
	if( isSuccess )
	{
		printf( "查找成功!!!!!!!!!!!!!!!! \n" );
	}
	else
	{
		printf( "查找失败!!!!!!!!!!!!!!!! \n" );
	}
}



//////////////////////////////////////////////////////////////////////////
//
//	程序的入口点,Main函数
//
//////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	FileData fd;
	createFileData( &fd );

	FILE *fp;
	fp = fopen( "ssi.dat", "rb" );

	if( fp )
	{
		createFileData( &fd );
		readInfoFromFile( fp, &fd );
	}

	// 进入系统的主循环
	char flag =  ' ';
	while ( flag != 'q' && flag != 'Q')
	{
		system( "cls" );
		// 显示系统描述
		showSystemDescription();
		scanf( "%c", &flag );

		system( "cls" );
		switch ( flag )
		{
		case '1':
			{
				systemFunction_AddData( &fd );
			}
			break;

		case '2':
			{
				systemFunction_RemoveData( &fd );
			}
			break;

		case '3':
			{
				systemFunction_DisplayAllData( &fd );
			}
			break;

		case '4':
			{
				systemFunction_FindStuInfo( &fd );
			}
			break;

		case 'q': case 'Q':
			{
				printf( "退出系统，谢谢使用! \n" );
			}
			break;

		default:
			{
				printf( "错误的字符，请重新输入! \n" );
			}
			break;
		}

		printf( "输入任意字符继续! \n" );
		getchar();
		//  清除缓冲区多余的字符
		while( getchar() != '\n' );
	}

	//displayAllData(&fd);
	saveInfoIntoFile( &fd );
	deleteFileData( &fd );
	return 0;
}

