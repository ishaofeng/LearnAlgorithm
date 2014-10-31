#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#define println(format, ...) ({ \
            printf(format "\n", __VA_ARGS__); \
        })

#define testname(name) ({ \
            printf("%s\n", #name); \
        })

#define testname1(name) ({ \
            #name; \
        })

#define testpaste(name, index) ({ \
            int i, len = sizeof(name ## index) / sizeof(int); \
            for (i = 0; i < len; i++) \
            { \
                printf("%d\n", name ## index[i]); \
            } \
        })

#define merge(a, b) a##b

#define get(a) #a

typedef struct
{
    int x;
    short y[3];
    long long z;
} data_t;

typedef struct string
{
    int length;
    char chars[];
} string;

typedef struct bitstruct
{
    unsigned int year:22;
    unsigned int month:4;
    unsigned int day:5;
} bitstruct;

void pp(char *info, int len)
{
    printf("%s: %d\n", info, len);
}

void test(int count, ...)
{
    va_list args;
    va_start(args, count);

    int i = 0;
    for (i = 0; i < count; ++i)
    {
        int value = va_arg(args, int);
        printf("va_arg: %d\n", value);
    }


    va_end(args);
}

void test1(int n)
{
    int x[n];
    int i = 0;
    for (i = 0; i< n; ++i)
    {
        x[i] = i;
    }

    struct data { int x[n]; } d;
    printf("%ld\n", sizeof(d));
}

extern int var1;
int main()
{
    bool a;
    println("%d", var1);
    /*
    pp("char", sizeof(char));
    pp("short", sizeof(short));
    pp("int", sizeof(int));
    pp("long", sizeof(long));
    pp("long long", sizeof(long long));
    pp("bool", sizeof(bool));

    pp("float", sizeof(float));
    pp("double", sizeof(double));
    pp("long double", sizeof(long double));

    char *s = "shao \
feng";

    printf("%s\n", s);

    //复合字面值
    int *i = &(int) {123};
    printf("%d\n", *i);

    //逗号运算符
    int p = 1;
    long long x = (p++, (long long)p);
    printf("%lld\n", x);

    int k = ({char a = 'a'; a++; a;});
    printf("%d\n", k);

    //可选自变量
    test(3, 100, 102, 103);


    int d[] = {1, 2, 3, 4};
    printf("%ld\n", sizeof(d));

    test1(2);

    //成员偏移量, 使用stddef.h中的offsetof宏
    printf("len %ld\n", sizeof(data_t));
    printf("z %ld\n", offsetof(data_t, z));
    printf("y[0] %ld\n", offsetof(data_t, y[0]));
    printf("y[1] %ld\n", offsetof(data_t, y[1]));
    printf("y[2] %ld\n", offsetof(data_t, y[2]));
    printf("y[3] %ld\n", offsetof(data_t, y[3]));

    //弹性结构成员
    printf("%ld\n", sizeof(string));

    //位字段
    bitstruct bb = {2010, 4, 30};
    printf("size=%ld year=%d month=%d day=%d\n", sizeof(bb), bb.year, bb.month, bb.day);

    //预处理
    println("%s %d %f", "shaofeng", 10, 32.34343);
    testname(2.3223);
    char *a = testname1(2.3234343);
    println("%s", a);

    int x1[] = {1, 2, 3};
    int x2[] = {11, 22, 33, 44, 55};

    testpaste(x, 1);
    testpaste(x, 2);

    println("%s %s %s %s %d", __DATE__, __TIME__, __FILE__, __func__, __LINE__);

    int ia = 10;
    char *str = get(ia);
    println("%s", str);
    */
    return 0;
}
