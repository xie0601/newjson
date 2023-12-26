#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
 

// ��ӡJSON�ַ������ļ���ʹ��ѭ��
void print_json(char* json, FILE* output_file) {
    int indent = 0;
    int flag = 0;
    while (*json) { // �����ַ���
        if (*json == '{' || *json == '[') {
            //            for (int i = 0; i < indent - INDENT_SPACES; i++) { // ��ӡ�����ո�
            //                fputc(' ', output_file);
            //            }
            fputc(*json, output_file);
            indent += INDENT_SPACES; // ��������
            if (*(json + 1) != '\n') {
                fputc('\n', output_file);
                for (int i = 0; i < indent; i++) { // ��ӡ�����ո�
                    fputc(' ', output_file);
                }
            }
            else
                for (int i = 0; i < indent; i++) { // ��ӡ�����ո�
                    fputc(' ', output_file);
                }
        }
        else if (*json == '}' || *json == ']') {
            if (*(json - 1) != '\n') {
                fputc('\n', output_file);
            }
            for (int i = 0; i < indent - INDENT_SPACES; i++) {
                fputc(' ', output_file);
            }
            fputc(*json, output_file);
            indent -= INDENT_SPACES; // ��������
        }
        else if (*json == ':') {
            fputc(*json, output_file);
            fputc(' ', output_file);
        }
        else if (*json == ',') {
            fputc(*json, output_file);
            fputc(' ', output_file);
            if (*(json + 1) != '\n') {
                fputc('\n', output_file);
                for (int i = 0; i < indent; i++) { // ��ӡ�����ո�
                    fputc(' ', output_file);
                }
            }
        }
        else if (*json == '\n') {
            flag = 1;
            fputc('\n', output_file);
        }
        else {
            if (flag) {
                flag = 0;
                for (int i = 0; i < indent; i++) { // ��ӡ�����ո�
                    fputc(' ', output_file);
                }
            }
            fputc(*json, output_file);
        }

        json++;
    }
}

