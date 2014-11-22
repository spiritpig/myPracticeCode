#ifndef MANAGE_AFX
#define MANAGE_AFX

class Manage
{
public:
	Manage();
	void init();
	bool update();
	bool render();
	~Manage();

private:
	void _processInput();
private:
	Sgge *m_pSgge;
	myMap m_gameMap;
	player m_hero;

	bool isRun;
};

#endif