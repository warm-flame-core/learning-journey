#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#define COMMAND_SIZE 1024
#define FORMAT "%s@VM-0-2-ubuntu:%s# "
#define MAXARGV 128
#define NONE_REDIR 0
#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3

int redir = NONE_REDIR;
std::string filename;

char *g_argv[MAXARGV];
int g_argc = 0;
char cwd[1024];
char cwdenv[1024];
int lastcode = 0;
const char *GetUserName() {
    const char *name = getenv("USER");
    return name == NULL ? "None" : name;
}
const char *GetPwd() {
    //const char *pwd = getenv("PWD");
    const char *pwd = getcwd(cwd, sizeof(cwd));
    if(pwd != NULL)
    {
        snprintf(cwdenv, sizeof(cwdenv), "PWD=%s", cwd);
        putenv(cwdenv);
    }
    return pwd == NULL ? "None" : pwd;
}

const char *GetHome()
{
    const char *home = getenv("HOME");
    return home == NULL ? "" : home;
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
    return g_argc > 0 ? true : false;
}

int Execute() {
    pid_t id = fork();
    if (id == 0) {
        int fd = -1;
        // 子进程检测重定向情况
        if(redir == INPUT_REDIR)
        {
            fd = open(filename.c_str(), O_RDONLY);
            if(fd < 0) exit(1);
            dup2(fd,0);
            close(fd);
        }
        else if(redir == OUTPUT_REDIR)
        {
            fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);
            if(fd < 0) exit(2);
            dup2(fd, 1);
            close(fd);
        }
        else if(redir == APPEND_REDIR)
        {
            fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666);
            if(fd < 0) exit(2);
            dup2(fd, 1);
            close(fd);
        }
        else
        {}
        execvp(g_argv[0], g_argv);
        exit(1);
    }
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    (void)rid;
    return 0;
}

bool CheckAndExecBuiltin()
{
    std::string cmd = g_argv[0];
    if(cmd == "cd")
    {

        if(g_argc == 1)
        {
            std::string home = GetHome();
            if(home.empty()) return true;
            chdir(home.c_str());
        }
        else
        {
            std::string where = g_argv[1];
            chdir(where.c_str());
        }
        return true;
    }
    return false;
}
void Trimspace(char cmd[], int& end)
{
    while(isspace(cmd[end]))
    {
        end++;
    }
}
void RedirCheck(char cmd[])
{
        
    redir = NONE_REDIR;
    filename.clear();
    int start = 0;
    int end = strlen(cmd);
    while(end > start)
    {
        if(cmd[end] == '<')
        {
            cmd[end++] = 0;
            redir = INPUT_REDIR;
            Trimspace(cmd, end);
            filename = cmd+end;
            break;
        }
        else if(cmd[end] == '>')
        {
            if(cmd[end - 1] == '>')
            {
                cmd[end - 1] = 0;
                cmd[end++] = 0;
                redir = APPEND_REDIR; 
            }
            else
            {
                cmd[end] = 0;
                redir = INPUT_REDIR;
            }
            Trimspace(cmd, end);
            filename = cmd+end;
            break;
        }
        else
        {
            end--;
        }
    }
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
        
        //命令好分析
        RedirCheck(commandline);

        // 拆字符串
        if(!CommandParse(commandline))
        {
            continue;
        }
        // 检查内建命令
        if(CheckAndExecBuiltin())
        {
            continue;
        }
        // 执行命令
        Execute();
    }

    return 0;
}
