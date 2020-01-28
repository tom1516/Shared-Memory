
#include "pm.h"
#include <sys/wait.h>
#include <minix/callnr.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"
#include "param.h"

int do_shmget(void)
{
	int i;
	int size = m_in.m1_i1;
	int numclick;
	int test;

	test = 1 <<CLICK_SHIFT;
	numclick = size /test;

	printf("NUM click: %d\n",numclick);
	for(i=0; i<NR_SHM_SEGS; i++){
		if(allmemory[i].numproc==0){
			allmemory[i].numproc=1;
			allmemory[i].size=size;
			allmemory[i].phaddr = alloc_mem(numclick);
			if(allmemory[i].phaddr==NO_MEM){
				printf("SHMGET: out of memory\n");
				return -1;
			}
			return i;
		}
	}
	printf("NOT FOUND\n");	
	return -1;
}
int do_shmread(void)
{
	int shmid = m_in.m1_i1;
	int offset = m_in.m1_i2;
	int len = m_in.m1_i3;
	char *start = m_in.m1_p1;
	phys_bytes source, dest,physbase,virtbase;

	if(allmemory[shmid].numproc==0) return -1;
	if(allmemory[shmid].size < len) return -1;

	/*metatropi apo arithmo click se byte*/
	source = (allmemory[shmid].phaddr << CLICK_SHIFT) + offset;
	physbase = (mp->mp_seg[D].mem_phys)<<CLICK_SHIFT;
	virtbase = (mp->mp_seg[D].mem_vir )<<CLICK_SHIFT;
	dest = physbase + ((int)start - virtbase);
	sys_abscopy(source,dest,len);
	return OK;
}
int do_shmwrite(void)
{
	int shmid = m_in.m1_i1;
	int offset = m_in.m1_i2;
	int len = m_in.m1_i3;
	char *start = m_in.m1_p1;
	phys_bytes source, dest,physbase,virtbase;

	if(allmemory[shmid].numproc==0) return -1;
	if(allmemory[shmid].size < len) return -1;

	/*metatropi apo arithmo click se byte*/
	dest = (allmemory[shmid].phaddr << CLICK_SHIFT) + offset;
	physbase = (mp->mp_seg[D].mem_phys)<<CLICK_SHIFT;
	virtbase = (mp->mp_seg[D].mem_vir )<<CLICK_SHIFT;
	source = physbase + ((int)start - virtbase);
	sys_abscopy(source,dest,len);
	return OK;
}
