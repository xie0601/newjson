#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


// �ж��ַ��Ƿ�Ϊ�ո�
int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}