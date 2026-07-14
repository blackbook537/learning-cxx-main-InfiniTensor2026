#include "../exercise.h"

// constexpr unsigned long long fibonacci(int i) {
//     switch (i) {
//         case 0:
//             return 0;
//         case 1:
//             return 1;
//         default:
//             return fibonacci(i - 1) + fibonacci(i - 2);
//     }
// }

constexpr unsigned long long fibonacci(int i) {//递归复杂度过高编译运行算不出结果，使用迭代方式
    if (i == 0) return 0;
    unsigned long long a = 0, b = 1;
    for (int k = 2; k <= i; ++k) {
        auto c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    constexpr auto ANS_N = 90;// constexpr = 编译期常量:等号右边的表达式必须在编译阶段算出固定数字;由于fibonacci(90)复杂度过高编译器有「常量表达式求值资源上限」所以使用递归方法不能编译阶段就计算出来。
    constexpr auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
