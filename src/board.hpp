// MIT License
//
// Copyright (c) 2016 Fingercomp
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// // AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


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
