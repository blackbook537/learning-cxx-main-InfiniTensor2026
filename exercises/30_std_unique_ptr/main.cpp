#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // drop(forward(reset(nullptr)));
        // 1.reset(nullptr)入参是空指针，不执行 record('r')；
        // 2.forward(临时R1);所有权移入 forward 局部变量，执行 record('f') → R1._records = "f"；
        // 3.drop(临时R1),所有权移入 drop 局部变量，执行 record('d') → R1._records = "fd"；返回 nullptr；
        // problems[0] = {"fd"}
        // forward(drop(reset(forward(forward(reset(nullptr))))));
        // 1.reset(nullptr) → 新建资源 R0，记录 ""，临时 T0=R0
        // 2.forward(T0)：R0 记录追加f → "f"，返回 R0，临时 T1=R0
        // 3.forward(T1)：R0 记录追加f → "ff"，返回 R0，临时 T2=R0
        // 4.reset(T2)：R0 移入 reset 局部变量，追加r → "ffr", 返回全新资源R1（记录""），临时 T3=R1, 局部 ptr 销毁，R0 析构 → RECORDS.push_back("ffr")
        // 5.drop(T3)：R1 移入 drop 局部变量，追加d → "d", 返回 nullptr，局部 ptr 销毁，R1 析构 → RECORDS.push_back("d")
        // 6.forward(nullptr)：空指针，无任何操作，无析构。
        // problems[1] = {"ffr", "d"}
        // drop(drop(reset(drop(reset(reset(nullptr))))));
        // 1.reset(nullptr) → 新建 R0，记录""，T0=R0;
        // 2.reset(T0)：R0 移入 reset 局部，追加r → "r", 返回新资源 R1，T1=R1, R0 析构 → RECORDS.push_back("r")
        // 3.drop(T1)：R1 移入 drop 局部，追加d → "d", 返回 nullptr，R1 析构 → RECORDS.push_back("d")
        // 4.reset(nullptr) → 新建 R2，记录""，T3=R2
        // 5.drop(T3)：R2 移入 drop 局部，追加d → "d", 返回 nullptr，R2 析构 → RECORDS.push_back("d")
        // 6.drop(nullptr)：空指针，无操作。
        // problems[2] = {"r", "d", "d"}
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"ffr", "d"},
        {"r", "d", "d"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
