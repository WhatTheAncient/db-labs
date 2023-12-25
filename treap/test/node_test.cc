#include <string>
#include "gtest/gtest.h"
#include "../src/treap/node.hpp"

TEST(Node, DefaultConstructorWithIntegralType) {
  auto defaultNode = treap::Node<uint32_t, std::string>();

  auto minVal = std::numeric_limits<uint32_t>::min();
  auto maxVal = std::numeric_limits<uint32_t>::max();

  bool keyInNumericLimits = minVal <= defaultNode.getKey() && defaultNode.getKey() <= maxVal;
  bool priorityInNumericLimits = minVal <= defaultNode.getPriority() && defaultNode.getPriority() <= maxVal;

  EXPECT_TRUE(keyInNumericLimits);
  EXPECT_TRUE(priorityInNumericLimits);
  EXPECT_TRUE(defaultNode.getData() == "");
}

TEST(Node, DefaultConstructorWithNotIntegralType) {
  auto defaultNode = treap::Node<float_t, std::string>();

  auto minVal = std::numeric_limits<float_t>::min();
  auto maxVal = std::numeric_limits<float_t>::max();

  bool keyInNumericLimits = minVal <= defaultNode.getKey() && defaultNode.getKey() <= maxVal;
  bool priorityInNumericLimits = minVal <= defaultNode.getPriority() && defaultNode.getPriority() <= maxVal;

  EXPECT_TRUE(keyInNumericLimits);
  EXPECT_TRUE(priorityInNumericLimits);
  EXPECT_TRUE(defaultNode.getData() == "");
}

TEST(Node, ParametrizedConstructor) {
  double_t key = 123.2;
  double_t priority = 10.312;
  std::string data = "Some data";

  auto parametrizedNode = treap::Node<double_t, std::string>(key, priority, data);

  EXPECT_DOUBLE_EQ(key, parametrizedNode.getKey());
  EXPECT_DOUBLE_EQ(priority, parametrizedNode.getPriority());
  EXPECT_TRUE(data == parametrizedNode.getData());
}

TEST(Node, SpaceshipOperator) {
  double_t lessKey = 123.2;
  double_t greaterKey = 123.3;
  double_t priority = 10.312;
  std::string data = "Some data";

  auto lessNode = treap::Node<double_t, std::string>(lessKey, priority, data);
  auto greaterNode = treap::Node<double_t, std::string>(greaterKey, priority, data);

  EXPECT_EQ(lessNode <=> lessNode, 0);
  EXPECT_EQ(lessNode <=> greaterNode, -1);
  EXPECT_EQ(greaterNode <=> lessNode, 1);
}

TEST(Node, EquityOperator) {
  double_t key = 123.2;
  double_t priority = 10.312;
  std::string data = "Some data";

  auto firstNode = treap::Node<double_t, std::string>(key, priority, data);
  auto secondNode = treap::Node<double_t, std::string>(key, (priority+12.1), (data + "Extra"));

  EXPECT_TRUE(firstNode == secondNode);
}

