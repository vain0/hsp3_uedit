/*===================================================================
CRegExpElementクラス
正規表現の要素クラス
===================================================================*/

#pragma once

#include "EditPosition.h"

class CRegExpElement
{
public:
	CRegExpElement();
	virtual ~CRegExpElement();

	bool Search(LinePt pStartLine,size_t nStartPos,CEditPosition *pEnd,LinePt pEndLine);
	virtual void ResetSearch(){}

protected:
	virtual bool SearchInner(LinePt pStartLine,size_t nStartPos,CEditPosition *pEnd,LinePt pEndLine) = 0;

public:

protected:
	typedef enum _tLoopType{
		LOOPTYPE_NONE,				//!< 繰り返しなし
		LOOPTYPE_LONG,				//!< 最長一致
		LOOPTYPE_SHORT,				//!< 最短一致
		LOOPTYPE_EQUALS,			//!< 数と一致したときのみ
	} tLoopType;
	
	tLoopType m_nLoopType;
};

/*[EOF]*/
