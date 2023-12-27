#pragma once

#include <random>
#include <memory>

namespace treap {
    /**
   * @brief Treap Node template implementation.
   * 
   * @tparam C should implement Comparable Interface (unfortunately there are no such thing in C++)
   * @tparam T just data of any type for storing in Node
   */
  template <typename C, typename T> class Node;
  /**
   * @brief std::shared_ptr<treap::Node<C, T>> type alias.
   * 
   * @tparam C should implement Comparable Interface (unfortunately there are no such thing in C++)
   * @tparam T just data of any type for storing in Node
   */
  template <typename C, typename T> using NodePtr = std::shared_ptr<Node<C,T>>;

  template <typename C, typename T>
  class Node : public std::enable_shared_from_this<Node<C, T>> {
    private:
      C key;
      C priority;
      T data;
    public:
      /**
       * @brief Construct a new Node object with default attributes:
       * 
       * @attention This constructor randomly generates node key & priority. Data has default T{} value.
       */
      Node();
      /**
       * @brief Construct a new treap Node object from passed params
       * 
       * @param key Node key
       * @param priority node priority
       * @param data stored in Node data
       */
      Node(C key, C priority, T data);
      /**
       * @brief Disabled copy constructor
       */
      Node(const Node& other) = delete;
      /**
       * @brief Default move constructor
       */
      Node(Node&& other) = default;
      /**
       * @brief Disabled assignment operator
       */
      Node& operator=(const Node& other) noexcept = delete;
      /**
       * @brief Default move assignment operator
      */
      Node& operator=(Node&& other) noexcept = default;
      /**
       * @brief Default Node destructor
       */
      ~Node() = default;

      C getKey() const noexcept { return this->key; };
      C getPriority() const noexcept { return this->priority; };
      T getData() const noexcept { return this->data; };

      NodePtr<C, T> ptr() { return this->shared_from_this(); };
      
      bool hasLessPriorityThan(const Node<C, T> &other) const;
      bool hasGreaterPriorityThan(const Node<C, T> &other) const;

      /**
       * @brief Spaceship operator overload (with by-key comparation)
       * 
       * @param lha The node for compare
       * @param rha The node for compare
       *
       * @return 1 in case of lha < rha, -1 in case of lha > rha, 0 in case of lha == rha
      */
      friend auto operator<=>(const Node& lha, const Node& rha) {
        if (std::less<C>{}(lha.key, rha.key)) return -1;
        if (std::greater<C>{}(lha.key, rha.key)) return 1;

        return 0;
      }

      /**
       * @brief Equity operator overload
       * 
       * @param lha The node for equity check
       * @param rha The node for equity check
       * @return boolean value 
       */
      friend bool operator==(const Node& lha, const Node& rha) {
        return (lha <=> rha) == 0;
      }
  };

  template <typename C, typename T>
  Node<C, T>::Node() {
    std::random_device randomizer;
    std::mt19937 gen{randomizer()};

    using eligible_dist = std::conditional_t<
      std::is_integral_v<C>,
      std::uniform_int_distribution<C>,
      std::uniform_real_distribution<C>
    >;

    eligible_dist dis{std::numeric_limits<C>::min(), std::numeric_limits<C>::max()};

    this->key = dis(gen);
    this->priority = dis(gen);
  }

  template <typename C, typename T>
  Node<C, T>::Node(C key, C priority, T data) : key{key}, priority{priority}, data{data} {};

  template <typename C, typename T>
  bool Node<C, T>::hasLessPriorityThan(const Node<C, T> &other) const {
    return std::less<C>{}(this->getPriority(), other.getPriority());
  };

  template <typename C, typename T>
  bool Node<C, T>::hasGreaterPriorityThan(const Node<C, T> &other) const {
    return std::greater<C>{}(this->getPriority(), other.getPriority());
  };
}
