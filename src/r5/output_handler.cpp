/*
	$ [KiPHP] /r5/output_handler.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			5

#include "../kiviuq.h"




/* ����հ� */
void r5_output_handler::print_space (void) {
	for(unsigned int i = 0; i < this->indent; i ++) {
		O0::print ("\t");
	}
}


/* ������Ա���� */
void r5_output_handler::print_feature (r2_class_feature_t feature) {
	switch(feature->access) {
		case R2_CLS_FTR_ACCESS_PUBLIC:		O0::print ("public "	);		break;
		case R2_CLS_FTR_ACCESS_PROTECTED:	O0::print ("protected "	);		break;
		case R2_CLS_FTR_ACCESS_PRIVATE:		O0::print ("private "	);		break;
	}

	if(feature->_abstract)	{	O0::print ("abstract "	);		}
	if(feature->_final)		{	O0::print ("final "		);		}
	if(feature->_static)	{	O0::print ("static "	);		}
}


/* ��������� */
void r5_output_handler::print_operand (r2_code_directive_operand_t operand) {
	switch(operand->type) {
		case R2_CD_OPND_CONSTANT:
			switch(operand->v._constant) {
				case R2_CD_OPND_CONSTANT_NULL:		O0::print ("null");				break;
				case R2_CD_OPND_CONSTANT_TRUE:		O0::print ("true");				break;
				case R2_CD_OPND_CONSTANT_FALSE:		O0::print ("false");			break;
				case R2_CD_OPND_CONSTANT_FUNCTION:	O0::print ("__FUNCTION__");		break;
				case R2_CD_OPND_CONSTANT_CLASS:		O0::print ("__CLASS__");		break;
				case R2_CD_OPND_CONSTANT_METHOD:	O0::print ("__METHOD__");		break;
				case R2_CD_OPND_CONSTANT_DIR:		O0::print ("__DIR__");			break;
				case R2_CD_OPND_CONSTANT_FILE:		O0::print ("__FILE__");			break;
			}
			break;

		case R2_CD_OPND_IDENTIFIER:
			O0::printf ("%s", operand->v._identifier->pointer ( ));
			break;

		case R2_CD_OPND_INTEGER:
			O0::printf ("%d", operand->v._integer);
			break;

		case R2_CD_OPND_FLOAT:
			O0::printf ("%lf", operand->v._float);
			break;

		case R2_CD_OPND_STRING:
			this->print_string (operand->v._string);
			break;
	}
}


/* ����ַ��� */
void r5_output_handler::print_string (const STR1 *p) {
	const char *	buffer	= p->pointer ( );

	unsigned int	length	= p->length ( );

	O0::print ("\"");

	for(unsigned int i = 0; i < length; i ++) {
		if(buffer [i] == '$') {
			O0::putchar ('\\');
		}

		O0::putchar ((int) buffer [i]);
	}

	O0::print ("\"");
}




void r5_output_handler::execute (void) {
	this->indent	= 0;

	O0::print ("<?php\n\n");

	// ������
	if(RCD4::table_class->ready ( ) == true) {
		r2_class_t	cls;

		while(RCD4::table_class->fetch (& cls) == true) {
			// ���л���ǩ
			r5_output::serialize (cls->code);

			O0::printf ("if(class_exists (\"%s\", false) == false) {\n", cls->name->pointer ( ));

			this->indent ++;

			this->print_space	( );
			this->print_feature	(cls);

			O0::printf ("class %s", cls->name->pointer ( ));

			// �������
			if(cls->_extend != NULL) {
				O0::printf (" extends %s", cls->_extend->pointer ( ));
			}

			// ����ӿ�
			if(cls->_implement->ready ( ) == true) {
				STR1 *			interf;
				const char *	split	= " implements ";

				while(cls->_implement->fetch (& interf) == true) {
					O0::printf ("%s%s", split, interf->pointer ( ));

					split	= ", ";
				}
			}

			O0::print (" {\n");

			this->indent ++;

			// �������
			if(cls->_const->ready ( ) == true) {
				r2_class_const_t	constant;

				while(cls->_const->fetch (& constant) == true) {
					this->print_space ( );

					O0::printf ("const %s = ", constant->name->pointer ( ));

					this->print_operand (& constant->value);

					O0::print (";\n");
				}

				O0::print ("\n");
			}

			// �������
			if(cls->_property->ready ( ) == true) {
				r2_class_property_t	prop;

				while(cls->_property->fetch (& prop) == true) {
					this->print_space	( );
					this->print_feature	(prop);

					O0::printf ("$%s = null;\n", prop->name->pointer ( ));
				}

				O0::print ("\n");
			}

			// �������
			if(cls->_method->ready ( ) == true) {
				r2_class_method_t	method;

				while(cls->_method->fetch (& method) == true) {
					this->print_space	( );
					this->print_feature	(method);

					// �ж��Ƿ�Ϊ���󷽷�
					if(method->_abstract == true) {
						O0::printf ("function %s (", method->name->pointer ( ));

						const char *	comma	= "";

						// ����������
						for(unsigned int i = method->parameter_total - method->parameter_optional; i > 0; i --) {
							O0::printf ("%s$v", comma);

							comma	= ", ";
						}

						// �����ѡ����
						for(unsigned int i = method->parameter_optional; i > 0; i --) {
							O0::printf ("%s$v = 0", comma);

							comma	= ", ";
						}

						// �ж��Ƿ�����˲���
						if(* comma == '\0') {
							O0::print (" ");
						}

						O0::print (");\n");
					} else {
						O0::printf ("function %s ( ) {", method->name->pointer ( ));

						if(method->entry == NULL) {
							O0::print (" ");
						} else {
							this->callback_function (cls, method->entry);
						}

						O0::print ("}\n");
					}
				}

				O0::print ("\n");
			}

			r2_class_feature_o feature;

			// ��ں�������
			feature.access		= R2_CLS_FTR_ACCESS_PUBLIC;
			feature._final		= true;
			feature._static		= true;
			feature._abstract	= false;

			this->print_space	( );
			this->print_feature	(& feature);

			O0::printf ("function %s ($%s, $args = array ( ), $that = null) {\n", C3(vm_entry)->pointer ( ), C3(vm_program)->pointer ( ));

			this->indent ++;

			this->callback_begin ( );

			// �����������
			if(cls->code->ready ( ) == true) {
				r2_code_t	code;

				while(cls->code->fetch (& code) == true) {
					this->callback_code (code);
				}
			}

			this->callback_end ( );

			this->indent --;

			O0::print  ("\t\t}\n");
			O0::print  ("\t}\n\n");
			O0::printf ("\t%s::%s (0);\n", cls->name->pointer ( ), C3(vm_entry)->pointer ( ));
			O0::print  ("}\n\n\n");

			this->indent --;
			this->indent --;
		}
	}

	// �ű�ִ�д���
	O0::printf ("%s::%s (1);\n\n", C3(vm_wrapper)->pointer ( ), C3(vm_entry)->pointer ( ));
}


