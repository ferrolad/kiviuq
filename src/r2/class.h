/*
	$ [KiPHP] /r2/class.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 2

#ifndef _R2_CLASS_H_
#define _R2_CLASS_H_




/* ����Ȩ�� */
typedef enum {
	R2_CLS_FTR_ACCESS_DEFAULT,
	R2_CLS_FTR_ACCESS_PUBLIC,
	R2_CLS_FTR_ACCESS_PROTECTED,
	R2_CLS_FTR_ACCESS_PRIVATE,
} r2_class_feature_access_e;


/* ���� */
typedef class r2_class_feature {
	public:
		r2_class_feature_access_e	access;			// ����Ȩ��

		bool	_final;
		bool	_abstract;
		bool	_static;
} r2_class_feature_o, * r2_class_feature_t;




/* ���� */
typedef struct {
	STR1 *			name;							// ������
	unsigned int	line;							// ������
	r2_code_directive_operand_o		value;			// ����ֵ
} r2_class_const_o, * r2_class_const_t;




/* ���� */
typedef class r2_class_property : public r2_class_feature {
	public:
		/* ������������ */
		void	feature		(r2_class_feature_t p);

		STR1 *			name;						// ������
		unsigned int	line;						// ������
} r2_class_property_o, * r2_class_property_t;




/* ���� */
typedef class r2_class_method : public r2_function, public r2_class_feature {
	public:
		/* ���·������� */
		void	feature		(r2_class_feature_t p);

		unsigned int	line;						// ������
} r2_class_method_o, * r2_class_method_t;




#endif

#endif