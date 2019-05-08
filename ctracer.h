#ifndef	CTRACER_H
#define	CTRACER_H

#define	LOG_SIZE	1024
#define	EV_START	0x1
#define	EV_END		0x2

struct event {
	uint8_t 	type;
	uint64_t	ip;
	uint64_t	pip;
	uint64_t	arg1;
	uint64_t	arg2;
	uint64_t	arg3;
	uint64_t	arg4;
	uint64_t	time;
};

typedef void (*ctracer_func_t)(uint64_t ip, uint64_t parent_ip, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4);

extern void ctracer_enable(void);
extern void ctracer_disable(void);
extern void trace_dump();

#endif	//CTRACER_H

