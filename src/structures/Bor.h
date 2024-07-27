//
// Created by fedor on 7/26/24.
//

#ifndef BOR_H
#define BOR_H

#include "BorNode.h"
#include "PriorityQueue.h"
#include "../CONSTANTS.h"

class Bor {
public:
    explicit Bor(const unsigned long long cnt_of_symbols[]) {
        alphabet_sz = 0;
        for (unsigned short ind = 0; ind < UCHAR_RANGE; ind++) {
            if (cnt_of_symbols[ind]) {
                alphabet_sz++;
            }
        }
        auto Q = PriorityQueue(alphabet_sz);
        for (unsigned short ind = 0; ind < UCHAR_RANGE; ind++) {
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
    }

    void get_codes(std::string codes[]) {
        std::string now_code;
        get_codes(root, codes, now_code);
    }

    [[nodiscard]] unsigned short get_alphabet_sz() const {
        return alphabet_sz;
    }

    ~Bor() {
        delete_bor(root);
    }

private:
    unsigned short alphabet_sz;
    BorNode *root{nullptr};

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
};

#endif //BOR_H
