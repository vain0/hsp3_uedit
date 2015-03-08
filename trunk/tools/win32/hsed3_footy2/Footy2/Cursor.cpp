/*===================================================================
CCursor�N���X
�J�[�\���Ǘ����s���܂��B
===================================================================*/

#include "Cursor.h"
#include "resource.h"

HCURSOR CCursor::m_hOnUrlCursor = NULL;
HCURSOR CCursor::m_hLineCountCursor = NULL;
HCURSOR CCursor::m_hIBeam = NULL;
HCURSOR CCursor::m_hArrowCursor = NULL;
HCURSOR CCursor::m_hUpDownCursor = NULL;
HCURSOR CCursor::m_hRightLeftCursor = NULL;

/*-------------------------------------------------------------------
CCursor::LoadCursors
�J�[�\�������[�h���܂��B
-------------------------------------------------------------------*/
bool CCursor::LoadCursors(HINSTANCE hInstance){
	if (!hInstance)return false;
	/*�J�[�\����j��*/
	DestroyCursors();
	/*�J�[�\���̓ǂݍ���*/
	m_hArrowCursor = LoadCursor(NULL,IDC_ARROW);
	m_hIBeam = LoadCursor(NULL,IDC_IBEAM);
	m_hUpDownCursor = LoadCursor(NULL,IDC_SIZENS);
	m_hRightLeftCursor = LoadCursor(NULL,IDC_SIZEWE);
	m_hOnUrlCursor = LoadCursor(NULL,IDC_ARROW);
	//m_hOnUrlCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDC_URL));
	if (!m_hOnUrlCursor)return false;
	m_hLineCountCursor = LoadCursor(NULL,IDC_ARROW);
	//m_hLineCountCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDC_LINE));
	if (!m_hLineCountCursor)return false;
	return true;
}

/*-------------------------------------------------------------------
CCursor::DestroyCursors
�J�[�\����j�����܂��B
-------------------------------------------------------------------*/
void CCursor::DestroyCursors(){
	/*�����Ń��[�h�����͔̂j�󂵂��Ⴄ��*/
	//SAFE_DELETEOBJECT(m_hOnUrlCursor);
	//SAFE_DELETEOBJECT(m_hLineCountCursor);
	/*���ʃI�u�W�F�N�g�͔j�󂵂���܂����ł���c*/
	m_hOnUrlCursor = NULL;
	m_hLineCountCursor = NULL;

	m_hIBeam = NULL;
	m_hArrowCursor = NULL;
	m_hUpDownCursor = NULL;
	m_hRightLeftCursor = NULL;
}

/*-------------------------------------------------------------------
CCursor::Use����
�e�J�[�\�����g�p���郋�[�`���ł��B
-------------------------------------------------------------------*/
void CCursor::UseArrow(){				/*�A���[�J�[�\�����g�p���܂��B*/
	SetCursor(m_hArrowCursor);	
}
void CCursor::UseIBeam(){				/*I�r�[���J�[�\�����g�p���܂��B*/
	SetCursor(m_hIBeam);
}
void CCursor::UseUrlCursor(){			/*URL�ɏ�����Ƃ��̃J�[�\�����g�p���܂��B*/
	SetCursor(m_hOnUrlCursor);
}
void CCursor::UseLineCount(){			/*�s�ԍ��\���̈�̃J�[�\�����g�p���܂��B*/
	SetCursor(m_hLineCountCursor);
}
void CCursor::UseUpDown(){			/*�s�ԍ��\���̈�̃J�[�\�����g�p���܂��B*/
	SetCursor(m_hUpDownCursor);
}
void CCursor::UseRightLeft(){			/*�s�ԍ��\���̈�̃J�[�\�����g�p���܂��B*/
	SetCursor(m_hRightLeftCursor);
}

/*[EOF]*/