/*
	$ [KiPHP] /r1/singleton.hpp  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 1

#ifndef _R1_SINGLETON_H_
#define _R1_SINGLETON_H_



#define __TEMPLATE__	template <class T, unsigned int S, T (*Cb)(T), unsigned int (* Ci)(T), bool (* Cc)(T, T), void (* Cd)(T)>
#define __CLASS__		r1_singleton<T, S, Cb, Ci, Cc, Cd>




__TEMPLATE__ __CLASS__::r1_singleton (void) {
	// ��ʼ��ӳ���
	M0::zero (& this->table, sizeof this->table);
}


__TEMPLATE__ __CLASS__::~r1_singleton (void) {
	// ��������ӳ���
	for(unsigned int i = 0; i <= S; i ++) {
		// ��ǰ��ָ��
		r1_node<T> **	list	= r1_singleton::table + i;

		while(* list != NULL) {
			r1_node<T> *	node	= * list;

			// ��һ���ڵ�
			r1_node<T> *	next	= node->next;

			// ��������
			if(Cd != NULL) {
				Cd (node->data);
			}

			// ���ٽڵ�
			delete node;

			* list	= next;
		}
	}
}




/* ��ȡԪ�� */
__TEMPLATE__ T __CLASS__::fetch (T data) {
	// ��������
	unsigned int	index	= Ci (data);

	// ������Χ����
	index	= index % S;

	// �ڵ�ָ��
	r1_node<T> *	node	= this->table [index];

	// ������ѯ
	while(node != NULL) {
		if(Cc (data, node->data) == true) {
			// ����ֵ
			return node->data;
		}

		node	= node->next;
	}

	// �����ڵ�
	node	= new r1_node<T>;

	node->data	= Cb (data);
	node->next	= this->table [index];

	// ���浽��Ӧ��������
	this->table [index]	= node;

	return node->data;
}




#undef __CLASS__
#undef __TEMPLATE__



#endif

#endif