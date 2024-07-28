//
// Created by fedor on 7/26/24.
//

#ifndef BORNODE_H
#define BORNODE_H

#include "../CONSTANTS.h"

class BorNode {
public:
    BorNode(const unsigned long long cnt_of_symbol, const LCHAR _symb) {
        weight = cnt_of_symbol;
        symb = _symb;
        is_terminal = true;
    }

    BorNode(BorNode *a, BorNode *b) {
        weight = a->weight + b->weight;
        symb = std::min(a->symb, b->symb);
        l = a, r = b;
    }

    BorNode() {
        is_terminal = false, weight = 0, symb = 0, l = nullptr, r = nullptr;
    }

    bool cmp(const BorNode *x) const {
        return weight < x->weight || (weight == x->weight && symb < x->symb);
    }

    [[nodiscard]] BorNode *get_left_son() const {
        return l;
    }

    [[nodiscard]] BorNode *get_right_son() const {
        return r;
    }

    [[nodiscard]] bool is_term() const {
        return is_terminal;
    }

    [[nodiscard]] LCHAR get_symb() const {
        return symb;
    }

    void set_left_son(BorNode *N) {
        l = N;
    }

    void set_right_son(BorNode *N) {
        r = N;
    }

    void set_symb(const LCHAR _symb) {
        symb = _symb, is_terminal = true;
    }

protected:
    bool is_terminal{false};
    unsigned long long weight{};
    LCHAR symb{};
    BorNode *l{nullptr}, *r{nullptr};
};

#endif //BORNODE_H
