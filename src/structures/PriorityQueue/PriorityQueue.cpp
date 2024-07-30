//
// Created by fedor on 7/28/24.
//

#include "PriorityQueue.h"


PriorityQueue::PriorityQueue(const unsigned queue_sz) {
    sz = 0;
    tree = new BorNode *[queue_sz];
    for (unsigned i = 0; i < queue_sz; i++) {
        tree[i] = nullptr;
    }
}

PriorityQueue::~PriorityQueue() {
    delete[] tree;
}

[[nodiscard]] BorNode *PriorityQueue::get_min() const {
    if (!sz) {
        return nullptr;
    }
    return tree[0];
}

void PriorityQueue::push_down(unsigned node_ind) const {
    while (2 * node_ind + 1 < sz) {
        const unsigned left_son = 2 * node_ind + 1, right_son = 2 * node_ind + 2;
        unsigned min_son = left_son;
        if (right_son < sz && *tree[right_son] < *tree[left_son]) {
            min_son = right_son;
        }
        if (*tree[node_ind] < *tree[min_son] || (
                !(*tree[node_ind] < *tree[min_son]) && !(*tree[min_son] < *tree[node_ind]))) {
            break;
        }
        BorNode *N = tree[node_ind];
        tree[node_ind] = tree[min_son];
        tree[min_son] = N;
        node_ind = min_son;
    }
}

void PriorityQueue::push_up(unsigned node_ind) const {
    while (node_ind && *tree[node_ind] < *tree[(node_ind - 1) / 2]) {
        BorNode *N = tree[node_ind];
        tree[node_ind] = tree[(node_ind - 1) / 2];
        tree[(node_ind - 1) / 2] = N;
        node_ind = (node_ind - 1) / 2;
    }
}

void PriorityQueue::erase() {
    if (!sz) {
        return;
    }
    tree[0] = tree[sz - 1];
    tree[--sz] = nullptr;
    push_down(0);
}

void PriorityQueue::insert(BorNode *N) {
    tree[sz++] = N;
    push_up(sz - 1);
}

[[nodiscard]] unsigned PriorityQueue::size() const {
    return sz;
}
