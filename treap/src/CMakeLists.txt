add_library(treap treap.hpp treap/node.hpp treap/iterator.hpp)

target_include_directories (treap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
