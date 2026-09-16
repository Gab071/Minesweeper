//
// Created by kamin on 29.04.2025.
//

#include "MSSFMLView.h"
#include <vector>

// Funkcje są wywoływane w konstruktorze, aby wcześniej załadować zdjęcia.
// Jeżeli my ich nie wywołamy teraz to trzeba by byłoby ich wywoływać ręcznie
MSSFMLView::MSSFMLView(MinesweeperBoard& board) : board(board)
{
    loadTextures();
    // setupSprites w scaleWindow
}
void drawGameStart(sf::RenderWindow& window)
{

}

void MSSFMLView::draw(sf::RenderWindow & window)
{
    float offsetX = 0, offsetY = 0, x, y;
    char info;

    scaleBoard(window, offsetX, offsetY);

   // sf::RectangleShape rectangle;
    //createRectangle(rectangle, offsetX, window);

   // sf::CircleShape circle;
   // createCircle(circle, window);

        for (int row = 0; row < boardHeight; ++row)
        {
            for (int col = 0; col < boardWidth; ++col)
            {
                x = col * tileSize + offsetX;
                y = row * tileSize + offsetY;

                if (board.isRevealed(row, col))
                { // Pobieramy klucz info i potem sprawdzamy, czy obiekt z takim kluczem posiadamy
                    info = board.getFieldInfo(row, col);
                    if (sprites.count(info))
                    {
                        sf::Sprite sprite = sprites[info];
                        sprite.setPosition(x, y);
                        window.draw(sprite);
                    }
                }
                else
                {
                    sf::Sprite sprite = hiddenSprite;
                    sprite.setPosition(x, y);
                    window.draw(sprite);

                    if (board.hasFlag(row, col) && sprites.count('f'))
                    {
                        sf::Sprite flagSprite = sprites['f'];
                        flagSprite.setPosition(x, y);
                        window.draw(flagSprite);
                    }
                }
            }
        }
}

void MSSFMLView::drawGameOver(sf::RenderWindow & window)
{
    // sf::Vector2u winSize = window.getSize();
    if(board.getGameState() != RUNNING)
    {
        sf::Font font;
        if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
            std::cerr << "Could not load font\n";
        }

        sf::Text win;
        win.setFont(font);

        if(board.getGameState() == FINISHED_WIN)
            win.setString("You won!");

        else if(board.getGameState() == FINISHED_LOSS)
            win.setString("You lost");

        win.setCharacterSize(50);
        win.setFillColor(sf::Color::Blue);
        win.setStyle(sf::Text::Bold);

        sf::FloatRect bounds = win.getLocalBounds();
        int winWidth = window.getSize().x / 2;
        int winHeight = window.getSize().y / 4.f;
        int tWidth = winWidth - bounds.width / 2.f;
        win.setPosition(tWidth, winHeight);

        window.draw(win);

    }
}

void MSSFMLView::loadTextures()
{
    // Char, bo porównujemy klucze z funkcją getFieldinfo();
    std::vector<std::pair<char, std::string>> texture =
    {
        {' ', "field0.png"}, {'1', "field1.png"}, {'2', "field2.png"},
        {'3', "field3.png"}, {'4', "field4.png"}, {'5', "field5.png"},
        {'6', "field6.png"}, {'7', "field7.png"}, {'8', "field8.png"},
        {'x', "angry.png"}, {'f', "flag.png"}  // 'f' for flag
    };

    for (auto& [key, filename] : texture)
    {
        sf::Texture tex;
        if (!tex.loadFromFile(filename))
        {
            std::cerr << "Failed to load " << filename << std::endl;
        }
        else
        {
            textures[key] = tex; // Jeżeli operacja w if się udaje to dla key zachowujemy obiekt tex
        }
    }

    // Oddzielnie, bo reprezentuje jeszcze nieotworzoną komórkę.
    if (!hiddenTexture.loadFromFile("smile.png"))
    {
        std::cerr << "Failed to load smile.png" << std::endl;
    }
}

void MSSFMLView::setupSprites()
{
    sprites.clear(); // Funkcja do czyszczenia mapy

    for (auto& [key, tex] : textures)
    {
        sf::Sprite sprite;
        sprite.setTexture(tex);
        // tex.getSize().xy oryginalna wielkość png, ryzykownie używać def
        float scaleX = static_cast<float>(tileSize) / tex.getSize().x;
        float scaleY = static_cast<float>(tileSize) / tex.getSize().y;
        sprite.setScale(scaleX, scaleY);

        sprites[key] = sprite; // Asocjuje klucz z obiektem sprite
    }

    hiddenSprite.setTexture(hiddenTexture);
    float scaleX = static_cast<float>(tileSize) / hiddenTexture.getSize().x;
    float scaleY = static_cast<float>(tileSize) / hiddenTexture.getSize().y;
    hiddenSprite.setScale(scaleX, scaleY);
}

void MSSFMLView::scaleBoard(sf::RenderWindow& window, float &offsetX, float &offsetY)
{
    sf::Vector2u winSize = window.getSize(); // Dostajemy rozmiar sfml screen (by def 800*600)
    // Potrzebne, gdy nasza plansza będzie za duża dla sfml screen

        float scaleX = static_cast<float>(winSize.x) / pixelWidth;
        float scaleY = static_cast<float>(winSize.y) / pixelHeight;
        scale = std::min(scaleX, scaleY); // Funkcja wybiera mniejszy wariant
        tileSize = static_cast<int>(tileSize * scale);
        setupSprites();

    // Robimy to po raz drugi, bo tileSize mógł się zmienić
    pixelWidth = boardWidth * tileSize;
    pixelHeight = boardHeight * tileSize;
    // pixelHeight = boardHeight * tileSize + tileSize;

    offsetX = (winSize.x - pixelWidth) / 2.0f;
    offsetY = ((winSize.y - pixelHeight) / 2.0f);
    // offsetY = ((winSize.y - pixelHeight) / 2.0f) + tileSize;
}

void MSSFMLView::createRectangle(sf::RectangleShape & rectangle, const float& offsetX, sf::RenderWindow& window)
{
    float tSize = tileSize;
    float pWidth = boardWidth * tileSize;
    rectangle.setSize({pWidth, tSize});
    rectangle.setPosition(sf::Vector2f(offsetX,0.f));
    window.draw(rectangle);
}

void MSSFMLView::createCircle(sf::CircleShape & circle, sf::RenderWindow& window)
{
    sf::Vector2u winSize = window.getSize();
    float tSize = tileSize;
    float offset = (winSize.x / 2.0f) - tSize/2.0f;
    circle.setRadius(tSize/2);
    circle.setFillColor(sf::Color::Yellow);
    circle.setPosition(sf::Vector2f(offset,0.f));
    window.draw(circle);
}

int MSSFMLView::getTileSize() const
{
    return tileSize;
}