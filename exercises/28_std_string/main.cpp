#include "../exercise.h"
#include <string>

// READ: 字符串 <https://zh.cppreference.com/w/cpp/string/basic_string>

int main(int argc, char **argv) {
    // READ: 字符串字面量 <https://zh.cppreference.com/w/cpp/string/basic_string/operator%22%22s>
    using namespace std::string_literals;
    auto hello = "Hello"s;//需要启用命名空间 std::string_literals，后缀 s 代表直接生成 std::string 对象：
    auto world = "world";//不带后缀 s：底层是常量字符数组 const char[长度]，赋值给 auto 变量时数组会退化，变成指针 const char*。
    // READ: `decltype` 表达式 <https://zh.cppreference.com/w/cpp/language/decltype>
    // READ: `std::is_same_v` 元编程判别 <https://zh.cppreference.com/w/cpp/types/is_same>
    ASSERT((std::is_same_v<decltype(hello), std::string>), "Fill in the missing type.");//decltype(表达式)：编译期获取表达式的类型，不会执行表达式，只提取类型。
    ASSERT((std::is_same_v<decltype(world), const char*>), "Fill in the missing type.");
    // TODO: 将 `?` 替换为正确的字符串
    ASSERT(hello + ", " + world + '!' == "Hello, world!", "Fill in the missing string.");
    return 0;
}
