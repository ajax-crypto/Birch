
#include "../include/bubble.h"

namespace birch
{

    BubbleChart::BubbleChart(const std::vector<Triplet>& d, float r)
    : data{d}, largest{r}
    {
        FSTART;
        max = (*std::max_element(data.begin(), data.end())).value;
        std::vector<DataFormat> temp ;
        for(int i = 0; i < d.size(); ++i)
            temp.push_back({ d[i].name, d[i].color });
        legend.addData(temp);
        FEND;
    }

    void BubbleChart::render()
    {
        FSTART;
        float x = chart_offsets.x/2.f, y = chart_offsets.y/2.f ;
        float ratio = max / largest ;
        sf::CircleShape bubble ;
        bubble.setPointCount(100);

        for(auto i = 0u; i < data.size(); ++i)
        {
            bubble.setRadius(data[i].value * ratio);
            bubble.setPosition(sf::Vector2f{data[i].x + x, chart_height - data[i].y - y - largest});
            bubble.setFillColor(data[i].color);
            chart_texture.draw(bubble);
        }
        drawAxes();
        FEND;
    }
}
