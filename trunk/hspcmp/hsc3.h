
//
//	hsc3.cpp structures
//
#ifndef __hsc3_h
#define __hsc3_h

#define HSC3TITLE "HSP script preprocessor"
#define HSC3TITLE2 "HSP code generator"

#define HSC3_OPT_NOHSPDEF 1
#define HSC3_OPT_DEBUGMODE 2
#define HSC3_OPT_MAKEPACK 4
#define HSC3_OPT_READAHT 8
#define HSC3_OPT_MAKEAHT 16
#define HSC3_OPT_UTF8IN 32		// UTF8�\�[�X�����
#define HSC3_OPT_UTF8OUT 64		// UTF8�R�[�h���o��

#define HSC3_MODE_DEBUG 1
#define HSC3_MODE_DEBUGWIN 2
#define HSC3_MODE_UTF8 4		// UTF8�R�[�h���o��

class CMemBuf;
class CToken;

/*
	rev 54
	lb_info �̌^�� void * ���� CLabel * �ɕύX�B

	hsc3.cpp:207
	mingw : warning : void * �^�� delete �͖���`
	�ɑΏ��B
*/

class CLabel;

// HSC3 class
class CHsc3 {
public:
	CHsc3();
	~CHsc3();
	char *GetError( void );
	int GetErrorSize( void );
	void ResetError( void );
	int PreProcess( char *fname, char *outname, int option, char *rname, void *ahtoption=NULL );
	int PreProcessAht( char *fname, void *ahtoption, int mode=0 );
	void PreProcessEnd( void );
	int Compile( char *fname, char *outname, int mode );
	void SetCommonPath( char *path );

	//		Service
	int MoveCmdListToErrorBuf();
	void GetCmdList( int option );
	void GetCmdList( CToken* tk, int option );
	int OpenPackfile( void );
	void ClosePackfile( void );
	void GetPackfileOption( char *out, char *keyword, char *defval );
	int GetPackfileOptionInt( char *keyword, int defval );
	int GetRuntimeFromHeader( char *fname, char *res );
	int SaveOutbuf( char *fname );
	int SaveAHTOutbuf( char *fname );

	//		Data
	//
	CMemBuf *symbuf;
	CMemBuf *errbuf;
	CMemBuf *pfbuf;
	CMemBuf *addkw;
	CMemBuf *outbuf;
	CMemBuf *ahtbuf;

private:
	//		Private Data
	//
	int process_option;
	void AddSystemMacros( CToken *tk, int option );

	char common_path[512];			// common path

	//		for Header info
	int hed_option;
	char hed_runtime[64];

	//		for Compile Optimize
	int cmpopt;
	CLabel *lb_info;
};


#endif