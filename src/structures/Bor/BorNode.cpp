//
// Created by fedor on 7/28/24.
//

#include "BorNode.h"

BorNode::BorNode(const unsigned long long cnt_of_symbol, const LCHAR _symb) {
    weight = cnt_of_symbol;
    symb = _symb;
    is_terminal = true;
}

BorNode::BorNode(BorNode *a, BorNode *b) {
    weight = a->weight + b->weight;
    symb = a->symb;
    if (b->symb < symb) {
        symb = b->symb;
    }
    l = a, r = b;
}

BorNode::BorNode() {
    is_terminal = false, weight = 0, symb = 0, l = nullptr, r = nullptr;
}

bool BorNode::operator<(const BorNode &x) const {
    return weight<x.weight || (weight == x.weight && symb<x.symb);
}


[[nodiscard]] BorNode *BorNode::get_left_son() const {
    return l;
}

[[nodiscard]] BorNode *BorNode::get_right_son() const {
    return r;
}

[[nodiscard]] bool BorNode::is_term() const {
    return is_terminal;
}

[[nodiscard]] LCHAR BorNode::get_symb() const {
    return symb;
}

void BorNode::set_left_son(BorNode *N) {
    l = N;
}

void BorNode::set_right_son(BorNode *N) {
    r = N;
}

void BorNode::set_symb(const LCHAR _symb) {
    symb = _symb, is_terminal = true;
}
