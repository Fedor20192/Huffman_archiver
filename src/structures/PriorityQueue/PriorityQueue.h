//
// Created by fedor on 7/28/24.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "../Bor/BorNode.h"


class PriorityQueue {
public:
    explicit PriorityQueue(unsigned queue_sz);

    ~PriorityQueue();

    [[nodiscard]] BorNode *get_min() const;

    void push_down(unsigned node_ind) const;

    void push_up(unsigned node_ind) const;

    void erase();

    void insert(BorNode *N);

    [[nodiscard]] unsigned size() const;

private:
    unsigned sz;
    BorNode **tree;
};


#endif //PRIORITYQUEUE_H
