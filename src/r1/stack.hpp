/*
	$ [KiPHP] /r1/stack.hpp  (1406)    (C) 2005-2014  MF
*/


#if KI_RING >= 1

#ifndef _R1_STACK_H_
#define _R1_STACK_H_



#define __TEMPLATE__	template <class T, void (* Cd)(T)>
#define __CLASS__		r1_stack<T, Cd>




__TEMPLATE__ __CLASS__::r1_stack (void) {
	// ��ʼ��Ԫ��
	this->top	= NULL;
	this->count	= 0;
}


__TEMPLATE__ __CLASS__::~r1_stack (void) {
	if(this->count == 0) {
		return;
	}

	// �����������нڵ�
	while(this->top != NULL) {
		r1_node<T> *	prev	= this->top->prev;

		// ��������
		if(Cd != NULL) {
			Cd (this->top->data);
		}

		// ���ٽڵ�
		delete this->top;

		this->top	= prev;
	}
}




/* ѹջ */
__TEMPLATE__ void __CLASS__::operator += (T data) {
	this->push (data);
}


/* ��ջ */
__TEMPLATE__ void __CLASS__::operator -- (int dummy) {
	this->pop ( );
}




/* ��ȡԪ�� */
__TEMPLATE__ T __CLASS__::operator [] (unsigned int offset) const {
	return this->peek (offset);
}




/* ѹջ */
__TEMPLATE__ void __CLASS__::push (T data) {
	r1_node<T> *	node	= new r1_node<T>;

	node->data	= data;
	node->prev	= this->top;
	node->next	= NULL;

	// ����ջ���ڵ�ĺ�һ���ڵ�
	if(this->top != NULL) {
		this->top->next	= node;
	}

	// ����ջ���ڵ�
	this->top	= node;

	this->count	++;
}


/* ��ջ */
__TEMPLATE__ void __CLASS__::pop (void) {
	if(this->count == 0) {
		O0::runtime ("���ԶԿ�ջִ����ջ������");
	}

	// ջ���ڵ��ǰһ���ڵ�
	r1_node<T> *	prev	= this->top->prev;

	// ��������
	if(Cd != NULL) {
		Cd (this->top->data);
	}

	// ���ٽڵ�
	delete this->top;

	// ����ջ���ڵ�
	this->top	= prev;

	this->count	--;
}




/* ջ��Ԫ�� */
__TEMPLATE__ T __CLASS__::peek (unsigned int offset = 0) const {
	if(this->count <= offset) {
		O0::runtime ("���Է��ʳ���ջ��Χ��Ԫ�ء�");
	}

	// ջ���ڵ�
	r1_node<T> *	node	= this->top;

	// ����ָ���ڵ�
	for(unsigned int i = 0; i < offset; i ++) {
		node	= node->prev;
	}

	return node->data;
}




/* ��Ԫ��ð�ݵ�ջ�� */
__TEMPLATE__ void __CLASS__::bubble (unsigned int offset) {
	if((offset == 0) || (this->count <= offset)) {
		O0::runtime ("����ð�ݳ���ջ��Χ��Ԫ�ء�");
	}

	// ջ���ڵ�
	r1_node<T> *	node	= this->top;

	// ����ָ���ڵ�
	for(unsigned int i = 0; i < offset; i ++) {
		node	= node->prev;
	}

	// ����ָ���ڵ��ǰһ���ڵ� 
	if(node->prev != NULL) {
		node->prev->next	= node->next;
	}

	// ����ָ���ڵ�ĺ�һ���ڵ�
	node->next->prev	= node->prev;

	node->prev			= this->top;

	this->top->next		= node;

	this->top			= node;
}




/* �ж��Ƿ�ջ�� */
__TEMPLATE__ bool __CLASS__::empty (void) const {
	if(this->count == 0) {
		return true;
	} else {
		return false;
	}
}




#undef __CLASS__
#undef __TEMPLATE__



#endif

#endif