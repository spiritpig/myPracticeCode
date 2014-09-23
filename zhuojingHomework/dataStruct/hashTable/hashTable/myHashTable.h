#ifndef MYHASHTABLE
#define MYHASHTABLE

#define MAX_REPEAT_INFO 10

struct info
{
	int age;
	bool sex;
	char *name;
};

struct hashTableNode
{
	char key;
	info *pInfo[MAX_REPEAT_INFO];
	int finalValidInfoId;
	hashTableNode *next;
};

class myHashTable
{
public:
	myHashTable(void);
	~myHashTable(void);
};

#endif	// END MYHASHTABLE
