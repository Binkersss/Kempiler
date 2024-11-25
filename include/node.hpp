//
// Created by binker on 11/25/24.
//

#ifndef NODE_HPP
#define NODE_HPP
enum class NodeType {
  Exit
};

struct ExitNode {
  std::string arg;
};

struct Node {
  NodeType type;
  ExitNode exit;
};

#endif //NODE_HPP
