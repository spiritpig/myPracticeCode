#ifndef BASE_LIFE
#define BASE_LIFE

class iLife
{
public:
	iLife(void);
	virtual ~iLife();

	//virtual void attack() = 0;
	virtual void move() = 0;
	// ÌØ¼¼
	virtual void specialEffect() = 0;
	virtual lifeState& getState();

protected:
	lifeState m_lifeState;
};

#endif	// END BASE_LIFE
