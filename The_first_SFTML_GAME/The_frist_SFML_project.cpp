#include <SFML\Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#define PI M_PI
struct Bullet
{
    sf::Vector2f pos;
    sf::Vector2f v;
    sf::Sprite hero;
    void update(float dt)
    {
        pos += v * (dt / 2) ;
    }
};

bool checkPosition(const sf::Sprite circle, const int Width, const int Height, const char way)
{
    sf::Vector2u circle_size = circle.getTexture()->getSize();
    float size = (float)sqrt(circle_size.x * circle_size.x + circle_size.y * circle_size.y) / 2;
    sf::Vector2f center = circle.getPosition();
    switch (way)
    {
    case (int)'u':
        return (center.y > size);
    case (int)'d':
        return (center.y + size < Height);
    case (int)'l':
        return (center.x > size);
    case (int)'r':
        return (center.x + size < Width);
    case (int)'b':
        return ((center.x < Width) && (center.x > 0) && (center.y < Height) && (center.y > 0));
    default:
        return 0;
        break;
    }
}

int main()
{
    bool FLAG_FOR_MOUSE;
    const int Widht = 800;
    const int Height = 600;
    float Max_speed = 400;
    Bullet tmp;
    std::vector <Bullet> bullets;
    bullets.reserve(1000);
    sf::RenderWindow window(sf::VideoMode(Widht, Height), "My window");
    sf::Event event;
    sf::Clock clock;
    sf::Texture texture_for_bullet;
    sf::Texture texture;
    texture.loadFromFile("hero.png");
    texture_for_bullet.loadFromFile("bullet.png");
    sf::Sprite circle(texture);
    circle.setPosition(400, 300);
    sf::Vector2u circleSize = circle.getTexture()->getSize();
    float Prev_time = 0;
    while (window.isOpen())
    {
        circle.setOrigin((float)circleSize.x / 2, (float)circleSize.y / 2);
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f center = circle.getPosition();
        sf::Vector2f d = sf::Vector2f((float)mousePosition.x, (float)mousePosition.y) - center;
        circle.setRotation(90 + (float)(atan2f(d.y, d.x) * 180 / PI));
        sf::Time time = clock.getElapsedTime();
        window.clear(sf::Color::Yellow);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && checkPosition(circle, Widht, Height, 'l'))
        {
            circle.move((-time.asSeconds() + Prev_time) * Max_speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && checkPosition(circle, Widht, Height, 'r'))
        {
            circle.move((time.asSeconds() - Prev_time) * Max_speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && checkPosition(circle, Widht, Height, 'u'))
        {
            circle.move(0, (-time.asSeconds() + Prev_time) * Max_speed);
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && checkPosition(circle, Widht, Height, 'd'))
        {
            circle.move(0, (time.asSeconds() - Prev_time) * Max_speed);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            FLAG_FOR_MOUSE = 1;
        }
        else 
        {
            if (FLAG_FOR_MOUSE == 1)
            {
                FLAG_FOR_MOUSE = 0;
                tmp.hero.setTexture(texture_for_bullet);
                tmp.hero.setOrigin((float)circleSize.x / 2, (float)circleSize.y / 2);
                tmp.hero.setScale(0.5, 0.5);
                tmp.v = d / sqrt(d.x * d.x + d.y * d.y);
                tmp.pos = center + tmp.v * (float)(3 * circleSize.x / 4);
                tmp.hero.setRotation(90 + (float)(atan2f(d.y, d.x) * 180 / PI));
                tmp.hero.setPosition(tmp.pos);
                bullets.push_back(tmp);
            }
        }
        for (auto itr = bullets.begin(); itr != bullets.end(); ++itr)
        {
            itr->update(static_cast<float>(time.asSeconds() - Prev_time + 1));
            itr->hero.setPosition(itr->pos);
            window.draw(itr->hero);
            if (!checkPosition(itr->hero, Widht, Height, 'b'))
            {
                bullets.erase(itr);
                itr--;
            }
           
        }
        Prev_time = time.asSeconds();
        window.draw(circle);
        window.display();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}
