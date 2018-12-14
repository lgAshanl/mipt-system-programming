#include "Computer.h"
#include "DieHardStack.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#define DEFINE_NEW_ASM_COMMAND(name) {ASM_##name, #name, (void*)asm_##name##_func}
//#define EXE_ASM() void (*f)()=asm_commands[regs.r0].func; (*f)();
#define EXE_ASM() void (*f)()=(void(*)())asm_commands[regs.r0].func; (*f)();
// Here we get register currently loaded into exe command
#define REG (*(&(regs.ax) + regs.r1))
#define SIDE_REG (*(&(regs.ax) + regs.r2))

#define BUF_LEN 255
#define BIN_BUF_LEN 2056
#define EMPTY 534523679


static DieHardStack<double > *stack;
static DieHardStack<double > *rets;

static struct registers regs = {
        .ax = 0.0,
        .bx = 0.0,
        .cx = 0.0,
        .dx = 0.0,
        .r0 = EMPTY,
        .r1 = EMPTY,
        .r2 = EMPTY,
        .r3 = EMPTY
};
static int bin_pointer = 1;
static int saved_bin_pointer = 0;
static int tag_pointer = 0;
static int last_tag = 0;
static int bins[BIN_BUF_LEN];
static int tags[BIN_BUF_LEN];
static char tags_names[BIN_BUF_LEN][BIN_BUF_LEN];


int get_tag_by_name(const char *tag) {
    int i = 0;
    while(i < BIN_BUF_LEN) {
        if (!strcmp(tags_names[i], tag)) {
            return i;
        }
        i++;
    }
    return -1;
}

// One genius hack is here: we get registers by pointer to raw memory
void asm_add_func() {
    if (regs.r3 == 0) {
        REG += SIDE_REG;
        return;
    }
    REG += regs.r2;
}

void asm_sub_func() {
    if (regs.r3 == 0) {
        REG -= SIDE_REG;
        return;
    }
    REG -= regs.r2;
}

void asm_mul_func() {
    if (regs.r3 == 0) {
        REG *= SIDE_REG;
        return;
    }
    REG *= regs.r2;
}

void asm_div_func() {
    if (regs.r3 == 0) {
        REG /= SIDE_REG;
        return;
    }
    REG /= regs.r2;
}

void asm_mov_func() {
    if (regs.r3 == 0) {
        REG = SIDE_REG;
        return;
    }
    REG = regs.r2;
}

void asm_push_func() {
    if (regs.r3 == 1) {
        stack->push(REG);
        return;
    }
    stack->push(regs.r1);
}

void asm_pop_func() {
    regs.dx = stack->top();
    stack->pop();
}

void asm_call_func() {
    rets->push(bin_pointer);
    bin_pointer = regs.r1;
}

void asm_ret_func() {
    int a = bin_pointer;
    bin_pointer = (int) rets->pop();
}

void asm_sqrt_func() {
    REG = sqrt(REG);
}

void asm_je_func() {
    if (regs.ax == regs.bx) {
        rets->push(bin_pointer);
        bin_pointer = regs.r1;
    }
}

void asm_jne_func() {
    if (regs.ax != regs.bx) {
        rets->push(bin_pointer);
        bin_pointer = regs.r1;
    }
}

void asm_in_func() {
    int val = 0;
    scanf("%d", &val);
    REG = val;
}

void asm_hello_func() {
    printf("\nHELLO\n");
}

void asm_cmp_func() {
    // Implement this
}

void asm_prt_func() {
    printf("%d\n", (int)REG);
}

struct asm_command asm_commands[] = {
        DEFINE_NEW_ASM_COMMAND(add),
        DEFINE_NEW_ASM_COMMAND(sub),
        DEFINE_NEW_ASM_COMMAND(mul),
        DEFINE_NEW_ASM_COMMAND(div),
        DEFINE_NEW_ASM_COMMAND(mov),
        DEFINE_NEW_ASM_COMMAND(push),
        DEFINE_NEW_ASM_COMMAND(pop),
        DEFINE_NEW_ASM_COMMAND(call),
        DEFINE_NEW_ASM_COMMAND(ret),
        DEFINE_NEW_ASM_COMMAND(sqrt),
        DEFINE_NEW_ASM_COMMAND(je),
        DEFINE_NEW_ASM_COMMAND(jne),
        DEFINE_NEW_ASM_COMMAND(in),
        DEFINE_NEW_ASM_COMMAND(hello),
        DEFINE_NEW_ASM_COMMAND(cmp),
        DEFINE_NEW_ASM_COMMAND(prt),//*/
};

const char commands_filename[] = "commands";

void flush_regs() {
    regs.ax = 0.0;
    regs.bx = 0.0;
    regs.cx = 0.0;
    regs.dx = 0.0;
    regs.r0 = EMPTY;
    regs.r1 = EMPTY;
    regs.r2 = EMPTY;
    regs.r3 = EMPTY;
}

void print_regs() {
    printf("Registers:\n ax: %f, bx: %f, cx: %f, dx: %f\n r0: %d, r1: %d, r2: %d, r3: %d\n",
           regs.ax, regs.bx, regs.cx, regs.dx, regs.r0, regs.r1, regs.r2, regs.r3);
}

void print_bin_buf() {
    int i;
    printf("Program: \n");
    for (i = 0; i < BIN_BUF_LEN; i++) {
        if (bins[i] == EMPTY && i % 4 == 0) {
            printf("\n");
            return;
        }
        printf("%d ", bins[i]);
    }
}

void print_tags() {
    int i = 0;
    printf("Tags:\n");
    for (; i < last_tag; i++) {
        printf("%s\n", tags_names[i]);
    }
}

int init_asm() {
    int i;
    stack = new DieHardStack<double>();
    rets = new DieHardStack<double>();
    for (i = 0; i < BIN_BUF_LEN; i++) {
        bins[i] = EMPTY;
    }
    return 0;
}

int get_bin_from_line(const char *line, char *ret_name) {
    char buf[BUF_LEN] = "";
    char symb = line[0];
    int i = 0;
    int buf_i = 0;
    while (symb) {
        if (symb == ' ') {
            strncpy(ret_name, buf, BUF_LEN);
            memset(buf, '\0', BUF_LEN);
            buf_i = 0;
        } else {
            buf[buf_i++] = symb;
        }
        symb = line[++i];
    }
    return atoi(buf);
}

int get_bin_by_name(const char *bin_name) {
    FILE *file = fopen(commands_filename, "r");
    char buf[BUF_LEN] = "";
    char command[BUF_LEN] = "";
    int command_index = -1;
    while(fgets(buf, BUF_LEN, file)) {
        command_index = get_bin_from_line(buf, command);
        if (!strcmp(command, bin_name)) {
            return command_index;
        }
        memset(command, '\0', BUF_LEN);
    }
    fclose(file);
    return EMPTY;
}

int parse_arg(const char *arg) {
    // Set mode that means we have reg as the 2nd arg
    if (!strcmp(arg, "ax") || !strcmp(arg, "bx") || !strcmp(arg, "cx")
        || !strcmp(arg, "dx")) {
        if (regs.r1 != EMPTY && regs.r0 != ASM_push) { // If we have a reg as the 2nd arg
            regs.r3 = 0;
        } else if (regs.r0 == ASM_push && regs.r1 == EMPTY) { // If we have a reg in push arg
            regs.r3 = 1;
        }
    }
    if (!strcmp(arg, "ax")) {
        return 0;
    } else if (!strcmp(arg, "bx")) {
        return 1;
    } else if (!strcmp(arg, "cx")) {
        return 2;
    } else if (!strcmp(arg, "dx")) {
        return 3;
    } else {
        return atoi(arg);
    }
}

void fill_bin_buf() {
    bins[bin_pointer++] = regs.r0;
    bins[bin_pointer++] = regs.r1;
    bins[bin_pointer++] = regs.r2;
    bins[bin_pointer++] = regs.r3;
}

void fill_regs_from_bins() {
    regs.r0 = bins[bin_pointer++];
    regs.r1 = bins[bin_pointer++];
    regs.r2 = bins[bin_pointer++];
    regs.r3 = bins[bin_pointer++];
}


void fill_reg(const char *buf) {
    if (regs.r0 == EMPTY) {
        regs.r0 = get_bin_by_name(buf);
    } else if (regs.r1 == EMPTY) {
        if (regs.r0 == ASM_call || regs.r0 == ASM_je
            || regs.r0 == ASM_jne) { // This is call command
            regs.r1 = tags[get_tag_by_name(buf)];
        } else {
            regs.r1 = parse_arg(buf);
        }
    } else if (regs.r2 == EMPTY) {
        regs.r2 = parse_arg(buf);
    } else if (regs.r3 == EMPTY) {
        regs.r3 = parse_arg(buf);
    }
}

int add_tag_from_buf(const char *buf) {
    strcpy(tags_names[last_tag++], buf);
    return 0;
}

// Get command with args from line
int parse_command(const char *line) {
    char buf[BUF_LEN] = "";
    int i = 0;
    int buf_i = 0;
    char symb = line[0];
    while (symb) {
        if (symb == ' ' || symb == ',') {
            if (buf_i == 0) {
                goto next_symb;
            }
            fill_reg(buf);
            memset(buf, '\0', BUF_LEN);
            buf_i = 0;
        } else if (symb == ':') {
            tags[tag_pointer++] = bin_pointer;
            add_tag_from_buf(buf);
            memset(buf, '\0', BUF_LEN);
            goto exit;
        } else if (symb != 10) { //Decline new line symbol
            buf[buf_i++] = symb;
        }
        next_symb:
        symb = line[++i];
    }
    fill_reg(buf);
    // For correct output
    if (regs.r3 == EMPTY) {
        regs.r3 = -1;
    }
    fill_bin_buf();
    exit:
    return 0;
}

// Execute all asm commands from "byte code" step by step
int exe_all() {
    //bin_pointer = tags[get_tag_by_name("main")];
    bin_pointer = bins[0];
    //printf("bin POINTER: %d\n", bin_pointer);
    while (bins[bin_pointer] != EMPTY) {
        //printf("### %d\n", bin_pointer);
        fill_regs_from_bins();
        //void (*f)()=(void(*)())asm_commands[regs.r0].func; (*f)();
        EXE_ASM();
        //print_regs();
        //rets->print();
    }
    return 0;
}

/*
 @brief run assembler code
 @param filename - path to asm program
*/
int parse_program(const char *filename) {
    FILE *file = fopen(filename, "r");
    char buf[BUF_LEN] = "";
    while(fgets(buf, BUF_LEN, file)) {
        if (!strcmp(buf, "\n")) {
            continue;
        }
        parse_command(buf);
        flush_regs();
    }
    bins[0] = tags[get_tag_by_name("main")];
    printf("parsed\n");
    fclose(file);
    print_bin_buf();
    print_tags();
    printf("exe\n");
    exe_all();
    return 0;
}
