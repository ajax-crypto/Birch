
#include "..\include\bar.h"

namespace birch
{
    BarChart::BarChart(const std::vector<DataElement>& d, bool al, bool dv) :
    data{d}, gap{10}, display_values{dv}, guides{true}
    {
        FSTART;
        max = (*std::max_element(data.begin(), data.end())).value;
        legend.exists = al ;
        if(legend.exists)
        {
            std::vector<DataFormat> temp ;
            for(int i = 0; i < d.size(); ++i)
                temp.push_back({ d[i].name, d[i].color });
            legend.addData(temp);
        }
        FEND;
    }

    void BarChart::render()
    {
        FSTART;
        float x = chart_offsets.x/2.f + gap, y = chart_offsets.y/2.f ;
        float ratio = (chart_height - 2.f*chart_offsets.y - vsize) / max;
        float item;
        sf::Text   text, values ;
        sf::RectangleShape guide_lines ;

        width = (chart_width - 2.f*chart_offsets.x - gap*static_cast<float>(data.size()))
            / static_cast<float>(data.size()) ;
        vsize = width/static_cast<float>(DigitCount(max) + 3u) ;

        if(!legend.exists)
        {
            text.setFont(axes.labels.font);
            text.setColor(axes.labels.font_color);
            text.setCharacterSize(axes.labels.font_size);
        }

        if(display_values)
        {
            values.setFont(axes.labels.font);
            values.setCharacterSize(vsize);
        }

        if(guides)
        {
            float incrs = max/static_cast<float>(guides);
            float x1 = x, y1 = chart_height - axes.labels.font_size ,
                  x2 = x + chart_width, y2 ;
            for(auto i = 0u; i < guides; ++i)
            {
                DrawDottedLine(&chart_texture, sf::Vector2f(x, y), sf::Vector2f(x, y), sf::Color(69, 69, 69));
            }
        }

        for(auto& d : data)
        {
            item = d.value ;
            item *= ratio ;
            bar.setPosition(x, chart_height - y - item + vsize);
            bar.setSize(sf::Vector2f(width, item - axes.labels.font_size - vsize));
            bar.setFillColor(d.color);
            chart_texture.draw(bar);
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
                SetTextAtCenter(values, x, chart_height - y - item - vsize/2.f,
                                width + gap, vsize);
                values.move(sf::Vector2f(-gap/2.f, 0.f));
                chart_texture.draw(values);
            }
            x += width + gap;
        }

        drawAxes();
        FEND;
    }

    MultiBarChart::MultiBarChart(const std::vector<std::vector<float>>& d1,
                                 const std::vector<std::string>& d2,
                                 const std::vector<sf::Color>& d3)
    : multi_data{d1}, axes_labels{d2}, bar_colors{d3}, display_values{true}
    {
        FSTART;
        assert(d1.size() == d2.size());
        assert(d1[0].size() == d3.size());

        float temp ;
        max = *(std::max_element(d1[0].begin(), d1[0].end()));
        for(int i = 1; i < d1.size(); ++i)
        {
            temp = (*std::max_element(d1[i].begin(), d1[i].end()));
            if(temp > max)
                max = temp ;
        }
        FEND;
    }

    void MultiBarChart::render()
    {
        FSTART;
        float x = chart_offsets.x/2.f, y = chart_offsets.y/2.f ;
        float ratio = (chart_height - 2.f*chart_offsets.y) / max;
        float item ;
        sf::RectangleShape bar ;
        sf::Text           text, values ;

        width = (chart_width - 2.f*chart_offsets.x) /
            static_cast<float>((multi_data[0].size() + 1u) * multi_data.size()) ;
        gap = width ;
        vsize = width/static_cast<float>(DigitCount(max)) ;

        if(display_values)
        {
            values.setFont(axes.labels.font);
            values.setCharacterSize(vsize);
        }

        text.setFont(axes.labels.font);
        text.setColor(axes.labels.font_color);
        text.setCharacterSize(axes.labels.font_size);

        for(int i = 0; i < multi_data.size(); ++i)
        {
            x += gap ;
            text.setString(axes_labels[i]);
            SetTextAtCenter(text, x, chart_height - y - 1.2f*axes.labels.font_size,
                width + gap, axes.labels.font_size);
            chart_texture.draw(text);
            for(int j = 0; j < multi_data[i].size(); ++j)
            {
                item = multi_data[i][j] * ratio ;
                bar.setPosition(x, chart_height - y - item + vsize);
                bar.setSize(sf::Vector2f(width, item - axes.labels.font_size - vsize));
                bar.setFillColor(bar_colors[j]);
                chart_texture.draw(bar);

                if(display_values)
                {
                    values.setString([&](){
                        std::ostringstream temp ;
                        temp << std::setprecision(2) << multi_data[i][j] ;
                        return temp.str();
                    }());
                    values.setColor(bar_colors[j]);
                    SetTextAtCenter(values, x, chart_height - y - item - vsize/2.f, width, vsize);
                    chart_texture.draw(values);
                }

                x += width ;
            }
        }
        drawAxes();
        FEND;
    }

    ColumnChart::ColumnChart(const std::vector<std::vector<float>>& d1,
                             const std::vector<std::string>& d2,
                             const std::vector<sf::Color>& d3)
    : multi_data{d1}, axes_labels{d2}, bar_colors{d3}, gap{10}
    {
        FSTART;
        assert(d1.size() == d2.size());
        assert(d1[0].size() == d3.size());

        float temp ;
        max = 0 ;
        for(int i = 1; i < d1.size(); ++i)
        {
            temp = std::accumulate(d1[i].begin(), d1[i].end(), 0);
            if(temp > max)
                max = temp ;
        }
        FEND;
    }

    void ColumnChart::render()
    {
        FSTART;
        float x = chart_offsets.x/2.f + gap, y = chart_offsets.y/2.f ;
        float ratio = (chart_height - 2.f*chart_offsets.y - axes.labels.font_size) / max;
        float item;
        sf::Text   text ;
        sf::RectangleShape guide_lines, bar ;

        width = (chart_width - 2.f*chart_offsets.x - gap*static_cast<float>(multi_data.size()))
            / static_cast<float>(multi_data.size()) ;

        text.setFont(axes.labels.font);
        text.setColor(axes.labels.font_color);
        text.setCharacterSize(axes.labels.font_size);

        for(int i = 0; i < multi_data.size(); ++i)
        {
            x += gap ;
            text.setString(axes_labels[i]);
            SetTextAtCenter(text, x, chart_height - y - 1.2f*axes.labels.font_size,
                width + gap, axes.labels.font_size);
            chart_texture.draw(text);
            for(int j = 0; j < multi_data[i].size(); ++j)
            {
                item = multi_data[i][j] * ratio ;
                bar.setPosition(x, chart_height - y - item);
                bar.setSize(sf::Vector2f(width, item - axes.labels.font_size));
                bar.setFillColor(bar_colors[j]);
                chart_texture.draw(bar);
                y += item - axes.labels.font_size ;
            }
            x += width ;
            y = chart_offsets.y/2.f ;
        }
        drawAxes();
        FEND;
    }

}
