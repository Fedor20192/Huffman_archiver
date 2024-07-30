//
// Created by fedor on 7/28/24.
//

#ifndef BORNODE_H
#define BORNODE_H


#include "../../CONSTANTS.h"

class BorNode {
public:
    BorNode(unsigned long long cnt_of_symbol, LCHAR _symb);

    BorNode(BorNode *a, BorNode *b);

    BorNode();

    bool operator<(const BorNode &x) const;

    [[nodiscard]] BorNode *get_left_son() const;

    [[nodiscard]] BorNode *get_right_son() const;

    [[nodiscard]] bool is_term() const;

    [[nodiscard]] LCHAR get_symb() const;

    void set_left_son(BorNode *N);

    void set_right_son(BorNode *N);

    void set_symb(LCHAR _symb);

protected:
    bool is_terminal{false};
    unsigned long long weight{};
    LCHAR symb{};
    BorNode *l{nullptr}, *r{nullptr};
};

#endif //BORNODE_H
