
#include "../include/graphics.h"

namespace birch
{
    sf::RectangleShape MakeRect(sf::Vector2f first,
                                sf::Vector2f second,
                                float thickness)
    {
        //FSTART;
        sf::RectangleShape plot ;
        float dist = std::sqrt((first.x - second.x)*(first.x - second.x) +
                         (first.y - second.y)*(first.y - second.y));
        plot.setSize(sf::Vector2f(dist, thickness));
        if(first.y > second.y)
            std::swap(first, second);
        plot.setPosition(first);
        plot.setOrigin(0.f, plot.getSize().y / 2.f);
        float m = (second.y - first.y) / (second.x - first.x) ;
        float angle = (180.0f / 3.1415f) * std::atan((m >= 0.0f) ? m : -m);
        if((first.x - second.x) > 0.01f)
           angle = 180.0f - angle ;
        plot.rotate(angle);
        //FEND;
        return plot ;
    }

    void DrawDottedLine(sf::RenderTarget* window,
                        const sf::Vector2f& start,
                        const sf::Vector2f& end,
                        const sf::Color& color,
                        float gap, float thickness)
    {
        FSTART;
        float dist = std::sqrt((start.x - end.x)*(start.x - end.x) + (start.y - end.y)*(start.y - end.y));
        float covered = 0.0f, ratio, x, y;
        int   total_segments = dist / gap ;
        bool  draw = true ;
        sf::Vector2f first = start, second ;
        covered = gap ;
        for(int i = 0; i < total_segments; ++i)
        {
            if(draw)
            {
                ratio = covered / dist ;
                x = start.x*(1.0f - ratio) + end.x*ratio;
                y = start.y*(1.0f - ratio) + end.y*ratio;
                second = sf::Vector2f(x, y);
                sf::RectangleShape rect = MakeRect(first, second, thickness);
                rect.setFillColor(color);
                window->draw(rect);
            }
            else
            {
                ratio = covered / dist ;
                x = start.x*(1.0f - ratio) + end.x*ratio;
                y = start.y*(1.0f - ratio) + end.y*ratio;
                first = sf::Vector2f(x, y);
            }
            draw = !draw ;
            covered += gap ;
        }

        if((total_segments % 2 == 0) &&
           ((dist / gap) > static_cast<float>(total_segments)))
        {
            sf::RectangleShape rect = MakeRect(first, end, thickness);
            rect.setFillColor(color);
            window->draw(rect);
        }
        FEND;
    }

    void SetTextAtCenter(sf::Text &text, float x, float y, float w, float h)
    {
        FSTART;
        float offsetx = (w - text.getLocalBounds().width)/2.f ,
              offsety = (h - text.getLocalBounds().height)/2.f ;
        text.setPosition(sf::Vector2f(x + offsetx, y + offsety));
        FEND;
    }

    sf::CircleShape PlotPoint(float x, float y, float r, const sf::Color& color)
    {
        FSTART;
        sf::CircleShape cs{r};
        cs.setPosition(sf::Vector2f(x, y));
        cs.setFillColor(color);
        FEND;
        return cs ;
    }

    SectorShape::SectorShape(float r, float a, const sf::Vector2f& c)
        :   radius{r}, angle{a}, center{c}
    {
        FSTART;
        points = 2u + static_cast<unsigned int>(0.05f*radius*angle);
        pie = sf::VertexArray{sf::TrianglesFan, points};
        update();
        FEND;
    }

    void SectorShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        FSTART;
        states.transform *= getTransform();
        target.draw(pie, states);
        FEND;
    }

    void SectorShape::update(float temp)
    {
        FSTART;
        float incr = angle / static_cast<float>(points - 2u);
        float x, y ;
        pie[0].position = center ;
        pie[0].color = fill_color ;
        for(auto i = 1u; i < points; ++i)
        {
            x = radius * std::cos(a2r * temp) ;
            y = radius * std::sin(a2r * temp) ;
            pie[i].position = sf::Vector2f{x, y} + center ;
            pie[i].color = fill_color ;
            temp += incr ;
        }
        FEND;
    }
}
