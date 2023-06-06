#include <iostream>
#include <World.hpp>
#include <Grid.hpp>
#include <SFML/Graphics.hpp>

void render(sf::RenderWindow *window, World *world, float gridSize)
{
    window->clear(sf::Color::Black);
    sf::RectangleShape aliveCell(sf::Vector2f(8.0f, 8.0f));
    aliveCell.setFillColor(sf::Color(255, 255, 255));
    aliveCell.setOutlineThickness(0.5f);
    aliveCell.setOutlineColor(sf::Color(50, 50, 50));

    sf::RectangleShape deadCell(sf::Vector2f(8.0f, 8.0f));
    deadCell.setFillColor(sf::Color(0, 0, 0));
    deadCell.setOutlineThickness(1.f);
    deadCell.setOutlineColor(sf::Color(50, 50, 50));

    for (int i = 0; i < world->getLength(); i++)
    {
        for (int j = 0; j < world->getWidth(); j++)
        {
            if (world->getCellVital(i, j))
            {
                aliveCell.setPosition(j * gridSize, i * gridSize);
                window->draw(aliveCell);
            }
            else
            {
                deadCell.setPosition(j * gridSize, i * gridSize);
                window->draw(deadCell);
            }
        }
    }

    window->display();
}

int main()
{
    int WORLD_HEIGHT = 90;
    int WORLD_WIDTH = 160;
    int SCALE = 8;
    float grid_size = 8.0f;

    bool playFlag = 0;
    float playSpeed = 0.25f;
    bool rightMouseHold = 0;
    bool leftMouseHold = 0;

    World world(WORLD_HEIGHT, WORLD_WIDTH);
    std::cout << "World Creation Completed" << std::endl;

    sf::RenderWindow window(sf::VideoMode(WORLD_WIDTH * SCALE, WORLD_HEIGHT * SCALE), "Conway's Game of Life");
    window.setFramerateLimit(60);
    printf("%d %d\n", WORLD_WIDTH * SCALE, WORLD_HEIGHT * SCALE);

    render(&window, &world, grid_size);
    window.display();

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                int column = (int)(worldPos.x / 8);
                int row = (int)(worldPos.y / 8);

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    world.setCellAlive(row, column);
                    leftMouseHold = 1;
                }
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                {
                    world.setCellDead(row, column);
                    rightMouseHold = 1;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                leftMouseHold = 0;
                rightMouseHold = 0;
            }
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

                int column = (int)(worldPos.x / 8);
                int row = (int)(worldPos.y / 8);

                if (leftMouseHold)
                {
                    world.setCellAlive(row, column);
                }
                if (rightMouseHold)
                {
                    world.setCellDead(row, column);
                }
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    playFlag ^= 1;
                }
                if (event.key.code == sf::Keyboard::Delete)
                {
                    world.clear();
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    playSpeed *= 2.0f;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    playSpeed /= 2.0f;
                }
            }
        }

        if ((clock.getElapsedTime() > sf::seconds(playSpeed)) && playFlag)
        {
            clock.restart();
            world.computeNextGeneration();
        }

        render(&window, &world, grid_size);
    }

    return 0;
}