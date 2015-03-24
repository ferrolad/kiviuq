/*
	$ [KiPHP] /kiviuq.h  (1406)    (C) 2005-2014  MF
*/


#ifndef _KIVIUQ_H_
#define _KIVIUQ_H_



/* ������ */
#ifdef _MSC_VER
	#pragma warning (disable: 4003)
	#pragma warning (disable: 4129)
	#pragma warning (disable: 4996)

	#define _KI_MSC_
#endif


/* ���뻷�� */
#ifdef __cplusplus
	#define _KI_CPP_
#endif


/* ����Ŀ��ƽ̨ */
#ifdef _KI_MSC_
	#ifdef _WIN64
		#define _KI_X64_
	#endif
#else
	#ifdef __SIZEOF_POINTER__
		#if __SIZEOF_POINTER__ > 4
			#define _KI_X64_
		#endif
	#endif
#endif




/* ������� C++ ���� */
#ifndef _KI_CPP_
	#error ��֧�ֵ�ǰ�ı��뻷�� (ANSI C)
#endif


/* ������� 32 λƽ̨ */
#ifdef _KI_X64_
	#error ��֧�ֵ�ǰ�ı���Ŀ��ƽ̨ (x64)
#endif




/* UNICODE */

#ifdef UNICODE
	#undef UNICODE
#endif

#ifdef _UNICODE
	#undef _UNICODE
#endif




/* ����ļ��Ƿ��趨�����ڵ�Ȩ�޻� */
#ifndef KI_RING
	#error �ļ�û���趨�����ڵ�Ȩ�޻�
#endif




#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>


#include "rx/helper.h"
#include "rx/licence.h"

#include "rx/r0.h"						// R0 : �ں�				core
#include "rx/r1.h"						// R1 : ͨ�����ݽṹ		general data structure
#include "rx/r2.h"						// R2 : �ڲ����ݽṹ		internal data structure
#include "rx/r3.h"						// R3 : ����				configuration
#include "rx/r4.h"						// R4 : ��֯				organization
#include "rx/r5.h"						// R5 : ������			generator
#include "rx/rx.h"						// Rx : ��������			con/destructor




#endif