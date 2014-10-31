##C语言
---
###一.数值表示
####1.1 整数表示

* stdbool.h 中定义bool, true, false
* stdint.h 中明确定义整数类型, 定义每种类型的最大和最小值
* 字符常量默认是一个Int整数, 编译器自行决定解释为char或者int
* stdint.h中的宏`__INT64_C(c)`将一个整数转换为long long

####1.2 浮点数表示

* float: 32位4字节浮点数, 精度6
* double: 64位8字节浮点数, 精度15
* long double: 80位10字节浮点数, 精度19
* C99复数支持 complex.h 
* long的等级比unsigned int高但是在32位系统中，他们都是32位整数, long不足以容纳unsigned int所有值
所以编译器会将将两个操作数都转换为unsigned long

####1.3 字符串

* 编译器自动连接相邻的字符串
* 使用`\`分割一个字符串为两行, 第一行中`\`左侧的空格和第二行第一个字符左侧的空格都会被计入

####1.4 运算符
* 复合字面值(C99新增内容，直接使用该语法声明一个结构或者数组指针)

    (类型名称){初始化列表}
    例子:
        int *i = &(int){123}
        int *x = (int[]){1, 2, 3, 4}
        struct data_t *data=&(struct data_t){.x=123}

* sizeof: 返回值size_t
* 逗号运算符: 操作数从左到右被顺序处理，并返回右操作数的值核类型

####1.5 语法
* 语句块 int i = ({ char a = 'a'; a++; a;});
* typedef void (funct_t)();  //函数类型
* typedef void (指针funct_t)(); //函数指针类型
* C函数调用所有参数从右向左入栈

* 修饰符
    
    extern: 默认修饰符,用于函数表示"具有外部链接的标示符",用于变量生命表示变量已经在其它单元中定义
    static: 使用改修饰符的函数仅在所编译的单元中使用，还表示函数内的静态变量
    inline: 建议编译器进行内链调用， 包含循环或者递归不能被定义为内联函数 (大量使用可能存在代码扩张)
    static inline: 内链接函数，在当前编译单元内内联

    inline关键字只能用于函数定义处

    const: 常量修饰符, 定义后无法修改
    volatile: 目标可能被其它线程或事件修改，使用该变量前，都须从主存重新获取
    restrict: 修饰指针

* 特殊常量
    __DATE__: 编译日期字符串
    __TIME__: 编译时间字符串
    __FILE__: 编译文件字符串
    __LINE__: 当前源码行号
    __func__: 当前函数名称

* 变量使用extern

    * 一个变量的声明可以出现任意多次，一个变量的定义只可以出现一次
    * `extern`关键字用来扩展变量和函数的可见域
    * 函数的可见域默认是整个程序,所以`extern`关键字没有必要出现在函数的定义或者生命
    * 当一个`extern`变量被被声明但是被初始化，它同样被定义

* void不是有个有效的能够声明变量的类型, void *是一个有效的类型

####1.6 可选性自变量
头函数: stdarg.h

* va_start: 通过可选自变量前一个位置初始化va_list自变量类型指针
* va_arg: 获取可选自变量的值，并能够将指针移动到下一个可选自变量
* va_end: 不在使用自变量指针时使用
* va_copy: 用现有的自变量指针初始化另一个指针

####1.7 数组
数组初始化规则:

* 如果数组为静态生存周期, 那么初始化必须是常量表达式
* 如果提供初始化器, 那么可以不提供数组长度, 由初始化器的最后一个元素决定
* 如果同时提供长度核初始化器,那么没有提供初始值的元素都被初始化为0或NULL

* int x[] = {1, 2, [6]=10, 11};  //初始化器中初始化特的那个的元素
* 数组作为函数参数传入时存在指针退化问题

####1.8 结构体

* 成员偏移量, 利用stddef.h中的offsetof宏可以获取结构成员的偏移量
    
    typedef struct
    {
        int x;
        short y[3];
        long long z;
    } data_t;

    x 偏移   offsetof(data_t, x);
    y[1] 偏移  offsetof(data_t, y[1]);

* 弹性结构成员: 成为"不定长结构", 在结构体尾部生命一个未制定长度的数组

    typedef struct string
    {
        int length;
        char chars[];
    } string;

* 位字段
    
    struct
    {
        unsigned int year:22;
        unsigned int month:4;
        unsigned int day:5;
    } bitstruct;

    不能对位字段成员使用offsetof

####1.9 预处理
* 常量 #define SIZE 10 
* 宏函数

    #define test(x, y) ({\
        int _z = x + y; \
        _z;
    })
    最后一个表达式作为返回值

* 可选性变量

    #define println(format, ...) ({ \
        printf(format "\n", __VA_ARGS__) \
    })

* 字符串化运算符
    
    #define test(name) ({ \
        printf("%s\n", #name); \
    })

* 粘贴记号运算符

    #define test(name, index) ({  \
        int i, len = sizeof(name ## index) / sizeof(int); \
        for (i = 0; i < len; i++) \
        {\
            printf("%d\n", name ## index[i]); \
        }\
    })


