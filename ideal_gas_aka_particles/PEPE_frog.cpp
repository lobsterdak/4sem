#include <SFML\Graphics.hpp>
#include "Vector2.h"

class material_point
{
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 acselleration;
    static const int speed_rate = 15;
    void set_rand_speed() {
        int rad = rand();
        velocity.x = cos(rad);
        velocity.y = sin(rad);
        velocity = velocity * speed_rate;
    }
};

class Ball : public material_point
{
public:
    void set_position(sf::Vector2i pos)
    {
        position.x = pos.x;
        position.y = pos.y;
    }
    double radius;
    sf::Sprite sprite;
    void update(double dt)
    {
        position += velocity * dt;
    }
    void update_velocity(double dt)
    {
        velocity += acselleration * dt;
    }
};

void check_balls_bump(Ball& b1, Ball b2)
{
    Vector2 d;
    Vector2 normal;
    d = b2.position - b1.position;
    normal = d.unit_vector();
    if (d.len() < (b1.radius + b2.radius) && ((b2.velocity - b1.velocity) * d) < 0)
    {
        b2.velocity += (-2 * (b2.velocity * normal)) * normal;
        b1.velocity += (-2 * (b1.velocity * normal)) * normal;
    }
    else
        return;
}

void check_ball(Ball& b, int Weight, int Height)
{
    if (b.position.x > Weight - b.radius && b.velocity.x > 0 || b.position.x < b.radius && b.velocity.x < 0)
        b.velocity.x = -b.velocity.x;
    if (b.position.y > Height - b.radius &&  b.velocity.y > 0 || b.position.y < b.radius && b.velocity.y < 0)
        b.velocity.y = -b.velocity.y;
}


int main()
{
    int weight = 1200;
    int height = 700;
    float dt;
    float prev_time = 0;
    float scale = 0.8;
    Ball tmp;
    sf::Clock clock;
    sf::Texture texture;
    sf::Time time;
    sf::Vector2i mousePosition;
    std::vector <Ball> balls;
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(weight, height), "My window");
    texture.loadFromFile("1.png");
    tmp.sprite.setTexture(texture);
    tmp.acselleration = { 0, 9.8 };
    tmp.radius = tmp.sprite.getTexture()->getSize().y / 2 * scale;
    tmp.sprite.setOrigin(tmp.sprite.getTexture()->getSize().x / 2, (tmp.sprite.getTexture()->getSize().y / 2));
    tmp.sprite.scale(scale, scale);
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonReleased)
            {
                tmp.set_position(sf::Mouse::getPosition(window));
                tmp.set_rand_speed();
                balls.push_back(tmp);
            }
        }
        time = clock.getElapsedTime();
        dt = time.asSeconds() - prev_time;
        for (int i = 0; i < balls.size(); i++)
        {
            check_ball(balls[i], weight, height);
            balls[i].update_velocity(dt);
            balls[i].update(dt);
        }
        for (int i = 0; i < balls.size(); i++)
        {
            for (int j = 0; j < balls.size(); j++)
            {
                if (i != j)
                    check_balls_bump(balls[i], balls[j]);
            }
        }
        for (auto itr : balls)
        {
            itr.sprite.setPosition(itr.position.x, itr.position.y);
            window.draw(itr.sprite);
        }
        window.display();
        prev_time = time.asSeconds();
    }
    return 0;
}
