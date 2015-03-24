/*
	$ [KiPHP] /r1/hashtable.hpp  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 1

#ifndef _R1_HASHTABLE_H_
#define _R1_HASHTABLE_H_



#define __TEMPLATE__	template <class T, unsigned int S, T D, unsigned int (* Ci)(const STR1 *), bool (* Cc)(const STR1 *, const STR1 *), void (* Cd)(T)>
#define __CLASS__		r1_hashtable<T, S, D, Ci, Cc, Cd>




__TEMPLATE__ __CLASS__::r1_hashtable (void) {
	// ��ʼ��ӳ���
	M0::zero (& this->table, sizeof this->table);

	// ��ʼ���ڵ�ָ��
	this->head	= NULL;
	this->tail	= NULL;
	this->seek	= NULL;

	// ��ʼ���ڵ�����
	this->count	= 0;
}


__TEMPLATE__ __CLASS__::~r1_hashtable (void) {
	if(this->count == 0) {
		return;
	}

	r1_node_duo<T> *	node	= this->head;

	// �����ͷŽڵ�
	while(node != NULL) {
		r1_node_duo<T> *	next	= node->next2;

		// ��������
		if(Cd != NULL) {
			Cd (node->value);
		}

		// ���ټ�
		delete node->key;

		// ���ٽڵ�
		delete node;

		node	= next;
	}
}




/* ��ȡԪ�� */

__TEMPLATE__ T __CLASS__::operator [] (const STR1 &p) {
	return this->read (* p);
}


__TEMPLATE__ T __CLASS__::operator [] (const STR1 *p) {
	return this->read (p);
}


__TEMPLATE__ T __CLASS__::operator [] (const char *p) {
	return this->read (p);
}




/* ��ȡԪ�� */
__TEMPLATE__ T * __CLASS__::at (const STR1 *p, bool created = true) {
	// ��������
	unsigned int	index	= Ci (p);

	// ������Χ����
	index	= index % S;

	// �ڵ�ָ��
	r1_node_duo<T> *	node	= this->table [index];

	// ������ѯ
	while(node != NULL) {
		// �Ƚϼ�
		if(Cc (p, node->key) == true) {
			break;
		}

		node	= node->next1;
	}

	// �ж��Ƿ��ҵ��ڵ�
	if(node == NULL) {
		// �ж��Ƿ񴴽��ڵ�
		if(created == false) {
			return NULL;
		}

		// �����ڵ�
		node	= new r1_node_duo<T>;

		// ������
		node->key		= new STR1 (p);

		// ����Ĭ������
		node->value		= D;

		// ����ָ��
		node->next1		= this->table [index];
		node->next2		= NULL;

		// ���浽��Ӧ��������
		this->table [index]	= node;

		// ���浽��������
		if(this->head == NULL) {
			this->head	= node;
		} else {
			this->tail->next2	= node;
		}

		this->tail	= node;

		this->count ++;
	}

	return & node->value;
}




/* ��ȡԪ�� */

__TEMPLATE__ T __CLASS__::read (const STR1 &p) {
	return this->read (* p);
}


__TEMPLATE__ T __CLASS__::read (const STR1 *p) {
	return  * (this->at (p, true));
}


__TEMPLATE__ T __CLASS__::read (const char *p) {
	// ��
	STR1	key		("%s", p);

	return this->read (& key);
}




/* д������ */

__TEMPLATE__ void __CLASS__::write (const STR1 &p, T data) {
	this->write (* p, data);
}


__TEMPLATE__ void __CLASS__::write (const STR1 *p, T data) {
	// ֵָ��
	T *		node	= this->at (p, true);

	// ��������
	if(Cd != NULL) {
		Cd (* node);
	}

	// ��������
	* (this->at (p, true))	= data;
}


__TEMPLATE__ void __CLASS__::write (const char *p, T data) {
	// ��
	STR1	key		("%s", p);

	this->write (& key, data);
}




/* ���Ԫ���Ƿ���� */

__TEMPLATE__ bool __CLASS__::exist (const STR1 &p) {
	return this->exist (& p);
}


__TEMPLATE__ bool __CLASS__::exist (const STR1 *p) {
	if(this->at (p, false) == NULL) {
		return false;
	} else {
		return true;
	}
}


__TEMPLATE__ bool __CLASS__::exist (const char *p) {
	// �����ַ���
	STR1	key		("%s", p);

	return this->exist (& key);
}




/* ����Ԥ�� */
__TEMPLATE__ bool __CLASS__::ready (void) {
	if(this->count == 0) {
		return false;
	}

	this->seek	= this->head;

	return true;
}


/* ��ȡ��ǰ����Ԫ�� */
__TEMPLATE__ bool __CLASS__::fetch (T *p1, const STR1 **p2) {
	// �ж��Ƿ��������
	if(this->seek == NULL) {
		return false;
	}

	// ����ֵ
	* p1	= this->seek->value;

	// ���ؼ�
	if(p2 != NULL) {
		* p2	= this->seek->key;
	}

	// ���±���ָ��
	this->seek	= this->seek->next2;

	return true;
}




#undef __CLASS__
#undef __TEMPLATE__



#endif

#endif