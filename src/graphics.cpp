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


#include <iostream>

#include "graphics.hpp"
#include "utils.hpp"


CellTilemap::CellTilemap(Board &board): _board(board) {
    _w = _board.getWidth();
    _h = _board.getHeight();
    fill(_tiles, _w * _h);
    update();
}

void CellTilemap::update() {
    int newWidth = _board.getWidth();
    int newHeight = _board.getHeight();
    if (_w != newWidth || _h != newHeight) {
        // The board was resized
        _w = newWidth;
        _h = newHeight;
        _tiles.clear();
        fill(_tiles, _w * _h);
    }
    const std::vector<bool> thisGen = _board.getCells();
    const std::vector<bool> nextGen = _board.getNextGeneration();
    for (int j = 0; j < _h; ++j) {
        for (int i = 0; i < _w; ++i) {
            int index = j * _w + i;
            bool thisGenCell = thisGen.at(index);
            bool nextGenCell = nextGen.at(index);
            if (thisGenCell && nextGenCell) {
                _tiles.at(index) = Tile::ALIVE;
            } else if (thisGenCell && !nextGenCell) {
                _tiles.at(index) = Tile::DEAD_NEXT_GEN;
            } else if (!thisGenCell && nextGenCell) {
                _tiles.at(index) = Tile::ALIVE_NEXT_GEN;
            } else if (!thisGenCell && !nextGenCell) {
                if ((i + j) % 2) {
                    _tiles.at(index) = Tile::DEAD;
                } else {
                    _tiles.at(index) = Tile::GRID;
                }
            }
        }
    }
}

Tile CellTilemap::get(const int x, const int y) const {
    return _tiles[y * _w + x];
}

void CellTilemap::set(const int x, const int y, const bool value) {
    _board.set(x, y, value);
    update();
}

void CellTilemap::resize(const int x, const int y) {
    _board.resize(x, y);
    update();
}

int CellTilemap::getWidth() const {
    return _w;
}

int CellTilemap::getHeight() const {
    return _h;
}


Tilemap::Tilemap(CellTilemap &tilemap, sf::Texture &tileset, std::vector<std::pair<Tile, sf::Color>> &tileNumbers)
        : _tilemap(tilemap), _tileset(tileset), _tileNumbers(tileNumbers) {}

void Tilemap::update() {
    _tilemap.update();
    int w = _tilemap.getWidth();
    int h = _tilemap.getHeight();

    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(w * h * 4);

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            Tile tile = _tilemap.get(i, j);
            int num = 0;
            for (auto item: _tileNumbers) {
                if (item.first == tile) {
                    break;
                }
                ++num;
            }

            sf::Vertex *quad = &_vertices[(i + j * w) * 4];
            quad[0].position = sf::Vector2f(i * graphicsSettings::cellWidth, j * graphicsSettings::cellHeight);
            quad[1].position = sf::Vector2f((i + 1) * graphicsSettings::cellWidth, j * graphicsSettings::cellHeight);
            quad[2].position = sf::Vector2f((i + 1) * graphicsSettings::cellWidth, (j + 1) * graphicsSettings::cellHeight);
            quad[3].position = sf::Vector2f(i * graphicsSettings::cellWidth, (j + 1) * graphicsSettings::cellHeight);

            quad[0].texCoords = sf::Vector2f(num * graphicsSettings::cellWidth, 0);
            quad[1].texCoords = sf::Vector2f((num + 1) * graphicsSettings::cellWidth, 0);
            quad[2].texCoords = sf::Vector2f((num + 1) * graphicsSettings::cellWidth, graphicsSettings::cellHeight);
            quad[3].texCoords = sf::Vector2f(num * graphicsSettings::cellWidth, graphicsSettings::cellHeight);
        }
    }
}

void Tilemap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.draw(_vertices, states);
}


// Creates a tileset
void createTileset(const std::map<Tile, sf::Color> &colors, std::vector<std::pair<Tile, sf::Color>> &result, sf::Uint8 *pixels, sf::Texture &texture) {
    assert(!pixels);
    pixels = new sf::Uint8[colors.size() * graphicsSettings::cellHeight * graphicsSettings::cellWidth * 4];
    int pos = 0;
    for (int i = 0; i < graphicsSettings::cellHeight; ++i) {
        for (auto &c: colors) {
            for (int j = 0; j < graphicsSettings::cellWidth; ++j) {
                pixels[pos] = c.second.r;
                pixels[pos + 1] = c.second.g;
                pixels[pos + 2] = c.second.b;
                pixels[pos + 3] = c.second.a;
                pos += 4;
            }
            if (i == 0) {
                result.push_back(c);
            }
        }
    }
    texture.create(result.size() * graphicsSettings::cellWidth, graphicsSettings::cellHeight);
    texture.update(pixels);
}
