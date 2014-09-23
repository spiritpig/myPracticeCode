// infoManageSystem.cpp : �������̨Ӧ�ó������ڵ㡣
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
	Data *pTail;	/* ָ�����һ��Ԫ�ص�λ�ã��������Ԫ�� */
	Data *pHead;	/* ָ��ϵͳ��ͷ����Ҳ����ͷ��� */
};

//////////////////////////////////////////////////////////////////////////
//
// ����ǰ������
//
//////////////////////////////////////////////////////////////////////////
void createFileData(FileData *);							// ���FileData�ĳ�ʼ��(�����ݵ�״̬)
bool addData(FileData *, Data *);							// ��FileData�У��������
bool removeData(FileData *, int);							// ��FileData�У��Ƴ����ݣ���ѧ�Ų�ѯ
bool removeData(FileData *, char *);						// ��FileData�У��Ƴ����ݣ���������ѯ
bool findStuInfo(FileData *, int);							// ��ѧ����ѧ�Ŵ�FileData�У�������Ϣ
bool findStuInfo(FileData *, char *);						// ��ѧ�������ִ�FileData�У�������Ϣ
void deleteFileData(FileData *);							// ɾ��һ��FileData
void displayAllData(FileData *);							// ��ʾ���е�ѧ����Ϣ
void saveInfoIntoFile(FileData *);							// ���浱ǰ��ѧ�����ݵ��ļ��У������´εĶ�ȡ
void readInfoFromFile(FILE *, FileData *);					// ���ļ��ж�ȡѧ������
bool isFileDataHaveData(FileData *);						// ���FileData���Ƿ���������

void showSystemDescription(FileData *);						// ��ʾ����ϵͳ���������
void systemFunction_AddData(FileData *);					// ��ʾ���ѧ����Ϣ���ܵ�����
void systemFunction_RemoveData(FileData *);					// ��ʾ�Ƴ�ѧ����Ϣ���ܵ�����
void systemFunction_DisplayAllData(FileData *);				// ��ʾ��ʾѧ����Ϣ���ܵ�����
void systemFunction_FindStuInfo(FileData *);				// ��ʾ��ѯѧ�����ܵ�����


//////////////////////////////////////////////////////////////////////////
//
// �����Ķ���
//
//////////////////////////////////////////////////////////////////////////
void createFileData( FileData *pFd )
{
	Data *pHead = new Data();
	pHead->Next = NULL;

	// Ϊϵͳ�ṹ�ı�������ʼֵ
	pFd->pHead = pHead;
	// �����ʼû�����ݣ����ԣ�pTailָ��pHead
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
		//  ���ѧ���Ƿ��ظ����ظ���ѧ���ǲ�����ġ�
		//  ��Ϊ������һ��Ψһ�ı�ʶ�����������ظ���
		if( pCur->num == newData->num )
		{
			isDuplicateData = true;
		}

		pCur = pCur->Next;
	}
	
	// ���ظ��Ų����������
	if( !isDuplicateData )
	{
		// ���µĽڵ����ӵ�β��ȥ�� Ȼ�󣬽�pTailָ���µ�β��
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
			// ��pCur������ȥ��
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
			// ��pCur������ȥ��
			pPrev->Next = pCur->Next;
			return true;
		}
		pPrev = pCur;
		pCur = pCur->Next;
	}

	return false;
}

// ����ѧ����Ϣ��������ѧ�Ų���
bool findStuInfo( FileData *pFd, int num )
{
	if( !isFileDataHaveData(pFd) )
	{
		return false;
	}

	Data *pCur = pFd->pHead->Next;
	while( pCur != NULL )
	{
		// ƥ��ѧ�ţ�һ�����ҵ��������ͬѧ��
		// ������Ϣ
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

// ����ѧ����Ϣ�����������ֲ���
bool findStuInfo( FileData *pFd, char *name )
{
	if( !isFileDataHaveData( pFd ) )
	{
		return false;
	}

	Data *pCur = pFd->pHead->Next;
	while( pCur != NULL )
	{
		// ƥ�������� һ�����ҵ��������ͬѧ��
		// ������Ϣ
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
		printf( "ϵͳ�У���ѧ����Ϣ��\n" );
		return;
	}

	Data *pCur = pFd->pHead->Next;

	printf( "--------------------------ѧ����Ϣ��--------------------------\n\n" );
	printf( "ѧ��\t����\t����������\t�Ա�\t����\tרҵ\n" );
	while( pCur != NULL )
	{
		printf( "%d\t%d\t%d\\%d\\%d\t%d\t%s\t%s\n",
				pCur->num, pCur->age, pCur->year, 
				pCur->moth, pCur->day, pCur->sex,
				pCur->name, pCur->zy );

		pCur = pCur->Next;
	}
	printf( "\n" );
	printf( "--------------------------   ����   --------------------------\n" );
}

void deleteFileData( FileData *pFd )
{
	if( !pFd )
	{
		return;
	}

	Data *pCur = pFd->pHead->Next;
	Data *pNext;

	// ����ͷ������û���ַ������ݣ����ԣ���Ҫ��ɾ����
	// Ȼ�������Ľڵ���ͳһ��ɾ����
	delete pFd->pHead;

	while( pCur != NULL )
	{
		pNext = pCur->Next;

		// ɾ�����ж�̬�������������
		delete pCur;

		pCur = pNext;
	}
}	

void saveInfoIntoFile( FileData *pFd )
{
	// ����û�����ݵ�FileDataû�д洢�ı�Ҫ
	if( !isFileDataHaveData( pFd ) )
	{
		return;
	}

	int num = 0;

	// ʹ�ö������ļ����棬���ױ���ȡ����
	FILE *file;
	file = fopen( "ssi.dat", "wb" );

	Data *pCur = pFd->pHead->Next;
	while( pCur != NULL )
	{
		fwrite( pCur, sizeof(Data), 1, file );
		pCur = pCur->Next;
		++num;
	}

	printf( "������%d����¼\n", num );
}


void readInfoFromFile( FILE *fp, FileData *pFd )
{
	if( !fp )
	{
		return;
	}

	// ��fdΪ�գ����Ǵ���һ���µ�FileData
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

		// �ƶ��ڵ�
		pFd->pTail->Next = temp;
		pFd->pTail = pFd->pTail->Next;

		num++;
	}

	printf( "��ȡ��%d����¼\n", num );
}

void showSystemDescription()
{
	printf( " -------------------------------------------------------------------\n" );
	printf( "!                                                                   !\n" );
	printf( "!                           ѧ����Ϣ����ϵͳ                        !\n" );
	printf( "!                                                                   !\n" );
	printf( " -------------------------------------------------------------------\n" );

	// ����˵��;
	printf( "�������ּ�ѡ���Ӧ�Ĳ���,����q(Q)�˳�ϵͳ��\n" );
	printf( "1�����ѧ����Ϣ\n" );
	printf( "2��ɾ��ѧ����Ϣ\n" );
	printf( "3����ʾ����ѧ����Ϣ\n" );
	printf( "4����ѯѧ����Ϣ\n" );
}

void systemFunction_AddData( FileData *pFd )
{
	if( !pFd )
	{
		return;
	}

	Data *newData = new Data();
	newData->Next = NULL;

	// ������Ϣ����
	printf( "������ѧ���� ѧ��,����,������, ��, ��, �Ա�(0Ϊ��/1ΪŮ), ����, רҵ: \n" );
	printf( "���ŷָ������������ÿո����\n" );

	scanf( "%d", &(newData->num)  );
	scanf( "%d", &(newData->age)  );
	scanf( "%d", &(newData->year) );
	scanf( "%d", &(newData->moth) );
	scanf( "%d", &(newData->day)  );
	scanf( "%d", &(newData->sex)  );
	scanf( "%s",  newData->name   );
	scanf( "%s",  newData->zy     );
	
	// ������յĲ���
	bool isSuccess = addData( pFd, newData );

	if( isSuccess )
	{
		printf( "����ɹ�!!!!!!!!!!!!!!!! \n" );
	}
	else
	{
		printf( "����ʧ��!!!!!!!!!!!!!!!! \n" );
	}
}

void systemFunction_RemoveData( FileData *pFd )
{
	if( !isFileDataHaveData( pFd ) )
	{
		return;
	}

	printf( "������Ҫɾ����ѧ��ѧ�Ż���������\n" );

	char temp[30] = " ";
	scanf( "%s", temp );
	// atoi��ʧ��ʱ���᷵��0���������ǽ������ֵ���м��
	int tempNum = atoi(temp);	

	bool isSuccess = false;
	// �������������ѡ�������һ����������
	if( tempNum != 0 )
	{
		isSuccess = removeData( pFd, tempNum );
	}
	else
	{
		isSuccess = removeData( pFd, temp );
	}

	// ����ɾ�������
	if( isSuccess )
	{
		printf( "ɾ���ɹ�!!!!!!!!!!!!!!!! \n" );
	}
	else
	{
		printf( "ɾ��ʧ��!!!!!!!!!!!!!!!! \n" );
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

	printf( "������Ҫɾ����ѧ��ѧ�Ż���������\n" );

	char temp[30] = " ";
	scanf( "%s", temp );
	// atoi��ʧ��ʱ���᷵��0���������ǽ������ֵ���м��
	int tempNum = atoi(temp);	

	bool isSuccess = false;
	// �������������ѡ�������һ����������
	if( tempNum != 0 )
	{
		isSuccess = findStuInfo( pFd, tempNum );
	}
	else
	{
		isSuccess = findStuInfo( pFd, temp );
	}

	// ����ɾ�������
	if( isSuccess )
	{
		printf( "���ҳɹ�!!!!!!!!!!!!!!!! \n" );
	}
	else
	{
		printf( "����ʧ��!!!!!!!!!!!!!!!! \n" );
	}
}



//////////////////////////////////////////////////////////////////////////
//
//	�������ڵ�,Main����
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

	// ����ϵͳ����ѭ��
	char flag =  ' ';
	while ( flag != 'q' && flag != 'Q')
	{
		system( "cls" );
		// ��ʾϵͳ����
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
				printf( "�˳�ϵͳ��ллʹ��! \n" );
			}
			break;

		default:
			{
				printf( "������ַ�������������! \n" );
			}
			break;
		}

		printf( "���������ַ�����! \n" );
		getchar();
		//  ���������������ַ�
		while( getchar() != '\n' );
	}

	//displayAllData(&fd);
	saveInfoIntoFile( &fd );
	deleteFileData( &fd );
	return 0;
}

