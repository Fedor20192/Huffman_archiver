//
// Created by fedor on 7/28/24.
//

#ifndef BOR_H
#define BOR_H

#include <string>

#include "../../CONSTANTS.h"
#include "BorNode.h"

class Bor {
public:
    explicit Bor(const unsigned long long cnt_of_symbols[]);

    explicit Bor(const std::string codes[]);

    void get_codes(std::string codes[]);

    [[nodiscard]] LCHAR get_alphabet_sz() const;

    [[nodiscard]] bool is_terminal() const;

    [[nodiscard]] LCHAR get_symb() const;

    void add(LCHAR bit);

    void reset();

    ~Bor();

private:
    LCHAR alphabet_sz;
    BorNode *root{nullptr}, *last{nullptr};

    static void delete_bor(const BorNode *N);

    void get_codes(const BorNode *N, std::string codes[], std::string &now_code);

    void add_bit(int bit);

    void add_code(const std::string &code, LCHAR symb);
};
#endif //BOR_H
