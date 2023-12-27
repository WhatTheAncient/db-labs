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

      /**
       * @brief Same as public Split method, but more eligible fore some cases.
       * 
       * @param treap 
       * @param separator 
       * @return SubTreaps<C, T> 
       */
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

      /**
       * @brief Same as public Merge method, but more eligible for some cases.
       * 
       * @param l 
       * @param r 
       * @return TreapPtr<C, T> 
       */
      friend TreapPtr<C, T> merge(TreapPtr<C, T> l, TreapPtr<C, T> r) {
        if (l == nullptr || l->getRoot() == nullptr) return r;
        if (r == nullptr || r->getRoot() == nullptr) return l;

        if (l->getRoot()->hasGreaterPriorityThan(*r->getRoot())) {
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

      /**
       * @brief Construct a new Treap object as copy of the given Treap.
       * 
       * @param other 
       */
      Treap(const Treap& other);

      treap::NodePtr<C, T> getRoot() const noexcept { return root; };
      TreapPtr<C, T> leftSubTreap() const noexcept { return subTreaps.first; };
      TreapPtr<C, T> rightSubTreap() const noexcept { return subTreaps.second; };

      /**
       * @brief Returns shared pointer of this object.
       * @attention bad_weak_pointer error will be raised if there are no existing shared pointers.
       * 
       * @return TreapPtr<C, T> 
       */
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

      /**
       * @brief Find node in treap by given key.
       * 
       * @param key 
       * @return treap::NodePtr<C, T> - found node (or nullptr)
       */
      treap::NodePtr<C, T> Find(const C key) const;

      /**
       * @brief Remove node from treap by given key.
       * 
       * @param key 
       * @return true if Node was removed,
       * @return false otherwise.
       */
      bool Remove(const C key);

      /**
       * @brief Returns vector of nodes in ordered traversal (by keys).
       * 
       * @return std::vector<treap::NodePtr<C, T>> - Vector of tree nodes.
       */
      std::vector<treap::NodePtr<C, T>> inOrderedVector() const noexcept;

      /**
       * @brief Returns iterator for first node in InOrdered tree
       * 
       * @return treap::Iterator<C, T> 
       */
      treap::Iterator<C, T> begin() const;
      
      /**
       * @brief Returns iterator for last node in InOrdered tree
       * 
       * @return treap::Iterator<C, T> 
       */
      treap::Iterator<C, T> end() const;

      friend bool operator==(const rut::Treap<C, T>& lha, const rut::Treap<C, T>& rha) {      
        auto lhaVector = lha.inOrderedVector();
        auto rhaVector = rha.inOrderedVector();
        
        if (lhaVector.size() != rhaVector.size()) return false;

        bool result = true;

        for (size_t i = 0; i < lhaVector.size(); i++) {
          result &= (lhaVector[i] == rhaVector[i]);
        }

        return result;
      };

      friend bool operator!=(rut::Treap<C, T>& lha, rut::Treap<C, T>& rha) { return !(lha == rha); };
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
    // IDK how to disallow instance mutation in other way, sorry :<
    TreapPtr<C, T> thisCopy = std::make_shared<Treap<C, T>>(*this);

    return split(thisCopy, separator);
  }

  template <typename C, typename T>
  TreapPtr<C, T> Treap<C, T>::Merge(TreapPtr<C, T> other) {
    return merge(ptr(), other);
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

    setRoot(result->getRoot());
    setLeftSubTreap(result->leftSubTreap());
    setRightSubTreap(result->rightSubTreap());
  }

  template <typename C, typename T>
  treap::NodePtr<C, T> Treap<C, T>::Find(const C key) const {
    if (getRoot() == nullptr) return nullptr;
    if (getRoot()->getKey() == key) return getRoot();

    if (std::greater{}(getRoot()->getKey(), key)) {
      if (!leftSubTreap()) return nullptr;

      return leftSubTreap()->Find(key);
    } else {
      if (!rightSubTreap()) return nullptr;

      return rightSubTreap()->Find(key);
    }
  }

  template <typename C, typename T>
  bool Treap<C, T>::Remove(const C key) {
    if (Find(key) == nullptr) return false;

    if (getRoot() == nullptr) {
      return false;
    } 

    if (getRoot()->getKey() == key) {
      auto replace = merge(leftSubTreap(), rightSubTreap());

      if (replace == nullptr) {
        return false;
      } else {
        setRoot(replace->getRoot());
        setLeftSubTreap(replace->leftSubTreap());
        setRightSubTreap(replace->rightSubTreap());

        return true;
      }
    }

    if (std::greater{}(getRoot()->getKey(), key)) {
      if (!leftSubTreap()) return false;
      if (!leftSubTreap()->Remove(key)) setLeftSubTreap(nullptr);;

      return true;
    } else {
      if (!rightSubTreap()) return false;
      if (!rightSubTreap()->Remove(key)) setRightSubTreap(nullptr);

      return true;
    }
  }

  template <typename C, typename T>
  std::vector<treap::NodePtr<C, T>> rut::Treap<C, T>::inOrderedVector() const noexcept {
    std::vector<treap::NodePtr<C, T>> result = std::vector<treap::NodePtr<C, T>>();

    if (begin() == end()) return result;

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