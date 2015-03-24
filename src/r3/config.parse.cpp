/*
	$ [KiPHP] /r3/config.parse.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			3

#include "../kiviuq.h"




/* ������� */
void r3_config::parse (const char *command) {
	KI_LOOKSTR (command, strcmp) {
		// �鿴����	-h
		KI_LOOKSTR_CASE ("-h")				r3_config::output (R3_CONFIG_OUTPUT_HELP);
		// �鿴�汾	-v
		KI_LOOKSTR_CASE ("-v")				r3_config::output (R3_CONFIG_OUTPUT_VERSION);
		// �鿴�ַ�	-distribution
		KI_LOOKSTR_CASE ("-distribution")	r3_config::output (R3_CONFIG_OUTPUT_DISTRIBUTION);


		// ���ļ�
#define	PARSE_FILE(cmd, mode, err)																\
		KI_LOOKSTR_CASE ("-" #cmd)																\
			const char *	file	= r3_config::fetch_string ( );								\
			if(file == NULL) {																	\
				O0::argument ("�����÷� : -" #cmd " {FILE}");										\
			}																					\
			FILE *	fp	= fopen (file, mode);													\
			if(fp == NULL) {																	\
				O0::argument ("��Ч�Ĳ��� : �޷���ָ����" err "���ļ���");							\
			}																					\
			O0::stream_##cmd = fp;

		// �����ļ�	-in {FILE}
		PARSE_FILE (in,		"rb",	"����")
		// ����ļ�	-out {FILE}
		PARSE_FILE (out,	"wb",	"���")
		// �����ļ�	-error {FILE}
		PARSE_FILE (error,	"wb",	"����")
#undef	PARSE_FILE


		// ���ģʽ	-O[cis]
		KI_LOOKSTR_CASE ("-Oc")			C3(output)		= R3_CONFIG_OUTPUT_CODE;
		KI_LOOKSTR_CASE ("-Oi")			C3(output)		= R3_CONFIG_OUTPUT_INTERLANG;
		KI_LOOKSTR_CASE ("-Os")			C3(output)		= R3_CONFIG_OUTPUT_SYMBOL;

		// ����ģʽ	-W[012]
		KI_LOOKSTR_CASE ("-W0")			C3(warning)		= R3_CONFIG_WARNING_DISABLE;
		KI_LOOKSTR_CASE ("-W1")			C3(warning)		= R3_CONFIG_WARNING_NORMAL;
		KI_LOOKSTR_CASE ("-W2")			C3(warning)		= R3_CONFIG_WARNING_ERROR;


		// ����ˮƽ	-N {UINT}
		KI_LOOKSTR_CASE ("-N")
			// ��ȡ����
			if(r3_config::fetch_uint (& C3(noise)) == false) {
				O0::argument ("�����÷� : -N {UINT}");
			}

			// �жϼ����Ƿ�Ϸ�
			if(C3(noise) > 100) {
				O0::argument ("��Ч�Ĳ��� : ��������ӦΪ 0 (��) �� 100 (��) ֮���������");
			}


		// ������м�¼	-log-(on|off)
		KI_LOOKSTR_CASE ("-log-on")			C3(log)		= true;
		KI_LOOKSTR_CASE ("-log-off")		C3(log)		= false;


		// ����֧��	-encode-(on|off)
		KI_LOOKSTR_CASE ("-encode-on")		C3(enable_encode)	= true;
		KI_LOOKSTR_CASE ("-encode-off")		C3(enable_encode)	= false;

		// ��������	-inline-(on|off)
		KI_LOOKSTR_CASE ("-inline-on")		C3(enable_inline)	= true;
		KI_LOOKSTR_CASE ("-inline-off")		C3(enable_inline)	= false;

		// ������ע	-pragma-(on|off)
		KI_LOOKSTR_CASE ("-pragma-on")		C3(enable_pragma)	= true;
		KI_LOOKSTR_CASE ("-pragma-off")		C3(enable_pragma)	= false;

		// �������	-random-(on|off)
		KI_LOOKSTR_CASE ("-random-on")		C3(enable_random)	= true;
		KI_LOOKSTR_CASE ("-random-off")		C3(enable_random)	= false;


		// �����
#define	PARSE_VM(cmdl, cmdu, func, err)															\
		KI_LOOKSTR_CASE ("-vm-" #cmdl)															\
			const char *	name	= r3_config::func ( );										\
			if(name == NULL) {																	\
				O0::argument ("�����÷� : " err);													\
			}																					\
			r3_config::update_vm (R3_CONFIG_VM_##cmdu, name);

		// -vm-wrapper {CLS}
		PARSE_VM (wrapper,		WRAPPER,	fetch_identifier,		"-vm-wrapper {CLS}")
		// -vm-entry {FUNC}
		PARSE_VM (entry,		ENTRY,		fetch_identifier,		"-vm-entry {FUNC}")
		// -vm-heap {VAR}
		PARSE_VM (heap,			HEAP,		fetch_variable,			"-vm-heap {VAR}")
		// -vm-stack {VAR}
		PARSE_VM (stack,		STACK,		fetch_variable,			"-vm-stack {VAR}")
		// -vm-top {VAR}
		PARSE_VM (top,			TOP,		fetch_variable,			"-vm-top {VAR}")
		// -vm-bottom {VAR}
		PARSE_VM (bottom,		BOTTOM,		fetch_variable,			"-vm-bottom {VAR}")
		// -vm-exception {VAR}
		PARSE_VM (exception,	EXCEPTION,	fetch_variable,			"-vm-exception {VAR}")
		// -vm-program {VAR}
		PARSE_VM (program,		PROGRAM,	fetch_variable,			"-vm-program {VAR}")
		// -vm-return {VAR}
		PARSE_VM (return,		RETURN,		fetch_variable,			"-vm-return {VAR}")
		// -vm-middle {VAR}
		PARSE_VM (middle,		MIDDLE,		fetch_variable,			"-vm-middle {VAR}")
#undef	PARSE_VM


		// ����ȫ�ֱ���	-Ev {VAR}
		KI_LOOKSTR_CASE ("-Ev")
			const char *	name	= r3_config::fetch_variable ( );

			if(name == NULL) {
				O0::argument ("�����÷� : -Ev {VAR}");
			}

			r3_config::update_export (C3(export_variable), name);

		// ��������	-Ef {FUNC}
		KI_LOOKSTR_CASE ("-Ef")
			const char *	name	= r3_config::fetch_identifier ( );

			if(name == NULL) {
				O0::argument ("�����÷� : -Ef {FUNC}");
			}

			r3_config::update_export (C3(export_function), name);


		// �޷�����
		KI_LOOKSTR_DEFAULT ( )
			O0::argument ("�޷�ʶ��Ĳ��� : %s", command);
	}
}


