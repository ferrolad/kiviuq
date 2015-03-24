/*
	$ [KiPHP] /rx/r1.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 1

#ifndef _R1_H_
#define _R1_H_



#define STR1	r1_string
#define LST1	r1_linkedlist
#define STK1	r1_stack
#define TBL1	r1_hashtable
#define SGL1	r1_singleton





/* �ַ��� */
class r1_string {
	private:
		/* ������ */
		char *	buffer;

		/* ���� */
		unsigned int	size_used;
		/* ʣ������ */
		unsigned int	size_available;


	public:
		/* �����ַ��� */
		r1_string	(void);												// �������ַ���
		r1_string	(const r1_string *p);								// ��¡�ַ���
		r1_string	(const char *format, ...);							// ��ʽ�������ַ���
		r1_string	(int dummy, const char *format, va_list ap);		// ��ʽָ�봴���ַ���

		~r1_string	(void);


		/* �Ƚ��ַ��� */
		bool	operator ==		(const r1_string &p)	const;
		bool	operator ==		(const r1_string *p)	const;
		bool	operator ==		(const char *p)			const;

		/* �����ַ��� */
		void	operator +=		(const r1_string &p);
		void	operator +=		(const r1_string *p);
		void	operator +=		(const char *p);


		/* �ַ������� */
		unsigned int	length	(void)	const;

		/* �ַ��������� */
		const char *	pointer	(void)	const;

		/* �����ַ��� */
		void	concat	(const r1_string *p);
		void	concat	(const char *format, ...);
		void	concat	(int dummy, const char *format, va_list ap);

		/* �ϲ����������ַ���β�� */
		void	append	(const void *buffer, unsigned int size);
};




/* �ڵ� */
template <typename T> struct r1_node {
	T	data;

	r1_node *		next;
	r1_node *		prev;
};


/* ˫����ڵ� */
template <typename T> struct r1_node_duo {
	/* ֵ */
	T	value;
	/* �� */
	r1_string *	key;

	r1_node_duo *	next1;
	r1_node_duo *	next2;
};




/* ���� */
template <class T, void (* Cd)(T) = NULL>
class r1_linkedlist {
	private:
		/* �ڵ�ָ�� */
		r1_node<T> *	head;						// ��ͷ
		r1_node<T> *	tail;						// ��β
		r1_node<T> *	seek;						// ����


	public:
		/* �ڵ����� */
		unsigned int	count;


		/* �������� */
		r1_linkedlist	(void);						// ����������
		r1_linkedlist	(const void *p);			// ��¡����

		~r1_linkedlist	(void);


		/* ����β����Ԫ�� */
		void	operator +=		(T data);

		/* ��ȡԪ�� */
		T		operator []		(signed int offset)		const;

		/* �ƶ�����ָ�� */
		void	operator ++		(int dummy);
		void	operator --		(int dummy);


		/* ��ȡԪ�� */
		T		at		(signed int offset)		const;

		/* �ڵ�ǰԪ��ǰ�����Ԫ�� */
		void	insert	(T data, bool after = true);
		/* ����β����Ԫ�� */
		void	append	(T data);

		/* ������һ������ */
		void	concat	(const void *p);

		/* ����Ԥ�� */
		bool	ready	(void);
		/* ��ȡ��ǰ����Ԫ�� */
		bool	fetch	(T *p);
};




/* ջ */
template <class T, void (* Cd)(T) = NULL>
class r1_stack {
	private:
		/* ջ��ָ�� */
		r1_node<T> *	top;

		/* Ԫ������ */
		unsigned int	count;


	public:
		r1_stack	(void);

		~r1_stack	(void);

		/* ѹջ */
		void	operator +=		(T data);
		/* ��ջ */
		void	operator --		(int dummy);

		/* ջ�� */
		T		operator []		(unsigned int offset)	const;


		/* ѹջ */
		void	push	(T data);
		/* ��ջ */
		void	pop		(void);

		/* ջ�� */
		T		peek	(unsigned int offset = 0)	const;

		/* ��Ԫ��ð�ݵ�ջ�� */
		void	bubble	(unsigned int offset);

		/* �ж��Ƿ�ջ�� */
		bool	empty	(void)		const;
};




/* ��ϣ�� */
template
	<
		class			T,
		unsigned int	S,												// ��ϣ���С
		T				D,												// Ĭ������
		unsigned int	(* Ci)(const STR1 *),							// ��ϣ����
		bool			(* Cc)(const STR1 *, const STR1 *),				// ���ȽϺ���
		void			(* Cd)(T) = NULL								// ����������
	>
class r1_hashtable {
	private:
		/* ӳ��� */
		r1_node_duo<T> *	table	[S + 1];

		/* �ڵ�ָ�� */
		r1_node_duo<T> *	head;
		r1_node_duo<T> *	tail;
		r1_node_duo<T> *	seek;


		/* ��ȡԪ�� */
		T *		at		(const STR1 *p, bool created = true);


	public:
		/* �ڵ����� */
		unsigned int	count;


		r1_hashtable	(void);

		~r1_hashtable	(void);


		/* ��ȡԪ�� */
		T		operator []		(const STR1 &p);
		T		operator []		(const STR1 *p);
		T		operator []		(const char *p);


		/* ��ȡԪ�� */
		T		read	(const STR1 &p);
		T		read	(const STR1 *p);
		T		read	(const char *p);

		/* д������ */
		void	write	(const STR1 &p, T data);
		void	write	(const STR1 *p, T data);
		void	write	(const char *p, T data);


		/* ���Ԫ���Ƿ���� */
		bool	exist	(const STR1 &p);
		bool	exist	(const STR1 *p);
		bool	exist	(const char *p);


		/* ����Ԥ�� */
		bool	ready	(void);
		/* ��ȡ��ǰ����Ԫ�� */
		bool	fetch	(T *p1, const STR1 **p2 = NULL);
};




/* �������� */
template
	<
		class			T,
		unsigned int	S,												// ��ϣ���С
		T				(* Cb)(T),										// ������������
		unsigned int	(* Ci)(T),										// ��ϣ����
		bool			(* Cc)(T, T),									// ֵ�ȽϺ���
		void			(* Cd)(T) = NULL								// ����������
	>
class r1_singleton {
	private:
		/* ӳ��� */
		r1_node<T> *	table	[S + 1];


	public:
		/* �ڵ����� */
		unsigned int	count;


		r1_singleton	(void);

		~r1_singleton	(void);


		/* ��ȡԪ�� */
		T		fetch	(T data);
};





#include "../r1/linkedlist.hpp"
#include "../r1/stack.hpp"
#include "../r1/hashtable.hpp"
#include "../r1/singleton.hpp"




#endif

#endif