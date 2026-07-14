#include "../exercise.h"
#include <cmath>

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
template<typename T>
T plus(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    // ANSWER:
    // 可以直接用 == 判断相等：小数是 2 的负整数次幂，能被二进制精确存储
    // 不能直接 == 必须判断差值：普通十进制小数（0.1、0.2、0.3、0.7 等）存在二进制舍入误差
    // 标准做法：计算两个数差值的绝对值，小于一个极小阈值（epsilon，如 1e-9）即认为相等;fabs(计算结果 - 目标值) < 1e-9
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过
    ASSERT(fabs(plus(0.1, 0.2) - 0.3) < 1e-9, "How to make this pass?");

    return 0;
}
