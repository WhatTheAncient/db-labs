#include <stdint.h>
#include <string>
#include <iostream>

#include "src/treap.hpp"

int main() {
  auto node1 = std::make_shared<treap::Node<uint32_t, std::string>>(1, 1, std::string{"Hello"});
  auto node2 = std::make_shared<treap::Node<uint32_t, std::string>>(2, 3, std::string{"world"});
  auto node3 = std::make_shared<treap::Node<uint32_t, std::string>>(3, 2, std::string{"!"});

  auto empty1 = rut::Treap<uint32_t, std::string>();
  auto empty2 = rut::Treap<uint32_t, std::string>(empty1);

  std::cout << (empty1 == empty2) << std::endl;

  auto treapPtr = std::make_shared<rut::Treap<uint32_t, std::string>>();
  treapPtr->Insert(3, 2, std::string{"world"});
  treapPtr->Insert(2, 1, std::string{"Hello"});
  treapPtr->Insert(3, 2, std::string{"!"});
  
  for (auto& current : treapPtr->inOrderedVector()) {
    std::cout << current->getData() << " ";
  }
  std::cout << std::endl;
}
