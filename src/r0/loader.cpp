/*
	$ [KiPHP] /r0/loader.cpp  (1406)    (C) 2005-2014  MF
*/


#define KI_RING			0

#include "../kiviuq.h"




/* ������ */
void	(* r0_loader::handler_boot		[r0_loader::size])	(int, char **)	= {NULL};
void	(* r0_loader::handler_shutdown	[r0_loader::size])	(void)			= {NULL};


/* ע�ắ������ */
unsigned int	r0_loader::count	= 0;




/* �����µĺ��� */
void r0_loader::mount (void (* boot)(int, char **), void (* shutdown)(void)) {
	// �жϹ�������
	if(r0_loader::count >= r0_loader::size) {
		return;
	}
	
	// ����
	r0_loader::handler_boot		[r0_loader::count]	= boot;
	r0_loader::handler_shutdown	[r0_loader::count]	= shutdown;

	r0_loader::count ++;
}




/* ���� */
void r0_loader::boot (int argc, char *argv[]) {
	// ����ִ����������
	for(unsigned int i = 0; i < r0_loader::count; i ++) {
		r0_loader::handler_boot [i] (argc, argv);
	}
}


/* ���� */
void r0_loader::shutdown (void) {
	// ����ִ�н�������
	for(unsigned int i = r0_loader::count; i > 0; i --) {
		r0_loader::handler_shutdown [i - 1] ( );
	}
}




/* ��ֹ���� */
void r0_loader::die (int code) {
	r0_loader::shutdown ( );

	exit (code);
}


