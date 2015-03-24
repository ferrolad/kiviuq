/*
	$ [KiPHP] /rx/r3.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 3

#ifndef _R3_H_
#define _R3_H_



#define CFG3		r3_config

#define C3(v)		r3_config_container::##v





/* ���ģʽ */
typedef enum {
	R3_CONFIG_OUTPUT_HELP,					//			-h
	R3_CONFIG_OUTPUT_VERSION,				//			-v
	R3_CONFIG_OUTPUT_DISTRIBUTION,			//			-distribution
	R3_CONFIG_OUTPUT_CODE,					// Ŀ�����	-Oc
	R3_CONFIG_OUTPUT_INTERLANG,				// �м�����	-Oi
	R3_CONFIG_OUTPUT_SYMBOL,				// ������Ϣ	-Os
} r3_config_output_e;


/* ����ģʽ */
typedef enum {
	R3_CONFIG_WARNING_DISABLE,				// ���þ���	-W0
	R3_CONFIG_WARNING_NORMAL,				// ��׼����	-W1
	R3_CONFIG_WARNING_ERROR,				// �������	-W2
} r3_config_warning_e;


/* ��������� */
typedef enum {
	R3_CONFIG_VM_WRAPPER,
	R3_CONFIG_VM_ENTRY,
	R3_CONFIG_VM_HEAP,
	R3_CONFIG_VM_STACK,
	R3_CONFIG_VM_TOP,
	R3_CONFIG_VM_BOTTOM,
	R3_CONFIG_VM_EXCEPTION,
	R3_CONFIG_VM_PROGRAM,
	R3_CONFIG_VM_RETURN,
	R3_CONFIG_VM_MIDDLE,
} r3_config_vm_e;




/* ���ù��� */
class r3_config {
	KI_LOADER_DECLARE ( );


	private:
		/* �������� */
		static	int			argc;
		static	char **		argv;


		/* �������� */
		static	bool			fetch_uint			(unsigned int *p);
		static	const char *	fetch_string		(void);
		static	const char *	fetch_variable		(void);
		static	const char *	fetch_identifier	(void);

		/* ������� */
		static	void	parse	(const char *command);

		/* ���ģʽ */
		static	void	output	(r3_config_output_e mode);


	public:
		static	void	handler_delete	(STR1 *data);


		/* ���µ����� */
		static	void	update_export	(LST1<STR1 *, r3_config::handler_delete> *table, const char *p);
		/* ��������� */
		static	void	update_vm		(r3_config_vm_e entry, const char *p);
};




/* �������� */
class r3_config_container {
	public:
		/* ������ */
		static	LST1<STR1 *, r3_config::handler_delete> *		export_variable;		// ȫ�ֱ���������
		static	LST1<STR1 *, r3_config::handler_delete> *		export_function;		// ����������


		/* ���ģʽ */
		static	r3_config_output_e		output;

		/* ����ģʽ */
		static	r3_config_warning_e		warning;

		/* ����ˮƽ */
		static	unsigned int	noise;

		/* ������м�¼ */
		static	bool		log;

		/* ���ñ���֧�� */
		static	bool		enable_encode;
		/* ������������ */
		static	bool		enable_inline;
		/* ���ñ�����ע */
		static	bool		enable_pragma;
		/* ����������� */
		static	bool		enable_random;

		/* �������Ϣ */
		static	STR1 *		vm_wrapper;					// ��װ������
		static	STR1 *		vm_entry;					// ������ڷ�����
		static	STR1 *		vm_heap;					// ��������
		static	STR1 *		vm_stack;					// ջ������
		static	STR1 *		vm_top;						// ջ��ָ�������
		static	STR1 *		vm_bottom;					// ջ��ָ�������
		static	STR1 *		vm_exception;				// �쳣ָ�������
		static	STR1 *		vm_program;					// ���������ָ�������
		static	STR1 *		vm_return;					// ����ֵ�ݴ���������
		static	STR1 *		vm_middle;					// �м�ֵ�ݴ���������
};




#endif

#endif