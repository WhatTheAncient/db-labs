#include <gtest/gtest.h>
#include "../src/treap.hpp"
#include "sample.hpp"

using KeyType = int;
using DataType = Sample;

TEST(TreapTest, DefaultConstructor) {
    rut::Treap<KeyType, DataType> treap;

    ASSERT_EQ(treap.getRoot(), nullptr);
}

TEST(TreapTest, CopyConstructor) {
  rut::Treap<KeyType, DataType> originalTreap;
  originalTreap.Insert(5, 10, Sample("Node 5"));
  originalTreap.Insert(3, 8, Sample("Node 3"));
  originalTreap.Insert(7, 15, Sample("Node 7"));

  rut::Treap<KeyType, DataType> copiedTreap(originalTreap);

  ASSERT_EQ(originalTreap, copiedTreap);
}

TEST(TreapTest, Split) {
    rut::Treap<KeyType, DataType> treap;
    treap.Insert(5, 10, Sample("Node 5"));
    treap.Insert(3, 8, Sample("Node 3"));
    treap.Insert(7, 15, Sample("Node 7"));
    treap.Insert(2, 12, Sample("Node 2"));

    auto [left, right] = treap.Split(4);

    ASSERT_EQ(left->inOrderedVector().size(), 2);
    ASSERT_EQ(left->inOrderedVector()[0]->getData(), Sample("Node 2"));
    ASSERT_EQ(left->inOrderedVector()[1]->getData(), Sample("Node 3"));

    ASSERT_EQ(right->inOrderedVector().size(), 2);
    ASSERT_EQ(right->inOrderedVector()[0]->getData(), Sample("Node 5"));
    ASSERT_EQ(right->inOrderedVector()[1]->getData(), Sample("Node 7"));
}

TEST(TreapTest, Merge) {
    auto node1 = std::make_shared<treap::Node<int, Sample>>(1, 10, Sample("Node 1"));
    auto node2 = std::make_shared<treap::Node<int, Sample>>(2, 20, Sample("Node 2"));
    auto node3 = std::make_shared<treap::Node<int, Sample>>(3, 30, Sample("Node 3"));
    auto node4 = std::make_shared<treap::Node<int, Sample>>(4, 40, Sample("Node 4"));

    auto treap1 = std::make_shared<rut::Treap<int, Sample>>();
    treap1->Insert(1, 10, Sample("Node 1"));

    auto treap2 = std::make_shared<rut::Treap<int, Sample>>();
    treap2->Insert(2, 20, Sample("Node 2"));

    auto treap3 = std::make_shared<rut::Treap<int, Sample>>();
    treap3->Insert(3, 30, Sample("Node 3"));

    auto treap4 = std::make_shared<rut::Treap<int, Sample>>();
    treap4->Insert(4, 40, Sample("Node 4"));

    auto mergedTreap = merge(merge(merge(treap1, treap2), treap3), treap4);
    auto orderedNodes = mergedTreap->inOrderedVector();

    ASSERT_EQ(orderedNodes.size(), 4);
    EXPECT_EQ(orderedNodes[0]->getKey(), 1);
    EXPECT_EQ(orderedNodes[1]->getKey(), 2);
    EXPECT_EQ(orderedNodes[2]->getKey(), 3);
    EXPECT_EQ(orderedNodes[3]->getKey(), 4);
}

TEST(TreapTest, Insert) {
    rut::Treap<KeyType, DataType> treap;

    treap.Insert(5, 10, Sample("Node 5"));
    treap.Insert(3, 8, Sample("Node 3"));
    treap.Insert(7, 15, Sample("Node 7"));

    ASSERT_EQ(treap.inOrderedVector().size(), 3);
    ASSERT_EQ(treap.inOrderedVector()[0]->getData(), Sample("Node 3"));
    ASSERT_EQ(treap.inOrderedVector()[1]->getData(), Sample("Node 5"));
    ASSERT_EQ(treap.inOrderedVector()[2]->getData(), Sample("Node 7"));
}

TEST(TreapTest, Find) {
    rut::Treap<KeyType, DataType> treap;
    treap.Insert(5, 10, Sample("Node 5"));
    treap.Insert(3, 8, Sample("Node 3"));
    treap.Insert(7, 15, Sample("Node 7"));

    auto foundNode = treap.Find(3);

    ASSERT_TRUE(foundNode != nullptr);
    ASSERT_EQ(foundNode->getData(), Sample("Node 3"));
}

TEST(TreapTest, Remove) {
    rut::Treap<KeyType, DataType> treap;
    treap.Insert(5, 10, Sample("Node 5"));
    treap.Insert(3, 8, Sample("Node 3"));
    treap.Insert(7, 15, Sample("Node 7"));

    ASSERT_TRUE(treap.Remove(3));

    ASSERT_EQ(treap.inOrderedVector().size(), 2);
    ASSERT_EQ(treap.inOrderedVector()[0]->getData(), Sample("Node 5"));
    ASSERT_EQ(treap.inOrderedVector()[1]->getData(), Sample("Node 7"));
}
