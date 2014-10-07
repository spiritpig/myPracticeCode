#ifndef AUTOTEXTUREMANAGER
#define AUTOTEXTUREMANAGER

class autoTextureManager
{
public:
	autoTextureManager(void);
	~autoTextureManager(void);

	static void create( Sgge *m_pEngine, char *filename );
	static void release( Sgge *m_pEngine );

	static PSTEXTURE getTexture()
	{
		return m_pTexture;
	}

private:
	static PSTEXTURE m_pTexture;
	static size_t m_useCount;
};

#endif	// END AUTOTEXTUREMANAGER
