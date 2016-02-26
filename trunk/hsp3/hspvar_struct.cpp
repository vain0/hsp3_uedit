
//
//	HSPVAR core module
//	onion software/onitama 2003/4
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hsp3code.h"
#include "hspvar_core.h"
#include "hsp3debug.h"

#include "strbuf.h"
#include "supio.h"

/*------------------------------------------------------------*/
/*
		HSPVAR core interface (struct)
*/
/*------------------------------------------------------------*/

struct StructMaster
{
	// 最初の null 要素の位置 (なければ pval->len[1])
	int i_first_null;
};

#define GetPtr(pdat) ((FlexValue *)(pdat))
#define GetMaster(pval) ((StructMaster *)(pval)->master)

// Core
static PDAT *HspVarStruct_GetPtr( PVal *pval )
{
	return (PDAT *)(( (FlexValue *)(pval->pt))+pval->offset);
}

int HspVarStruct_FirstNullElementIndex(PVal *pval)
{
	return GetMaster(pval)->i_first_null;
}

void HspVarStruct_OnElementModified(PVal *pval, int index)
{
	assert( pval->flag == HSPVAR_FLAG_STRUCT );
	FlexValue *fv = GetPtr(pval->pt);
	int& i_first_null = GetMaster(pval)->i_first_null;

	if ( fv[index].type == FLEXVAL_TYPE_NONE ) {
		if ( index < i_first_null ) { i_first_null = index; }
	} else {
		if ( index == i_first_null ) {
			// 次の null 要素の位置を探す
			int i = i_first_null + 1;
			for ( ; i < pval->len[1]; i++ ) {
				if ( GetPtr(pval->pt)[i].type == FLEXVAL_TYPE_NONE ) break;
			}
			i_first_null = i;
		}
	}
}

/*
static void *HspVarStruct_Cnv( const void *buffer, int flag )
{
	//		リクエストされた型 -> 自分の型への変換を行なう
	//		(組み込み型にのみ対応でOK)
	//		(参照元のデータを破壊しないこと)
	//
	throw HSPERR_INVALID_TYPE;
	return buffer;
}


static void *HspVarStruct_CnvCustom( const void *buffer, int flag )
{
	//		(カスタムタイプのみ)
	//		自分の型 -> リクエストされた型 への変換を行なう
	//		(組み込み型に対応させる)
	//		(参照元のデータを破壊しないこと)
	//
	throw HSPERR_INVALID_TYPE;
	return buffer;
}
*/

static void HspVarStruct_Free( PVal *pval )
{
	//		PVALポインタの変数メモリを解放する
	//
	int i;
	FlexValue *fv;
	if ( pval->mode == HSPVAR_MODE_MALLOC ) {

		code_delstruct_all( pval );					// デストラクタがあれば呼び出す

		fv = (FlexValue *)pval->pt;
		for(i=0;i<pval->len[1];i++) {
			if ( fv->type == FLEXVAL_TYPE_ALLOC ) sbFree( fv->ptr );
			fv++;
		}
		sbFree( pval->pt );
		sbFree( pval->master );
	}
	pval->mode = HSPVAR_MODE_NONE;
}


static void HspVarStruct_Alloc( PVal *pval, const PVal *pval2 )
{
	//		pval変数が必要とするサイズを確保する。
	//		(pvalがすでに確保されているメモリ解放は呼び出し側が行なう)
	//		(pval2がNULLの場合は、新規データ)
	//		(pval2が指定されている場合は、pval2の内容を継承して再確保)
	//
	int size;
	char *pt;
	if ( pval->len[1] < 1 ) pval->len[1] = 1;		// 配列を最低1は確保する
	size = pval->len[1] * sizeof(FlexValue);

	int old_size;
	if ( pval == pval2 ) {
		old_size = pval2->size;
		if ( size > STRBUF_BLOCKSIZE ) {
			size = (size > old_size ? size + size / 8 : old_size);
		}
		pt = sbExpand(pval->pt, size);
	} else {
		pt = sbAlloc(size);
		StructMaster *mas = (StructMaster *)sbAlloc(sizeof(StructMaster));

		if ( pval2 == NULL ) {
			old_size = 0;
			mas->i_first_null = 0;
		} else {
			old_size = pval2->size;
			memcpy(pt, pval2->pt, pval2->size);
			sbFree(pval->pt);
			*mas = *GetMaster(pval2);
		}

		pval->master = mas;
	}

	// 新規要素を初期化
	if ( size > old_size ) {
		memset(pt + old_size, 0, size - old_size);
		int index_new = old_size / sizeof(FlexValue);
		if ( index_new < GetMaster(pval)->i_first_null ) {
			GetMaster(pval)->i_first_null = index_new;
		}
	}

	pval->pt = pt;
	pval->size = size;
	pval->mode = HSPVAR_MODE_MALLOC;
}

/*
static void *HspVarStruct_ArrayObject( PVal *pval, int *mptype )
{
	//		配列要素の指定 (文字列/連想配列用)
	//
	throw( HSPERR_UNSUPPORTED_FUNCTION );
	return NULL;
}
*/

// Size
static int HspVarStruct_GetSize( const PDAT *pdat )
{
	//		(実態のポインタが渡されます)
	return sizeof(FlexValue);
}

// Using
static int HspVarStruct_GetUsing( const PDAT *pdat )
{
	//		(実態のポインタが渡されます)
	FlexValue *fv;
	fv = (FlexValue *)pdat;
	return fv->type;
}

// Set
static void HspVarStruct_Set( PVal *pval, PDAT *pdat, const void *in )
{
	FlexValue *fv;
	FlexValue *fv_src;
	fv = (FlexValue *)in;
	fv->type = FLEXVAL_TYPE_CLONE;
	fv_src = (FlexValue *)pdat;
	if ( fv_src->type == FLEXVAL_TYPE_ALLOC ) { sbFree( fv_src->ptr ); }
	memcpy( pdat, fv, sizeof(FlexValue) );
	//sbCopy( (char **)pdat, (char *)fv->ptr, fv->size );
	HspVarStruct_OnElementModified(pval, fv - GetPtr(pval->pt));
}

/*
// INVALID
static void HspVarStruct_Invalid( PDAT *pval, const void *val )
{
	throw( HSPERR_UNSUPPORTED_FUNCTION );
}
*/

static void *GetBlockSize( PVal *pval, PDAT *pdat, int *size )
{
	FlexValue *fv;
	fv = (FlexValue *)pdat;
	*size = fv->size;
	return (void *)(fv->ptr);
}

static void AllocBlock( PVal *pval, PDAT *pdat, int size )
{
}


/*------------------------------------------------------------*/

void HspVarStruct_Init( HspVarProc *p )
{
	p->Set = HspVarStruct_Set;
	p->GetPtr = HspVarStruct_GetPtr;
//	p->Cnv = HspVarStruct_Cnv;
//	p->CnvCustom = HspVarStruct_CnvCustom;
	p->GetSize = HspVarStruct_GetSize;
	p->GetUsing = HspVarStruct_GetUsing;
	p->GetBlockSize = GetBlockSize;
	p->AllocBlock = AllocBlock;

//	p->ArrayObject = HspVarStruct_ArrayObject;
	p->Alloc = HspVarStruct_Alloc;
	p->Free = HspVarStruct_Free;
/*
	p->AddI = HspVarStruct_Invalid;
	p->SubI = HspVarStruct_Invalid;
	p->MulI = HspVarStruct_Invalid;
	p->DivI = HspVarStruct_Invalid;
	p->ModI = HspVarStruct_Invalid;

	p->AndI = HspVarStruct_Invalid;
	p->OrI  = HspVarStruct_Invalid;
	p->XorI = HspVarStruct_Invalid;

	p->EqI = HspVarStruct_Invalid;
	p->NeI = HspVarStruct_Invalid;
	p->GtI = HspVarStruct_Invalid;
	p->LtI = HspVarStruct_Invalid;
	p->GtEqI = HspVarStruct_Invalid;
	p->LtEqI = HspVarStruct_Invalid;

	p->RrI = HspVarStruct_Invalid;
	p->LrI = HspVarStruct_Invalid;
*/
	p->vartype_name = "struct";				// タイプ名
	p->version = 0x001;					// 型タイプランタイムバージョン(0x100 = 1.0)
	p->support = HSPVAR_SUPPORT_STORAGE | HSPVAR_SUPPORT_FLEXARRAY | HSPVAR_SUPPORT_VARUSE;
										// サポート状況フラグ(HSPVAR_SUPPORT_*)
	p->basesize = sizeof(FlexValue);	// １つのデータが使用するサイズ(byte) / 可変長の時は-1
}

/*------------------------------------------------------------*/

