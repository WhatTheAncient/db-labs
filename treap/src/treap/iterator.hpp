#pragma once

#include <cstddef>
#include <stack>
#include <optional>
#include <memory>

namespace rut { template<typename C, typename T> class Treap; };

namespace treap {

  /**
   * @brief Treap template bidirectional iterator implementation.
   * 
   * @tparam C should implement Comparable Interface (unfortunately there are no such thing in C++).
   * @tparam T just data of any type for storing in Treap nodes.
   */
  template <typename C, typename T> class Iterator {
    public:
      using iterator_category = std::bidirectional_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = treap::Node<C, T>;
      using pointer = std::shared_ptr<rut::Treap<C, T>>;
      using reference = rut::Treap<C, T>&;

      Iterator(reference r) {
        auto left = std::make_shared<rut::Treap<C, T>>(r);
        // If we got blank root in beginning then whole treap is empty.
        if (r.getRoot() == nullptr) left = nullptr;

        while(left != nullptr) {
          iter.push(left);
          left = left->leftSubTreap();
        }

        if (iter.size() == 0) {
          current = nullptr;
        } else {
          current = iter.top();
          iter.pop();
        }
      }

      Iterator(const pointer& p) {
        auto left = p;

        while(left != nullptr) {
          iter.push(left);
          left = left->leftSubTreap();
        }

        if (iter.size() == 0) {
          current = nullptr;
        } else {
          current = iter.top();
          iter.pop();
        }
      }

      NodePtr<C, T> operator->() const { return (current != nullptr) ? current->getRoot() : nullptr ; };
      Node<C, T>& operator*() const { if (current != nullptr) return *current->getRoot(); };

      Iterator<C, T>& operator++() {
        if (current == nullptr) return *this;

        if (current->rightSubTreap() != nullptr) {
          iter.push(current->rightSubTreap());

          if (current->rightSubTreap()->leftSubTreap() != nullptr) {
            iter.push(current->rightSubTreap()->leftSubTreap());
          }
        }

        if (iter.size() == 0) {
          current = nullptr;
          return *this;
        }
        
        current = iter.top();
        iter.pop();

        return *this;
      }

      Iterator<C, T> operator++(int)  {
        auto unchanged = *this;
        ++(*this);

        return unchanged;
      }

      bool operator==(Iterator<C, T> const &other) const {  return current == other.current; }
      bool operator!=(Iterator<C, T> const &other) const {  return current != other.current; }
    private:
      pointer current;
      std::stack<pointer> iter;
  };
}
