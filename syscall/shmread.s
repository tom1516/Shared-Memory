.sect .text
.extern	__shmread
.define	_shmread
.align 2

_shmread:
	jmp	__shmread
