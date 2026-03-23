# include <SFML/Graphics.hpp>
using namespace sf;

const int FPS = 60;

// graphics
void loadFont(Font&);
void handleEvents(RenderWindow&);
void render(RenderWindow&, Font&);
void drawGrid(RenderWindow&);
void drawStatus(RenderWindow&, Font&);

int main()  {
    RenderWindow window(VideoMode({600u, 660u}), "TicTacToe");
    window.setFramerateLimit(FPS);

    Font font;
    loadFont(font);

    while (window.isOpen()) {
        handleEvents(window);
        render(window, font);
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

void handleEvents(RenderWindow& window) {
    while (const auto event = window.pollEvent())   {
        if (event->is<Event :: Closed>())     window.close();
    }
}

void render(RenderWindow& window, Font& font) {
    window.clear(Color(30, 30, 30));
    drawStatus(window, font);
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

void drawStatus(RenderWindow& window, Font& font)    {
    RectangleShape bar(Vector2f(600.f, 60.f));
    bar.setPosition({0.f, 0.f});
    bar.setFillColor(Color(40, 40, 40));
    window.draw(bar);

    Text txt(font, "X's Turn", 24); // string is currently hardcoded since no game state added
    txt.setFillColor(Color :: White);

    // centre text inside the allocated rectangle
    FloatRect b = txt.getLocalBounds();

    // x = barwidth - text width / 2 or *0.5f - internal left padding
    // y = barheight - text height * 0.5f - internal top padding
    txt.setPosition({(600.f - b.size.x) * 0.5f - b.position.x,
                     (60.f - b.size.y) * 0.5f - b.position.y});
    window.draw(txt);
}