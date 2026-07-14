#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG);
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG);
    ASSERT(rbc.virtual_name() == 'C', MSG);
    ASSERT(rcd.virtual_name() == 'C', MSG);
    ASSERT(rab.direct_name() == 'A', MSG);
    ASSERT(rbc.direct_name() == 'B', MSG);
    ASSERT(rcd.direct_name() == 'C', MSG);

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG);
    ASSERT(rbd.virtual_name() == 'C', MSG);
    ASSERT(rac.direct_name() == 'A', MSG);
    ASSERT(rbd.direct_name() == 'B', MSG);

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG);
    ASSERT(rad.direct_name() == 'A', MSG);

    return 0;
}
// final 虚函数阻断重写：D 不能重写 virtual_name，所有 D 对象调用虚函数都走 C 的实现；
// 只有虚函数 + 基类引用 / 指针才会触发多态；普通函数永远看引用类型；
// 直接对象 . 调用不触发多态，无论是否 virtual，只调用自身类型函数；
// override 仅用于校验，不改变运行逻辑，是编译期安全工具。
// 只有同时满足两个条件才会动态绑定（走子类函数）：
// 1.函数被 virtual 修饰；
// 2.通过父类引用 / 父类指针调用。
// 两种情况不触发多态，只看自身类型：
// 1.直接用对象 . 调用（d.virtual_name()）；
// 2.普通成员函数（无 virtual），无论引用还是对象，编译期就定死调用父类版本。
// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>
