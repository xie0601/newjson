#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#pragma warning(disable : 4996)

#define INDENT_SPACES 4 // 缩进空格数

// 函数声明
// 打印JSON
void print_json(char *json, FILE *output_file);
// 验证JSON
int is_json(const char *filename);
// 去除空格
void remove_spaces(char *str);
// 输出JSON文件(压缩)
void print_json_file_compact(char *json, FILE *output_file);
// 判断是否是空格
int is_whitespace(char c);

int main() {

    // 输入JSON文件的路径文件名
    char filename[100];
    printf("请输入文件名称: ");
    scanf("%s", filename);

    // 打开并读取文件内容
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("文件打开错误.\n");
        system("pause"); // 按任意键继续
        return 1;
    }

    // 获取文件大小
    int file_size = 0;
    while (fgetc(file) != EOF) {
        file_size++;
    }
    fseek(file, 0, SEEK_SET); // 将文件指针重新指向文件开头

    // 读取文件内容
    char *json_content = (char *) malloc(file_size + 1);
    fread(json_content, 1, file_size, file);
    json_content[file_size] = '\0';

    // 关闭文件
    fclose(file);

    // 检查文件内容是否符合JSON格式

    if (!is_json(filename)) {
        free(json_content);
        system("pause"); // 按任意键继续
        return 1;
    }
    remove_spaces(json_content);

    // 按照文件格式将JSON字符串显示在屏幕上
    printf("格式化输出为:\n");
    print_json(json_content, stdout); // stdout 是标准输出流
    printf("\n");

    // 按照文件格式将JSON字符串保存在指定的文本文件中
    char output_filename[100];
    printf("请输出想要格式化保存json的文件名: ");
    scanf("%s", output_filename);
    FILE *output_file = fopen(output_filename, "w");
    print_json(json_content, output_file);
    fclose(output_file);
    printf("格式化保存成功，文件名为 %s.\n", output_filename);

    printf("请输出想要压缩保存json的文件名: ");
    scanf("%s", output_filename);
    FILE *output_file2 = fopen(output_filename, "w");
    print_json_file_compact(json_content, output_file2);
    fclose(output_file2);
    printf("压缩保存成功，文件名为 %s.\n", output_filename);

    // 释放内存
    free(json_content);
    system("pause"); // 按任意键继续
    return 0;
}

 
