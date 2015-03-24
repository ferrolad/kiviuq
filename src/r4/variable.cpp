/*
	$ [KiPHP] /r4/variable.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			4

#include "../kiviuq.h"




/* ��ȫ�ֱ����� */
TBL1<r2_variable_t, r2_hash::size_small, NULL, r2_hash::handler_index_short, r2_hash::handler_compare_sensitive, NULL> *	r4_variable::super	= NULL;

/* �ѱ����� */
TBL1<r2_variable_t, r2_hash::size_small, NULL, r4_variable::handler_index, r4_variable::handler_compare, r4_variable::handler_delete> *		r4_variable::heap	= NULL;




KI_LOADER_BOOT (r4_variable) {
	// ������ȫ�ֱ�����
	r4_variable::super	= new TBL1<r2_variable_t, r2_hash::size_small, NULL, r2_hash::handler_index_short, r2_hash::handler_compare_sensitive, NULL>;
	// �����ѱ�����
	r4_variable::heap	= new TBL1<r2_variable_t, r2_hash::size_small, NULL, r4_variable::handler_index, r4_variable::handler_compare, r4_variable::handler_delete>;

	// ע�ᳬȫ�ֱ���
	r4_variable::register_super ("GLOBALS");
	r4_variable::register_super ("_SERVER");
	r4_variable::register_super ("_GET");
	r4_variable::register_super ("_POST");
	r4_variable::register_super ("_FILES");
	r4_variable::register_super ("_COOKIE");
	r4_variable::register_super ("_REQUEST");
	r4_variable::register_super ("_SESSION");
	r4_variable::register_super ("_ENV");
}


KI_LOADER_SHUTDOWN (r4_variable) {
	// ���ٳ�ȫ�ֱ�����
	delete r4_variable::super;

	// ���ٶѱ�����
	delete r4_variable::heap;
}




r4_variable::r4_variable (const STR1 *name_class, const STR1 *name_function, unsigned int offset) {
	// �ж�ȫ��������
	if(name_function == NULL) {
		this->global	= true;

		// ȫ�ֱ���ǰ׺
		this->prefix	= new STR1 ("@");
	} else {
		this->global	= false;

		this->prefix	= new STR1 ( );

		// ����ǰ׺
		if(name_class == NULL) {
			this->prefix->concat ("::");
		} else {
			this->prefix->concat ("%s::", name_class->pointer ( ));
		}

		// ������ǰ׺
		this->prefix->concat ("%s@", name_function->pointer ( ));
	}

	// ����ջ��ƫ����
	this->offset	= offset;

	// ����ջ������
	this->stack		= new TBL1<r2_variable_t, r2_hash::size_small, NULL, r4_variable::handler_index, r4_variable::handler_compare, r4_variable::handler_delete>;
}


r4_variable::~r4_variable (void) {
	// ����ǰ׺
	delete this->prefix;

	// ����ջ������
	delete this->stack;
}




unsigned int r4_variable::handler_index (const STR1 *p) {
	// ����
	const char *	buffer	= p->pointer ( );
	// ���Ƴ���
	unsigned int	length	= p->length ( );

	// �ж��Ƿ�Ϊ��ȫ�ֱ���
	if(* buffer != '#') {
		// ����ǰ׺����
		const char *	start	= strchr (buffer, '@');

		length	= length - (start - buffer);
		buffer	= start;
	}

	return r2_hash::handler_index (buffer, length, r2_hash::max_short);
}


bool r4_variable::handler_compare (const STR1 *p1, const STR1 *p2) {
	const char *	buffer_1	= p1->pointer ( );
	const char *	buffer_2	= p2->pointer ( );

	// �Ƚ�����
	if(strcmp (buffer_1, buffer_2) == 0) {
		return true;
	} else {
		return false;
	}
}


void r4_variable::handler_delete (r2_variable_t p) {
	if(p == NULL) {
		return;
	}

	// ���ٱ�����
	delete p->name;

	// ���ٱ���
	delete p;
}




r2_variable_t r4_variable::add_heap (const STR1 *name) {
	r2_variable_t	var		= newz r2_variable_o;

	var->name		= new STR1 (name);
	var->line		= RCD4::line;
	var->offset		= r4_variable::heap->count;

	// ��ӵ��ѱ�����
	r4_variable::heap->write (name, var);

	return var;
}


r2_variable_t r4_variable::add_stack (const STR1 *name) {
	r2_variable_t	var		= newz r2_variable_o;

	var->name		= new STR1 (name);
	var->line		= RCD4::line;
	var->offset		= this->stack->count;

	// ��ӵ�ջ������
	this->stack->write (name, var);

	return var;
}




/* ��ȡ���� */

r2_variable_t r4_variable::fetch_heap (const STR1 *name) {
	r2_variable_t	var		= (* r4_variable::heap) [name];

	// ��ӵ��ѱ�����
	if(var == NULL) {
		var	= r4_variable::add_heap (name);

		// ��������ӵĶѱ���ƫ����
		var->offset --;
	}

	return var;
}


r2_variable_t r4_variable::fetch_stack (const STR1 *name) {
	r2_variable_t	var		= (* this->stack) [name];

	// ��ӵ�ջ������
	if(var == NULL) {
		var	= this->add_stack (name);

		// ��������ӵ�ջ����ƫ����
		var->offset	= this->offset + var->offset - 1;
	}

	return var;
}




/* ���²����� */
void r4_variable::update (r2_variable_t var, r2_code_directive_operand_address_base_e base, r2_code_directive_operand_t operand) {
	// �������ô���
	var->reference ++;

	// ���²�����
	operand->type				= R2_CD_OPND_ADDRESS;
	operand->v._address.base	= base;
	operand->v._address.offset	= (signed int) var->offset;
}




/* ע�ᳬȫ�ֱ��� */

void r4_variable::register_super (const char *p) {
	STR1	name	("%s", p);

	r4_variable::register_super (& name);
}


void r4_variable::register_super (const STR1 *p) {
	// ��ȫ�ֱ�����
	STR1	name	("#%s", p->pointer ( ));

	// �жϱ����Ƿ����
	if(r4_variable::super->exist (name) == true) {
		return;
	}

	// ��ӵ��ѱ�����
	r2_variable_t	var		= r4_variable::add_heap (& name);

	// ���ó�ȫ�ֱ������
	var->super	= true;

	// ��ӵ���ȫ�ֱ�����
	r4_variable::super->write (p, var);
}




/* ע�ᾲ̬���� */
bool r4_variable::register_static (const STR1 *p, r2_code_directive_operand_t operand_old, r2_code_directive_operand_t operand_new) {
	// �ж��Ƿ�Ϊ��ȫ�ֱ���
	if(r4_variable::super->exist (p) == true) {
		RCD4::warning (true, "�Գ�ȫ�ֱ��� $%s ʹ�� static �ؼ�����Ч��", p->pointer ( ));

		return false;
	}

	// �ж�ȫ��������
	if(this->global == true) {
		RCD4::warning (true, "��ȫ�ֱ��� $%s ʹ�� static �ؼ�����Ч��", p->pointer ( ));

		return false;
	}

	STR1	name;

	// �ڲ�������
	name	+= this->prefix;
	name	+= p;

	// ��ջ�в��ұ���
	r2_variable_t	var_stack	= this->fetch_stack (& name);

	// �ڶ��в��ұ���
	r2_variable_t	var_heap	= r4_variable::fetch_heap (& name);

	// ջ������ַ
	r4_variable::update (var_stack,	R2_CD_OPND_ADDRESS_BOTTOM,	operand_old);

	// �ѱ�����ַ
	r4_variable::update (var_heap,	R2_CD_OPND_ADDRESS_HEAP,	operand_new);

	return true;
}


/* ע��ȫ�ֱ��� */
bool r4_variable::register_global (const STR1 *p, r2_code_directive_operand_t operand_old, r2_code_directive_operand_t operand_new) {
	// �ж��Ƿ�Ϊ��ȫ�ֱ���
	if(r4_variable::super->exist (p) == true) {
		RCD4::warning (true, "�Գ�ȫ�ֱ��� $%s ʹ�� global �ؼ�����Ч��", p->pointer ( ));

		return false;
	}

	// �ж��Ƿ�Ϊȫ��������
	if(this->global == true) {
		STR1	name;

		// �ڲ�������
		name	+= this->prefix;
		name	+= p;

		// ��Ϊȫ�ֱ�������
		r2_variable_t	var		= r4_variable::fetch_heap (& name);

		// ���ÿɼ���
		var->visible	= true;

		// �������
		RCD4::warning (true, "��ȫ���������У���ȫ�ֱ��� $%s ʹ�� global �ؼ��ʣ���Ϊ���׼ PHP ��һ�£��˴�����ѱ������������Ƽ�ʹ�������÷������赼����������ʹ�ñ�����ע #!export �� -Ev ������", p->pointer ( ));

		return false;
	}

	STR1	name_stack;
	STR1	name_heap;

	// ջ������
	name_stack	+= this->prefix;
	name_stack	+= p;

	// �ѱ�����
	name_heap	+= "@";
	name_heap	+= p;

	// ��ջ�в��ұ���
	r2_variable_t	var_stack	= this->fetch_stack (& name_stack);

	// �ڶ��в��ұ���
	r2_variable_t	var_heap	= r4_variable::fetch_heap (& name_heap);

	// ջ������ַ
	r4_variable::update (var_stack,	R2_CD_OPND_ADDRESS_BOTTOM,	operand_old);

	// �ѱ�����ַ
	r4_variable::update (var_heap,	R2_CD_OPND_ADDRESS_HEAP,	operand_new);

	return true;
}




/* ʹ�ñ��� */
void r4_variable::use (const STR1 *p, r2_code_directive_operand_t operand) {
	// �ж��Ƿ�Ϊ��ȫ�ֱ���
	if(r4_variable::super->exist (p) == true) {
		// ��ȡ���еĳ�ȫ�ֱ�����Ϣ
		r2_variable_t	var		= (* r4_variable::super) [p];

		r4_variable::update (var, R2_CD_OPND_ADDRESS_HEAP, operand);

		return;
	}

	STR1	name;

	// �ڲ�������
	name	+= this->prefix;
	name	+= p;

	// �ж��Ƿ���ȫ��������
	if(this->global == true) {
		// �ڶ��в���
		r2_variable_t	var		= r4_variable::fetch_heap (& name);

		r4_variable::update (var, R2_CD_OPND_ADDRESS_HEAP, operand);
	} else {
		// �ڶ��в���
		r2_variable_t	var		= this->fetch_stack (& name);

		r4_variable::update (var, R2_CD_OPND_ADDRESS_BOTTOM, operand);
	}
}


