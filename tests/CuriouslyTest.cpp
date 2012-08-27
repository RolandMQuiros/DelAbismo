#include <gtest/gtest.h>
#include "da/Attribute.h"

struct A : da::Attribute<A> {
    
};

struct B : da::Attribute<B> {
    
};

struct C : public B {
    
};

template <class Derived>
struct D : public B {
    
};

TEST(CuriouslyAttributeTest, TypeIdTest) {
    EXPECT_EQ(1, A::typeId());
    EXPECT_EQ(2, B::typeId());
    
    EXPECT_EQ(2, da::Attribute<B>::typeId());
    
    A a;
    B b;
    B bb[10];
    
    EXPECT_EQ(1, a.getTypeId());
    EXPECT_EQ(2, b.getTypeId());
    
    for (int i = 0; i < 10; i++) {
        EXPECT_EQ(2, bb[i].getTypeId());
    }
    
    C c;
    
    EXPECT_EQ(3, c.getTypeId());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
