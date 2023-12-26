#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
// 删除字符串中的空格
void remove_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    // 定义两个指针，一个用于遍历原始字符串，另一个用于保存非空格字符
    char* source = str;
    char* destination = str;
    int inside = 1; // 1表示不在双引号内，-1表示在双引号内

    // 遍历字符串
    while (*source) {
        if (*source == '\"') {
            inside *= -1;// 改变inside的值
        }
        if ((*source != ' ' && *source != '\n' && *source != '\r' && *source != '\t') || inside == -1) {
            *destination = *source; // 保存非空格字符
            destination++;
        }

        source++;
    }
    // 在新字符串的末尾添加终止符
    *destination = '\0';
}
