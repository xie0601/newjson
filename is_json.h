#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
// 检查JSON格式是否有效，并记录错误位置
int is_json(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return 0;
    }
    int line = 1; // 当前行数
    int column = 0; // 当前列数
    char ch;
    int stack1 = 0; // 花括号 { 的匹配栈
    int stack2 = 0; // 方括号 [ 的匹配栈
    int inString = 0; // 是否在字符串中
    int lastChar = 0; // 上一个字符

    while ((ch = (char)fgetc(file)) != EOF) {
        column++;
        if (ch == '\n') {
            line++;
            column = 0;
        }
        else if (ch == '{') {
            if (!inString) {
                stack1++;
            }
        }
        else if (ch == '}') {
            if (!inString) {
                stack1--;
                if (stack1 < 0) {
                    printf("错误：缺少左花括号 { 在第 %d 行，第 %d 列\n", line, column);
                    fclose(file);
                    return 0;
                }
            }
        }
        else if (ch == '[') {
            if (!inString) {
                stack2++;
            }
        }
        else if (ch == ']') {
            if (!inString) {
                stack2--;
                if (stack2 < 0) {
                    printf("错误：缺少左方括号 [ 在第 %d 行，第 %d 列\n", line, column);
                    fclose(file);
                    return 0;
                }
            }
        }
        else if (ch == '"') {
            if (inString) {
                inString = 0;
            }
            else {
                inString = 1;
            }
        }
        else if (ch == ':' && !inString) {
            if (lastChar != '"') {
                printf("错误：键必须是字符串，在第 %d 行，第 %d 列\n", line, column);
                fclose(file);
                return 0;
            }
        }
        else if (ch == ',' && !inString) {
            if (lastChar == '{' || lastChar == '[' || lastChar == ',') {
                printf("错误：逗号后面缺少元素，在第 %d 行，第 %d 列\n", line, column);
                fclose(file);
                return 0;
            }
        }
        lastChar = (int)ch;
    }
    fclose(file);
    if (stack1 != 0) {
        printf("错误：缺少右花括号 }\n");
        return 0;
    }
    if (stack2 != 0) {
        printf("错误：缺少右方括号 ]\n");
        return 0;
    }
    return 1;
}

