#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
// ɾ���ַ����еĿո�
void remove_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    // ��������ָ�룬һ�����ڱ���ԭʼ�ַ�������һ�����ڱ���ǿո��ַ�
    char* source = str;
    char* destination = str;
    int inside = 1; // 1��ʾ����˫�����ڣ�-1��ʾ��˫������

    // �����ַ���
    while (*source) {
        if (*source == '\"') {
            inside *= -1;// �ı�inside��ֵ
        }
        if ((*source != ' ' && *source != '\n' && *source != '\r' && *source != '\t') || inside == -1) {
            *destination = *source; // ����ǿո��ַ�
            destination++;
        }

        source++;
    }
    // �����ַ�����ĩβ�����ֹ��
    *destination = '\0';
}
