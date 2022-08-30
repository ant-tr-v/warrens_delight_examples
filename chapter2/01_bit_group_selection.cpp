/// Here I implement Gospers algorithm for finding next integer that 
/// has the same number of 1-bits and apply it to itterating over 
/// all grops of N of M elements
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <iomanip>
#include <iostream>

#include <bitset>

std::vector<std::vector<uint8_t>> generate_groups(uint32_t N, uint32_t M) {
    if(M > 63) {
        throw std::runtime_error("in this version only M <= 63 is supported");
    }
    if (N > M) {
        throw std::invalid_argument("N should be lower or equal to N");
    }
    if (N == M) {
        std::vector<std::vector<uint8_t>> result(1);
        result[0].resize(M);
        for (uint8_t i = 0; i < M; ++i) {
            result[0][i] = i + 1;
        }
        return result;
    }
    std::vector<std::vector<uint8_t>> result;
    uint64_t res_code = (1ull << N) - 1;
    uint64_t finish = 1ull << M;
    while (!(res_code & finish)) {
        // uncoding current group
        uint64_t ptr = 1u;
        uint8_t idx = 0;
        uint8_t i = 0;
        std::vector<uint8_t> res_block(N);
        while(ptr <= res_code) {
            if (ptr & res_code) {
                res_block[idx++] = i + 1;
            }
            ++i;
            ptr <<= 1;
        }
        result.emplace_back(res_block);
        // updating code with Gospers algorithm
        uint64_t x = res_code;                 // x = xxxx0111100
        uint64_t s = x & (-x);                 // s = 00000000100
        uint64_t u = x + s;                    // u = xxxx1000000 
        uint64_t n = u ^ x;                    // n = 00001111100
        uint64_t y = u | ((n >> 2) / s);       // y = xxxx1000111
        res_code = y;
    }
    return result;
}


int main() {
    auto res = generate_groups(3, 10);
    for (const auto& group: res) {
        for(uint8_t val: group) {
            std::cout << std::setw(2) << int(val) << " ";
        }
        std::cout << "\n";
    }
    return 0;
}