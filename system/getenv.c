#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 三种方式获取环境变量

#if 0
// 1.main函数的参数获取环境变量

int main(int argc, char* argv[], char* env[])
{
    // argc 命令行参数个数
    // argv 命令行参数具体的内容
    // env 环境变量
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n",argv[i]);
    }
    // char* env[]
    // env[0] = xxx
    // env[1] = yyy
    // env[2] = zzz
    // env[3] = NULL
    for(int i = 0; env[i]; i++)
    {
        printf("%s",env[i]);
    }
    return 0;
}

// 第二种方式 libc库当中提供的变量来获取

int main()
{
    // libc
    extern char** environ;
    for(int i = 0; environ[i]; i++)
    {
        printf("%s", environ[i]);
    }
    return 0;
}
#endif

int main()
{
    // libc库
    // 提供的函数获取某一个具体的环境变量的值
    // 库函数
    // char *getenv(const char *name)
    // name：环境变量的名称
    // 返回值：具体环境变量所对应的值
    char* PATH = getenv("PATH");
    printf("PATH = %s\n", PATH);
    return 0;
}
