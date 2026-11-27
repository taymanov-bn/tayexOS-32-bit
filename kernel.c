#include "kernel.h"
#include "common.h"

typedef uint32_t size_t;


extern char __bss[], __bss_end[], __stack_top[];

struct sbiret sbi_call(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4, int32_t arg5, int32_t fid, int32_t eid) {

    register int32_t a0 __asm__("a0") = arg0;
    register int32_t a1 __asm__("a1") = arg1;
    register int32_t a2 __asm__("a2") = arg2;
    register int32_t a3 __asm__("a3") = arg3;
    register int32_t a4 __asm__("a4") = arg4;
    register int32_t a5 __asm__("a5") = arg5;
    register int32_t a6 __asm__("a6") = fid;
    register int32_t a7 __asm__("a7") = eid;

    __asm__ __volatile__("ecall"
        : "=r"(a0), "=r"(a1) // изменение только регистров a0 a1
        : "r"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a6), "r"(a7)
        : "memory");

    return (struct sbiret) {.error = a0, .value = a1};
}

void kmain() {
    kmemset(__bss, 0, (size_t) __bss_end - (size_t) __bss); // обнуление секции .bss
    kprintf("Hello, %s", "World!\n");
    kprintf("I am %d years old!\n", 19);
    kprintf("number 10 in hex is: %x\n", 10);
    kprintf("number 255 in hex is: %x\n", 255);
    kprintf("number 23567 in hex is: %x\n", 23567);
    kprintf("Hello %t\n");
    kprintf("Bumbum");
    while(1) __asm__ __volatile__("wfi");
}

__attribute__((section(".text.boot")))
__attribute__((naked))
void boot() {
    __asm__ __volatile__ (
        "mv sp, %[stack_top]\n"
        "j kmain\n"
        :
        : [stack_top] "r" (__stack_top)
    );
}
