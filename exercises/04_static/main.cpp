#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
// ANSWER:
// 函数内的 static 局部变量只会初始化 1 次，后续调用不会重新赋值
// 函数前面的 static int func(int param) —— 控制函数「文件可见范围」
// 函数内部 static int static_ = param; —— 静态局部变量:内存存在全局静态存储区，程序运行全程存活;仅第一次调用函数执行一次初始化，后续调用跳过赋值;会永久保存上一次调用后的数值

static int func(int param) {
    static int static_ = param;
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++;
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
