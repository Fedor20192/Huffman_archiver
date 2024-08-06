//
// Created by fedor on 7/28/24.
//

#include "Bor.h"
#include "../PriorityQueue.h"


Bor::Bor(const unsigned long long cnt_of_symbols[]) {
    alphabet_sz = 0;
    for (LCHAR ind = 0; ind < LCHAR_RANGE; ind++) {
        if (cnt_of_symbols[ind]) {
            alphabet_sz++;
        }
    }
    auto Q = PriorityQueue<BorNode>();
    for (LCHAR ind = 0; ind < LCHAR_RANGE; ind++) {
        if (cnt_of_symbols[ind]) {
            Q.insert(new BorNode(cnt_of_symbols[ind], ind));
        }
    }
    while (Q.size() > 1) {
        BorNode *A = Q.get_min();
        Q.erase();
        BorNode *B = Q.get_min();
        Q.erase();
        Q.insert(new BorNode(A, B));
    }
    root = Q.get_min();
    last = root;
}

Bor::Bor(const std::string codes[]) {
    root = new BorNode();
    last = root;
    alphabet_sz = 0;
    for (LCHAR ind = 0; ind < LCHAR_RANGE; ind++) {
        if (!codes[ind].empty()) {
            alphabet_sz++;
            add_code(codes[ind], ind);
        }
    }
}

void Bor::get_codes(std::string codes[]) {
    std::string now_code;
    get_codes(root, codes, now_code);
}

[[nodiscard]] LCHAR Bor::get_alphabet_sz() const {
    return alphabet_sz;
}

[[nodiscard]] bool Bor::is_terminal() const {
    return last->is_term();
}

[[nodiscard]] LCHAR Bor::get_symb() const {
    return last->get_symb();
}

void Bor::add(const LCHAR bit) {
    add_bit(bit);
}

void Bor::reset() {
    last = root;
}

Bor::~Bor() {
    delete_bor(root);
}

void Bor::delete_bor(const BorNode *N) {
    if (!N) {
        return;
    }
    if (N->get_left_son()) {
        delete_bor(N->get_left_son());
    }
    if (N->get_right_son()) {
        delete_bor(N->get_right_son());
    }
    delete N;
}

void Bor::get_codes(const BorNode *N, std::string codes[], std::string &now_code) {
    if (!N) {
        return;
    }
    if (alphabet_sz == 1) {
        codes[N->get_symb()] = "0";
        return;
    }
    if (N->get_left_son()) {
        now_code += '0';
        get_codes(N->get_left_son(), codes, now_code);
        now_code.pop_back();
    }
    if (N->get_right_son()) {
        now_code += '1';
        get_codes(N->get_right_son(), codes, now_code);
        now_code.pop_back();
    }
    if (N->is_term()) {
        codes[N->get_symb()] = now_code;
    }
}

void Bor::add_bit(const int bit) {
    if (!last) {
        return;
    }
    if (bit) {
        if (!last->get_right_son()) {
            last->set_right_son(new BorNode());
        }
        last = last->get_right_son();
    } else {
        if (!last->get_left_son()) {
            last->set_left_son(new BorNode());
        }
        last = last->get_left_son();
    }
}

void Bor::add_code(const std::string &code, const LCHAR symb) {
    for (const char c: code) {
        add_bit(c - '0');
    }
    last->set_symb(symb);
    last = root;
}
