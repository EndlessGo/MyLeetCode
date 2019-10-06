[TOC]

# Memory

## 1. memcpy

1. 原型：extern void *memcpy(void *dest, void *src, unsigned int count);
2. 库文件：C标准库#include <string.h>
3. 功能：由src所指内存区域复制count个字节到dest所指内存区域。
4. 说明：src和dest所指内存区域不能重叠，函数返回指向dest的指针。



# String

## **1. strchr**

1. 原型：char *strchr(const char *str, int c)
2. 库文件：C标准库<string.h>
3. 功能：在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置。
4. 说明：src和dest所指内存区域不能重叠，函数返回指向dest的指针。