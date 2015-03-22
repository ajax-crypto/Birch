
#include "..\include\radar.h"

namespace birch
{

    RadarChart::RadarChart(const std::vector<DataElement>& d, float r)
    :   data{d}, radius{r}, dotted_plot{false}, point_radius{4}
    {
        std::vector<DataFormat> temp ;
        for(auto i = 0; i < d.size(); ++i)
            temp.push_back({ d[i].name, d[i].color });
        legend.addData(temp);
    }

    void RadarChart::render()
    {
        FSTART;
        float max = (*std::max_element(data.begin(), data.end())).value ;
        float guide_angle = 360.0f / static_cast<float>(data.size()),
              angle = 0.0f, x, y, m ;
        float ratio = radius / max ;
        std::vector<sf::Vector2f> plot_points ;
        sf::Vector2f center((chart_width - chart_offsets.x) / 2, (chart_height - chart_offsets.y) / 2);
        sf::RectangleShape guide ;
        sf::CircleShape point(point_radius);

        guide.setPosition(center);
        guide.setSize(sf::Vector2f(max * ratio, 2.f));
        guide.setOrigin(0, guide.getSize().y / 2.f);
        guide.setFillColor(sf::Color::Black);

        for(int i = 0; i < data.size(); ++i)
        {
            x = (ratio * max * std::cos((3.1415f / 180.0f) * angle)) + center.x;
            y = (ratio * max * std::sin((3.1415f / 180.0f) * angle)) + center.y;
            angle += guide_angle ;
            guide.rotate(guide_angle);
            m = data[i].value / max ;
            x = m * x + (1.0f - m) * center.x ;
            y = m * y + (1.0f - m) * center.y ;
            plot_points.push_back(sf::Vector2f(x, y));
            chart_texture.draw(guide);
        }

        for(int i = 0; i < plot_points.size(); ++i)
        {
            sf::Vector2f first = plot_points[i] ,
                         second = plot_points[(i + 1) % plot_points.size()];
            sf::RectangleShape plot ;
            point.setPosition(sf::Vector2f(first.x - point_radius, first.y - point_radius));
            if(dotted_plot)
                DrawDottedLine(&chart_texture, first, second, sf::Color::Black, 8.f);
            else
            {
                plot = MakeRect(first, second, 2.f);
                plot.setFillColor(sf::Color::Black);
                chart_texture.draw(plot);
            }
            point.setFillColor(data[i].color);
            chart_texture.draw(point);
        }
        point.setFillColor(data[0].color);
        point.setPosition(sf::Vector2f(plot_points[0].x - point_radius, plot_points[0].y - point_radius));
        chart_texture.draw(point);
        FEND;
    }

}
