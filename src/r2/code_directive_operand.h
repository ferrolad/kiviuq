/*
	$ [KiPHP] /r2/code_directive_operand.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 2

#ifndef _R2_CODE_DIRECTIVE_OPERAND_H_
#define _R2_CODE_DIRECTIVE_OPERAND_H_




/* ���������� */
typedef enum {
	R2_CD_OPND_NULL,							// �޲�����
	R2_CD_OPND_LABEL,							// ��ǩ
	R2_CD_OPND_ADDRESS,							// Ѱַ
	R2_CD_OPND_CONSTANT,						// ����
	R2_CD_OPND_IDENTIFIER,						// ��ʶ��
	R2_CD_OPND_INTEGER,							// ����
	R2_CD_OPND_FLOAT,							// ������
	R2_CD_OPND_STRING,							// �ַ���
	R2_CD_OPND_FUNCTION,						// ����
} r2_code_directive_operand_e;




/* Ѱַ��ַ */
typedef enum {
	R2_CD_OPND_ADDRESS_DIRECT,					// ֱ��Ѱַ
	R2_CD_OPND_ADDRESS_HEAP,					// �ѻ�ַ
	R2_CD_OPND_ADDRESS_TOP,						// ջ��Ѱַ
	R2_CD_OPND_ADDRESS_BOTTOM,					// ջ��Ѱַ
} r2_code_directive_operand_address_base_e;


/* Ѱַ */
typedef struct {
	signed int		offset;
	r2_code_directive_operand_address_base_e	base;
} r2_code_directive_operand_address_o, * r2_code_directive_operand_address_t;




/* ���� */
typedef enum {
	R2_CD_OPND_CONSTANT_NULL,
	R2_CD_OPND_CONSTANT_TRUE,
	R2_CD_OPND_CONSTANT_FALSE,
	R2_CD_OPND_CONSTANT_FUNCTION,
	R2_CD_OPND_CONSTANT_CLASS,
	R2_CD_OPND_CONSTANT_METHOD,
	R2_CD_OPND_CONSTANT_DIR,
	R2_CD_OPND_CONSTANT_FILE,
} r2_code_directive_operand_constant_e;




/* ������ */
typedef struct {
	r2_code_directive_operand_e		type;

	union {
		struct r2_code_label_o *				_label;
		r2_code_directive_operand_address_o		_address;
		r2_code_directive_operand_constant_e	_constant;
		STR1 *		_identifier;
		signed int	_integer;
		double		_float;
		STR1 *		_string;
		class r2_function *		_function;
	} v;
} r2_code_directive_operand_o, * r2_code_directive_operand_t;




#endif

#endif