.sect .text
.extern	__shmwrite
.define	_shmwrite
.align 2

_shmwrite:
	jmp	__shmwrite
