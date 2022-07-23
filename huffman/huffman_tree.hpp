#ifndef HUFFMAN_HUFFMAN_TREE_H__
#define HUFFMAN_HUFFMAN_TREE_H__

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

#include "histgram.hpp"

class Node {
   public:
    char data;
    int left;
    int right;
    int parent;
    Node(char data, int left, int right);
};

class HuffmanTree {
   public:
    std::vector<Node> nodes;
    int root;
    int push_node(Node node);

    void show();
    std::vector<bool> encode(char character);
};

HuffmanTree make_huffman_tree(const Histgram &histgram);
#endif