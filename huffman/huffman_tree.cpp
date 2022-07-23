#include "huffman_tree.hpp"

Node::Node(char data, int left, int right)
    : data(data), left(left), right(right), parent(-1) {
}

// nodeを木に追加し、インデックスを返す
int HuffmanTree::push_node(Node node) {
    int index = this->nodes.size();
    this->nodes.push_back(node);

    return index;
}

HuffmanTree make_huffman_tree(const Histgram &histgram) {
    // (priority, index)
    std::priority_queue<
        std::pair<int, int>, std::vector<std::pair<int, int>>,
        std::function<bool(std::pair<int, int>, std::pair<int, int>)>>
        q([](const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) {
            return lhs.first > rhs.first;
        });

    HuffmanTree tree;

    // 各文字をキューに挿入
    // 優先度は文字の登場回数
    // 優先度が小さい順にポップされる
    for (int i = 0; i < data_size; i++) {
        char data = (char)i;
        Node node(data, -1, -1);
        int index = tree.push_node(node);
        int priority = histgram.data[i];

        q.push(std::make_pair(priority, index));
    }

    std::pair<int, int> p_left;   // 1番目に優先度が低いノード
    std::pair<int, int> p_right;  // 2番目に優先度が低いノード
    while (true) {
        // 1, 2番目に頻度の低いノードを求める
        p_left = q.top();
        q.pop();
        if (q.empty()) {
            break;
        }

        p_right = q.top();
        q.pop();

        // 新しいノードを作成
        Node node(-1, p_left.second, p_right.second);
        int index = tree.push_node(node);

        // 新しいノードをparentに設定
        tree.nodes[p_left.second].parent = index;
        tree.nodes[p_right.second].parent = -index;

        // 新しいノードの優先度は、1, 2番目に優先度が低いノードの優先度の和
        int priority = p_left.first + p_right.first;
        q.push(std::make_pair(priority, index));
    }

    tree.root = p_left.second;

    return tree;
}

void HuffmanTree::show() {
    for (auto &node : this->nodes) {
        std::cout << node.data << ": " << node.left << ", " << node.right
                  << std::endl;
    }
}

std::vector<bool> HuffmanTree::encode(char character) {
    // true: 1, false: 0
    std::vector<bool> data;

    int index = (int)character;
    while (index != this->root) {
        Node node = this->nodes[index];
        if (node.parent >= 0) {
            // parentが正の場合
            // nodeはparentの左側の子
            // 符号は1
            data.push_back(true);
            index = node.parent;
        } else {
            // parentが負の場合
            // nodeはparentの右側の子
            // 符号は0
            data.push_back(false);
            index = -node.parent;
        }
    }

    std::reverse(data.begin(), data.end());
    return data;
}

char HuffmanTree::decode(const std::vector<bool> &code) {
    Node node = this->nodes[this->root];
    for (bool d : code) {
        if (d) {
            // 符号が1の場合
            // 左側の子を参照する
            node = this->nodes[node.left];
        } else {
            // 符号が0の場合
            // 右側の子を参照する
            node = this->nodes[node.right];
        }
    }
    // 最終的にたどり着いたノードが結果となる
    return node.data;
}