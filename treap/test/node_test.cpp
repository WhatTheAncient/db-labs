#include <string>
#include <gtest/gtest.h>

#include "../src/treap/node.hpp"
#include "sample.hpp"

using DataType = Sample;

TEST(Node, DefaultConstructorWithIntegralType) {
  auto defaultNode = treap::Node<uint32_t, DataType>();

  auto minVal = std::numeric_limits<uint32_t>::min();
  auto maxVal = std::numeric_limits<uint32_t>::max();

  bool keyInNumericLimits = minVal <= defaultNode.getKey() && defaultNode.getKey() <= maxVal;
  bool priorityInNumericLimits = minVal <= defaultNode.getPriority() && defaultNode.getPriority() <= maxVal;

  EXPECT_TRUE(keyInNumericLimits);
  EXPECT_TRUE(priorityInNumericLimits);
  EXPECT_TRUE(defaultNode.getData() == Sample());
}

TEST(Node, DefaultConstructorWithNotIntegralType) {
  auto defaultNode = treap::Node<float, DataType>();

  auto minVal = std::numeric_limits<float>::min();
  auto maxVal = std::numeric_limits<float>::max();

  bool keyInNumericLimits = minVal <= defaultNode.getKey() && defaultNode.getKey() <= maxVal;
  bool priorityInNumericLimits = minVal <= defaultNode.getPriority() && defaultNode.getPriority() <= maxVal;

  EXPECT_TRUE(keyInNumericLimits);
  EXPECT_TRUE(priorityInNumericLimits);
  EXPECT_TRUE(defaultNode.getData() == Sample());
}

TEST(Node, ParametrizedConstructor) {
  float key = 123.2;
  float priority = 10.312;
  Sample data("Some data");

  auto parametrizedNode = treap::Node<float, DataType>(key, priority, data);

  EXPECT_DOUBLE_EQ(key, parametrizedNode.getKey());
  EXPECT_DOUBLE_EQ(priority, parametrizedNode.getPriority());
  EXPECT_TRUE(data == parametrizedNode.getData());
}

TEST(Node, SpaceshipOperator) {
  float lessKey = 123.2;
  float greaterKey = 123.3;
  float priority = 10.312;
  Sample data("Some data");

  auto lessNode = treap::Node<float, DataType>(lessKey, priority, data);
  auto greaterNode = treap::Node<float, DataType>(greaterKey, priority, data);

  EXPECT_EQ(lessNode <=> lessNode, 0);
  EXPECT_EQ(lessNode <=> greaterNode, -1);
  EXPECT_EQ(greaterNode <=> lessNode, 1);
}

TEST(Node, EquityOperator) {
  float key = 123.2;
  float priority = 10.312;
  Sample data("Some data");

  auto firstNode = treap::Node<float, DataType>(key, priority, data);
  auto secondNode = treap::Node<float, DataType>(key, (priority+12.1), Sample("Another data"));

  EXPECT_TRUE(firstNode == secondNode);
}

TEST(Node, hasLessPriorityThan) {
  auto key = 123;
  Sample data("Some data");
  auto greaterPriorityNode = treap::Node<int16_t, DataType>(key, 3, data);
  auto lessPriorityNode = treap::Node<int16_t, DataType>(key, 2, data);

  EXPECT_TRUE(lessPriorityNode.hasLessPriorityThan(greaterPriorityNode));
  EXPECT_FALSE(lessPriorityNode.hasLessPriorityThan(lessPriorityNode));
}

TEST(Node, hasGreaterPriorityThan) {
  auto key = 123;
  Sample data("Some data");
  auto greaterPriorityNode = treap::Node<int16_t, DataType>(key, 3, data);
  auto lessPriorityNode = treap::Node<int16_t, DataType>(key, 2, data);

  EXPECT_TRUE(greaterPriorityNode.hasGreaterPriorityThan(lessPriorityNode));
  EXPECT_FALSE(greaterPriorityNode.hasGreaterPriorityThan(greaterPriorityNode));
}
