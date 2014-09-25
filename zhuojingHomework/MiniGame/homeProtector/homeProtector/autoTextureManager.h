#ifndef AUTOTEXTUREMANAGER
#define AUTOTEXTUREMANAGER

class autoTextureManager
{
public:
	autoTextureManager(void);
	~autoTextureManager(void);

	void create( Sgge *m_pEngine, char *filename );
	void release( Sgge *m_pEngine );

	PSTEXTURE getTexture() const
	{
		return m_pTexture;
	}

private:
	PSTEXTURE m_pTexture;
	size_t m_useCount;
};

#endif	// END AUTOTEXTUREMANAGER
