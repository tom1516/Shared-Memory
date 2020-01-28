.sect .text
.extern	__shmget
.define	_shmget
.align 2

_shmget:
	jmp	__shmget
