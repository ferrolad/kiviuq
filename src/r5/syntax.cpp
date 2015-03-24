/*
	$ [KiPHP] /r5/syntax.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			5

#include "../kiviuq.h"
#include "./syntax.h"




void *	r5_syntax_alloc		(size_t size)			{	return	M0::allocate	(size);			}
void *	r5_syntax_realloc	(void *p, size_t size)	{	return	M0::reallocate	(p, size);		}
void 	r5_syntax_free		(void *p)				{			M0::release		(p);			}




STK1<r2_code_t> *	r5_syntax::stack	= NULL;




void r5_syntax::begin (void) {
	// ��ʼ��ջ
	r5_syntax::stack	= new STK1<r2_code_t>;

	// �ض�����
	yyin	= O0::stream_in;
	yyout	= NULL;

	// ��ʼ���к�
	RCD4::line	= 1;
}


void r5_syntax::end (void) {
	// �ͷ�ջ
	delete r5_syntax::stack;

	yylex_destroy ( );
}


void r5_syntax::call (void) {
	if(yyparse ( ) != 0) {
		LDR0::die ( );
	}
}




void r5_syntax::execute (void) {
	// ִ�д���
	r5_syntax::begin	( );
	r5_syntax::call		( );
	r5_syntax::end		( );

	// �����ɵĴ����������
	BLD4::collect ( );
}


