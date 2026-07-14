#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // TODO: 正确初始化静态字段
    static int num_a;

    A() {
        ++num_a;
    }
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

int A::num_a = 0;

struct B final : public A {
    // TODO: 正确初始化静态字段
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() {
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;
    auto b = new B;
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");

    delete a;
    delete b;
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");

    // TODO: 基类指针无法随意转换为派生类指针，补全正确的转换语句
    B &bb = static_cast<B &>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");

    // TODO: ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}
//注意：
// 静态变量初始化：C++14 及更早版本不能直接 static int num_a=0;，必须类外单独定义初始化；
// 虚析构是强制要求：只要基类指针可能指向派生类并执行 delete，析构必须加 virtual，否则子类析构不会执行，计数错乱、内存泄漏；
// 创建 B 一定会同时增加 A 的计数：子类构造自动调用父类构造，父类静态计数同步自增；
// 向下转换不能隐式：基类指针 / 引用转派生类必须用 static_cast 显式转换，禁止直接赋值；
// 静态变量生命周期和程序一致，不受对象创建销毁影响，全局唯一一份。
// 虚析构强制规则:
// 只要存在「基类指针 / 引用指向派生类，并且会执行 delete」，基类析构必须写 virtual ~基类()。
// 不加 virtual 的后果:
// 1.派生类析构函数完全不执行；
// 2.子类堆资源无法释放（内存泄漏）；
// 3.子类静态计数、成员清理逻辑全部失效（本题 num_b 不归零）。
// 析构执行顺序（有虚析构时）
// 销毁派生类对象：先子类析构 → 后父类析构。
