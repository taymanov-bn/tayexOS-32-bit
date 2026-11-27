#include <stdint.h>

typedef uint32_t size_t;

extern char __bss[], __bss_end[], __stack_top[];

void* kmemset(void* arr, char c, size_t n) {
    uint8_t* pointer = (uint8_t *)arr;

    while(n--) *pointer++ = c;
    return arr;
}

void kmain() {
    kmemset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    while(1);
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
