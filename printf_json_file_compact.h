#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// ��ӡѹ��JSON�ַ������ļ�
void print_json_file_compact(char* json, FILE* output_file) {
    while (*json) {
        if (!is_whitespace(*json)) { // �ǿո��ַ�
            fputc(*json, output_file);
        }
        json++;
    }
}