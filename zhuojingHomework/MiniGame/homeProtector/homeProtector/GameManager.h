#ifndef GAMEMANAGER
#define GAMEMANAGER

class GameManager
{
public:
	GameManager(void);
	~GameManager(void);

	void init();
	bool update();
	bool render();

private:
	void _processInput();

	myMap *m_pMap;
	Sgge *m_pSgge;
	bool m_isRun;
};

#endif	// END GAMEMANAGER