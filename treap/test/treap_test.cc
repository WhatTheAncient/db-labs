#include <string>
#include "gtest/gtest.h"
#include "../src/treap.hpp"

TEST(Treap, DefaultConstructor) {
  auto defaultTreap = rut::Treap<uint32_t, std::string>();

  EXPECT_TRUE(defaultTreap.getRoot() != nullptr);
  EXPECT_TRUE(defaultTreap.leftSubTreap() == nullptr);
  EXPECT_TRUE(defaultTreap.rightSubTreap() == nullptr);
};

TEST(Treap, setRoot) {
  auto treap = rut::Treap<uint32_t, std::string>();
  auto rootPtr = std::make_shared<treap::Node<uint32_t, std::string>>();

  treap.setRoot(rootPtr);

  EXPECT_TRUE(treap.getRoot() == rootPtr);
  EXPECT_TRUE(treap.getRoot()->getPriority() == rootPtr->getPriority());
}

TEST(Treap, setLeftSubTreap) {
  auto treap = rut::Treap<uint32_t, std::string>();
  auto leftSubTreapPtr = std::make_shared<rut::Treap<uint32_t, std::string>>();

  treap.setLeftSubTreap(leftSubTreapPtr);

  EXPECT_TRUE(treap.leftSubTreap() == leftSubTreapPtr);
  EXPECT_TRUE(treap.leftSubTreap()->getRoot() == leftSubTreapPtr->getRoot());
  EXPECT_TRUE(treap.leftSubTreap()->getRoot()->getPriority() == leftSubTreapPtr->getRoot()->getPriority());
}

TEST(Treap, setRightSubTreap) {
  auto treap = rut::Treap<uint32_t, std::string>();
  auto rightSubTreapPtr = std::make_shared<rut::Treap<uint32_t, std::string>>();

  treap.setRightSubTreap(rightSubTreapPtr);

  EXPECT_TRUE(treap.rightSubTreap() == rightSubTreapPtr);
  EXPECT_TRUE(treap.rightSubTreap()->getRoot()->getPriority() == rightSubTreapPtr->getRoot()->getPriority());
}

TEST(Treap, SplitWithNullRoot) {
  auto treap = rut::Treap<uint32_t, std::string>();
  auto separator = std::make_shared<treap::Node<uint32_t, std::string>>();
  treap.setRoot(nullptr);

  rut::SubTreaps<uint32_t, std::string> splitted = treap.Split(separator);

  EXPECT_TRUE(splitted.first == nullptr);
  EXPECT_TRUE(splitted.second == nullptr);
}

TEST(Treap, SplitByNullSeparator) {
  auto treap = rut::Treap<uint32_t, std::string>();
  auto separator = nullptr;

  rut::SubTreaps<uint32_t, std::string> splitted = treap.Split(separator);

  EXPECT_TRUE(splitted.first == nullptr);
  EXPECT_TRUE(splitted.second == nullptr);
}

TEST(Treap, SplitBySeparatorLessThanRoot) {
  // update after Insert implementation
}

TEST(Treap, SplitWithRootLessThanSeparator) {
  // update after Insert implementation
}



