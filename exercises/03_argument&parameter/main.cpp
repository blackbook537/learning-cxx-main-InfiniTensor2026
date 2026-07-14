#include "../exercise.h"

// READ: <https://stackoverflow.com/questions/156767/whats-the-difference-between-an-argument-and-a-parameter>
// THINK: 参数都有哪些传递方式？如何选择传递方式？
// ANSWER:
// 1.值传递（Pass by Value）:将实参的副本复制一份传给函数。函数内部对形参的修改不会影响原始实参。
// 例如：void swap(int a, int b)
// 2.引用传递（Pass by Reference）:将实参的引用（内存地址） 传给函数，形参是实参的别名。函数内对形参的修改会直接影响原始实参。
// 例如：void swap(int *a, int *b)
// 3. 指针传递（Pass by Pointer）:传递的是实参的地址（指针的值），本质上是值传递的一种。函数通过指针间接操作原始数据。
// 例如：void swap(int *a, int *b)
// 4. 常量引用传递（Pass by Const Reference）: 传递引用，但加上 const 修饰，禁止函数内部修改实参。
// 例如：void print(const int &value) 
// 注意：int 通常占 4 字节,引用在底层通常由指针（地址）实现，在 64 位系统下占 8 字节,对于 int 类型，按值传递通常比按常量引用传递更快。对于体积小（通常不超过16-24字节）、拷贝代价低廉的类型，优先按值传递；对于体积大、拷贝昂贵的类型（如 std::string, std::vector），则按常量引用传递。

void func(int);

// TODO: 为下列 ASSERT 填写正确的值
int main(int argc, char **argv) {
    auto arg = 99;
    ASSERT(arg == 99, "arg should be ?");
    std::cout << "befor func call: " << arg << std::endl;
    func(arg);
    ASSERT(arg == 99, "arg should be ?");
    std::cout << "after func call: " << arg << std::endl;
    return 0;
}

// TODO: 为下列 ASSERT 填写正确的值
void func(int param) {
    ASSERT(param == 99, "param should be ?");
    std::cout << "befor add: " << param << std::endl;
    param += 1;
    ASSERT(param == 100, "param should be ?");
    std::cout << "after add: " << param << std::endl;
}
