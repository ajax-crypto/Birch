
#include "..\include\line.h"

namespace birch
{
    LineGraph::LineGraph(std::vector<DataElement> const& d)
    : data{d}, anchor_size{8}, anchor_color{sf::Color(88, 172, 250)},
      hguide{true}, vguide{true}, guide_color{sf::Color(100, 100, 100)},
      line_color{sf::Color::Black}, gap{0.0f}, start_pos{0.0f},
      yaxis_guide{true}, xaxis_guide{true}, line_thickness{2},
      display_values{true}, display_guides{true}
    {
        FSTART;
        max = (*std::max_element(d.begin(), d.end())).value ;
        anchor.setRadius(anchor_size);
        anchor.setFillColor(anchor_color);
        std::vector<DataFormat> temp ;
        for(int i = 0; i < d.size(); ++i)
            temp.push_back({ d[i].name, d[i].color });
        legend.addData(temp);
        axes.labels.font_size = 10 ;
        FEND ;
    }

    void LineGraph::drawAxisAnchors(float x, float y)
    {
        FSTART;
        if(yaxis_guide)
        {
            anchor.setPosition(sf::Vector2f(chart_offsets.x/2.f - anchor_size/2.f,
                                            y - anchor_size/2.f));
            anchor.setRadius(anchor_size/2.f);
            chart_texture.draw(anchor);
        }
        if(xaxis_guide)
        {
            anchor.setPosition(sf::Vector2f(x - anchor_size/2.f,
                                            chart_height - chart_offsets.y/2.f - anchor_size/2.f - axes.labels.font_size));
            anchor.setRadius(anchor_size/2.f);
            chart_texture.draw(anchor);
        }
        FEND;
    }

    void LineGraph::drawAxisGuides(float x, float y)
    {
        FSTART;
        if(vguide)
            DrawDottedLine(&chart_texture, sf::Vector2f(x, y),
                           sf::Vector2f(x, chart_height - chart_offsets.y/2.f - axes.labels.font_size), guide_color);
        if(hguide)
            DrawDottedLine(&chart_texture, sf::Vector2f(chart_offsets.x/2.f, y),
                           sf::Vector2f(x, y), guide_color);
        FEND;
    }

    void LineGraph::drawValueAnchor(float x, float y, const sf::Color& fill)
    {
        FSTART;
        anchor.setPosition(sf::Vector2f(x - anchor_size, y - anchor_size));
        anchor.setRadius(anchor_size);
        anchor.setFillColor(fill);
        chart_texture.draw(anchor);
        FEND;
    }

    void LineGraph::render()
    {
        FSTART;
        float x = chart_offsets.x/2.f + gap, y = chart_offsets.y/2.f ;
        float ratio = (chart_height - chart_offsets.y - anchor_size) / max;
        float item = data[0].value;
        gap = (chart_width - chart_offsets.x) / data.size();
        float width = (chart_width - 2.f*chart_offsets.x - gap*static_cast<float>(data.size()))
            / static_cast<float>(data.size()) ;
        sf::RectangleShape line ;
        sf::Vector2f first, second ;
        sf::Text   text, values ;
        item *= ratio ;
        first = sf::Vector2f(x, chart_height - y - item);
        if(start_pos > 0.0f)
            drawAxisGuides(first.x, first.y);
        drawAxisAnchors(first.x, first.y);

        if(!legend.exists)
        {
            text.setFont(axes.labels.font);
            text.setColor(axes.labels.font_color);
            text.setCharacterSize(axes.labels.font_size);
        }

        if(display_values)
        {
            values.setFont(axes.labels.font);
            values.setCharacterSize(axes.labels.font_size);
        }

        for(auto& d : data)
        {
            item = d.value * ratio ;
            x += gap ;
            second = sf::Vector2f(x, chart_height - y - item);
            line = MakeRect(first, second, line_thickness);
            line.setFillColor(line_color);
            chart_texture.draw(line);
            first = second ;
            if(!legend.exists)
            {
                text.setString(d.name);
                SetTextAtCenter(text, x, chart_height - y - 1.2f*axes.labels.font_size,
                                width + gap, axes.labels.font_size);
                text.move(sf::Vector2f(-gap/2.f, 0.f));
                chart_texture.draw(text);
            }

            if(display_values)
            {
                values.setColor(d.color);
                values.setString([&](){
                        std::ostringstream temp ;
                        temp << std::setprecision(2) << d.value ;
                        return temp.str();
                    }());
                SetTextAtCenter(values, x, chart_height - y - item - axes.labels.font_size/2.f,
                                width + gap, axes.labels.font_size);
                values.move(sf::Vector2f(-gap/2.f, -anchor_size -axes.labels.font_size));
                std::string v = values.getString();
                chart_texture.draw(values);
            }
            drawAxisGuides(first.x, first.y);
            drawAxisAnchors(first.x, first.y);
        }

        x = chart_offsets.x/2.f + gap;
        for(auto& d : data)
        {
            item = d.value * ratio ;
            drawValueAnchor(x, chart_height - y - item, d.color);
            x += gap ;
        }
        drawAxes();
        FEND;
    }

    MultiLineGraph::MultiLineGraph(const std::vector<std::vector<float>>& d,
                                   const std::vector<std::string>& n,
                                   const std::vector<sf::Color>& c)
    : data{d}, colors{c}, axes_labels{n}, hguide{true}, vguide{true}, gap{0.0f},
      start_pos{0.0f}, yaxis_guide{true}, xaxis_guide{true}, adjust{8.f}, anchor_color{c}
    {
        FSTART;
        float temp ;
        max = *std::max_element(d[0].begin(), d[0].end());
        for(int i = 1; i < d.size(); ++i)
        {
            temp = *std::max_element(d[i].begin(), d[i].end());
            if(temp > max)
                max = temp ;
        }
        line_color = std::vector<sf::Color>(data[0].size(), sf::Color::Black);
        guide_color = std::vector<sf::Color>(data[0].size(), sf::Color::Black);
        anchor_size = std::vector<float>(data[0].size(), 8.f);
        line_thickness = std::vector<float>(data[0].size(), 2.f);
        FEND;
    }

    void MultiLineGraph::drawAxisAnchors(float x, float y, unsigned int index)
    {
        FSTART;
        anchor.setRadius(anchor_size[index]/2);
        anchor.setFillColor(anchor_color[index]);
        if(yaxis_guide)
        {
            anchor.setPosition(sf::Vector2f(chart_offsets.x/2 - anchor_size[index]/2,
                                            y - anchor_size[index]/2));
            chart_texture.draw(anchor);
        }
        if(xaxis_guide)
        {
            anchor.setPosition(sf::Vector2f(x - anchor_size[index]/2,
                chart_height - chart_offsets.y/2 - anchor_size[index]/2 - axes.labels.font_size));
            chart_texture.draw(anchor);
        }
        FEND;
    }

    void MultiLineGraph::drawAxisGuides(float x, float y, unsigned int index)
    {
        FSTART;
        if(vguide)
            DrawDottedLine(&chart_texture, sf::Vector2f(x, y),
                sf::Vector2f(x, chart_height - chart_offsets.y/2 - axes.labels.font_size),
                guide_color[index]);
        if(hguide)
            DrawDottedLine(&chart_texture, sf::Vector2f(chart_offsets.x/2, y),
                                     sf::Vector2f(x, y), guide_color[index]);
        FEND;
    }

    void MultiLineGraph::drawValueAnchor(float x, float y, unsigned int index)
    {
        FSTART;
        anchor.setPosition(sf::Vector2f(x - anchor_size[index], y - anchor_size[index]));
        anchor.setRadius(anchor_size[index]);
        anchor.setFillColor(anchor_color[index]);
        chart_texture.draw(anchor);
        FEND;
    }

    void MultiLineGraph::render()
    {
        FSTART;
        float x, y = chart_offsets.y/2, item ;
        float ratio = (chart_height - chart_offsets.y - adjust) / max;
        unsigned int i, j ;
        sf::RectangleShape line ;
        sf::Vector2f first, second ;
        sf::Text  text ;
        float width = (chart_width - 2.f*chart_offsets.x - gap*static_cast<float>(data.size()))
            / static_cast<float>(data.size()) ;

        text.setFont(axes.labels.font);
        text.setColor(axes.labels.font_color);
        text.setCharacterSize(axes.labels.font_size);

        gap = (chart_width - chart_offsets.x) / data.size();
        for(j = 0; j < data[0].size(); ++j)
        {
            x = chart_offsets.x/2 ;
            item = data[0][j] * ratio ;
            first = sf::Vector2f(x, chart_height - y - item);
            if(start_pos > 0.0f)
                drawAxisGuides(first.x, first.y, j);
            drawAxisAnchors(first.x, first.y, j);
            text.setString(axes_labels[0]);
            SetTextAtCenter(text, first.x - width/2.f, chart_height - 1.2f*axes.labels.font_size, width, axes.labels.font_size);
            chart_texture.draw(text);
            for(i = 1; i < data.size(); ++i)
            {
                item = data[i][j] * ratio ;
                x += gap ;
                second = sf::Vector2f(x, chart_height - y - item);
                line = MakeRect(first, second, line_thickness[j]);
                line.setFillColor(line_color[j]);
                chart_texture.draw(line);
                first = second ;
                drawAxisGuides(first.x, first.y, j);
                drawAxisAnchors(first.x, first.y, j);

                text.setString(axes_labels[i]);
                SetTextAtCenter(text, first.x - width/2.f, chart_height - 1.2f*axes.labels.font_size, width, axes.labels.font_size);
                chart_texture.draw(text);
            }
        }

        for(j = 0; j < data[0].size(); ++j)
        {
            x = chart_offsets.x/2;
            for(i = 0; i < data.size(); ++i)
            {
                item = data[i][j] * ratio ;
                drawValueAnchor(x, chart_height - y - item, j);
                x += gap ;
            }
        }
        drawAxes();
        FEND;
    }
}
