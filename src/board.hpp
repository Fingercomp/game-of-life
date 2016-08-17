#pragma once

#include <cassert>
#include <vector>


class Board {
private:
    int _w;  // the width of board
    int _h;  // the height of board

    //  i  i  i  i  i
    //  0  1  2  3  4 j
    //  5  6  7  8  9 j
    // 10 [11] = {i=1, j=2}
    // 15 16 17 18 19 j
    std::vector<bool> _cells;  // the vector of cells
    std::vector<bool> _nextGen;  // for highlighting
    std::vector<bool> newGeneration();
public:
    Board(const int w, const int h);
    int getWidth() const;
    int getHeight() const;
    std::vector<bool> step();
    const std::vector<bool>& getCells() const;
    const std::vector<bool>& getNextGeneration() const;
    int getNeighborCount(const int x, const int y) const;
    void set(const int x, const int y, const bool value);
    bool get(const int x, const int y) const;
    void resize(const int w, const int h);
};
