/*
	$ [KiPHP] /r3/config.output.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			3

#include "../kiviuq.h"




/* ���ģʽ */
void r3_config::output (r3_config_output_e mode) {
	switch(mode) {
		case R3_CONFIG_OUTPUT_HELP:
			O0::printf (
				"�÷� : kiviuq [...]\n\n"

				"%s  (%s)\n\n\n"

				"��� (����):\n"
				"      -h                         ��������������˳�����\n"
				"      -v                         ����汾��Ϣ���˳�����\n\n"

				"��� (ģʽ):\n"
				"  [1] -Oc                        ���Ŀ�����\n"
				"  (1) -Oi                        ����м�����\n"
				"  (1) -Os                        ���������Ϣ\n\n"

				"���ļ�:\n"
				"      -in {FILE}                 ָ���������ļ���ȡ�� STDIN\n"
				"      -out {FILE}                ָ��������ļ���ȡ�� STDOUT\n"
				"      -error {FILE}              ָ���������ļ���ȡ�� STDERR\n\n"

				"����ģʽ:\n"
				"  (2) -W0                        ���þ���\n"
				"  [2] -W1                        �������\n"
				"  (2) -W2                        ������沢��ֹ����\n\n"

				"����ˮƽ:\n"
				"      -N {UINT}                  ָ����������ˮƽ����ΧΪ 0������ �� 100������\n\n"

				"���м�¼:\n"
				"  (3) -log-on                    �������м�¼���\n"
				"  [3] -log-off                   �������м�¼���\n\n"

				"����֧��:\n"
				"  [4] -encode-on                 ���ñ���֧��\n"
				"  (4) -encode-off                ���ñ���֧��\n"
				"  (5) -inline-on                 ������������\n"
				"  [5] -inline-off                ������������\n"
				"  [6] -pragma-on                 ���ñ�����ע\n"
				"  (6) -pragma-off                ���ñ�����ע\n"
				"  (7) -random-on                 �����������\n"
				"  [7] -random-off                �����������\n\n"

				"���������:\n"
				"      -vm-wrapper {CLS}          ָ����װ��������ȡ�� __kiviuq_wrapper\n"
				"      -vm-entry {FUNC}           ָ��������ڷ�������ȡ�� __kiviuq__\n"
				"      -vm-heap {VAR}             ָ������������ȡ�� $HEAP\n"
				"      -vm-stack {VAR}            ָ��ջ��������ȡ�� $STACK\n"
				"      -vm-top {VAR}              ָ��ջ��ָ���������ȡ�� $T\n"
				"      -vm-bottom {VAR}           ָ��ջ��ָ���������ȡ�� $B\n"
				"      -vm-exception {VAR}        ָ���쳣ָ���������ȡ�� $E\n"
				"      -vm-pointer {VAR}          ָ�����������ָ���������ȡ�� $P\n"
				"      -vm-return {VAR}           ָ������ֵ�ݴ�����������ȡ�� $R\n"
				"      -vm-middle {VAR}           ָ���м�ֵ�ݴ�����������ȡ�� $M\n\n"

				"����:\n"
				"      -Ev {VAR}                  ����ȫ�ֱ���\n"
				"      -Ef {FUNC}                 ��������\n\n"

				"��������ʹ�� [n] �� (n) ������֯����ͬ���ִ���Ϊ��������\n"
				"���У�[n] ΪĬ�����ã�(n) Ϊ��ѡ����"

				, KI_LIC_NAME
				, KI_LIC_VERSION
			);

			break;


		case R3_CONFIG_OUTPUT_VERSION:
			O0::printf (
				"%s  (%s)\n"
				"%s\n\n"

				"�ⲻ��һ����������ʹ��ǰ��������Ȩ��\n\n"

				"��ҳ : %s"

				, KI_LIC_NAME
				, KI_LIC_VERSION
				, KI_LIC_COPYRIGHT
				, KI_LIC_HOMEPAGE
			);

			break;


		case R3_CONFIG_OUTPUT_DISTRIBUTION:
			{
				O0::printf ("D = %s\n",		__DATE__);
				O0::printf ("T = %s\n",		__TIME__);

				const char *	p	= KI_LIC_DISTRIBUTION;

				for(int i = 0; i < (sizeof (KI_LIC_DISTRIBUTION) - 1); i ++) {
					if((i % 8) == 0) {
						O0::printf ("\n");
					}

					O0::printf ("%02X ", (unsigned int) * (p ++));
				}
			}

			break;


		default:
			return;
	}

	// �˳�����
	LDR0::die ( );
}


