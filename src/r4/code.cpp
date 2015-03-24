/*
	$ [KiPHP] /r4/code.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			4

#include "../kiviuq.h"




/* �����ַ����Ƚ� */
int r4_code::compare (const char *p1, const char *p2) {
	unsigned int	length	= strlen (p2);

	return strncmp (p1, p2, length);
}




/* �ͷŴ��� */
void r4_code::free (r2_code_t p) {
	// �ͷ��ڲ���Ϣ
	switch(p->type) {
		// ��ǩ
		case R2_CD_LABEL:
			// ɾ����ǩ���ñ�
			delete p->v._label.operand;

			break;
	}

	delete p;
}




/* ������ǩ */
r2_code_t r4_code::label (void) {
	r2_code_t	code	= newz r2_code_o;

	code->type		= R2_CD_LABEL;

	// ������ǩ���ñ�
	code->v._label.operand	= new LST1<r2_code_directive_operand_t>;

	return code;
}


/* ����ָ�� */
r2_code_t r4_code::directive (r2_code_directive_opcode_e opcode, const char *format, ...) {
	r2_code_t	code	= newz r2_code_o;

	code->type					= R2_CD_DIRECTIVE;
	code->v._directive.opcode	= opcode;
	
	code->v._directive.operand_1.type	= R2_CD_OPND_NULL;
	code->v._directive.operand_2.type	= R2_CD_OPND_NULL;
	code->v._directive.operand_3.type	= R2_CD_OPND_NULL;

	// �ж��Ƿ���Ҫ��ʽ��ָ��
	if(format != NULL) {
		// ����������
		r2_code_directive_operand_t	operands	[ ]	= {
			& code->v._directive.operand_1,
			& code->v._directive.operand_2,
			& code->v._directive.operand_3,
			NULL,
		};

		// ��ǰ������
		r2_code_directive_operand_t *	operand	= operands;

		// ��ʽ����
		unsigned int	length	= strlen (format);

		KI_VARG_BEGIN (format);

		while(length > 0) {
			// �ж��Ƿ�������þ�
			if(* operand == NULL) {
				O0::runtime ("��Ч�Ĳ�������ʽ������ȱ�ٲ�������");
			}

			unsigned int	read	= r4_code::operand (* operand, & ap, format);

			// �жϽ���������
			if(read > length) {
				O0::runtime ("��Ч�Ĳ�������ʽ���������������");
			} else if(read == 0) {
				O0::runtime ("��Ч�Ĳ�������ʽ����������ʧ�ܡ�");
			}

			format	+= read;
			length	-= read;

			operand	++;
		}

		KI_VARG_END ( );

		// �ж��Ƿ������
		if(* format != '\0') {
			O0::runtime ("��Ч�Ĳ�������ʽ����������ʣ�ࡣ");
		}
	}

	return code;
}




/* ���²����� */

unsigned int r4_code::operand (r2_code_directive_operand_t operand, const char * format, ...) {
	KI_VARG_BEGIN (format);

	unsigned int	size	= r4_code::operand (operand, & ap, format);

	KI_VARG_END ( );

	return size;
}


unsigned int r4_code::operand (r2_code_directive_operand_t operand, va_list *ap, const char *format) {
	// ��ȡ�ĳ���
	unsigned int	length	= 1;

	// ������ʽ����
	switch(* format) {
		// ����
		case '@':
			break;

		// ��ǩ
		case 'L':
			{
				operand->type		= R2_CD_OPND_LABEL;

				r2_code_t	label	= va_arg (* ap, r2_code_t);

				if(label != NULL) {
					operand->v._label	= & label->v._label;

					* label->v._label.operand	+= operand;
				}
			}

			break;

		// Ѱַ
		case 'A':
			operand->type				= R2_CD_OPND_ADDRESS;
			operand->v._address.offset	= va_arg (* ap, signed int);

			switch(* (format + 1)) {
				case 'd':		operand->v._address.base	= R2_CD_OPND_ADDRESS_DIRECT;		break;
				case 'h':		operand->v._address.base	= R2_CD_OPND_ADDRESS_HEAP;			break;
				case 't':		operand->v._address.base	= R2_CD_OPND_ADDRESS_TOP;			break;
				case 'b':		operand->v._address.base	= R2_CD_OPND_ADDRESS_BOTTOM;		break;

				default:
					O0::runtime ("��Ч�Ĳ�������ʽ������δ֪��Ѱַ��ַ��");
			}

			length ++;

			break;

		// ����
		case 'C':
			{
				operand->type	= R2_CD_OPND_CONSTANT;

				KI_LOOKSTR (format + 1, r4_code::compare) {
					KI_LOOKSTR_CASE ("null")		operand->v._constant	= R2_CD_OPND_CONSTANT_NULL;			length	= sizeof ("null");
					KI_LOOKSTR_CASE ("true")		operand->v._constant	= R2_CD_OPND_CONSTANT_TRUE;			length	= sizeof ("true");
					KI_LOOKSTR_CASE ("false")		operand->v._constant	= R2_CD_OPND_CONSTANT_FALSE;		length	= sizeof ("false");
					KI_LOOKSTR_CASE ("function")	operand->v._constant	= R2_CD_OPND_CONSTANT_FUNCTION;		length	= sizeof ("function");
					KI_LOOKSTR_CASE ("class")		operand->v._constant	= R2_CD_OPND_CONSTANT_CLASS;		length	= sizeof ("class");
					KI_LOOKSTR_CASE ("method")		operand->v._constant	= R2_CD_OPND_CONSTANT_METHOD;		length	= sizeof ("method");
					KI_LOOKSTR_CASE ("dir")			operand->v._constant	= R2_CD_OPND_CONSTANT_DIR;			length	= sizeof ("dir");
					KI_LOOKSTR_CASE ("file")		operand->v._constant	= R2_CD_OPND_CONSTANT_FILE;			length	= sizeof ("file");

					KI_LOOKSTR_DEFAULT ( )
						O0::runtime ("��Ч�Ĳ�������ʽ������δ֪�ĳ������͡�");
				}
			}

			break;

		// ��ʶ��
		case 'D':
			operand->type			= R2_CD_OPND_IDENTIFIER;
			operand->v._identifier	= STR4 (va_arg (* ap, const STR1 *));

			break;

		// ����
		case 'I':
			operand->type		= R2_CD_OPND_INTEGER;
			operand->v._integer	= va_arg (* ap, signed int);

			break;

		// ������
		case 'F':
			operand->type		= R2_CD_OPND_FLOAT;
			operand->v._float	= va_arg (* ap, double);

			break;

		// �ַ���
		case 'S':
			operand->type		= R2_CD_OPND_STRING;
			operand->v._string	= STR4 (va_arg (* ap, const STR1 *));

			break;

		// ����
		case 'N':
			operand->type			= R2_CD_OPND_FUNCTION;
			operand->v._function	= BLD4::function_call (va_arg (* ap, const STR1 *), operand);

			break;

		default:
			O0::runtime ("��Ч�Ĳ�������ʽ������δ֪���͡�");
	}

	return length;
}


