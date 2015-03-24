/*
	$ [KiPHP] /r4/builder.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			4

#include "../kiviuq.h"




/* ��ȡȫ�ֱ��� */
r2_variable_t r4_builder::variable_fetch (const STR1 *name) {
	r2_variable_t	node	= (* RCD4::table_variable) [name];

	// �жϱ����Ƿ񲻴���
	if(node == NULL) {
		node		= newz r2_variable_o;

		node->name	= new STR1 (name);

		// ���浽ȫ�ֱ�����
		RCD4::table_variable->write (name, node);
	}

	return node;
}


/* ����ȫ�ֱ��� */
void r4_builder::variable_export (const STR1 *name) {
	r2_variable_t	node	= r4_builder::variable_fetch (name);

	if(node->visible == false) {
		node->visible		= true;
		node->line_export	= RCD4::line;
	}
}




/* ���뺯�� */
void r4_builder::function_enter (const STR1 *name) {
	if(RCD4::function != NULL) {
		O0::runtime ("���뺯������ʧ�ܣ������������ڱ����塣");
	}

	if(RCD4::cls == NULL) {
		RCD4::function	= r4_builder::function_fetch (name);

		// ���ݺ�������ж��Ƿ��ѱ�����
		if(RCD4::function->entry != NULL) {
			RCD4::error (true, "���� %s �ظ����壬��һ�ζ���λ�ڵ� %u �С�", name->pointer ( ), RCD4::function->line_declare);
		}

		// �ж��Ƿ�Ĭ��Ϊ��������
		if(C3(enable_inline) == false) {
			RCD4::function->visible		= true;
		}

		// ������������������
		RCD4::var	= new VAR4 (NULL, name);
	} else {
		r2_class_method_t	method	= (* RCD4::cls->_method) [name];

		// �жϷ����Ƿ��ѱ�����
		if(method != NULL) {
			RCD4::error (true, "���� %s::%s �ظ����壬��һ�ζ���λ�ڵ� %u �С�", RCD4::cls->name->pointer ( ), name->pointer ( ), method->line_declare);
		}

		// ��������
		method	= newz r2_class_method_o;

		method->name	= new STR1 (name);

		method->feature (RCD4::class_feature);

		// ���浽������
		RCD4::cls->_method->write (name, method);

		// ָ�򷽷�
		RCD4::function	= method;

		// ��ǰ����ָ����ڴ���
		RCD4::code		= RCD4::cls->code_entry;

		// ������������������
		RCD4::var		= new VAR4 (RCD4::cls->name, name);
	}

	// ��ڱ�ǩ
	r2_code_t	label	= COD4::label ( );

	// �����ǩ
	* RCD4::code	+= label;

	// �������
	RCD4::function->entry			= label;

	// ���ö�������
	RCD4::function->line_declare	= RCD4::line;
}


/* �˳����� */
void r4_builder::function_leave (void) {
	if(RCD4::function == NULL) {
		O0::runtime ("�˳���������ʧ�ܣ�û�к������ڱ����塣");
	}

	RCD4::function	= NULL;

	// ɾ������������
	delete RCD4::var;

	if(RCD4::cls == NULL) {
		// ����ǰ����������ӳ��Ϊȫ�ֱ���������
		RCD4::var	= RCD4::var_global;
	} else {
		RCD4::var	= NULL;

		// ��ǰ����ָ����������
		RCD4::code	= RCD4::cls->code_boot;
	}
}


/* ���ú��� */
r2_function_t r4_builder::function_call (const STR1 *name, r2_code_directive_operand_t p) {
	r2_function_t	node	= r4_builder::function_fetch (name);

	// �ж��Ƿ�Ϊ��һ�ε���
	if(node->line_call == 0) {
		node->line_call	= RCD4::line;
	}

	// ���浽���ñ�
	* node->caller	+= p;

	return node;
}


/* ��ȡ���� */
r2_function_t r4_builder::function_fetch (const STR1 *name) {
	r2_function_t	node	= (* RCD4::table_function) [name];

	// �жϺ����Ƿ񲻴���
	if(node == NULL) {
		node	= newz r2_function_o;

		node->name		= new STR1 (name);
		node->caller	= new LST1<r2_code_directive_operand_t>;

		// ���浽������
		RCD4::table_function->write (name, node);
	}

	return node;
}


/* �������� */
void r4_builder::function_export (const STR1 *name) {
	r2_function_t	node	= r4_builder::function_fetch (name);

	if(node->visible == false) {
		node->visible		= true;
		node->line_export	= RCD4::line;
	}
}




/* ������ */
void r4_builder::class_enter (const STR1 *name) {
	if(RCD4::cls != NULL) {
		O0::runtime ("�����ඨ��ʧ�ܣ����������ڱ����塣");
	}

	// �ж����Ƿ��ѱ�����
	if(RCD4::table_class->exist (name) == true) {
		r2_class_t	last	= (* RCD4::table_class) [name];

		RCD4::error (true, "�� %s �ظ����壬��һ�ζ���λ�ڵ� %u �С�", name->pointer ( ), last->line);
	}

	// ������
	RCD4::cls	= r4_builder::class_fetch (name);

	// ��ʼ�����Ա����
	RCD4::class_feature		= newz r2_class_feature_o;

	// ��ǰ����ָ����������
	RCD4::code		= RCD4::cls->code_boot;

	// û�б���������
	RCD4::var		= NULL;

	// û�ж����κκ���
	RCD4::function	= NULL;
}


/* �˳��� */
void r4_builder::class_leave (void) {
	if(RCD4::cls == NULL) {
		O0::runtime ("�˳��ඨ��ʧ�ܣ�û�������ڱ����塣");
	}

	// ɾ�����Ա����
	delete RCD4::class_feature;

	RCD4::class_feature	= NULL;

	// ��ǰ����ӳ��Ϊȫ�ִ���
	RCD4::code	= RCD4::code_global;

	// ��ǰ����������ӳ��Ϊȫ�ֱ���������
	RCD4::var	= RCD4::var_global;

	// ��ֹ�ඨ��
	RCD4::cls	= NULL;

	// ��ֹ��������
	RCD4::function	= NULL;
}


/* ��ʵ�ֽӿ� */
void r4_builder::class_implement (const STR1 *name) {
	if(RCD4::cls == NULL) {
		O0::runtime ("�����ඨ��ʧ�ܣ�û�������ڱ����塣");
	}

	// �жϽӿ��Ƿ��ѱ�ʵ��
	if(RCD4::cls->_implement->exist (name) == true) {
		RCD4::error (true, "�� %s �ظ�ʵ�ֽӿ� %s��", RCD4::cls->name->pointer ( ), name->pointer ( ));
	}

	RCD4::cls->_implement->write (name, new STR1 (name));
}


/* �ೣ������ */
void r4_builder::class_declare_const (const STR1 *name, r2_code_directive_operand_t operand) {
	if(RCD4::cls == NULL) {
		O0::runtime ("�����ඨ��ʧ�ܣ�û�������ڱ����塣");
	}

	// �жϳ����Ƿ񱻶���
	if(RCD4::cls->_const->exist (name) == true) {
		r2_class_const_t	last	= (* RCD4::cls->_const) [name];

		RCD4::error (true, "�ೣ�� %s::%s �ظ����壬��һ�ζ���λ�ڵ� %u �С�", RCD4::cls->name->pointer ( ), name->pointer ( ), last->line);
	}

	r2_class_const_t	node	= newz r2_class_const_o;

	node->name	= new STR1 (name);
	node->line	= RCD4::line;

	// ���泣������
	M0::copy (& node->value, operand, sizeof node->value);

	// ���浽�ೣ����
	RCD4::cls->_const->write (name, node);
}


/* �����Զ��� */
void r4_builder::class_declare_property (const STR1 *name) {
	if(RCD4::cls == NULL) {
		O0::runtime ("�����ඨ��ʧ�ܣ�û�������ڱ����塣");
	}

	// �ж����Ƿ񱻶���
	if(RCD4::cls->_property->exist (name) == true) {
		r2_class_property_t		last	= (* RCD4::cls->_property) [name];

		RCD4::error (true, "������ %s::$%s �ظ����壬��һ�ζ���λ�ڵ� %u �С�", RCD4::cls->name->pointer ( ), name->pointer ( ), last->line);
	}

	r2_class_property_t		node	= newz r2_class_property_o;

	node->name	= new STR1 (name);
	node->line	= RCD4::line;

	// ����������
	node->feature (RCD4::class_feature);

	// ���浽�����Ա�
	RCD4::cls->_property->write (name, node);
}


/* ��ȡ�� */
r2_class_t r4_builder::class_fetch (const STR1 *name, LST1<r2_code_t> *code) {
	r2_class_t	node	= (* RCD4::table_class) [name];

	// �ж����Ƿ񲻴���
	if(node == NULL) {
		node	= newz r2_class_o;

		node->name		= new STR1 (name);
		node->line		= RCD4::line;

		node->_implement	= new TBL1<STR1 *, r2_hash::size_small, NULL, r2_hash::handler_index_short, r2_hash::handler_compare_insensitive, r2_hash::handler_delete> ( );

		node->_const		= new TBL1<r2_class_const_t,	r2_hash::size_small,	NULL,	r2_hash::handler_index_short,	r2_hash::handler_compare_sensitive,		r2_class::handler_delete_const>		( );
		node->_property		= new TBL1<r2_class_property_t,	r2_hash::size_small,	NULL,	r2_hash::handler_index_short,	r2_hash::handler_compare_sensitive,		r2_class::handler_delete_property>	( );
		node->_method		= new TBL1<r2_class_method_t,	r2_hash::size_small,	NULL,	r2_hash::handler_index_short,	r2_hash::handler_compare_insensitive,	r2_class::handler_delete_method>	( );

		// ��������
		node->code_boot		= new LST1<r2_code_t> ( );

		// ��ڴ���
		if(code == NULL) {
			node->code_entry	= new LST1<r2_code_t> ( );
		} else {
			node->code_entry	= code;
		}

		// ���浽���
		RCD4::table_class->write (name, node);
	}

	return node;
}




/* ����������� */
void r4_builder::collect (void) {
	// �ϲ���ȫ�ֱ���
	if(VAR4::heap->ready ( ) == true) {
		r2_variable_t	var;

		while(VAR4::heap->fetch (& var) == true) {
			// �ж��Ƿ�Ϊ��ȫ�ֱ���
			if(var->super == true) {
				continue;
			}

			const char *	p	= var->name->pointer ( );

			// �ж��Ƿ�Ϊ��̬����
			if(* p != '@') {
				continue;
			}

			// ʵ�ʱ�����
			STR1	name	("%s", p + 1);

			// ��ȫ�ֱ������л�ȡ����
			r2_variable_t	node	= r4_builder::variable_fetch (& name);

			node->line		= var->line;
			node->offset	= var->offset;
		}
	}

	// ����ȫ�ֱ���
	if(RCD4::table_variable->ready ( ) == true) {
		r2_variable_t	var;

		while(RCD4::table_variable->fetch (& var) == true) {
			// �ж��Ƿ񵼳���δ����
			if((var->visible == true) && (var->offset == 0)) {
				if(var->line_export == 0) {
					RCD4::warning (false, "ʹ�� -Ev �������Ե���δ�����ȫ�ֱ��� $%s��", var->name->pointer ( ));
				} else {
					RCD4::warning (var->line_export, "ʹ�ñ�����ע #!export ���Ե���δ�����ȫ�ֱ��� $%s��", var->name->pointer ( ));
				}
			}
		}
	}

	// ��������
	if(RCD4::table_function->ready ( ) == true) {
		r2_function_t	node;

		while(RCD4::table_function->fetch (& node) == true) {
			// �ж��Ƿ񵼳�
			if(node->visible == true) {
				// �ж��Ƿ�δ����
				if(node->entry == NULL) {
					if(node->line_export == 0) {
						RCD4::warning (false, "ʹ�� -Ef �������Ե���δ����ĺ��� %s��", node->name->pointer ( ));
					} else {
						RCD4::warning (node->line_export, "ʹ�ñ�����ע #!export ���Ե���δ����ĺ��� %s��", node->name->pointer ( ));
					}
				}
			} else {
				// �ж��Ƿ�δ��ʹ��
				if(node->caller->count == 0) {
					RCD4::warning (node->line_declare, "�������� %s δ���������ⲿ���ɼ���", node->name->pointer ( ));
				}
			}

			// ������
			r4_builder::collect_function (node);
		}
	}

	// �ж��Ƿ��������װ������ͻ
	if(RCD4::table_class->exist (C3(vm_wrapper)) == true) {
		r2_class_t	node	= (* RCD4::table_class) [C3(vm_wrapper)];

		RCD4::error (node->line, "�� %s ���Ƴ�ͻ�����������װ��������ͬ��", node->name->pointer ( ));
	}

	// ���������
	r4_builder::collect_vm ( );

	// ������
	if(RCD4::table_class->ready ( ) == true) {
		r2_class_t	node;

		while(RCD4::table_class->fetch (& node) == true) {
			if(node->_method->exist (C3(vm_entry)) == true) {
				r2_class_method_t	method	= (* node->_method) [C3(vm_entry)];

				RCD4::error (method->line_declare, "���� %s::%s ���Ƴ�ͻ���������������ڷ�������ͬ��", node->name->pointer ( ), method->name->pointer ( ));
			}

			// ������
			r4_builder::collect_class (node);
		}
	}
}


/* ��������� */
void r4_builder::collect_vm (void) {
	// ������
	r2_class_t	node	= r4_builder::class_fetch (C3(vm_wrapper), RCD4::code_global);

	node->_final	= true;

	node->code_boot->ready ( );

	// ����������
	r2_class_property_t		heap	= newz r2_class_property_o;

	// ����������
	heap->name	= new STR1 (C3(vm_heap));

	// ����������
	heap->access	= R2_CLS_FTR_ACCESS_PUBLIC;
	heap->_final	= true;
	heap->_static	= true;

	// ���浽�����Ա�
	node->_property->write (C3(vm_heap), heap);

	// �������췽��
	r2_class_method_t	method	= newz r2_class_method_o;

	// ���췽������
	method->name	= new STR1 ("__construct");

	// ���췽����������
	method->access	= R2_CLS_FTR_ACCESS_PRIVATE;

	// ���浽�෽����
	node->_method->write ("__construct", method);

	// ������ȫ�ֱ���
	if(VAR4::heap->ready ( ) == true) {
		r2_variable_t	var;

		while(VAR4::heap->fetch (& var) == true) {
			if(var->super == false) {
				continue;
			}

			STR1	name	("%s", var->name->pointer ( ) + 1);

			r2_code_t	code	= COD4::directive (R2_CD_OPC_REF, "AhD", var->offset, & name);

			* node->code_boot	+= code;
		}
	}
}


/* ������ */
void r4_builder::collect_function (r2_function_t node) {
	r2_code_directive_operand_t	operand;

	node->caller->ready ( );

	// �ж��Ƿ���
	if(node->entry == NULL) {
		while(node->caller->fetch (& operand) == true) {
			COD4::operand (operand, "D", node->name);
		}
	} else {
		while(node->caller->fetch (& operand) == true) {
			COD4::operand (operand, "L", node->entry);
		}
	}
}


/* ������ */
void r4_builder::collect_class	(r2_class_t node) {
	// ��ʼ������ָ��
	r2_code_t	code	= COD4::directive (R2_CD_OPC_RETN, NULL);

	node->code_boot ->ready ( );
	node->code_entry->ready ( );

	// ������ǩ
	node->label_code_boot	= COD4::label ( );
	node->label_code_entry	= COD4::label ( );

	// �����ǩ
	node->code_boot ->insert (node->label_code_boot,	false);
	node->code_entry->insert (node->label_code_entry,	false);

	// �����ʼ������ָ��
	node->code_entry->insert (code, false);

	// ������������
	node->code	= new LST1<r2_code_t, r2_class::handler_delete_code>;

	// �ϲ�����
	node->code->concat (node->code_boot);
	node->code->concat (node->code_entry);
}


