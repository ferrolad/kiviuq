/*
	$ [KiPHP] /rx/r0.h  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 0

#ifndef _R0_H_
#define _R0_H_



#define LDR0	r0_loader
#define O0		r0_io
#define M0		r0_memory





/* ������ */
class r0_loader {
	private:
		/* �������С */
		static	const	unsigned int	size	= 32;

		/* ������ */
		static	void	(* handler_boot		[r0_loader::size])	(int, char **);
		static	void	(* handler_shutdown	[r0_loader::size])	(void);

		/* ע�ắ������ */
		static	unsigned int	count;


	public:
		/* �����µĺ��� */
		static	void	mount		(void (* boot)(int, char **), void (* shutdown)(void));


		/* ���� */
		static	void	boot		(int argc, char *argv[]);
		/* ���� */
		static	void	shutdown	(void);


		/* ��ֹ���� */
		static	void	die			(int code = 0);
};




/* ��� */
class r0_io {
	KI_LOADER_DECLARE ( );


	public:
		/* ���ļ� */
		static	FILE *	stream_in;								// ������
		static	FILE *	stream_out;								// �����
		static	FILE *	stream_error;							// ������


		/* �����������ַ� */
		static	void	putchar		(const int data);
		/* �����������ַ��� */
		static	void	print		(const char *data);
		static	void	printf		(const char *format, ...);

		/* �����������﷨����/���� */
		static	void	syntax		(const char *message, unsigned int line = 0, bool fatal = false);
		/* ��������������ʱ������ֹ���� */
		static	void	runtime		(const char *message);
		/* ��������������������ֹ���� */
		static	void	argument	(const char *format, ...);

		/* ������������¼��Ϣ */
		static	void	log			(const char *entry, const char *format, ...);
};




/* �ڴ� */
class r0_memory {
	public:
		/* �����С */
		static	unsigned int	size_total;						// �ۻ������С
		static	unsigned int	size_peak;						// �����ֵ��С
		static	unsigned int	size_current;					// ��ǰ�����С

		/* ���ô��� */
		static	unsigned int	call_allocate;					// ������ô���
		static	unsigned int	call_reallocate;				// �ط�����ô���
		static	unsigned int	call_release;					// �ͷŵ��ô���


		/* ��¡�ڴ�� */
		static	void *	clone		(void *p);

		/* �����ڴ� */
		static	void *	allocate	(size_t size);
		/* �ط����ڴ� */
		static	void *	reallocate	(void *p, size_t size);
		/* �ͷ��ڴ� */
		static	void	release		(void *p);

		/* �����ڴ� */
		static	void *	copy	(void *target, const void *source, unsigned int size);

		/* �ڴ���� */
		static	void *	fill	(void *p, int value);
		static	void *	fill	(void *p, unsigned int size, int value);

		/* �ڴ����� */
		static	void *	zero	(void *p);
		static	void *	zero	(void *p, unsigned int size);
};





/* ���� new */
inline	void *	operator new	(size_t size)				{	return				M0::allocate (size);									}
inline	void *	operator new	(size_t size, bool dummy)	{	return	M0::fill (	M0::allocate (size),	(unsigned int) size,	0);		}

/* ���� delete */
inline	void	operator delete	(void *p)					{	M0::release (p);	}
inline	void	operator delete	(void *p, bool dummy)		{	M0::release (p);	}


/* placement new */
inline	void *	operator new	(size_t size, void *p)		{	return p;	}
inline	void	operator delete	(void *p1, void *p2)		{				}




/* ���ڴ���յ� new ����� */
#define newz	new (true)

/* placement new */
#define recall	new (this)




#endif

#endif