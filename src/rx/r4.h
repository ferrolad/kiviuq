/*
	$ [KiPHP] /rx/r4.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 4

#ifndef _R4_H_
#define _R4_H_



#define VAR4			r4_variable
#define COD4			r4_code
#define BLD4			r4_builder
#define RCD4			r4_recorder

#define STR4(p)			r4_constring::build (p)





/* �ַ��������� */
class r4_constring {
	KI_LOADER_DECLARE ( );


	private:
		/* ������ */
		static	SGL1<STR1 *, r2_hash::size_big, r2_hash::handler_build, r2_hash::handler_index_long, r2_hash::handler_compare_sensitive, r2_hash::handler_delete> *	table;


	public:
		/* ��ȡ�ַ������� */
		static	STR1 *	build	(const char *p);
		static	STR1 *	build	(const STR1 *p);
};




/* ���������� */
class r4_variable {
	KI_LOADER_DECLARE ( );


	public:
		static	unsigned int	handler_index		(const STR1 *p);
		static	bool			handler_compare		(const STR1 *p1, const STR1 *p2);
		static	void			handler_delete		(r2_variable_t p);


	private:
		/* ��ǰʶ��ǰ׺ */
		STR1 *	prefix;

		/* ȫ�������� */
		bool	global;
		/* ջ��ƫ���� */
		unsigned int	offset;

		
		/* ��ӱ��� */
		static	r2_variable_t	add_heap		(const STR1 *name);
				r2_variable_t	add_stack		(const STR1 *name);

		/* ��ȡ���� */
		static	r2_variable_t	fetch_heap		(const STR1 *name);
				r2_variable_t	fetch_stack		(const STR1 *name);


		/* ���²����� */
		static	void	update	(r2_variable_t var, r2_code_directive_operand_address_base_e base, r2_code_directive_operand_t operand);


	public:
		/* ��ȫ�ֱ����� */
		static	TBL1<r2_variable_t, r2_hash::size_small, NULL,	r2_hash::handler_index_short,	r2_hash::handler_compare_sensitive,	NULL> *	super;
		/* �ѱ����� */
		static	TBL1<r2_variable_t, r2_hash::size_small, NULL,	r4_variable::handler_index,		r4_variable::handler_compare,		r4_variable::handler_delete> *	heap;

		/* ջ������ */
				TBL1<r2_variable_t, r2_hash::size_small, NULL,	r4_variable::handler_index,		r4_variable::handler_compare,		r4_variable::handler_delete> *	stack;


		r4_variable		(const STR1 *name_class, const STR1 *name_function, unsigned int offset = 0);

		~r4_variable	(void);


		/* ע�ᳬȫ�ֱ��� */
		static	void	register_super	(const char *p);
		static	void	register_super	(const STR1 *p);


		/* ע�ᾲ̬���� */
		bool	register_static	(const STR1 *p, r2_code_directive_operand_t operand_old, r2_code_directive_operand_t operand_new);
		/* ע��ȫ�ֱ��� */
		bool	register_global	(const STR1 *p, r2_code_directive_operand_t operand_old, r2_code_directive_operand_t operand_new);

		/* ʹ�ñ��� */
		void	use		(const STR1 *p, r2_code_directive_operand_t operand);
};




/* ���������� */
class r4_code {
	private:
		/* �����ַ����Ƚ� */
		static	int		compare		(const char *p1, const char *p2);


	public:
		/* �ͷŴ��� */
		static	void		free		(r2_code_t p);

		/* ������ǩ */
		static	r2_code_t	label		(void);
		/* ����ָ�� */
		static	r2_code_t	directive	(r2_code_directive_opcode_e opcode, const char *format, ...);

		/* ���²����� */
		static	unsigned int	operand		(r2_code_directive_operand_t operand, const char * format, ...);
		static	unsigned int	operand		(r2_code_directive_operand_t operand, va_list *ap, const char *format);
};




/* ������ */
class r4_builder {
	public:
		/* ��ȡȫ�ֱ��� */
		static	r2_variable_t	variable_fetch	(const STR1 *name);

		/* ����ȫ�ֱ��� */
		static	void	variable_export		(const STR1 *name);


		/* ���뺯�� */
		static	void	function_enter	(const STR1 *name);
		/* �˳����� */
		static	void	function_leave	(void);

		/* ���ú��� */
		static	r2_function_t	function_call	(const STR1 *name, r2_code_directive_operand_t p);

		/* ��ȡ���� */
		static	r2_function_t	function_fetch	(const STR1 *name);

		/* �������� */
		static	void	function_export		(const STR1 *name);


		/* ������ */
		static	void	class_enter		(const STR1 *name);
		/* �˳��� */
		static	void	class_leave		(void);

		/* ��ʵ�ֽӿ� */
		static	void	class_implement	(const STR1 *name);

		/* �ೣ������ */
		static	void	class_declare_const		(const STR1 *name, r2_code_directive_operand_t operand);
		/* �����Զ��� */
		static	void	class_declare_property	(const STR1 *name);

		/* ��ȡ�� */
		static	r2_class_t	class_fetch		(const STR1 *name, LST1<r2_code_t> *code = NULL);


		/* ����������� */
		static	void	collect		(void);

		/* ��������� */
		static	void	collect_vm			(void);
		/* ������ */
		static	void	collect_function	(r2_function_t node);
		/* ������ */
		static	void	collect_class		(r2_class_t node);
};




/* ���м�¼ */
class r4_recorder {
	KI_LOADER_DECLARE ( );


	public:
		static	void	handler_delete_variable	(r2_variable_t p);
		static	void	handler_delete_function	(r2_function_t p);
		static	void	handler_delete_class	(r2_class_t p);


		/* �Ѵ����� */
		static	unsigned int	line;
		/* �Ѵ����ֽ� */
		static	unsigned int	byte;


		/* ȫ�ֱ����� */
		static	TBL1<r2_variable_t,	r2_hash::size_small, NULL, r2_hash::handler_index_short, r2_hash::handler_compare_sensitive,	r4_recorder::handler_delete_variable> *		table_variable;

		/* ������ */
		static	TBL1<r2_function_t,	r2_hash::size_small, NULL, r2_hash::handler_index_short, r2_hash::handler_compare_insensitive,	r4_recorder::handler_delete_function> *		table_function;

		/* ��� */
		static	TBL1<r2_class_t,	r2_hash::size_small, NULL, r2_hash::handler_index_short, r2_hash::handler_compare_insensitive,	r4_recorder::handler_delete_class> *		table_class;


		/* ��ǰ���� */
		static	LST1<r2_code_t> *	code;
		/* ȫ�ִ��� */
		static	LST1<r2_code_t> *	code_global;

		/* ��ǰ���� */
		static	r2_function_t	function;

		/* ��ǰ�� */
		static	r2_class_t			cls;
		/* ��ǰ���Ա���� */
		static	r2_class_feature_t	class_feature;


		/* ��ǰ���������� */
		static	VAR4 *		var;
		/* ȫ�ֱ��������� */
		static	VAR4 *		var_global;

		
		/* ����ʱ���� */
		static	void	warning		(bool line,			const char *format, ...);
		static	void	warning		(unsigned int line,	const char *format, ...);

		/* ����ʱ���� */
		static	void	error		(bool line,			const char *format, ...);
		static	void	error		(unsigned int line,	const char *format, ...);
};




#endif

#endif