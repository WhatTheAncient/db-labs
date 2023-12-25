#pragma once

#include <vector>

#include "treap/node.hpp"
#include "treap/iterator.hpp"

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

      void setRoot(treap::NodePtr<C, T> root) { this->root = root; };
      void setLeftSubTreap(TreapPtr<C, T> treap) { this->subTreaps.first = treap; };
      void setRightSubTreap(TreapPtr<C, T> treap) { this->subTreaps.second = treap; };

      friend SubTreaps<C, T> split(TreapPtr<C, T> treap, C separator) {
        if (treap == nullptr || treap->getRoot() == nullptr) return {nullptr, nullptr};

        if (treap->getRoot()->getKey() <= separator) {
          auto result = split(treap->rightSubTreap(), separator);
          treap->setRightSubTreap(result.first);

          return {treap, result.second};
        }
        else {
          auto result = split(treap->leftSubTreap(), separator);
          treap->setLeftSubTreap(result.second);

          return {result.first, treap};
        }
      };

      friend TreapPtr<C, T> merge(TreapPtr<C, T> l, TreapPtr<C, T> r) {
        if (l == nullptr || l->getRoot() == nullptr) return r;
        if (r == nullptr || r->getRoot() == nullptr) return l;

        if (std::greater<C>{}(l->getRoot()->getPriority(), r->getRoot()->getPriority())) {
          auto newRight = merge(l->rightSubTreap(), r);
          l->setRightSubTreap(newRight);

          return l;
        }
        else {
          auto newLeft = merge(l, r->leftSubTreap());
          r->setLeftSubTreap(newLeft);

          return r;
        }
      };

    public:
      /**
       * @brief Construct a new empty Treap object with root node
       * 
       * @attention Root node key & priority are randomly generated.
       */
      Treap();

      Treap(const Treap& other);

      treap::NodePtr<C, T> getRoot() const noexcept { return root; };
      TreapPtr<C, T> leftSubTreap() const noexcept { return subTreaps.first; };
      TreapPtr<C, T> rightSubTreap() const noexcept { return subTreaps.second; };

      TreapPtr<C, T> ptr() { return this->shared_from_this(); };

      /**
       * @brief Separate treap in 2 sub-treaps.
       * 
       * @return Pair of sub-treaps which meets condition: 1st sub-treap nodes keys <= passed node key <= 2nd sub-treap nodes keys.
       */
      SubTreaps<C, T> Split(C key) const;

      /**
       * @brief Merge sub treap to current instance.
       * 
       * @param other Subtreap to merge.
       * @return Result of treap merging.
       */
      TreapPtr<C, T> Merge(TreapPtr<C, T> other);

      /**
       * @brief Creates new node in treap.
       * 
       * @param key Key of stored node.
       * @param priority Priority of stored node.
       * @param data Data of stored node.
       */
      void Insert(const C key, const C priority, const T data);

      treap::NodePtr<C, T> Find(const C key) const;

      void Remove(const C key);

      std::vector<treap::NodePtr<C, T>> inOrderedVector() const noexcept;

      treap::Iterator<C, T> begin() const;
      treap::Iterator<C, T> end() const;
  };

  template<typename C, typename T>
  Treap<C, T>::Treap() {
    setRoot(nullptr);
    setLeftSubTreap(nullptr);
    setRightSubTreap(nullptr);
  };

  template<typename C, typename T>
  Treap<C, T>::Treap(const Treap<C, T>& other) {
    setRoot(other.getRoot());
    setLeftSubTreap(other.leftSubTreap());
    setRightSubTreap(other.rightSubTreap());
  }

  template <typename C, typename T>
  SubTreaps<C, T> Treap<C, T>::Split(C separator) const {
    if (!root) return std::make_pair(nullptr, nullptr);

    // IDK how to disallow instance mutation in other way, sorry :<
    TreapPtr<C, T> thisCopy = std::make_shared<Treap<C, T>>(*this);

    if (separator >= root->getKey()) {
      if (rightSubTreap()) {
        SubTreaps<C, T> result = thisCopy->rightSubTreap()->Split(separator);
        thisCopy->setRightSubTreap(result.first);

        return {thisCopy->ptr(), result.second};
      } else {
        return {thisCopy->ptr(), nullptr};
      }
    } else {
      if (leftSubTreap()) {
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
    if (!other) return ptr();
    if (!root) return other->ptr();

    if (std::greater<C>{}(root->getPriority(), other->root->getPriority())) {
      setRightSubTreap(rightSubTreap()->Merge(other));

      return ptr();
    } else {
      setLeftSubTreap(Merge(other->leftSubTreap()));

      return other->ptr();
    }
  };

  template <typename C, typename T>
  void Treap<C, T>::Insert(const C key, const C priority, const T data) {
    auto node = std::make_shared<treap::Node<C, T>>(key, priority, data);

    if (root == nullptr) return setRoot(node);

    auto result = std::make_shared<Treap<C, T>>();
    auto thisCopy = std::make_shared<Treap<C, T>>(*this);

    auto [left, right] = split(thisCopy, key);
    result->setRoot(node);

    auto newRight = merge(result, right);    
    result = merge(left, newRight);

    this->setRoot(result->getRoot());
    this->setLeftSubTreap(result->leftSubTreap());
    this->setRightSubTreap(result->rightSubTreap());
  }

  template <typename C, typename T>
  treap::NodePtr<C, T> Treap<C, T>::Find(const C key) const {
    if (this->getRoot() == nullptr || this->getRoot()->getKey() == key) return this->getRoot();

    if (std::greater{}(this->getRoot()->getKey(), key)) 
      return this->leftSubTreap()->Find(key);
    else 
      return this->rightSubTreap()->Find(key);
  }

  template <typename C, typename T>
  void Treap<C, T>::Remove(const C key) {
    if (this->getRoot() == nullptr) {
      std::cout << "Blank" << std::endl;
      return;
    } 

    if (this->getRoot()->getKey() == key) {
      auto replace = merge(this->leftSubTreap(), this->rightSubTreap());
      std::cout << "deletable" << replace << std::endl;

      if (replace == nullptr) {
        this->setRoot(nullptr);
        this->setLeftSubTreap(nullptr);
        this->setRightSubTreap(nullptr);
      } else {
        this->setRoot(replace->getRoot());
        this->setLeftSubTreap(replace->leftSubTreap());
        this->setRightSubTreap(replace->rightSubTreap());
      }

      return;
    }

    if (std::greater{}(this->getRoot()->getKey(), key)) 
      return this->leftSubTreap()->Remove(key);
    else 

      std::cout << "R" << std::endl; return this->rightSubTreap()->Remove(key);
  }

  template <typename C, typename T>
  std::vector<treap::NodePtr<C, T>> rut::Treap<C, T>::inOrderedVector() const noexcept {
    std::vector<treap::NodePtr<C, T>> result = std::vector<treap::NodePtr<C, T>>();

    for (treap::Node<C, T>& currentNode : *this) {
      result.push_back(currentNode.ptr());
    }

    return result;
  }

  template <typename C, typename T>
  treap::Iterator<C, T> rut::Treap<C, T>::begin() const {
    auto thisRef = *this; // for some reason treap::Iterator<C, T>(*this) raises error

    return treap::Iterator<C, T>(thisRef);
  }

  template <typename C, typename T>
  treap::Iterator<C, T> rut::Treap<C, T>::end() const {
    return treap::Iterator<C, T>(nullptr);
  }
}