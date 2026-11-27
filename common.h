#include "kernel.h"
#pragma once

typedef uint32_t size_t;

void kputc(char symbol);
void* kmemset(void* arr, char symbol, size_t n);
void kprintf(char* fmt, ...);
