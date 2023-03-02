#include <iostream>

#include "board.hpp"
#include "movegen.hpp"
#include "perft.hpp"

uint64_t Perft::perftFunction(Board &b, int depth, int max)
{
    Movelist moves;
    Movegen::legalmoves(b, moves);
    if (depth == 0)
        return 1;
    else if (depth == 1 && max != 1)
    {
        return moves.size;
    }
    uint64_t nodesIt = 0;

    for (const auto move : moves)
    {
        b.makeMove(move);
        nodesIt += perftFunction(b, depth - 1, depth);
        b.unmakeMove(move);
        if (depth == max)
        {
            nodes += nodesIt;
            if (print)
                std::cout << uciMove(move) << " " << nodesIt << std::endl;
            nodesIt = 0;
        }
    }
    if (depth == max && print)
        std::cout << "\n" << std::endl;
    return nodesIt;
}

uint64_t Perft::getAndResetNodes()
{
    auto tmp = nodes;
    nodes = 0;
    return tmp;
}