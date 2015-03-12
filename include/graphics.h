#ifndef __BIRCH_GRAPHICS__
#define __BIRCH_GRAPHICS__

#include "SFML/Graphics.hpp"
#include "log.h"
#include <cmath>

namespace birch
{
    const float a2r = 3.1415f / 180.0f ;

    enum Position { LEFT, RIGHT, TOP, BOTTOM };
    enum Shape    { RECTANGULAR, CIRCULAR };
    enum Orientation { HORIZONTAL, VERTICAL };

    sf::RectangleShape MakeRect(sf::Vector2f,
                                sf::Vector2f,
                                float = 1.f);

    void DrawDottedLine(sf::RenderTarget*,
                        const sf::Vector2f&,
                        const sf::Vector2f&,
                        const sf::Color&,
                        float = 3.f,
                        float = 1.f);

    void SetTextAtCenter(sf::Text&, float, float, float, float);

    sf::CircleShape PlotPoint(float, float, float, const sf::Color&);

    class SectorShape : public sf::Transformable, public sf::Drawable
    {
        sf::Vector2f    center ;
        float           radius ;
        float           angle ;
        sf::VertexArray pie ;
        sf::Color       fill_color ;
        unsigned int    points ;

        void            update(float = 0.0f);

    public:
        SectorShape(float, float, const sf::Vector2f& = sf::Vector2f{ 0.f, 0.f });
        SectorShape() {}

        void setCenter(const sf::Vector2f& c) { center = c; update(); }
        void setFillColor(const sf::Color& c) { fill_color = c; update(); }
        void rotate(float a) { FSTART; update(a); FEND;  }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    };
}

#endif // __BIRCH_GRAPHICS__
