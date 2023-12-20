#pragma once

#include "node.hpp"

namespace rut {
  /**
   * @brief Treap template implementation.
   * 
   * @tparam C should implement Comparable Interface (unfortunately there are no such thing in C++).
   * @tparam T just data of any type for storing in Treap nodes.
   */
  template<typename C, typename T> class Treap;

  /**
   * @brief std::shared_ptr<rut::Treap<C, T>> type alias.
   * 
   * @tparam C should implement Comparable Interface (unfortunately there are no such thing in C++).
   * @tparam T just data of any type for storing in Treap nodes.
   */
  template<typename C, typename T> using TreapPtr = std::shared_ptr<rut::Treap<C, T>>;

  /**
   * @brief Sub-treaps of current treap root. 
   * 
   * @tparam C C should implement Comparable Interface (unfortunately there are no such thing in C++).
   * @tparam T T just data of any type for storing in Treap nodes.
   * 
   * @param first - left sub-treap of current treap.
   * @param second - right sub-treap of current treap.
   */
  template <typename C, typename T> using SubTreaps = std::pair<TreapPtr<C, T>, TreapPtr<C, T>>;

  template<typename C, typename T> 
  class Treap : public std::enable_shared_from_this<Treap<C, T>> {
    private:
      treap::NodePtr<C, T> root;
      SubTreaps<C, T> subTreaps;
    public:
      /**
       * @brief Construct a new empty Treap object with root node
       * 
       * @attention Root node key & priority are randomly generated.
       */
      Treap();

      treap::NodePtr<C, T> getRoot() { return this->root; };
      TreapPtr<C, T> leftSubTreap() { return this->subTreaps.first; };
      TreapPtr<C, T> rightSubTreap() { return this->subTreaps.second; };

      void setRoot(treap::NodePtr<C, T> root) { this->root = root; };
      void setLeftSubTreap(TreapPtr<C, T> treap) { this->subTreaps.first = treap; };
      void setRightSubTreap(TreapPtr<C, T> treap) { this->subTreaps.second = treap; };

      TreapPtr<C, T> ptr() { return this->shared_from_this(); };

      /**
       * @brief Separate treap in 2 sub-treaps.
       * 
       * @return Pair of sub-treaps which meets condition: 1st sub-treap nodes keys <= passed node key <= 2nd sub-treap nodes keys.
       * 
       */
      SubTreaps<C, T> Split(treap::NodePtr<C, T>);

      TreapPtr<C, T> Merge(TreapPtr<C, T> other);

      void Insert(const treap::NodePtr<C, T>);
  };

  template<typename C, typename T>
  Treap<C, T>::Treap() {
    this->setRoot(std::make_shared<treap::Node<C, T>>());
    this->setLeftSubTreap(nullptr);
    this->setRightSubTreap(nullptr);
  };

  template <typename C, typename T>
  SubTreaps<C, T> Treap<C, T>::Split(treap::NodePtr<C, T> separator) {
    if (!root || !separator) return std::make_pair(nullptr, nullptr);

    // IDK how disallow instance mutation in this method, sorry :<
    TreapPtr<C, T> thisCopy = std::make_shared<Treap<C, T>>();
    thisCopy->root = this->getRoot();
    thisCopy->setLeftSubTreap(this->leftSubTreap());
    thisCopy->setRightSubTreap(this->rightSubTreap());

    if (separator >= this->root) {
      if (this->subTreaps.second) {
        SubTreaps<C, T> result = thisCopy->rightSubTreap()->Split(separator);
        thisCopy->setRightSubTreap(result.first);

        return {thisCopy->ptr(), result.second};
      } else {
        return {thisCopy->ptr(), nullptr};
      }
    } else {
      if (this->subTreaps.first) {
        SubTreaps<C, T> result = thisCopy->leftSubTreap()->Split(separator);
        thisCopy->setLeftSubTreap(result.second);

        return {result.first, thisCopy->ptr()};
      } else {
        return {nullptr, thisCopy->ptr()};
      }
    }
  }

  template <typename C, typename T>
  TreapPtr<C, T> Treap<C, T>::Merge(TreapPtr<C, T> other) {
    if (!this) return other->ptr();
    if (!other) return this->ptr();

    if (std::greater<C>{}(this->root->getPriority(), other->root->getPriority())) {
      this->setRightSubTreap(this->rightSubTreap()->Merge(other));

      return this->ptr();
    } else {
      this->setLeftSubTreap(this->Merge(other->leftSubTreap()));

      return other->ptr();
    }
  };
}