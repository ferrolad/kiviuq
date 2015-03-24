/*
	$ [KiPHP] /r0/memory.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			0

#include "../kiviuq.h"




/* �����С */
unsigned int	r0_memory::size_total		= 0;				// �ۻ������С
unsigned int	r0_memory::size_peak		= 0;				// �����ֵ��С
unsigned int	r0_memory::size_current		= 0;				// ��ǰ�����С

/* ���ô��� */
unsigned int	r0_memory::call_allocate	= 0;				// ������ô���
unsigned int	r0_memory::call_reallocate	= 0;				// �ط�����ô���
unsigned int	r0_memory::call_release		= 0;				// �ͷŵ��ô���




/* ��¡�ڴ�� */
void * r0_memory::clone (void *p) {
	// Ŀ���ַ
	void *	target	= NULL;

	if(p == NULL) {
		return target;
	}

	KI_EXCEPTION_BEGIN ( );

	// �ڴ��С
	size_t	size	= (size_t) *((unsigned int *) p - 1);

	// �����ڴ�
	target	= r0_memory::allocate ((size_t) size);

	// ִ���ڴ濽��
	r0_memory::copy (target, p, size);

	KI_EXCEPTION_END ("���Զ���Ч���ڴ�鴴��������");

	return target;
}




/* �����ڴ� */
void * r0_memory::allocate (size_t size) {
	// 0 �ֽڱ���
	if(size == 0) {
		size	= 1;
	}

	// ʵ�ʷ����С
	unsigned int	byte	= (unsigned int) size + sizeof (unsigned int);

	// �����ڴ�
	unsigned int *	p		= (unsigned int *) malloc (byte);

	// ����Ƿ����ɹ�
	if(p == NULL) {
		O0::runtime ("��������ڴ�ʧ�ܡ�");
	}

	// ���ڴ��д���С��Ϣ
	* p	= (unsigned int) size;

	// ���·����С
	r0_memory::size_total	+= byte;
	r0_memory::size_current	+= byte;

	// ���·����ֵ
	if(r0_memory::size_peak < r0_memory::size_current) {
		r0_memory::size_peak	= r0_memory::size_current;
	}

	// ���µ��ô���
	r0_memory::call_allocate ++;

	return p + 1;
}


/* �ط����ڴ� */
void * r0_memory::reallocate (void *p, size_t size) {
	// ���µ��ô���
	r0_memory::call_reallocate ++;

	// ��ָ�뱣��
	if(p == NULL) {
		return r0_memory::allocate (size);
	}

	KI_EXCEPTION_BEGIN ( );

	// ��ȡ�ѷ����С
	unsigned int	size_real	= * (((unsigned int *) p) - 1);

	// �ж��ѷ����С�Ƿ���������С
	if(size_real >= size) {
		return p;
	}

	// �������ڴ�
	void *	p_new	= r0_memory::allocate (size);

	// �����ڴ�
	r0_memory::copy (p_new, p, size_real);

	// �ͷ����ڴ�
	r0_memory::release (p);

	return p_new;

	KI_EXCEPTION_END ("�������·�����Ч���ڴ�顣");

	return NULL;
}


/* �ͷ��ڴ� */
void r0_memory::release (void *p) {
	// ��ָ�뱣��
	if(p == NULL) {
		return;
	}

	// ʵ�ʷ����С
	unsigned int	size	= 0;

	// ʵ�ʵ�ַ
	p	= ((unsigned int *) p) - 1;

	KI_EXCEPTION_BEGIN ( );

	// ��ȡʵ�ʷ����С
	size	= *((unsigned int *) p) + sizeof (unsigned int);

	// �ͷ��ڴ�
	free (p);

	KI_EXCEPTION_END ("�����ͷ���Ч���ڴ�顣");

	// ���·����С
	r0_memory::size_current	-= size;

	// ���µ��ô���
	r0_memory::call_release	++;
}




/* �����ڴ� */
void * r0_memory::copy (void *target, const void *source, unsigned int size) {
	KI_EXCEPTION_BEGIN ( );

	memcpy (target, source, (size_t) size);

	KI_EXCEPTION_END ("���Ը�����Ч���ڴ�顣");

	return target;
}




/* �ڴ���� */

void * r0_memory::fill (void *p, int value) {
	KI_EXCEPTION_BEGIN ( );

	// ��ȡ�ڴ��С
	unsigned int	size	= *((unsigned int *) p - 1);

	// ����
	memset (p, value, (size_t) size);

	KI_EXCEPTION_END ("���������Ч���ڴ�顣");

	return p;
}


void * r0_memory::fill (void *p, unsigned int size, int value) {
	KI_EXCEPTION_BEGIN ( );

	// ����
	memset (p, value, (size_t) size);

	KI_EXCEPTION_END ("���������Ч���ڴ�顣");

	return p;
}




/* �ڴ����� */

void * r0_memory::zero (void *p) {
	return r0_memory::fill (p, 0);
}


void * r0_memory::zero (void *p, unsigned int size) {
	return r0_memory::fill (p, size, 0);
}


