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
        unsigned alphabet_sz = 0;
        unsigned char ind = 0;
        do {
            if (cnt_of_symbols[ind]) {
                alphabet_sz++;
            }
        } while (ind++ < UCHAR_RANGE - 1);
        ind = 0;
        auto Q = PriorityQueue(alphabet_sz);
        do {
            if (cnt_of_symbols[ind]) {
                Q.insert(new BorNode(cnt_of_symbols[ind], ind));
            }
        } while (ind++ < UCHAR_RANGE - 1);
        while (Q.size() > 1) {
            BorNode *A = Q.get_min();
            Q.erase();
            BorNode *B = Q.get_min();
            Q.erase();
            Q.insert(new BorNode(A, B));
        }
        root = Q.get_min();
    }

    void delete_bor(BorNode *N) {
        if (N->get_left_son()) {
            delete_bor(N->get_left_son());
        }
        if (N->get_right_son()) {
            delete_bor(N->get_right_son());
        }
        delete N;
    }

    ~Bor() {
        delete_bor(root);
    }

private:
    BorNode *root{nullptr};
};

#endif //BOR_H
