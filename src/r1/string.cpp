/*
	$ [KiPHP] /r1/string.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			1

#include "../kiviuq.h"



/* ���������С */
#define BLOCK			0x20				// 32 Byte




/* �������ַ��� */
r1_string::r1_string (void) {
	// ���仺����
	this->buffer	= new char [BLOCK];

	// ��ʼ��ʹ�ü�¼
	this->size_used			= 0;
	this->size_available	= BLOCK;

	// ���ý�β�� \0
	this->buffer [0]	= '\0';
}


/* ��¡�ַ��� */
r1_string::r1_string (const r1_string *p) {
	// ��������������
	this->buffer	= (char *) M0::clone (p->buffer);

	// ����ʹ�ü�¼
	this->size_used			= p->size_used;
	this->size_available	= p->size_available;
}


/* ��ʽ�������ַ��� */
r1_string::r1_string (const char *format, ...) {
	// �������ַ���
	recall r1_string ( );

	KI_VARG_BEGIN (format);

	// ִ������
	this->concat (0, format, ap);

	KI_VARG_END ( );
}


/* ��ʽָ�봴���ַ��� */
r1_string::r1_string (int dummy, const char *format, va_list ap) {
	// �������ַ���
	recall r1_string ( );

	// ִ������
	this->concat (dummy, format, ap);
}




r1_string::~r1_string (void) {
	delete [] this->buffer;
}




/* �Ƚ��ַ��� */

bool r1_string::operator == (const r1_string &p) const {
	return r1_string::operator== (& p);
}


bool r1_string::operator == (const r1_string *p) const {
	if(p->size_used == this->size_used) {
		if(memcmp (p->buffer, this->buffer, this->size_used) == 0) {
			return true;
		}
	}

	return false;
}


bool r1_string::operator == (const char *p) const {
	unsigned int	length	= strlen (p);

	if(length == this->size_used) {
		if(memcmp (p, this->buffer, length) == 0) {
			return true;
		}
	}

	return false;
}




/* �����ַ��� */

void r1_string::operator += (const r1_string &p) {
	this->concat (& p);
}


void r1_string::operator += (const r1_string *p) {
	this->concat (p);
}


void r1_string::operator += (const char *p) {
	this->concat ("%s", p);
}




/* �ַ������� */
unsigned int r1_string::length (void) const {
	return this->size_used;
}


/* �ַ��������� */
const char * r1_string::pointer (void) const {
	return this->buffer;
}




/* �����ַ��� */

void r1_string::concat (const r1_string *p) {
	this->append (p->buffer, p->size_used);
}


void r1_string::concat (const char *format, ...) {
	KI_VARG_BEGIN (format);

	this->concat (0, format, ap);

	KI_VARG_END ( );
}


void r1_string::concat (int dummy, const char *format, va_list ap) {
	// �������ɳ���
	unsigned int	length	= vsnprintf (NULL, 0, format, ap);

	// �����ڴ�ռ�
	char *	buffer	= newz char [length + 4];

	// �����ַ���
	vsprintf (buffer, format, ap);

	// ִ�����Ӳ���
	this->append (buffer, length);

	// �ͷ���ʱ�ڴ�ռ�
	delete [] buffer;
}




/* �ϲ����������ַ���β�� */
void r1_string::append (const void *buffer, unsigned int size) {
	// �ж��Ƿ���Ҫ���·���ռ� (���� \0 ����)
	if(this->size_available <= size) {
		// ��Ҫ��չ������
		unsigned int	extend	= ((size / BLOCK) + 1) * BLOCK;

		// ���·����ڴ�
		this->buffer	= (char *) M0::reallocate (this->buffer, extend + this->size_used + this->size_available);

		// ���¿�������
		this->size_available	+= extend;
	}

	// �ϲ�����
	M0::copy (this->buffer + this->size_used, buffer, size);

	// ����ͳ����Ϣ
	this->size_used			+= size;
	this->size_available	-= size;

	// ���ý�β�� \0
	this->buffer [this->size_used]	= '\0';
}


