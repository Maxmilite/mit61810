#include "sysinfo.h"
#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64 sys_sysinfo(void) {
    struct proc *p = myproc();
    struct sysinfo si;
    uint64 info_addr;
    argaddr(0, &info_addr);

    si.freemem = kcollect_free();
    si.nproc = collect_proc_num();

    if (copyout(p->pagetable, info_addr, (char *)&si, sizeof(si)) < 0) {
        return -1;
    }

    return 0;
}