# include <SFML/Graphics.hpp>
# include "TicTacToe.h"
using namespace sf;

const int FPS = 60;

// graphics
void loadFont(Font&);
void handleEvents(RenderWindow&, TicTacToe&);
void render(RenderWindow&, Font&, TicTacToe&);
void drawGrid(RenderWindow&);
void drawStatus(RenderWindow&, Font&, TicTacToe&);

int main()  {
    RenderWindow window(VideoMode({600u, 660u}), "TicTacToe");
    window.setFramerateLimit(FPS);

    Font font;
    loadFont(font);

    TicTacToe game;

    while (window.isOpen()) {
        handleEvents(window, game);
        render(window, font, game);
    }
    return 0;   
}

void loadFont(Font& font)   {
    const char* fontPointer[] = {"C:/Windows/Fonts/arial.ttf", 
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", nullptr};

    for (int i = 0; fontPointer[i]; i++)    {
        if (font.openFromFile(fontPointer[i])) return;
    }
}

void handleEvents(RenderWindow& window, TicTacToe& game) {
    while (const auto event = window.pollEvent())   {
        if (event->is<Event :: Closed>())     window.close();

        if (const auto* key = event->getIf<Event::KeyPressed>())
            if (key->code == Keyboard::Key::R)
                game.reset();

        if (const auto* click = event->getIf<Event::MouseButtonPressed>()) {
            if (click->button == Mouse::Button::Left) {
                float mx = (float)click->position.x;
                float my = (float)click->position.y;

                // only register clicks inside the board area
                if (my > 60.f && !game.isGameOver()) {
                    int col  = (int)(mx / 200.f);
                    int row  = (int)((my - 60.f) / 200.f);
                    int move = row * 3 + col + 1;
                    game.makeMove(move);
                }
            }
        }
    }
}

void render(RenderWindow& window, Font& font, TicTacToe& game) {
    window.clear(Color(30, 30, 30));
    drawStatus(window, font, game);
    drawGrid(window);
    window.display();
}

void drawGrid(RenderWindow& window)    {
    // vertical lines
    Vertex verticalLine1[2] = {Vertex {Vector2f(200.f, 60.f), Color :: Yellow},
                               Vertex {Vector2f(200.f, 660.f), Color :: Yellow}};
    window.draw(verticalLine1, 2, PrimitiveType :: Lines);

    Vertex verticalLine2[2] = {Vertex {Vector2f(400.f, 60.f), Color :: Yellow},
                               Vertex {Vector2f(400.f, 660.f), Color :: Yellow}};
    window.draw(verticalLine2, 2, PrimitiveType :: Lines);

    // horizontal lines
    Vertex horizontalLine1[2] = {Vertex {Vector2f(0.f, 260.f), Color :: Yellow},
                                 Vertex {Vector2f(600.f, 260.f), Color :: Yellow}};
    window.draw(horizontalLine1, 2, PrimitiveType :: Lines);

    Vertex horizontalLine2[2] = {Vertex {Vector2f(0.f, 460.f), Color :: Yellow},
                                 Vertex {Vector2f(600.f, 460.f), Color :: Yellow}};
    window.draw(horizontalLine2, 2, PrimitiveType :: Lines);

    return;
}

void drawStatus(RenderWindow& window, Font& font, TicTacToe& game)    {
    RectangleShape bar(Vector2f(600.f, 60.f));
    bar.setPosition({0.f, 0.f});
    bar.setFillColor(Color(40, 40, 40));
    window.draw(bar);

    // real chat message
    char msg[32];
    if (game.isGameOver()) {
        if (game.checkWin())
            snprintf(msg, sizeof(msg), "%c wins!", game.getTurn());
        else
            snprintf(msg, sizeof(msg), "Draw!");
    } else {
        snprintf(msg, sizeof(msg), "%c's Turn", game.getTurn());
    }

    Text txt(font, msg, 24);
    txt.setFillColor(Color :: White);

    // centre text inside the allocated rectangle
    FloatRect b = txt.getLocalBounds();

    // x = barwidth - text width / 2 or *0.5f - internal left padding
    // y = barheight - text height * 0.5f - internal top padding
    txt.setPosition({(600.f - b.size.x) * 0.5f - b.position.x,
                     (60.f - b.size.y) * 0.5f - b.position.y});
    window.draw(txt);
}