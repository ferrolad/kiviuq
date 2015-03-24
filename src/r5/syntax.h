/*
	$ [KiPHP] /r5/syntax.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 5

#ifndef _R5_SYNTAX_H_
#define _R5_SYNTAX_H_




/* ���� */

struct r5_syntax_token_o;

#define YYSTYPE		struct r5_syntax_token_o




/* ���ʶ���� */
#include "syntax/parser.yy.h"




/* �������� */
typedef	enum yytokentype	r5_syntax_token_type_e;




/* ���� */
typedef struct r5_syntax_token_o {
	r5_syntax_token_type_e		type;

	union {
		signed int	_integer;
		double		_float;
		STR1 *		_string;
	} v;
} r5_syntax_token_o, * r5_syntax_token_t;




/* �ʷ������� */

extern	FILE *	yyin;
extern	FILE *	yyout;

extern	int		yylex			(YYSTYPE *);
extern	int		yylex_destroy	(void);




/* �﷨������ */

extern	int		yyparse	(void);




extern	void *	r5_syntax_alloc		(size_t size);
extern	void *	r5_syntax_realloc	(void *p, size_t size);
extern	void 	r5_syntax_free		(void *p);




#endif

#endif