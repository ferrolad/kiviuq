/*
	$ [KiPHP] /rx/rx.h  (1406)    (C) 2005-2014  MF
*/


#ifndef _RX_RX_H_
#define _RX_RX_H_



/* ���ػ����� */
#define _RX_MOUNT_(cls)						LDR0::mount (cls##::__boot, cls##::__shutdown)




/* ���ظ��� */
#define _RX_MOUNT_R0_()						_RX_MOUNT_ (	O0		);
#define _RX_MOUNT_R1_()
#define _RX_MOUNT_R2_()
#define _RX_MOUNT_R3_()						_RX_MOUNT_ (	CFG3	);
#define _RX_MOUNT_R4_()						_RX_MOUNT_ (	r4_constring	);				\
											_RX_MOUNT_ (	VAR4	);						\
											_RX_MOUNT_ (	RCD4	);
#define _RX_MOUNT_R5_()




/* ���غ��� */
#define rx_mount()							_RX_MOUNT_R0_ ( );								\
											_RX_MOUNT_R1_ ( );								\
											_RX_MOUNT_R2_ ( );								\
											_RX_MOUNT_R3_ ( );								\
											_RX_MOUNT_R4_ ( );								\
											_RX_MOUNT_R5_ ( );								\




#endif