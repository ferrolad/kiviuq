/*
	$ [KiPHP] /r5/syntax_parser.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			5

#include "../kiviuq.h"
#include "./syntax.h"
#include "./syntax_parser.h"




#define self			r5_syntax_parser


#define _I(t)			t->v._integer
#define _F(t)			t->v._float
#define _S(t)			t->v._string


#define CODE			(* RCD4::code)
#define STACK			(* r5_syntax::stack)

#define VAR(t, d, id)	RCD4::var->use (_S(t), & d->v._directive.operand_##id);


#ifdef _KI_MSC_
	#define L()						COD4::label		( )
	#define D(opcode, ...)			COD4::directive	(R2_CD_OPC_##opcode, __VA_ARGS__)
	#define O(var, id, ...)			COD4::operand	(& var->v._directive.operand_##id, __VA_ARGS__)
#else
	#define L()						COD4::label		( )
	#define D(opcode, ...a)			COD4::directive	(R2_CD_OPC_##opcode, ##a)
	#define O(var, id, ...a)		COD4::operand	(& var->v._directive.operand_##id, ##a)
#endif




void r5_syntax_parser::token_to_operand (r5_syntax_token_t token, r2_code_directive_operand_t operand) {
	switch(token->type) {
		case T_INTEGER:				operand->type	= R2_CD_OPND_INTEGER;		operand->v._integer		= _I(token);			break;
		case T_FLOAT:				operand->type	= R2_CD_OPND_FLOAT;			operand->v._float		= _F(token);			break;
		case T_STRING:				operand->type	= R2_CD_OPND_STRING;		operand->v._string		= _S(token);			break;
		case T_IDENTIFIER:			operand->type	= R2_CD_OPND_IDENTIFIER;	operand->v._string		= _S(token);			break;

		case T_CONSTANT_TRUE:		operand->type	= R2_CD_OPND_CONSTANT;		operand->v._constant	= R2_CD_OPND_CONSTANT_TRUE;			break;
		case T_CONSTANT_FALSE:		operand->type	= R2_CD_OPND_CONSTANT;		operand->v._constant	= R2_CD_OPND_CONSTANT_FALSE;		break;
		case T_CONSTANT_NULL:		operand->type	= R2_CD_OPND_CONSTANT;		operand->v._constant	= R2_CD_OPND_CONSTANT_NULL;			break;
		case T_CONSTANT_FUNCTION:	operand->type	= R2_CD_OPND_CONSTANT;		operand->v._constant	= R2_CD_OPND_CONSTANT_FUNCTION;		break;
		case T_CONSTANT_CLASS:		operand->type	= R2_CD_OPND_CONSTANT;		operand->v._constant	= R2_CD_OPND_CONSTANT_CLASS;		break;
		case T_CONSTANT_METHOD:		operand->type	= R2_CD_OPND_CONSTANT;		operand->v._constant	= R2_CD_OPND_CONSTANT_METHOD;		break;
		case T_CONSTANT_DIR:		operand->type	= R2_CD_OPND_CONSTANT;		operand->v._constant	= R2_CD_OPND_CONSTANT_DIR;			break;
		case T_CONSTANT_FILE:		operand->type	= R2_CD_OPND_CONSTANT;		operand->v._constant	= R2_CD_OPND_CONSTANT_FILE;			break;
	}
}




DEF_T2 (pragma) {
	// �ж��Ƿ�ر��˱�����ע��֧��
	if(C3(enable_pragma) == false) {
		RCD4::warning (true, "������ע��֧���ѱ����á��������ñ�����ע����ʹ�� -pragma-on ������");

		return;
	}

	switch(t1->type) {
		case T_PRAGMA_EXPORT:
			switch(t2->type) {
				case T_IDENTIFIER:		BLD4::function_export	(_S(t2));		break;
				case T_VARIABLE:		BLD4::variable_export	(_S(t2));		break;
			}

			break;

		case T_PRAGMA_ENCODE:
			switch(t2->type) {
				case T_CONSTANT_TRUE:		C3(enable_encode)	= true;			break;
				case T_CONSTANT_FALSE:		C3(enable_encode)	= false;		break;
			}

			break;

		case T_PRAGMA_INLINE:
			switch(t2->type) {
				case T_CONSTANT_TRUE:		C3(enable_inline)	= true;			break;
				case T_CONSTANT_FALSE:		C3(enable_inline)	= false;		break;
			}

			break;
			
		case T_PRAGMA_VM_WRAPPER:		r3_config::update_vm (R3_CONFIG_VM_WRAPPER,		_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_ENTRY:			r3_config::update_vm (R3_CONFIG_VM_ENTRY,		_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_HEAP:			r3_config::update_vm (R3_CONFIG_VM_HEAP,		_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_STACK:			r3_config::update_vm (R3_CONFIG_VM_STACK,		_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_TOP:			r3_config::update_vm (R3_CONFIG_VM_TOP,			_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_BOTTOM:		r3_config::update_vm (R3_CONFIG_VM_BOTTOM,		_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_EXCEPTION:		r3_config::update_vm (R3_CONFIG_VM_EXCEPTION,	_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_PROGRAM:		r3_config::update_vm (R3_CONFIG_VM_PROGRAM,		_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_RETURN:		r3_config::update_vm (R3_CONFIG_VM_RETURN,		_S(t2)->pointer ( ));		break;
		case T_PRAGMA_VM_MIDDLE:		r3_config::update_vm (R3_CONFIG_VM_MIDDLE,		_S(t2)->pointer ( ));		break;
	}
}




DEF_T1 (define_function_begin) {
	// �ж��Ƿ�Ϊ��ͨ����
	if(RCD4::cls == NULL) {
		// ��ת��� - ������������
		r2_code_t	jmp	= D (	JMP,	NULL	);

		CODE	+= jmp;
		STACK	+= jmp;
	} else {
		// �жϳ��󷽷�
		if(RCD4::class_feature->_abstract == true) {
			if(RCD4::cls->_abstract == false) {
				RCD4::error (true, "�� %s ���ڳ��󷽷� %s::%s������ʹ�� abstract �ؼ��ʶ���Ϊ�����ࡣ", RCD4::cls->name->pointer ( ), RCD4::cls->name->pointer ( ), _S(t1)->pointer ( ));
			}
		}
	}

	// ���뺯��
	BLD4::function_enter (_S(t1));

	// �ж��Ƿ�Ϊ�Ǿ�̬����, ע�� this ָ��
	if((RCD4::class_feature != NULL) && (RCD4::class_feature->_static == false)) {
		STR1		name	("%s",	"this");

		r2_code_t	code	= D (	THIS,	NULL	);

		RCD4::var->use (& name, & code->v._directive.operand_1);

		CODE	+= code;
	}
}


DEF_T1 (define_function_end) {
	// �ж��Ƿ�Ϊ���󷽷�
	if((RCD4::class_feature == NULL) || (RCD4::class_feature->_abstract == false)) {
		// �ж��Ƿ�ʵ���˺���
		if(t1 == NULL) {
			if(RCD4::cls == NULL) {
				RCD4::error (true, "û��ʵ�ֺ��� %s��", RCD4::function->name->pointer ( ));
			} else {
				RCD4::error (true, "û��ʵ�ַǳ��󷽷� %s::%s���ǳ��󷽷������ṩ�����塣", RCD4::cls->name->pointer ( ), RCD4::function->name->pointer ( ));
			}
		}
	} else {
		// �ж��Ƿ�δʵ�ַ���
		if(t1 != NULL) {
			RCD4::error (true, "ʵ���˳��󷽷� %s::%s�����󷽷�Ӧ��ֻ�з���ͷ��ǩ�������޷����塣", RCD4::cls->name->pointer ( ), RCD4::function->name->pointer ( ));
		}
	}

	CODE	+= D (	RETN,	NULL	);

	// �ж��Ƿ�Ϊ��ͨ����
	if(RCD4::cls == NULL) {
		// ��ת��� - ������������
		r2_code_t	jmp		= STACK [0];

		// �������������ǩ
		r2_code_t	label	= L ( );

		O (	jmp,	1,	"L",	label	);

		CODE	+= label;

		STACK	--;
	}

	// �˳�����
	BLD4::function_leave ( );
}


DEF_T1 (define_function_parameter_required) {
	// �ж��Ƿ�Ϊ���󷽷�
	if((RCD4::class_feature == NULL) || (RCD4::class_feature->_abstract == false)) {
		r2_code_t	mov		= D (	MOV,	NULL	);
		r2_code_t	mova	= D (	MOVA,	"@I",	RCD4::function->parameter_total	);

		VAR (	t1,		mov,	1	);
		VAR (	t1,		mova,	1	);

		CODE	+= D (	PUSH,	NULL	);
		CODE	+= mov;
		CODE	+= mova;
		CODE	+= D (	POP,	NULL	);
	}

	RCD4::function->parameter_total ++;
}


DEF_T1 (define_function_parameter_optional) {
	// �ж��Ƿ�Ϊ���󷽷�
	if((RCD4::class_feature == NULL) || (RCD4::class_feature->_abstract == false)) {
		r2_code_t	mov		= D (	MOV,	NULL									);
		r2_code_t	mova	= D (	MOVA,	"@I",	RCD4::function->parameter_total	);

		VAR (	t1,		mov,	1	);
		VAR (	t1,		mova,	1	);

		CODE	+= mov;
		CODE	+= mova;
	}

	CODE	+= D (	POP,	NULL	);

	RCD4::function->parameter_total ++;
	RCD4::function->parameter_optional ++;
}




DEF_T2 (define_class_begin) {
	// ������
	BLD4::class_enter (_S(t1));

	// ��������
	switch(t2->type) {
		case T_FINAL:		RCD4::cls->_final		= true;			break;
		case T_ABSTRACT:	RCD4::cls->_abstract	= true;			break;
	}
}


DEF_T0 (define_class_end) {
	// �˳���
	BLD4::class_leave ( );
}


DEF_T1 (define_class_extend) {
	RCD4::cls->_extend	= new STR1 (_S(t1));
}


DEF_T1 (define_class_implement) {
	BLD4::class_implement (_S(t1));
}


DEF_T1 (define_class_feature) {
	r2_class_feature_access_e	access	= R2_CLS_FTR_ACCESS_DEFAULT;

	switch(t1->type) {
		case T_PUBLIC:			access	= R2_CLS_FTR_ACCESS_PUBLIC;			break;
		case T_PROTECTED:		access	= R2_CLS_FTR_ACCESS_PROTECTED;		break;
		case T_PRIVATE:			access	= R2_CLS_FTR_ACCESS_PRIVATE;		break;

		case T_STATIC:
			if(RCD4::class_feature->_static == true) {
				RCD4::error (true, "���ʹ�� static �ؼ�������ͬһ�����Ա��");
			}

			RCD4::class_feature->_static	= true;

			break;

		case T_FINAL:
			if(RCD4::class_feature->_final == true) {
				RCD4::error (true, "���ʹ�� final �ؼ�������ͬһ�����Ա��");
			}
			if(RCD4::class_feature->_abstract == true) {
				RCD4::error (true, "ͬʱʹ�� final �ؼ��ʺ� abstract �ؼ�������ͬһ�����Ա�����Ա���ܼ����ռ������ǳ���ġ�");
			}

			RCD4::class_feature->_final	= true;

			break;

		case T_ABSTRACT:
			if(RCD4::class_feature->_abstract == true) {
				RCD4::error (true, "���ʹ�� abstract �ؼ�������ͬһ�����Ա��");
			}
			if(RCD4::class_feature->_final == true) {
				RCD4::error (true, "ͬʱʹ�� final �ؼ��ʺ� abstract �ؼ�������ͬһ�����Ա�����Ա���ܼ����ռ������ǳ���ġ�");
			}

			RCD4::class_feature->_abstract	= true;

			break;
	}

	if(access != R2_CLS_FTR_ACCESS_DEFAULT) {
		if(RCD4::class_feature->access != R2_CLS_FTR_ACCESS_DEFAULT) {
			RCD4::error (true, "���ʹ�����Ա���ʿ������η�����ͬһ�����Ա��");
		}

		RCD4::class_feature->access	= access;
	}
}


DEF_T0 (define_class_next) {
	// �������Ա����
	M0::zero (RCD4::class_feature, sizeof (r2_class_feature_o));
}


DEF_T2 (define_class_const) {
	r2_code_directive_operand_o	operand;

	self::token_to_operand (t2, & operand);

	BLD4::class_declare_const (_S(t1), & operand);
}


DEF_T2 (define_class_property) {
	// ��Ĭ��ֵ����
	if(t2 == NULL) {
		CODE	+= D (	PUSH,	NULL	);
	}

	// �ж��Ƿ�Ϊ��̬����
	if(RCD4::class_feature->_static == true) {
		STR1	name	("%s",	"self");

		CODE	+= D (	PUSH,	NULL						);
		CODE	+= D (	REF,	"DD",	& name,		_S(t1)	);
		CODE	+= D (	ASG,	NULL						);
	} else {
		if(t2 != NULL) {
			RCD4::warning (true, "������������Ľṹ���޷�ʵ��Ϊ�Ǿ�̬������ %s::$%s ����Ĭ��ֵ����Ϊ���׼ PHP ��һ�¡�����Ϊ�Ǿ�̬����������Ĭ��ֵ���뽫��ֵ���д���๹�췽���С�", RCD4::cls->name->pointer ( ), _S(t1)->pointer ( ));
		}
	}

	CODE	+= D (	POP,	NULL	);

	BLD4::class_declare_property (_S(t1));
}




DEF_T0 (statement_expression) {
	CODE	+= D (	POP,	NULL	);
}


DEF_T1 (statement_html) {
	CODE	+= D (	PUSH,	"S",	_S(t1)	);
	CODE	+= D (	ECHO,	NULL			);
	CODE	+= D (	POP,	NULL			);
}


DEF_T0 (statement_echo) {
	CODE	+= D (	ECHO,	NULL	);
	CODE	+= D (	POP,	NULL	);
}


DEF_T0 (statement_exit) {
	CODE	+= D (	EXIT,	NULL	);
}


DEF_T0 (statement_eval) {
	CODE	+= D (	EVAL,	NULL	);
	CODE	+= D (	POP,	NULL	);
}


DEF_T1 (statement_return) {
	if(t1 == NULL) {
		CODE	+= D (	PUSH,	NULL	);
	}

	CODE	+= D (	RET,	NULL	);
}


DEF_T2 (statement_static) {
	if(t2 == NULL) {
		CODE	+= D (	PUSH,	NULL	);
	}

	r2_code_t	ref		= D (	REF,	NULL	);

	if(RCD4::var->register_static (_S(t1), & ref->v._directive.operand_1, & ref->v._directive.operand_2) == true) {
		r2_code_t	mova	= D (	MOVA,	NULL	);

		M0::copy (& mova->v._directive.operand_1, & ref->v._directive.operand_2, sizeof (r2_code_directive_operand_o));

		CODE	+= ref;
		CODE	+= mova;
	} else {
		COD4::free (ref);
	}

	CODE	+= D (	POP,	NULL	);
}


DEF_T1 (statement_global) {
	r2_code_t	ref		= D (	REF,	NULL	);

	if(RCD4::var->register_global (_S(t1), & ref->v._directive.operand_1, & ref->v._directive.operand_2) == true) {
		CODE	+= ref;
	} else {
		COD4::free (ref);
	}
}




DEF_T1 (unset_variable) {
	r2_code_t	unset		= D (	UNSET,	NULL	);

	VAR (	t1,		unset,	1	);

	CODE	+= unset;
}


DEF_T1 (unset_array_begin) {
	r2_code_t	ref		= D (	REF,	NULL	);

	VAR (	t1,		ref,	1	);

	CODE	+= D (	PUSH,	NULL	);
	CODE	+= ref;
}


DEF_T0 (unset_array_end) {
	CODE	+= D (	UNSETK,	NULL	);
}


DEF_T0 (unset_array_shift) {
	CODE	+= D (	SHK,	NULL	);
	CODE	+= D (	POP,	NULL	);
}




DEF_T0 (exprlist_next) {
	CODE	+= D (	POP,	NULL	);
}


DEF_T0 (exprlist_empty) {
	CODE	+= D (	PUSH,	NULL	);
}




DEF_T0 (expr_silent_on) {
	CODE	+= D (	SLTON,	NULL	);
}


DEF_T0 (expr_silent_off) {
	CODE	+= D (	SLTOFF,	NULL	);
}




DEF_T1 (const_expression) {
	switch(t1->type) {
		case T_INTEGER:					CODE	+= D (	PUSH,	"I",	_I(t1)	);		break;
		case T_FLOAT:					CODE	+= D (	PUSH,	"F",	_F(t1)	);		break;
		case T_STRING:					CODE	+= D (	PUSH,	"S",	_S(t1)	);		break;
		case T_IDENTIFIER:				CODE	+= D (	PUSH,	"D",	_S(t1)	);		break;
			
		case T_CONSTANT_TRUE:			CODE	+= D (	PUSH,	"Ctrue"		);			break;
		case T_CONSTANT_FALSE:			CODE	+= D (	PUSH,	"Cfalse"	);			break;
		case T_CONSTANT_NULL:			CODE	+= D (	PUSH,	"Cnull"		);			break;
		case T_CONSTANT_DIR:			CODE	+= D (	PUSH,	"Cdir"		);			break;
		case T_CONSTANT_FILE:			CODE	+= D (	PUSH,	"Cfile"		);			break;

		case T_CONSTANT_FUNCTION:
			if(RCD4::function == NULL) {
				STR1	name;

				CODE	+= D (	PUSH,	"S",	& name					);
			} else {
				CODE	+= D (	PUSH,	"S",	RCD4::function->name	);
			}

			break;

		case T_CONSTANT_CLASS:
			if(RCD4::cls == NULL) {
				STR1	name;

				CODE	+= D (	PUSH,	"S",	& name				);
			} else {
				CODE	+= D (	PUSH,	"S",	RCD4::cls->name		);
			}

			break;

		case T_CONSTANT_METHOD:
			{
				STR1	name;

				if(RCD4::cls != NULL) {
					name	+= RCD4::cls->name;

					if(RCD4::function != NULL) {
						name	+= "::";
					}
				}

				if(RCD4::function != NULL) {
					name	+= RCD4::function->name;
				}

				CODE	+= D (	PUSH,	"S",	& name	);
			}

			break;
	}
}




DEF_T0 (array_build) {
	CODE	+= D (	PUSH,	NULL	);
	CODE	+= D (	ARRAY,	NULL	);
}


DEF_T0 (array_extend) {
	CODE	+= D (	PUSH,	NULL		);
	CODE	+= D (	REF,	"At",	-2	);
	CODE	+= D (	ASGE,	NULL		);
	CODE	+= D (	POP,	NULL		);
}


DEF_T1 (array_update) {
	CODE	+= D (	PUSH,	NULL		);
	CODE	+= D (	REF,	"At",	-2	);

	CALL (const_expression)	(t1);

	CODE	+= D (	SHK,	NULL		);
	CODE	+= D (	POP,	NULL		);
	CODE	+= D (	ASG,	NULL		);
	CODE	+= D (	POP,	NULL		);
}


