#include "../exercise.h"

// READ: 派生类 <https://zh.cppreference.com/w/cpp/language/derived_class>

static int i = 0;

struct X {
    int x;

    X(int x_) : x(x_) {
        std::cout << ++i << ". " << "X(" << x << ')' << std::endl;
    }
    X(X const &other) : x(other.x) {
        std::cout << ++i << ". " << "X(X const &) : x(" << x << ')' << std::endl;
    }
    ~X() {
        std::cout << ++i << ". " << "~X(" << x << ')' << std::endl;
    }
};
struct A {
    int a;

    A(int a_) : a(a_) {
        std::cout << ++i << ". " << "A(" << a << ')' << std::endl;
    }
    A(A const &other) : a(other.a) {
        std::cout << ++i << ". " << "A(A const &) : a(" << a << ')' << std::endl;
    }
    ~A() {
        std::cout << ++i << ". " << "~A(" << a << ')' << std::endl;
    }
};
struct B : public A {
    X x;

    B(int b) : A(1), x(b) {
        std::cout << ++i << ". " << "B(" << a << ", X(" << x.x << "))" << std::endl;
    }
    B(B const &other) : A(other.a), x(other.x) {
        std::cout << ++i << ". " << "B(B const &) : A(" << a << "), x(X(" << x.x << "))" << std::endl;
    }
    ~B() {
        std::cout << ++i << ". " << "~B(" << a << ", X(" << x.x << "))" << std::endl;
    }
};

int main(int argc, char **argv) {
    X x = X(1);
    A a = A(2);
    B b = B(3);

    // TODO: 补全三个类型的大小
    // struct X：仅成员 int x → 大小 = 4
    // struct A：仅成员 int a → 大小 = 4
    // struct B : public A：公有继承 A，内部包含完整 A 基类子对象 + 成员 X
    // A(4) + X(4) = 8 → sizeof(B)=8
    static_assert(sizeof(X) == 4, "There is an int in X");
    static_assert(sizeof(A) == 4, "There is an int in A");
    static_assert(sizeof(B) == 8, "B is an A with an X");

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    // 这是不可能的，A 无法提供 B 增加的成员变量的值
    // B ba = A(4);

    // 这也是不可能的，因为 A 是 B 的一部分，就好像不可以把套娃的外层放进内层里。
    A ab = B(5);// 然而这个代码可以编译和运行！
    // THINK: 观察打印出的信息，推测把大象放进冰箱分几步？
    // ANSWER:
    // 1. 创建临时B对象：先构造基类A(1) → 构造成员X(5) → 执行B构造函数体
    // 2. 切片拷贝：调用A的拷贝构造，仅复制临时B里A的部分给ab
    // 3. 销毁临时B对象：执行B析构体 → 销毁X成员 → 销毁基类A
    // THINK: 这样的代码是“安全”的吗？
    // ANSWER: 不安全，发生对象切片，派生类独有的X成员数据直接丢失，产生数据截断逻辑错误
    // NOTICE: 真实场景中不太可能出现这样的代码

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    return 0;
}
