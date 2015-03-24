/*
	$ [KiPHP] /r2/hash.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			2

#include "../kiviuq.h"




/* ��ϣ�㷨 */
unsigned int r2_hash::handler_index (const char *buffer, unsigned int length, unsigned int max) {
	// ����ϣ�ֽ�
	if(length < max) {
		max	= length;
	}

	// ��ϣֵ
	int	value	= 0;

	for(unsigned int i = 0; i < max; i ++) {
		if(buffer [i] != '\0') {
			value	+= tolower ((int) buffer [i]);
		}
	}

	return (unsigned int) value;
}




/* ��ϣ���� */

unsigned int r2_hash::handler_index_short (STR1 *p) {
	return r2_hash::handler_index_short ((const STR1 *) p);
}


unsigned int r2_hash::handler_index_long (STR1 *p) {
	return r2_hash::handler_index_long ((const STR1 *) p);
}




/* ��ϣ���� (const) */

unsigned int r2_hash::handler_index_short (const STR1 *p) {
	return r2_hash::handler_index (p->pointer ( ), p->length ( ), r2_hash::max_short);
}


unsigned int r2_hash::handler_index_long (const STR1 *p) {
	return r2_hash::handler_index (p->pointer ( ), p->length ( ), r2_hash::max_long);
}




/* ���ȽϺ��� */

bool r2_hash::handler_compare_sensitive (STR1 *p1, STR1 *p2) {
	return r2_hash::handler_compare_sensitive ((const STR1 *) p1, (const STR1 *) p2);
}


bool r2_hash::handler_compare_insensitive (STR1 *p1, STR1 *p2) {
	return r2_hash::handler_compare_insensitive ((const STR1 *) p1, (const STR1 *) p2);
}




/* ���ȽϺ��� (const) */

bool r2_hash::handler_compare_sensitive (const STR1 *p1, const STR1 *p2) {
	return (* p1) == p2;
}


bool r2_hash::handler_compare_insensitive (const STR1 *p1, const STR1 *p2) {
	if(stricmp (p1->pointer ( ), p2->pointer ( )) == 0) {
		return true;
	} else {
		return false;
	}
}




/* ��ϣ���� */
STR1 * r2_hash::handler_build (STR1 *p) {
	return new STR1 (p);
}




/* ��ϣ���� */
void r2_hash::handler_delete (STR1 *p) {
	delete p;
}


