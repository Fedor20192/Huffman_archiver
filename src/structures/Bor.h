//
// Created by fedor on 7/26/24.
//

#ifndef BOR_H
#define BOR_H

#include <string>

#include "BorNode.h"
#include "PriorityQueue.h"
#include "../CONSTANTS.h"

class Bor {
public:
    explicit Bor(const unsigned long long cnt_of_symbols[]) {
        alphabet_sz = 0;
        for (LCHAR ind = 0; ind < LCHAR_RANGE; ind++) {
            if (cnt_of_symbols[ind]) {
                alphabet_sz++;
            }
        }
        auto Q = PriorityQueue(alphabet_sz);
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

    explicit Bor(const std::string codes[]) {
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

    void get_codes(std::string codes[]) {
        std::string now_code;
        get_codes(root, codes, now_code);
    }

    [[nodiscard]] LCHAR get_alphabet_sz() const {
        return alphabet_sz;
    }

    [[nodiscard]] bool is_terminal() const {
        return last->is_term();
    }

    [[nodiscard]] LCHAR get_symb() const {
        return last->get_symb();
    }

    void add(const LCHAR bit) {
        add_bit(bit);
    }

    void reset() {
        last = root;
    }

    ~Bor() {
        delete_bor(root);
    }

private:
    LCHAR alphabet_sz;
    BorNode *root{nullptr}, *last{nullptr};

    static void delete_bor(const BorNode *N) {
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

    void get_codes(const BorNode *N, std::string codes[], std::string &now_code) {
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

    void add_bit(const int bit) {
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

    void add_code(const std::string &code, const LCHAR symb) {
        for (const char c : code) {
            add_bit(c - '0');
        }
        last->set_symb(symb);
        last = root;
    }
};

#endif //BOR_H
