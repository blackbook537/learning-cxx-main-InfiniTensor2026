#include "../exercise.h"
#include <algorithm>
#include <string>
#include <vector>

// READ: `std::transform` <https://zh.cppreference.com/w/cpp/algorithm/transform>
// std::transform 是标准库变换算法：遍历输入容器所有元素，对每个元素执行自定义一元函数，将函数结果写入输出容器。
// template<class InputIt, class OutputIt, class UnaryOp>
// OutputIt transform(InputIt first, InputIt last, OutputIt dest, UnaryOp op);
// READ: `std::vector::begin` <https://zh.cppreference.com/w/cpp/container/vector/begin>
// 返回指向 vector 首元素的迭代器。如果 vector 为空，那么返回的迭代器等于 end()。

int main(int argc, char **argv) {
    std::vector<int> val{8, 13, 21, 34, 55};
    // TODO: 调用 `std::transform`，将 `v` 中的每个元素乘以 2，并转换为字符串，存入 `ans` 
    std::vector<std::string> ans;
    // transform：遍历val，每个元素执行 x*2 再转字符串，存入ans
    std::transform(val.begin(), val.end(), std::back_inserter(ans),
        [](int x){
            return std::to_string(x * 2);
        }
    );
    ASSERT(ans.size() == val.size(), "ans size should be equal to val size");
    ASSERT(ans[0] == "16", "ans[0] should be 16");
    ASSERT(ans[1] == "26", "ans[1] should be 26");
    ASSERT(ans[2] == "42", "ans[2] should be 42");
    ASSERT(ans[3] == "68", "ans[3] should be 68");
    ASSERT(ans[4] == "110", "ans[4] should be 110");
    return 0;
}
