#ifndef TOPCOMP_COMPUTER_H
#define TOPCOMP_COMPUTER_H

#endif //TOPCOMP_COMPUTER_H

#include "stdlib.h"

// First 4 regs are for sharing, others - for commands
struct registers {
    double ax;
    double bx;
    double cx;
    double dx;
    int r0;
    int r1;
    int r2;
    int r3;
};


struct asm_command {
    int number;
    char *name;
    void *func;
};

// This schedule must be the same in three files
enum commands {
    ASM_add,
    ASM_sub,
    ASM_mul,
    ASM_div,
    ASM_mov,
    ASM_push,
    ASM_pop,
    ASM_call,
    ASM_ret,
    ASM_sqrt,
    ASM_je,
    ASM_jne,
    ASM_in,
    ASM_hello,
    ASM_cmp,
    ASM_prt,
};

// Create stack and other objects
int init_asm();
// Run asm program from given path
int parse_program(const char *);
