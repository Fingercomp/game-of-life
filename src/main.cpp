#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "graphics.hpp"
#include "main.hpp"


int main() {
    Board board(10, 10);
    CellTilemap cellTilemap(board);
    sf::Texture texture;
    std::vector<std::pair<Tile, sf::Color>> tilesetNumbers;
    sf::Uint8 *tilesetBytes = nullptr;
    createTileset(graphicsSettings::colors, tilesetNumbers, tilesetBytes, texture);
    Tilemap tilemap(cellTilemap, texture, tilesetNumbers);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game of Life");
    window.setFramerateLimit(30);  // no need for high FPS

    sf::Vector2u windowSize = window.getSize();
    cellTilemap.resize(ceil(static_cast<float>(windowSize.x) / graphicsSettings::cellWidth), ceil(static_cast<float>(windowSize.y) / graphicsSettings::cellHeight));

    State state = State::PAUSED;
    sf::Time updateInterval = sf::milliseconds(1000 / 5);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized: {
                    sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                    window.setView(sf::View(visibleArea));
                    cellTilemap.resize(ceil(static_cast<float>(event.size.width) / graphicsSettings::cellWidth), ceil(static_cast<float>(event.size.height) / graphicsSettings::cellHeight));
                }
                case sf::Event::MouseButtonPressed: {
                    switch (event.mouseButton.button) {
                        case sf::Mouse::Left: {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            x /= graphicsSettings::cellWidth;
                            y /= graphicsSettings::cellHeight;
                            cellTilemap.set(x, y, true);
                            break;
                        }
                        case sf::Mouse::Right: {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            x /= graphicsSettings::cellWidth;
                            y /= graphicsSettings::cellHeight;
                            cellTilemap.set(x, y, false);
                            break;
                        }
                        case sf::Mouse::Middle: {
                            int x = event.mouseButton.x;
                            int y = event.mouseButton.y;
                            x /= graphicsSettings::cellWidth;
                            y /= graphicsSettings::cellHeight;
                            std::cout << "DEBUG INFO FOR {x=" << x << ", y=" << y << "}:\n";
                            std::cout << "Neighbors: " << board.getNeighborCount(x, y) << "\n";
                            break;
                        }
                        default:
                            break;
                    }
                }
                case sf::Event::KeyPressed: {
                    switch (event.key.code) {
                        case sf::Keyboard::Space:
                            if (state == State::PAUSED) {
                                state = State::RUNNING;
                            } else if (state == State::RUNNING) {
                                state = State::PAUSED;
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case sf::Event::MouseMoved: {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
                            sf::Mouse::isButtonPressed(sf::Mouse::Right) ||
                            sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                        int x = event.mouseMove.x;
                        int y = event.mouseMove.y;
                        x /= graphicsSettings::cellWidth;
                        y /= graphicsSettings::cellHeight;
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            cellTilemap.set(x, y, true);
                        }
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                            cellTilemap.set(x, y, false);
                        }
                    }
                }
                default:
                    break;
            }
        }
        if (state == State::RUNNING) {
            if (clock.getElapsedTime() >= updateInterval) {
                board.step();
                clock.restart();
            }
        }
        window.clear();
        tilemap.update();
        window.draw(tilemap);
        window.display();
    }

    delete[] tilesetBytes;
    return 0;
}
