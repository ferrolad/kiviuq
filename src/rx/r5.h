/*
	$ [KiPHP] /rx/r5.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 5

#ifndef _R5_H_
#define _R5_H_



#define OUT5		r5_output
#define STX5		r5_syntax





/* ��������� */
class r5_output {
	private:
		/* ���м�¼ */
		static	void	log			(void);


	public:
		/* ִ����� */
		static	void	execute		(void);


		/* ���л����� */
		static	void	serialize	(LST1<r2_code_t, r2_class::handler_delete_code> *p);
};




class r5_output_handler {
	protected:
		unsigned int	indent;

		/* ����հ� */
		void	print_space		(void);
		/* ������Ա���� */
		void	print_feature	(r2_class_feature_t feature);
		/* ��������� */
		void	print_operand	(r2_code_directive_operand_t operand);
		/* ����ַ��� */
		void	print_string	(const STR1 *p);


	public:
		virtual	void	execute		(void);

		
		virtual	void	callback_begin		(void)						= 0;
		virtual	void	callback_end		(void)						= 0;
		virtual	void	callback_code		(r2_code_t)					= 0;
		virtual	void	callback_function	(r2_class_t, r2_code_t)		= 0;
};




class r5_syntax {
	private:
		static	void	begin	(void);
		static	void	end		(void);

		/* ִ�� */
		static	void	call	(void);


	public:
		static	STK1<r2_code_t> *	stack;


		static	void	execute		(void);
};





#include "../r5/output_handler.h"




#endif

#endif