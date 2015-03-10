
#include "..\include\pie.h"

namespace birch
{

    PieChart::PieChart(const std::vector<DataElement>& d, ExplodeMode mode, PieChartType pt)
    : data{d}, radius{100}, outline{false}, explode_mode{mode}, type{pt}
    {
        FSTART;
        total = [&](){
            float total = 0.f ;
            for(const auto& e : d)
                total += e.value ;
            return total ;
        }();

        if(explode_mode == LARGEST)
        {
            explode_sector = [&](){
                unsigned int i = 0u ;
                float data = d[0].value ;
                for(auto j = 1u; j < d.size(); ++j)
                    if(data < d[j].value)
                    {
                        data = d[j].value;
                        i = j ;
                    }
                return i ;
            }();
        }

        std::vector<DataFormat> temp ;
        for(auto i = 0; i < d.size(); ++i)
            temp.push_back({ d[i].name, d[i].color });
        legend.addData(temp);
        FEND;
    }

    void PieChart::render()
    {
        FSTART ;
        float angle = 0.0f ;
        float x, y ;
        sf::VertexArray line, pline, triangle ;
        center = sf::Vector2f((chart_width - chart_offsets.x) / 2.f,
                        (chart_height - chart_offsets.y) / 2.f);
        if(type == POLYGONAL)
        {
            if(outline)
            {
                pline.setPrimitiveType(sf::Lines);
                pline.append(sf::Vertex(sf::Vector2f(0, 0)));
                pline.append(sf::Vertex(sf::Vector2f(0, 0)));
            }

            triangle.setPrimitiveType(sf::Triangles);
            triangle.append(sf::Vertex(sf::Vector2f(0, 0)));
            triangle.append(sf::Vertex(sf::Vector2f(0, 0)));
            triangle.append(sf::Vertex(sf::Vector2f(0, 0)));
        }
        line.setPrimitiveType(sf::Lines);
        line.append(sf::Vertex(sf::Vector2f(0, 0)));
        line.append(sf::Vertex(sf::Vector2f(0, 0)));
        line[0].color = sf::Color(0, 0, 0);
        line[1].color = sf::Color(0, 0, 0);
        line[0].position = sf::Vector2f(center.x + chart_offsets.x, center.y + chart_offsets.y);
        line[1].position = sf::Vector2f(center.x + radius + chart_offsets.x, center.y + chart_offsets.y);
        if(type == POLYGONAL)
        {
            if(outline)
                pline[0].position = line[1].position ;
            triangle[0].position = line[0].position ;
        }
        chart_texture.draw(line);
        for(const auto& d : data)
        {
            float temp = angle ;
            angle += (d.value / total) * (2.f * 3.1415f) ;
            if(type == POLYGONAL)
            {
                x = radius * std::cos(angle) + chart_offsets.x + center.x;
                y = radius * std::sin(angle) + chart_offsets.y + center.y;
                triangle[1].position = line[1].position ;
                line[1].position = sf::Vector2f(x, y);
                triangle[2].position = line[1].position ;
                triangle[0].color = d.color ;
                triangle[1].color = d.color ;
                triangle[2].color = d.color ;
                chart_texture.draw(triangle);
                if(outline)
                {
                    pline[1].position = line[1].position ;
                    chart_texture.draw(line);
                    chart_texture.draw(pline);
                    pline[0].position = pline[1].position ;
                }
            }
            else
            {
                while(temp <= angle)
                {
                    x = radius * std::cos(temp) + chart_offsets.x + center.x;
                    y = radius * std::sin(temp) + chart_offsets.y + center.y;
                    line[1].position = sf::Vector2f(x, y);
                    line[0].color = d.color;
                    line[1].color = d.color;
                    chart_texture.draw(line);
                    temp += 0.005f ;
                }
            }
        }
        if(type == POLYGONAL)
            chart_texture.draw(pline);
        else if(type == DONUT)
        {
            sf::CircleShape tshape(donut_radius);
            tshape.setFillColor(sf::Color::White);
            tshape.setPosition(line[0].position - sf::Vector2f(donut_radius, donut_radius));
            chart_texture.draw(tshape);
            LOG("drawn donut");
        }

        FEND;
    }

}
