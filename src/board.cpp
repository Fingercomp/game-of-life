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


#include <vector>

#include "board.hpp"
#include "utils.hpp"


Board::Board(const int w, const int h): _w(w), _h(h) {
    assert(w > 1);
    assert(h > 1);

    // Fill the board
    fill(_cells, _w * _h);
    fill(_nextGen, _w * _h);
}

std::vector<bool> Board::newGeneration() {
    std::vector<bool> newGen;
    fill(newGen, _w * _h);
    for (int y = 0; y < _h; ++y) {
        for (int x = 0; x < _w; ++x) {
            bool cell = _cells[y * _w + x];
            int nb = getNeighborCount(x, y);
            newGen[y * _w + x] = (cell && nb == 2) || nb == 3;
        }
    }
    return newGen;
}

int Board::getWidth() const {
    return _w;
}

int Board::getHeight() const {
    return _h;
}

const std::vector<bool>& Board::getCells() const {
    return _cells;
}

const std::vector<bool>& Board::getNextGeneration() const {
    return _nextGen;
}

int Board::getNeighborCount(const int x, const int y) const {
    int neighbors = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        // "glue" the edges of a board
        int indexI = i;
        if (i < 0) {
            indexI = _w + i;
        } else if (i >= _w) {
            indexI = i % _w;
        }
        for (int j = y - 1; j <= y + 1; ++j) {
            int indexJ = j;
            if (j < 0) {
                indexJ = _h + j;
            } else if (j >= _h) {
                indexJ = j % _h;
            }
            if (_cells[indexJ * _w + indexI]) {
                if (i != x || j != y) {
                    ++neighbors;
                }
            }
        }
    }
    return neighbors;
}

std::vector<bool> Board::step() {
    std::vector<bool> oldGen(_cells);
    _cells = _nextGen;
    _nextGen = newGeneration();
    return oldGen;
}

void Board::set(const int x, const int y, const bool value) {
    assert(x >= 0 && x < _w);
    assert(y >= 0 && y < _h);
    _cells[y * _w + x] = value;
    _nextGen = newGeneration();  // Update the highlighting
}

bool Board::get(const int x, const int y) const {
    assert(x >= 0 && x < _w);
    assert(y >= 0 && y < _h);

    return _cells[y * _w + x];
}

void Board::resize(const int w, const int h) {
    assert(w > 1);
    assert(h > 1);

    std::vector<bool> newBoard;
    fill(newBoard, w * h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            bool cell;
            if (x < _w && y < _h) {
                cell = _cells[y * _w + x];
            } else {
                cell = false;
            }
            newBoard[y * w + x] = cell;
        }
    }
    _cells = newBoard;
    _w = w;
    _h = h;
    _nextGen = newGeneration();
}
