//
// Created by fedor on 7/26/24.
//

#ifndef BORNODE_H
#define BORNODE_H

class BorNode {
public:
    BorNode(const unsigned long long cnt_of_symbol, const unsigned char _symb) {
        weight = cnt_of_symbol;
        symb = _symb;
        is_terminal = true;
    }

    BorNode(BorNode *a, BorNode *b) {
        weight = a->weight + b->weight;
        symb = '0';
        l = a, r = b;
    }

    BorNode() {
        is_terminal = false, weight = 0, symb, l = nullptr, r = nullptr;
    }

    bool cmp(const BorNode *x) const {
        return this->weight < x->weight;
    }

    [[nodiscard]] unsigned long long get_weight() const {
        if (this == nullptr) {
            return 0;
        }
        return weight;
    }

    BorNode* get_left_son() {
        return this->l;
    }

    BorNode* get_right_son() {
        return this->r;
    }

protected:
    bool is_terminal{false};
    unsigned long long weight{};
    unsigned char symb{};
    BorNode *l{nullptr}, *r{nullptr};
};

#endif //BORNODE_H
