#ifndef MYLIST
#define MYLIST

template<typename T>
struct listNode
{
	T data;
	listNode<T> *next;

	listNode() {}
};

template<typename T>
class linkedList
{
public:
	linkedList(void);
	~linkedList(void);

	size_t Length()const;  
	bool IsEmpty()const;	bool Insert(size_t index, const T &data);	bool Delete(size_t index, T &data);	int  Search(const T &data, int time) const; 	// 在链表中，查询第time个值为data的元素是否存在	bool Find(T &data, int time);
private:
	listNode<T> *m_pHead, *m_pEnd,
		*m_pRear, *m_pTemp;

	size_t size;
};

#endif	// END MYLIST
