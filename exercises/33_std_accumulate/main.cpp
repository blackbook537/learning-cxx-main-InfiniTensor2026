#include "../exercise.h"
#include <numeric>

// READ: `std::accumulate` <https://zh.cppreference.com/w/cpp/algorithm/accumulate>
// 遍历一段区间，用自定义二元运算持续累积计算，默认是累加，我们这里用来求所有维度的乘积。

int main(int argc, char **argv) {
    using DataType = float;
    int shape[]{1, 3, 224, 224};//张量总字节数 = 张量总元素数量 × 单个元素占用字节
    // TODO: 调用 `std::accumulate` 计算：
    //       - 数据类型为 float；
    //       - 形状为 shape；
    //       - 连续存储；
    //       的张量占用的字节数
    // int size =
    int elem_count = std::accumulate(
        std::begin(shape), std::end(shape),
        1,//累积乘法初始值为1
        [](int a, int b){return a * b;}
    );
    int size = elem_count * sizeof(DataType);
    ASSERT(size == 602112, "4x1x3x224x224 = 602112");
    return 0;
}
