#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
// ���JSON��ʽ�Ƿ���Ч������¼����λ��
int is_json(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ� %s\n", filename);
        return 0;
    }
    int line = 1; // ��ǰ����
    int column = 0; // ��ǰ����
    char ch;
    int stack1 = 0; // ������ { ��ƥ��ջ
    int stack2 = 0; // ������ [ ��ƥ��ջ
    int inString = 0; // �Ƿ����ַ�����
    int lastChar = 0; // ��һ���ַ�

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
                    printf("����ȱ�������� { �ڵ� %d �У��� %d ��\n", line, column);
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
                    printf("����ȱ�������� [ �ڵ� %d �У��� %d ��\n", line, column);
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
                printf("���󣺼��������ַ������ڵ� %d �У��� %d ��\n", line, column);
                fclose(file);
                return 0;
            }
        }
        else if (ch == ',' && !inString) {
            if (lastChar == '{' || lastChar == '[' || lastChar == ',') {
                printf("���󣺶��ź���ȱ��Ԫ�أ��ڵ� %d �У��� %d ��\n", line, column);
                fclose(file);
                return 0;
            }
        }
        lastChar = (int)ch;
    }
    fclose(file);
    if (stack1 != 0) {
        printf("����ȱ���һ����� }\n");
        return 0;
    }
    if (stack2 != 0) {
        printf("����ȱ���ҷ����� ]\n");
        return 0;
    }
    return 1;
}

