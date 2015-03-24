/*
	$ [KiPHP] /r0/io.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			0

#include "../kiviuq.h"




/* ���ļ� */
FILE *	r0_io::stream_in		= NULL;						// ������
FILE *	r0_io::stream_out		= NULL;						// �����
FILE *	r0_io::stream_error		= NULL;						// ������




KI_LOADER_BOOT (r0_io) {
	r0_io::stream_in		= stdin;
	r0_io::stream_out		= stdout;
	r0_io::stream_error		= stderr;
}


KI_LOADER_SHUTDOWN (r0_io) {
	fclose (r0_io::stream_in);
	fclose (r0_io::stream_out);
	fclose (r0_io::stream_error);
}




/* �����������ַ� */
void r0_io::putchar (const int data) {
	if((data >= 0x20) && (data <= 0x7E)) {
		fputc (data, r0_io::stream_out);
	} else {
		switch(data) {
			case '\a':		fprintf (r0_io::stream_out,		"%s",		"\\a");			break;
			case '\f':		fprintf (r0_io::stream_out,		"%s",		"\\f");			break;
			case '\n':		fprintf (r0_io::stream_out,		"%s",		"\\n");			break;
			case '\r':		fprintf (r0_io::stream_out,		"%s",		"\\r");			break;
			case '\t':		fprintf (r0_io::stream_out,		"%s",		"\\t");			break;

			default:		fprintf (r0_io::stream_out,		"\\x%02X",	(unsigned int) data);
		}
	}
}




/* �����������ַ��� */

void r0_io::print (const char *data) {
	fprintf (r0_io::stream_out, "%s", data);
}


void r0_io::printf (const char *format, ...) {
	KI_VARG_BEGIN (format);

	vfprintf (r0_io::stream_out, format, ap);

	KI_VARG_END ( );
}




/* �����������﷨����/���� */
void r0_io::syntax (const char *message, unsigned int line, bool fatal) {
	if(fatal == true) {
		// �������
		if(line == 0) {
			fprintf (r0_io::stream_error,	"@E.ST@"    "%s\n",			message);
		} else {
			fprintf (r0_io::stream_error,	"@E.ST:%u@" "%s\n",	line,	message);
		}

		// ��ֹ����
		LDR0::die ( );
	} else {
		// �������
		if(line == 0) {
			fprintf (r0_io::stream_error,	"@W.ST@"    "%s\n",			message);
		} else {
			fprintf (r0_io::stream_error,	"@W.ST:%u@" "%s\n",	line,	message);
		}
	}
}


/* ��������������ʱ������ֹ���� */
void r0_io::runtime (const char *message) {
	// �������
	fprintf (r0_io::stream_error,	"@E.RT@" "%s\n",	message);

	// ��ֹ����
	LDR0::die ( );
}


/* ��������������������ֹ���� */
void r0_io::argument (const char *format, ...) {
	KI_VARG_BEGIN (format);

	fprintf  (r0_io::stream_error,	"@E.AR@");

	vfprintf (r0_io::stream_error,	format,		ap);

	fprintf  (r0_io::stream_error,	"\n");

	KI_VARG_END ( );

	// ��ֹ����
	LDR0::die ( );
}




/* ������������¼��Ϣ */
void r0_io::log (const char *entry, const char *format, ...) {
	KI_VARG_BEGIN (format);

	fprintf  (r0_io::stream_error,	"@L@" "%s=",	entry);

	vfprintf (r0_io::stream_error,	format,			ap);

	fprintf  (r0_io::stream_error,	"\n");

	KI_VARG_END ( );
}


