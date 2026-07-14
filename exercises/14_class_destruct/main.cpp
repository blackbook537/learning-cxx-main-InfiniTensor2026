#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci(){
        delete[] cache;
    }
    // new size_t[capacity]：在堆开辟 capacity 个 size_t 空间，返回首地址指针，赋值给 cache；
    // 堆内存不会自动回收，必须手动释放，否则造成内存泄漏；
    // 释放动态数组必须用 delete[] cache;，普通 delete 只能释放单个变量，不能释放数组。
    // 析构函数 Destructor
    // 写法：~类名()，无返回值、无参数，一个类只能有 1 个析构；
    // 调用时机：对象生命周期结束（离开作用域、delete 对象）时自动调用；
    // 本题作用：释放构造时 new[] 申请的堆内存，杜绝内存泄漏。

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
