/*
	$ [KiPHP] /r1/linkedlist.hpp  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 1

#ifndef _R1_LINKEDLIST_H_
#define _R1_LINKEDLIST_H_



#define __TEMPLATE__	template <class T, void (* Cd)(T)>
#define __CLASS__		r1_linkedlist<T, Cd>




/* ���������� */
__TEMPLATE__ __CLASS__::r1_linkedlist (void) {
	// ��ʼ���ڵ�ָ��
	this->head	= NULL;
	this->tail	= NULL;
	this->seek	= NULL;

	// ��ʼ���ڵ�����
	this->count	= 0;
}


/* ��¡���� */
__TEMPLATE__ __CLASS__::r1_linkedlist (const void *p) {
	// ��������
	recall r1_linkedlist ( );

	// ��������
	this->concat (p);
}




__TEMPLATE__ __CLASS__::~r1_linkedlist (void) {
	r1_node<T> *	node	= this->head;

	// ����ɾ���ڵ�
	while(node != NULL) {
		r1_node<T> *	next	= node->next;

		// ��������
		if(Cd != NULL) {
			Cd (node->data);
		}

		// ���ٽڵ�
		delete node;

		node	= next;
	}
}




/* ����β����Ԫ�� */
__TEMPLATE__ void __CLASS__::operator += (T data) {
	this->append (data);
}


/* ��ȡԪ�� */
__TEMPLATE__ T __CLASS__::operator [] (signed int offset) const {
	return this->at (offset);
}




/* �ƶ�����ָ�� */

__TEMPLATE__ void __CLASS__::operator ++ (int dummy) {
	if(this->seek != NULL) {
		this->seek	= this->seek->next;
	}
}


__TEMPLATE__ void __CLASS__::operator -- (int dummy) {
	// �ж��Ƿ�ӱ���������ǰ�ƶ�
	if(this->seek == NULL) {
		this->seek	= this->tail;

		return;
	}

	// �ж��Ƿ��ƶ�������ͷ
	if(this->seek == this->head) {
		return;
	}

	this->seek	= this->seek->prev;
}




/* ��ȡԪ�� */
__TEMPLATE__ T __CLASS__::at (signed int offset) const {
	// ���ҵĽڵ�
	r1_node<T> *	node	= NULL;

	// ���ݲ�ͬ������ҽڵ�
	if(offset < 0) {
		// ��β����ʼ����
		node	= this->tail;

		// �������
		while((++ offset) < 0) {
			if(node == NULL) {
				break;
			}

			node	= node->prev;
		}
	} else {
		// ��ͷ����ʼ����
		node	= this->head;

		// �������
		while((offset --) > 0) {
			if(node == NULL) {
				break;
			}

			node	= node->next;
		}
	}

	// �ж��Ƿ���ҳɹ�
	if(node == NULL) {
		O0::runtime ("����ͨ����Ч�±��������");
	}

	return node->data;
}




/* �ڵ�ǰԪ��ǰ�����Ԫ�� */
__TEMPLATE__ void __CLASS__::insert (T data, bool after = true) {
	// �ж������Ƿ�Ϊ��
	if(this->head == NULL) {
		// ��β��ֱ�Ӳ���
		this->append (data);

		return;
	}

	r1_node<T> *	node	= new r1_node<T>;

	node->data	= data;

	// ����Ŀ��
	r1_node<T> *	target	= this->seek;

	// �ж��Ƿ��������
	if(this->seek == NULL) {
		target	= this->tail;
	}

	// �жϲ��뷽��
	if(after == true) {
		// �жϲ���Ŀ���Ƿ�Ϊ���һ���ڵ�
		if(target->next == NULL) {
			// ����β�ڵ�
			this->tail	= node;
		} else {
			target->next->prev	= node;
		}

		node->prev	= target;
		node->next	= target->next;

		target->next	= node;
	} else {
		// �жϲ���Ŀ���Ƿ�Ϊ��һ���ڵ�
		if(target->prev == NULL) {
			// ����ͷ���
			this->head	= node;
		} else {
			target->prev->next	= node;
		}

		node->prev	= target->prev;
		node->next	= target;

		target->prev	= node;
	}

	// ���±���ָ��ָ���²���Ľڵ�
	this->seek	= node;
}


/* ����β����Ԫ�� */
__TEMPLATE__ void __CLASS__::append (T data) {
	r1_node<T> *	node	= new r1_node<T>;

	node->data	= data;
	node->prev	= this->tail;
	node->next	= NULL;

	if(this->tail != NULL) {
		this->tail->next	= node;
	}

	// ����ǵ�һ��Ԫ��, ������ͷ
	if(this->head == NULL) {
		this->head	= node;
	}

	// ������β
	this->tail	= node;
	// ���±���ָ��
	this->seek	= node;

	this->count	++;
}




/* ������һ������ */
__TEMPLATE__ void __CLASS__::concat (const void *p) {
	// Դ����
	r1_linkedlist<T, Cd> *	list	= (r1_linkedlist<T, Cd> *) p;

	// Դ����ͷ���
	r1_node<T> *	node	= list->head;

	// ���������ڵ�
	while(node != NULL) {
		this->append (node->data);

		node	= node->next;
	}
}




/* ����Ԥ�� */
__TEMPLATE__ bool __CLASS__::ready (void) {
	// �ж��Ƿ���Ԫ��
	if(this->count == 0) {
		return false;
	}

	// ����Ѱַָ��
	this->seek	= this->head;

	return true;
}


/* ��ȡ��ǰ����Ԫ�� */
__TEMPLATE__ bool __CLASS__::fetch (T *p) {
	// �ж��Ƿ��������
	if(this->seek == NULL) {
		return false;
	}

	// ��������
	* p	= this->seek->data;

	// ���±���ָ��
	this->seek	= this->seek->next;

	return true;
}




#undef __CLASS__
#undef __TEMPLATE__



#endif

#endif