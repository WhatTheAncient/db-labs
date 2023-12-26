#include <string>
#include <vector>
#include "gtest/gtest.h"

#include "../src/treap.hpp"
#include "sample.hpp"

using TreapWithSample = rut::Treap<uint32_t, Sample>;
using NodeWithSample = treap::Node<uint32_t, Sample>;

TEST(Treap, DefaultConstructor) {
  auto defaultTreap = TreapWithSample();

  EXPECT_TRUE(defaultTreap.getRoot() == nullptr);
  EXPECT_TRUE(defaultTreap.leftSubTreap() == nullptr);
  EXPECT_TRUE(defaultTreap.rightSubTreap() == nullptr);
};

TEST(Treap, CopyConstructor) {
  auto copySrc = TreapWithSample();
  auto copy = TreapWithSample(copySrc);

  EXPECT_TRUE(copy == copySrc);
}

TEST(Treap, InsertInEmptyTreap) {
  auto emptyTreap = TreapWithSample();
  auto key = 2;
  auto priority = 3;
  auto data = Sample("Some");

  emptyTreap.Insert(key, priority, data);
  
  EXPECT_TRUE(emptyTreap.getRoot()->getKey() == key);
  EXPECT_TRUE(emptyTreap.getRoot()->getPriority() == priority);
  EXPECT_TRUE(emptyTreap.getRoot()->getData() == data);
}

TEST(Treap, InsertWithLessKeyAndPriority) {
  auto emptyTreap = TreapWithSample();
  auto key = 2, lessKey = 1;
  auto priority = 3, lessPriority = 2;
  auto data = Sample("Some"), otherData = Sample("Other");

  emptyTreap.Insert(key, priority, data);
  emptyTreap.Insert(lessKey, lessPriority, otherData);
  
  EXPECT_TRUE(emptyTreap.leftSubTreap()->getRoot()->getKey() == lessKey);
  EXPECT_TRUE(emptyTreap.leftSubTreap()->getRoot()->getPriority() == lessPriority);
  EXPECT_TRUE(emptyTreap.leftSubTreap()->getRoot()->getData() == otherData);
}

TEST(Treap, InsertWithLessKeyAndGreaterPriority) {
  auto emptyTreap = TreapWithSample();
  auto key = 2, greaterKey = 3;
  auto priority = 3, lessPriority = 2;
  auto data = Sample("Some"), otherData = Sample("Other");

  emptyTreap.Insert(key, priority, data);
  emptyTreap.Insert(greaterKey, lessPriority, otherData);
  
  EXPECT_TRUE(emptyTreap.rightSubTreap()->getRoot()->getKey() == greaterKey);
  EXPECT_TRUE(emptyTreap.rightSubTreap()->getRoot()->getPriority() == lessPriority);
  EXPECT_TRUE(emptyTreap.rightSubTreap()->getRoot()->getData() == otherData);
}

TEST(Treap, InsertWithGreaterKeyAndPriority) {
  auto emptyTreap = TreapWithSample();
  auto key = 2, greaterKey = 3;
  auto priority = 3, greaterPriority = 4;
  auto data = Sample("Some"), otherData = Sample("Other");

  emptyTreap.Insert(key, priority, data);
  emptyTreap.Insert(greaterKey, greaterPriority, otherData);
  
  EXPECT_TRUE(emptyTreap.getRoot()->getKey() == greaterKey);
  EXPECT_TRUE(emptyTreap.getRoot()->getPriority() == greaterPriority);
  EXPECT_TRUE(emptyTreap.getRoot()->getData() == otherData);
  EXPECT_TRUE(emptyTreap.leftSubTreap()->getRoot()->getKey() == key);
  EXPECT_TRUE(emptyTreap.leftSubTreap()->getRoot()->getPriority() == priority);
  EXPECT_TRUE(emptyTreap.leftSubTreap()->getRoot()->getData() == data);
}
