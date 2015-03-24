/*
	$ [KiPHP] /rx/r2.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 2

#ifndef _R2_H_
#define _R2_H_




/* ��ϣ */
class r2_hash {
	public:
		/* ���С */
		static	const	unsigned int	size_small	= 47;			// С��
		static	const	unsigned int	size_big	= 151;			// ���


		/* ��ϣ���� */
		static	const	unsigned int	max_short	= 5;			// �̹�ϣ
		static	const	unsigned int	max_long	= 14;			// ����ϣ


		/* ��ϣ�㷨 */
		static	unsigned int	handler_index	(const char *buffer, unsigned int length, unsigned int max);


		/* ��ϣ���� */
		static	unsigned int	handler_index_short		(STR1 *p);								// �̹�ϣ
		static	unsigned int	handler_index_long		(STR1 *p);								// ����ϣ

		/* ��ϣ���� (const) */
		static	unsigned int	handler_index_short		(const STR1 *p);						// �̹�ϣ
		static	unsigned int	handler_index_long		(const STR1 *p);						// ����ϣ


		/* ���ȽϺ��� */
		static	bool	handler_compare_sensitive		(STR1 *p1, STR1 *p2);					// ���ִ�Сд
		static	bool	handler_compare_insensitive		(STR1 *p1, STR1 *p2);					// ���Դ�Сд (�����Ʋ���ȫ)

		/* ���ȽϺ��� */
		static	bool	handler_compare_sensitive		(const STR1 *p1, const STR1 *p2);		// ���ִ�Сд
		static	bool	handler_compare_insensitive		(const STR1 *p1, const STR1 *p2);		// ���Դ�Сд (�����Ʋ���ȫ)


		/* ��ϣ���� */
		static	STR1 *	handler_build		(STR1 *p);


		/* ��ϣ���� */
		static	void	handler_delete		(STR1 *p);
};




struct	r2_code_label_o;
struct	r2_code_directive_o;

class	r2_function;




/* ������ */
#include "../r2/code_directive_operand.h"
/* ������ */
#include "../r2/code_directive_opcode.h"


/* �������� */
typedef enum {
	R2_CD_LABEL,
	R2_CD_DIRECTIVE,
} r2_code_e;


/* ��ǩ */
typedef struct r2_code_label_o {
	unsigned int	id;									// ��ǩ���
	LST1<r2_code_directive_operand_t> *	operand;		// ���ñ�
} r2_code_label_o, * r2_code_label_t;


/* ָ�� */
typedef struct r2_code_directive_o {
	r2_code_directive_opcode_e		opcode;				// ������
	r2_code_directive_operand_o		operand_1;			// ������ #1
	r2_code_directive_operand_o		operand_2;			// ������ #2
	r2_code_directive_operand_o		operand_3;			// ������ #3
} r2_code_directive_o, * r2_code_directive_t;


/* ���� */
typedef struct {
	r2_code_e		type;								// ��������

	union {
		r2_code_label_o			_label;					// ��ǩ
		r2_code_directive_o		_directive;				// ָ��
	} v;
} r2_code_o, * r2_code_t;




/* ���� */
typedef struct {
	STR1 *		name;									// ������

	bool		visible;								// �ɼ��� (�Ƿ񵼳�)
	bool		super;									// ��ȫ�ֱ���

	unsigned int	line;								// �״γ���������
	unsigned int	line_export;						// ����������

	unsigned int	reference;							// ���ô���

	unsigned int	offset;								// ƫ����
} r2_variable_o, * r2_variable_t;




/* ���� */
typedef class r2_function {
	public:
		STR1 *	name;									// ������

		bool	visible;								// �ɼ��� (�Ƿ񵼳�)

		unsigned int	line_call;						// �״ε���������
		unsigned int	line_declare;					// ����������
		unsigned int	line_export;					// ����������

		unsigned int	parameter_total;				// ��������
		unsigned int	parameter_optional;				// ��ѡ��������

		r2_code_t		entry;							// �������

		LST1<r2_code_directive_operand_t> *	caller;		// ������
} r2_function_o, * r2_function_t;




/* ����� */
#include "../r2/class.h"


/* �� */
typedef class r2_class : public r2_class_feature {
	public:
		static	void	handler_delete_const		(r2_class_const_t p);
		static	void	handler_delete_property		(r2_class_property_t p);
		static	void	handler_delete_method		(r2_class_method_t p);
		static	void	handler_delete_code			(r2_code_t p);


		STR1 *	name;									// ����

		unsigned int	line;							// ����������

		STR1 *	_extend;								// ����

		// ʵ�ֽӿ�
		TBL1<STR1 *, r2_hash::size_small, NULL, r2_hash::handler_index_short, r2_hash::handler_compare_insensitive, r2_hash::handler_delete> *	_implement;

		// ����
		TBL1<r2_class_const_t,		r2_hash::size_small,	NULL,	r2_hash::handler_index_short,	r2_hash::handler_compare_sensitive,		r2_class::handler_delete_const> *		_const;
		// ����
		TBL1<r2_class_property_t,	r2_hash::size_small,	NULL,	r2_hash::handler_index_short,	r2_hash::handler_compare_sensitive,		r2_class::handler_delete_property> *	_property;
		// ����
		TBL1<r2_class_method_t,		r2_hash::size_small,	NULL,	r2_hash::handler_index_short,	r2_hash::handler_compare_insensitive,	r2_class::handler_delete_method> *		_method;

		LST1<r2_code_t> *	code_boot;					// ��������
		LST1<r2_code_t> *	code_entry;					// ��ڴ���

		// ����
		LST1<r2_code_t, r2_class::handler_delete_code> *	code;

		// �����ǩ
		r2_code_t		label_code_boot;
		r2_code_t		label_code_entry;
} r2_class_o, * r2_class_t;




#endif

#endif