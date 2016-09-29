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
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

#include <SFML/Graphics.hpp>

#include "board.hpp"


enum class Tile {
    DEAD,
    DEAD_NEXT_GEN,
    ALIVE,
    ALIVE_NEXT_GEN,
    GRID
};


namespace graphicsSettings {
    const int cellWidth = 8;
    const int cellHeight = 8;
    const std::map<Tile, sf::Color> colors {
        {Tile::DEAD, sf::Color(0x00, 0x00, 0x00)},
        {Tile::DEAD_NEXT_GEN, sf::Color(0xff, 0x40, 0x40)},
        {Tile::ALIVE, sf::Color(0xff, 0xff, 0xff)},
        {Tile::ALIVE_NEXT_GEN, sf::Color(0x00, 0x40, 0x00)},
        {Tile::GRID, sf::Color(0x20, 0x20, 0x20)}
    };
    const std::vector<sf::Time> speed {
        sf::milliseconds(1000 / 1000),
        sf::milliseconds(1000 / 500),
        sf::milliseconds(1000 / 250),
        sf::milliseconds(1000 / 100),
        sf::milliseconds(1000 / 50),
        sf::milliseconds(1000 / 20),
        sf::milliseconds(1000 / 10),
        sf::milliseconds(1000 / 5),
        sf::milliseconds(1000 / 4),
        sf::milliseconds(1000 / 2),
        sf::milliseconds(1000),
        sf::milliseconds(1000 * 1.5f),
        sf::milliseconds(1000 * 2),
        sf::milliseconds(1000 * 3),
        sf::milliseconds(1000 * 4),
        sf::milliseconds(1000 * 5),
        sf::milliseconds(1000 * 8),
        sf::milliseconds(1000 * 10)
    };
    const std::vector<float> zoomLevels {
        1.0f / 10,
        1.0f / 5,
        1.0f / 4,
        1.0f / 2,
        1.0f,
        1.0f * 1.5f
    };
}


class CellTilemap {
private:
    Board &_board;
    std::vector<Tile> _tiles;
    int _w;
    int _h;
public:
    CellTilemap(Board &board);
    void update();
    Tile get(const int x, const int y) const;
    void set(const int x, const int y, const bool value);
    void resize(const int x, const int y);
    int getWidth() const;
    int getHeight() const;
};

class Tilemap: public sf::Drawable, public sf::Transformable {
private:
    CellTilemap _tilemap;
    sf::Texture _tileset;
    std::vector<std::pair<Tile, sf::Color>> _tileNumbers;
    sf::VertexArray _vertices;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Tilemap(CellTilemap &tilemap, sf::Texture &tileset, std::vector<std::pair<Tile, sf::Color>> &tileNumbers);
    void update();
};


void createTileset(const std::map<Tile, sf::Color> &colors, std::vector<std::pair<Tile, sf::Color>> &result, sf::Uint8 *pixels, sf::Texture &texture);
