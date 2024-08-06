//
// Created by fedor on 7/28/24.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

template<typename T>
class PriorityQueue {
public:
    explicit PriorityQueue() {
        constexpr unsigned default_queue_sz = 1;
        last_ind = 0, sz = default_queue_sz;
        tree = new T*[default_queue_sz];
        for (unsigned i = 0; i < default_queue_sz; i++) {
            tree[i] = nullptr;
        }
    }

    ~PriorityQueue() {
        delete[] tree;
    }

    [[nodiscard]] T *get_min() const {
        if (!last_ind) {
            return nullptr;
        }
        return tree[0];
    }

    void push_down(unsigned node_ind) const {
        while (2 * node_ind + 1 < last_ind) {
            const unsigned left_son = 2 * node_ind + 1, right_son = 2 * node_ind + 2;
            unsigned min_son = left_son;
            if (right_son < last_ind && *tree[right_son] < *tree[left_son]) {
                min_son = right_son;
            }
            if (*tree[node_ind] < *tree[min_son] || (
                    !(*tree[node_ind] < *tree[min_son]) && !(*tree[min_son] < *tree[node_ind]))) {
                break;
                    }
            T *N = tree[node_ind];
            tree[node_ind] = tree[min_son];
            tree[min_son] = N;
            node_ind = min_son;
        }
    }

    void push_up(unsigned node_ind) const {
        while (node_ind && *tree[node_ind] < *tree[(node_ind - 1) / 2]) {
            T *N = tree[node_ind];
            tree[node_ind] = tree[(node_ind - 1) / 2];
            tree[(node_ind - 1) / 2] = N;
            node_ind = (node_ind - 1) / 2;
        }
    }

    void erase() {
        if (!last_ind) {
            return;
        }
        tree[0] = tree[last_ind - 1];
        tree[--last_ind] = nullptr;
        push_down(0);
    }

    void insert(T *N) {
        if (last_ind >= sz) {
            alloc();
        }
        tree[last_ind++] = N;
        push_up(last_ind - 1);
    }

    [[nodiscard]] unsigned size() const {
        return last_ind;
    }

private:
    unsigned last_ind, sz;
    T **tree;

    void alloc() {
        T **new_tree = new T*[sz * 2];
        for (unsigned ind = 0; ind < sz; ind++) {
            new_tree[ind] = tree[ind];
        }
        delete[] tree;
        tree = new_tree;
        sz *= 2;
    }
};


#endif //PRIORITYQUEUE_H
