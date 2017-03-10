#include <SFML\Graphics.hpp>
#include <math.h>

using Centroids = std::vector<sf::Color>;
using closest_centroid_indices = std::vector<int>;


class ColorBuf
{
    public:
        int r, g, b;
        int count;
        ColorBuf() :
            r(0),
            g(0),
            b(0),
            count(0)
        {}
        ColorBuf& operator+=(const sf::Color& c)
        {
            count++;
            r += c.r;
            g += c.g;
            b += c.b;
            return *this;
        }
};

double distance(sf::Color first, sf::Color second)
{
    int r = first.r - second.r;
    int g = first.g - second.g;
    int b = first.b - second.b;
    return sqrt(r * r + g * g + b * b);
}

void initial_centorids(sf::Image& image, const int k, Centroids& result)
{
    for (int i = 0; i < k; i++)
    {
        int x = rand() % image.getSize().x;
        int y = rand() % image.getSize().y;
        result.push_back(image.getPixel(x, y));
    }
    return;
}

void find_closest_centroids(sf::Image& image, Centroids centroids, closest_centroid_indices& ids)
{
    double dist = -1;
    int num_of_centroid;
    double current_distance = 0;
    sf::Color current_pixel;
    for (int j = 0; j < image.getSize().y; j++)
    {
        for (int i = 0; i < image.getSize().x; i++)
        {
            current_pixel = image.getPixel(i, j);
            for (int l = 0; l < centroids.size(); l ++)
            {
                current_distance = distance(centroids[l], current_pixel);
                if (current_distance < dist || dist == -1) {
                    dist = current_distance;
                    num_of_centroid = l;
                }
            }
            ids[i + j * image.getSize().x] = num_of_centroid;
            dist = -1;
        }
    }
    return ;
}

void compute_means(sf::Image image, closest_centroid_indices ids, const int k, Centroids& result)
{
    std::vector<ColorBuf> BUF;
    BUF.resize(k);
    for (int i = 0; i < ids.size(); i++)
    {
        BUF[ids[i]] += image.getPixel(i % image.getSize().x, i / image.getSize().x);
    }
    for (int j = 0; j < BUF.size(); j++)
    {
        if (BUF[j].count == 0)
            continue;
        result[j].r = BUF[j].r / BUF[j].count;
    }
    return ;
}

void change_color(sf::Image& image, closest_centroid_indices ids, Centroids centorids)
{
    sf::Color tmp;
    for (int i = 0; i < ids.size(); i++)
    {
        tmp = centorids[ids[i]];
        int x = i % image.getSize().x;
        int y = i / image.getSize().x;
        image.setPixel(x, y, tmp);
    }
}

int main()
{
    const int k = 7;
    const int iteration_count = 50;
    sf::Sprite sprite;
    sf::Event event;
    sf::Texture texture;
    closest_centroid_indices ids;
    Centroids centroids;
    texture.loadFromFile("don.png");
    sprite.setTexture(texture);
    sf::Vector2u size = sprite.getTexture()->getSize();
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "My window");
    auto image = texture.copyToImage();
    initial_centorids(image, k, centroids);
    ids.resize(image.getSize().x * image.getSize().y);
    for (int it = 0; it < iteration_count; ++it)
    {
        find_closest_centroids(image, centroids, ids);
        compute_means(image, ids, k, centroids);
    }
    change_color(image, ids, centroids);
    texture.update(image);
    sprite.setTexture(texture);
    while (window.isOpen())
    {
        
        window.draw(sprite);
        window.display();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}