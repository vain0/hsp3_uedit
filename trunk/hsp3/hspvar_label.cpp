
//
//	HSPVAR core module
//	onion software/onitama 2007/1
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hsp3code.h"
#include "hspvar_core.h"
#include "hsp3debug.h"
#include "hspvar_label.h"

#include "strbuf.h"
#include "supio.h"

/*------------------------------------------------------------*/
/*
		HSPVAR core interface (label)
*/
/*------------------------------------------------------------*/

#define GetPtr(pval) ((HSPVAR_LABEL *)pval)

// Core
static PDAT *HspVarLabel_GetPtr( PVal *pval )
{
	return (PDAT *)(( (HSPVAR_LABEL *)(pval->pt))+pval->offset);
}


static int GetVarSize( PVal *pval )
{
	//		PVALポインタの変数が必要とするサイズを取得する
	//		(sizeフィールドに設定される)
	//
	int size;
	size = pval->len[1];
	if ( pval->len[2] ) size*=pval->len[2];
	if ( pval->len[3] ) size*=pval->len[3];
	if ( pval->len[4] ) size*=pval->len[4];
	size *= sizeof(HSPVAR_LABEL);
	return size;
}


static void HspVarLabel_Free( PVal *pval )
{
	//		PVALポインタの変数メモリを解放する
	//
	if ( pval->mode == HSPVAR_MODE_MALLOC ) { sbFree( pval->pt ); }
	pval->pt = NULL;
	pval->mode = HSPVAR_MODE_NONE;
}


static void HspVarLabel_Alloc( PVal *pval, const PVal *pval2 )
{
	//		pval変数が必要とするサイズを確保する。
	//		(pvalがすでに確保されているメモリ解放は呼び出し側が行なう)
	//		(flagの設定は呼び出し側が行なう)
	//		(pval2がNULLの場合は、新規データ)
	//		(pval2が指定されている場合は、pval2の内容を継承して再確保)
	//
	int i,size;
	char *pt;
	HSPVAR_LABEL *fv;
	if ( pval->len[1] < 1 ) pval->len[1] = 1;		// 配列を最低1は確保する
	size = GetVarSize( pval );
	pval->mode = HSPVAR_MODE_MALLOC;
	pt = sbAlloc( size );
	fv = (HSPVAR_LABEL *)pt;
	for(i=0;i<(int)(size/sizeof(HSPVAR_LABEL));i++) { fv[i]=NULL; }
	if ( pval2 != NULL ) {
		memcpy( pt, pval->pt, pval->size );
		sbFree( pval->pt );
	}
	pval->pt = pt;
	pval->size = size;
}

// Size
static int HspVarLabel_GetSize( const PDAT *pval )
{
	return sizeof(HSPVAR_LABEL);
}

// Using
static int HspVarLabel_GetUsing( const PDAT *pdat )
{
	//		(実態のポインタが渡されます)
	return ( *pdat != NULL );
}

// SwapVar
static void HspVarLabel_SwapVar(PVal *pval, PDAT *pdat, PVal *pval2, PDAT *pdat2)
{
	myswap(*GetPtr(pdat), *GetPtr(pdat2));
}

// Set
static void HspVarLabel_Set( PVal *pval, PDAT *pdat, const void *in )
{
	*GetPtr(pdat) = *((HSPVAR_LABEL *)(in));
}

static void *GetBlockSize( PVal *pval, PDAT *pdat, int *size )
{
	*size = pval->size - ( ((char *)pdat) - pval->pt );
	return (pdat);
}

static void AllocBlock( PVal *pval, PDAT *pdat, int size )
{
}


/*------------------------------------------------------------*/

void HspVarLabel_Init( HspVarProc *p )
{
	p->Set = HspVarLabel_Set;
	p->SwapVar = HspVarLabel_SwapVar;
	p->GetPtr = HspVarLabel_GetPtr;
	p->GetSize = HspVarLabel_GetSize;
	p->GetUsing = HspVarLabel_GetUsing;
	p->GetBlockSize = GetBlockSize;
	p->AllocBlock = AllocBlock;

	p->Alloc = HspVarLabel_Alloc;
	p->Free = HspVarLabel_Free;

	p->vartype_name = "label";				// タイプ名
	p->version = 0x001;					// 型タイプランタイムバージョン(0x100 = 1.0)
	p->support = HSPVAR_SUPPORT_STORAGE | HSPVAR_SUPPORT_FLEXARRAY | HSPVAR_SUPPORT_VARUSE;
										// サポート状況フラグ(HSPVAR_SUPPORT_*)
	p->basesize = sizeof(HSPVAR_LABEL);	// １つのデータが使用するサイズ(byte) / 可変長の時は-1
}

/*------------------------------------------------------------*/

