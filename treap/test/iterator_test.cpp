#include <gtest/gtest.h>

#include "sample.hpp"
#include "../src/treap.hpp" 

using KeyType = int;
using DataType = Sample;

TEST(IteratorTest, ConstructorWithReference) {
    auto treap = std::make_shared<rut::Treap<KeyType, DataType>>();
    treap->Insert(1, 10, Sample("Node 1"));
    treap->Insert(2, 20, Sample("Node 2"));
    treap->Insert(3, 30, Sample("Node 3"));

    treap::Iterator<KeyType, DataType> it(*treap);

    EXPECT_EQ(it->getKey(), 1);
}

TEST(IteratorTest, ConstructorWithPointer) {
    auto treap = std::make_shared<rut::Treap<KeyType, DataType>>();
    treap->Insert(1, 10, Sample("Node 1"));
    treap->Insert(2, 20, Sample("Node 2"));
    treap->Insert(3, 30, Sample("Node 3"));

    treap::Iterator<KeyType, DataType> it(treap);

    EXPECT_EQ(it->getKey(), 1);
}

TEST(IteratorTest, OperatorArrow) {
    auto treap = std::make_shared<rut::Treap<KeyType, DataType>>();
    treap->Insert(1, 10, Sample("Node 1"));
    treap->Insert(2, 20, Sample("Node 2"));
    treap->Insert(3, 30, Sample("Node 3"));

    treap::Iterator<KeyType, DataType> it(treap);

    EXPECT_EQ(it->getKey(), 1);
}

TEST(IteratorTest, OperatorDereference) {
    auto treap = std::make_shared<rut::Treap<KeyType, DataType>>();
    treap->Insert(1, 10, Sample("Node 1"));
    treap->Insert(2, 20, Sample("Node 2"));
    treap->Insert(3, 30, Sample("Node 3"));

    treap::Iterator<KeyType, DataType> it(treap);

    EXPECT_EQ((*it).getKey(), 1);
}

TEST(IteratorTest, PrefixIncrementOperator) {
    auto treap = std::make_shared<rut::Treap<KeyType, DataType>>();
    treap->Insert(1, 10, Sample("Node 1"));
    treap->Insert(2, 20, Sample("Node 2"));
    treap->Insert(3, 30, Sample("Node 3"));

    treap::Iterator<KeyType, DataType> it(treap);

    ++it;
    EXPECT_EQ(it->getKey(), 2);
}

TEST(IteratorTest, PostfixIncrementOperator) {
    auto treap = std::make_shared<rut::Treap<KeyType, DataType>>();
    treap->Insert(1, 10, Sample("Node 1"));
    treap->Insert(2, 20, Sample("Node 2"));
    treap->Insert(3, 30, Sample("Node 3"));

    treap::Iterator<KeyType, DataType> it(treap);

    it++;
    EXPECT_EQ(it->getKey(), 2);
}
