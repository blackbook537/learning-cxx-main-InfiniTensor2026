#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);//shared 创建后计数 = 1；
    std::shared_ptr<int> ptrs[]{shared, shared, shared};//数组 3 次拷贝 shared，每次拷贝计数 + 1：1 → 2 → 3 → 4；

    std::weak_ptr<int> observer = shared;//observer 是弱指针，不改变计数；
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();//ptrs[0] 释放所有权，计数 -1 → 4-1=3
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;//ptrs[1] 释放所有权，计数 -1 → 3-1=2
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);//新建独立内存，ptrs[2] 不再指向原资源；原资源只剩变量 shared 持有，计数 = 1
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);// 移动，shared变空，计数保持3
    ASSERT(observer.use_count() == 3, "");

    std::ignore = std::move(ptrs[0]);//std::move(ptrs[0]) 生成临时shared_ptr，接管 ptrs [0] 所有权，ptrs [0] 置空；临时对象直接丢弃给std::ignore，语句结束临时析构，计数减 1；
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");

    return 0;
}
