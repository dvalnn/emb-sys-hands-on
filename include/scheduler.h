#ifndef __SCHED__H__
#define __SCHED__H__

typedef struct {
    /* period in ticks */
    int period;
    /* ticks until next activation */
    int delay;
    /* function pointer */
    void (*func)(void);
    /* activation counter */
    int exec;
} Sched_Task_t;

#define NT 20
Sched_Task_t Tasks[NT];

void Sched_Init(void);
void Sched_Schedule(void);
void Sched_Dispatch(void);

int Sched_AddT(void (*f)(void), int d, int p);
#endif
