#include "kernel.h"
#include "common.h"

void kputc(char symbol) {
    sbi_call(symbol, 0, 0, 0, 0, 0, 0, 1);
}

void* kmemset(void* arr, char c, size_t n) {
    uint8_t* pointer = (uint8_t *)arr;

    while(n--) *pointer++ = c;
    return arr;
}

void kprintf(char* fmt, ...) {
    __builtin_va_list vargs;
    __builtin_va_start(vargs, fmt);

    while(*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch(*fmt) {
                case '\0': {
                    kputc('%');
                    goto end;
                }

                case '%': {
                    kputc('%');
                    break;
                }


                /* -- string -- */
                case 's': {
                    uint8_t* symbol = __builtin_va_arg(vargs, uint8_t*);
                    while(*symbol) {
                        kputc(*symbol);
                        symbol++;
                    }
                    break;
                }

                /* -- integer -- */
                case 'd': {
                    int32_t value = __builtin_va_arg(vargs, int32_t);
                    if (value < 0) {
                        kputc('-');
                        value = -value;
                    }

                    int32_t div = 1;
                    while (value / div > 9) {
                        div *= 10;
                    }

                    while (div > 0) {
                        kputc('0' + (value / div));
                        value %= div;
                        div /= 10;
                    }
                    break;
                }
               /* -- hex -- */

                case 'x': {
                    uint32_t hex_value = __builtin_va_arg(vargs, uint32_t);
                    uint8_t hex_format[] = "0123456789ABCDEF";
                    kputc('0');
                    kputc('x');
                    for (uint32_t i = 1; i < 9; i++) {
                        uint8_t half_byte = (hex_value >> (32 - (i * 4))) & 0x000F;
                        kputc(hex_format[half_byte]);
                    }
                    break;
                }

                default:
                    kputc(*fmt);
            }
        } else kputc(*fmt);
        fmt++;
    }
end:
    __builtin_va_end(vargs);
}
