
//
//	HSPVAR core module
//	onion software/onitama 2003/4
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hsp3config.h"

#include "hspvar_core.h"
#include "hsp3debug.h"
#include "strbuf.h"
#include "supio.h"

/*------------------------------------------------------------*/
/*
		HSPVAR core interface (int)
*/
/*------------------------------------------------------------*/

#define GetPtr(pval) ((int *)pval)

static int conv;


// Core
static PDAT *HspVarInt_GetPtr( PVal *pval )
{
	return (PDAT *)(( (int *)(pval->pt))+pval->offset);
}

static void *HspVarInt_Cnv( const void *buffer, int flag )
{
	//		リクエストされた型 -> 自分の型への変換を行なう
	//		(組み込み型にのみ対応でOK)
	//		(参照元のデータを破壊しないこと)
	//
	switch( flag ) {
	case HSPVAR_FLAG_STR:
		if ( *(char *)buffer == '$' ) {					// 16->10進数
			conv = htoi( (char *)buffer );
		} else {
			conv = atoi( (char *)buffer );
		}
		return &conv;
	case HSPVAR_FLAG_INT:
		break;
	case HSPVAR_FLAG_DOUBLE:
		conv = (int)( *(double *)buffer );
		return &conv;
	default:
		throw HSPVAR_ERROR_TYPEMISS;
	}
	return (void *)buffer;
}

/*
static void *HspVarInt_CnvCustom( const void *buffer, int flag )
{
	//		(カスタムタイプのみ)
	//		自分の型 -> リクエストされた型 への変換を行なう
	//		(組み込み型に対応させる)
	//		(参照元のデータを破壊しないこと)
	//
	return buffer;
}
*/

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
	size *= sizeof(int);
	return size;
}


static void HspVarInt_Free( PVal *pval )
{
	//		PVALポインタの変数メモリを解放する
	//
	if ( pval->mode == HSPVAR_MODE_MALLOC ) { sbFree( pval->pt ); }
	pval->pt = NULL;
	pval->mode = HSPVAR_MODE_NONE;
}


static void HspVarInt_Alloc( PVal *pval, const PVal *pval2 )
{
	//		pval変数が必要とするサイズを確保する。
	//		(pvalがすでに確保されているメモリ解放は呼び出し側が行なう)
	//		(pval2がNULLの場合は、新規データ)
	//		(pval2が指定されている場合は、pval2の内容を継承して再確保)
	//
	int i,size;
	char *pt;
	int *fv;
	if ( pval->len[1] < 1 ) pval->len[1] = 1;		// 配列を最低1は確保する
	size = GetVarSize( pval );
	pval->mode = HSPVAR_MODE_MALLOC;
	pt = sbAlloc( size );
	fv = (int *)pt;
	for(i=0;i<(int)(size/sizeof(int));i++) { fv[i]=0; }
	if ( pval2 != NULL ) {
		memcpy( pt, pval->pt, pval->size );
		sbFree( pval->pt );
	}
	pval->pt = pt;
	pval->size = size;
}

/*
static void *HspVarInt_ArrayObject( PVal *pval, int *mptype )
{
	//		配列要素の指定 (文字列/連想配列用)
	//
	throw HSPERR_UNSUPPORTED_FUNCTION;
	return NULL;
}
*/

// Size
static int HspVarInt_GetSize( const PDAT *pval )
{
	return sizeof(int);
}

// Set
static void HspVarInt_Set( PVal *pval, PDAT *pdat, const void *in )
{
	*GetPtr(pdat) = *((int *)(in));
}

// SwapVar
static void HspVarInt_SwapVar(PVal *pval, PDAT *pdat, PVal *pval2, PDAT *pdat2)
{
	myswap(*GetPtr(pdat), *GetPtr(pdat2));
}

// Add
static void HspVarInt_AddI( PDAT *pval, const void *val )
{
	*GetPtr(pval) += *((int *)(val));
}


// Sub
static void HspVarInt_SubI( PDAT *pval, const void *val )
{
	*GetPtr(pval) -= *((int *)(val));
}

// Mul
static void HspVarInt_MulI( PDAT *pval, const void *val )
{
	*GetPtr(pval) *= *((int *)(val));
}

// Div
static void HspVarInt_DivI( PDAT *pval, const void *val )
{
	int p = *((int *)(val));
	if ( p == 0 ) throw( HSPVAR_ERROR_DIVZERO );
	*GetPtr(pval) /= p;
}

// Mod
static void HspVarInt_ModI( PDAT *pval, const void *val )
{
	int p = *((int *)(val));
	if ( p == 0 ) throw( HSPVAR_ERROR_DIVZERO );
	*GetPtr(pval) %= p;
}


// And
static void HspVarInt_AndI( PDAT *pval, const void *val )
{
	*GetPtr(pval) &= *((int *)(val));
}

// Or
static void HspVarInt_OrI( PDAT *pval, const void *val )
{
	*GetPtr(pval) |= *((int *)(val));
}

// Xor
static void HspVarInt_XorI( PDAT *pval, const void *val )
{
	*GetPtr(pval) ^= *((int *)(val));
}


// Eq
static void HspVarInt_EqI( PDAT *pval, const void *val )
{
	*GetPtr(pval) = ( *GetPtr(pval) == *((int *)(val)) );
}

// Ne
static void HspVarInt_NeI( PDAT *pval, const void *val )
{
	*GetPtr(pval) = ( *GetPtr(pval) != *((int *)(val)) );
}

// Gt
static void HspVarInt_GtI( PDAT *pval, const void *val )
{
	*GetPtr(pval) = ( *GetPtr(pval) > *((int *)(val)) );
}

// Lt
static void HspVarInt_LtI( PDAT *pval, const void *val )
{
	*GetPtr(pval) = ( *GetPtr(pval) < *((int *)(val)) );
}

// GtEq
static void HspVarInt_GtEqI( PDAT *pval, const void *val )
{
	*GetPtr(pval) = ( *GetPtr(pval) >= *((int *)(val)) );
}

// LtEq
static void HspVarInt_LtEqI( PDAT *pval, const void *val )
{
	*GetPtr(pval) = ( *GetPtr(pval) <= *((int *)(val)) );
}

// Rr
static void HspVarInt_RrI( PDAT *pval, const void *val )
{
	*GetPtr(pval) >>= *((int *)(val));
}

// Lr
static void HspVarInt_LrI( PDAT *pval, const void *val )
{
	*GetPtr(pval) <<= *((int *)(val));
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

void HspVarInt_Init( HspVarProc *p )
{
	p->Set = HspVarInt_Set;
	p->SwapVar = HspVarInt_SwapVar;
	p->Cnv = HspVarInt_Cnv;
	p->GetPtr = HspVarInt_GetPtr;
//	p->CnvCustom = HspVarInt_CnvCustom;
	p->GetSize = HspVarInt_GetSize;
	p->GetBlockSize = GetBlockSize;
	p->AllocBlock = AllocBlock;

//	p->ArrayObject = HspVarInt_ArrayObject;
	p->Alloc = HspVarInt_Alloc;
	p->Free = HspVarInt_Free;

	p->AddI = HspVarInt_AddI;
	p->SubI = HspVarInt_SubI;
	p->MulI = HspVarInt_MulI;
	p->DivI = HspVarInt_DivI;
	p->ModI = HspVarInt_ModI;

	p->AndI = HspVarInt_AndI;
	p->OrI  = HspVarInt_OrI;
	p->XorI = HspVarInt_XorI;

	p->EqI = HspVarInt_EqI;
	p->NeI = HspVarInt_NeI;
	p->GtI = HspVarInt_GtI;
	p->LtI = HspVarInt_LtI;
	p->GtEqI = HspVarInt_GtEqI;
	p->LtEqI = HspVarInt_LtEqI;

	p->RrI = HspVarInt_RrI;
	p->LrI = HspVarInt_LrI;

	p->vartype_name = "int";			// タイプ名
	p->version = 0x001;					// 型タイプランタイムバージョン(0x100 = 1.0)
	p->support = HSPVAR_SUPPORT_STORAGE | HSPVAR_SUPPORT_FLEXARRAY;
										// サポート状況フラグ(HSPVAR_SUPPORT_*)
	p->basesize = sizeof(int);			// １つのデータが使用するサイズ(byte) / 可変長の時は-1
}

/*------------------------------------------------------------*/

