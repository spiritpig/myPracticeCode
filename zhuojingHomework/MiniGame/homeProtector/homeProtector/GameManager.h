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

	Sgge *m_pSgge;
	myMap *m_pMap;
	tower_Slipper *m_towerSlipper;
	bool m_isRun;
};

#endif	// END GAMEMANAGER