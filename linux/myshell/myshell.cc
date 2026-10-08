#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define COMMAND_SIZE 1024
#define FORMAT "%s@VM-0-2-ubuntu:%s# "
#define MAXARGV 128
char *g_argv[MAXARGV];
int g_argc = 0;

const char *GetUserName() {
    const char *name = getenv("USER");
    return name == NULL ? "None" : name;
}
const char *GetPwd() {
    const char *pwd = getenv("PWD");
    return pwd == NULL ? "None" : pwd;
}

void MakeCommandLine(char cmd_prompt[], int size) {
    snprintf(cmd_prompt, size, FORMAT, GetUserName(), GetPwd());
}

void PrintCommandPrompt() {
    char prompt[COMMAND_SIZE];
    MakeCommandLine(prompt, sizeof(prompt));
    printf("%s", prompt);
    fflush(stdout);
}

bool GetCommandLine(char *out, int size) {
    char *c = fgets(out, size, stdin);
    if (c == NULL)
        return false;
    out[strlen(out) - 1] = 0;
    if (strlen(out) == 0)
        return false;
    return true;
}

bool CommandParse(char *commandline) {
#define SEP " "
    g_argc = 0;
    g_argv[g_argc++] = strtok(commandline, SEP);
    while (g_argv[g_argc++] = strtok(nullptr, SEP));
    g_argc--;
    return true;
}

int Execute() {
    pid_t id = fork();
    if (id == 0) {
        execvp(g_argv[0], g_argv);
        exit(1);
    }
    pid_t rid = waitpid(id, nullptr, 0);
    (void)rid;
    return 0;
}

int main() {
    while (1) {
        // 输出命令行提示符
        PrintCommandPrompt();

        // 获取用户输入

        char commandline[COMMAND_SIZE];
        if (!GetCommandLine(commandline, sizeof(commandline))) {
            continue;
        }

        // 拆字符串
        CommandParse(commandline);
        // 执行命令
        Execute();
    }

    return 0;
}
