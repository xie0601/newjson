#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#pragma warning(disable : 4996)

#define INDENT_SPACES 4 // �����ո���

// ��������
// ��ӡJSON
void print_json(char *json, FILE *output_file);
// ��֤JSON
int is_json(const char *filename);
// ȥ���ո�
void remove_spaces(char *str);
// ���JSON�ļ�(ѹ��)
void print_json_file_compact(char *json, FILE *output_file);
// �ж��Ƿ��ǿո�
int is_whitespace(char c);

int main() {

    // ����JSON�ļ���·���ļ���
    char filename[100];
    printf("�������ļ�����: ");
    scanf("%s", filename);

    // �򿪲���ȡ�ļ�����
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("�ļ��򿪴���.\n");
        system("pause"); // �����������
        return 1;
    }

    // ��ȡ�ļ���С
    int file_size = 0;
    while (fgetc(file) != EOF) {
        file_size++;
    }
    fseek(file, 0, SEEK_SET); // ���ļ�ָ������ָ���ļ���ͷ

    // ��ȡ�ļ�����
    char *json_content = (char *) malloc(file_size + 1);
    fread(json_content, 1, file_size, file);
    json_content[file_size] = '\0';

    // �ر��ļ�
    fclose(file);

    // ����ļ������Ƿ����JSON��ʽ

    if (!is_json(filename)) {
        free(json_content);
        system("pause"); // �����������
        return 1;
    }
    remove_spaces(json_content);

    // �����ļ���ʽ��JSON�ַ�����ʾ����Ļ��
    printf("��ʽ�����Ϊ:\n");
    print_json(json_content, stdout); // stdout �Ǳ�׼�����
    printf("\n");

    // �����ļ���ʽ��JSON�ַ���������ָ�����ı��ļ���
    char output_filename[100];
    printf("�������Ҫ��ʽ������json���ļ���: ");
    scanf("%s", output_filename);
    FILE *output_file = fopen(output_filename, "w");
    print_json(json_content, output_file);
    fclose(output_file);
    printf("��ʽ������ɹ����ļ���Ϊ %s.\n", output_filename);

    printf("�������Ҫѹ������json���ļ���: ");
    scanf("%s", output_filename);
    FILE *output_file2 = fopen(output_filename, "w");
    print_json_file_compact(json_content, output_file2);
    fclose(output_file2);
    printf("ѹ������ɹ����ļ���Ϊ %s.\n", output_filename);

    // �ͷ��ڴ�
    free(json_content);
    system("pause"); // �����������
    return 0;
}

 
