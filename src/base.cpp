
#include "..\include\base.h"

namespace birch
{
    unsigned int DigitCount(float val)
    {
        unsigned int dc = 0u ;
        int v = static_cast<int>(val);
        while(v > 0)
        {
            dc++ ;
            v /= 10 ;
        }
        return dc ;
    }

    GraphLegendUnit::GraphLegendUnit(float x, float y, const sf::Color& c, const std::string& str)
    {
        FSTART;
        setRectangleShape(x, y, c);
        setString(str);
        FEND;
    }

    GraphLegendUnit::GraphLegendUnit(float r, const sf::Color& c, const std::string& str)
    {
        FSTART;
        setCircleShape(r, c);
        setString(str);
        FEND;
    }

    void GraphLegendUnit::setRectangleShape(float x, float y, const sf::Color& c)
    {
        FSTART;
        shape = new sf::RectangleShape(sf::Vector2f(x, y));
        shape->setFillColor(c);
        shape_type = RECTANGULAR;
        FEND;
    }

    void GraphLegendUnit::setCircleShape(float r, const sf::Color& c)
    {
        FSTART;
        shape = new sf::CircleShape(r);
        shape->setFillColor(c);
        shape_type = CIRCULAR ;
        FEND;
    }

    void GraphLegend::createLegendObjects()
    {
        FSTART;

        auto longest_name = (*std::max_element(legend_data.begin(), legend_data.end(),
                                               [](const DataFormat& a, const DataFormat& b)
                                               {
                                                   return a.name.size() < b.name.size() ;
                                               })).name.size();

        auto limit = legend_data.size();

        if(orientation == VERTICAL)
        {
            shape.width = (width/3.f) ;
            shape.height = (height - 5.f*(limit - 1))/limit;
            font_size = (width - shape.width - 5.f) / static_cast<float>(longest_name);
        }
        else if(orientation == HORIZONTAL)
        {
            shape.width = (width - 5.f*(limit - 1))/limit;
            font_size = height / 3.f ;
            shape.height = height - font_size - 5.f;
        }

        for(int i = 0; i < limit; ++i)
        {
            auto& e = legend_data[i];
            legend.emplace_back(shape.width, shape.height, e.color, e.name);
            if(text_matches_key_color)
                legend[i].setTextColor(e.color);
            else
                legend[i].setTextColor(font_color);
        }

        FEND ;
    }

    unsigned int GraphLegend::getLongestName() const
    {
        FSTART;
        unsigned int size = 0u ;
        for(auto& e : legend)
            if(size < e.getString().size())
                size = e.getString().size();
        FEND;
        return size;
    }

    void GraphLegend::render()
    {
        FSTART ;
        float lx = 0.0f, ly = 0.0f ;

        texture.create(width, height);
        texture.clear(bg_color);
        createLegendObjects();

        switch(orientation)
        {
        case VERTICAL:
            for(auto& e : legend)
            {
                lx = 0.0f ;
                e.text.setCharacterSize(font_size);
                e.text.setFont(font);
                if(before_text)
                {
                    e.shape->setPosition(sf::Vector2f(lx, ly));
                    lx += shape.width + 5.f ;
                    SetTextAtCenter(e.text, lx, ly, shape.width, shape.height);
                }
                else
                {
                    SetTextAtCenter(e.text, lx, ly, shape.width, shape.height);
                    lx += font_size * e.text.getString().getSize() + 5.f ;
                    e.shape->setPosition(sf::Vector2f(lx, ly));
                }
                ly += shape.height + 5.f ;
                texture.draw(e.text);
                texture.draw(*e.shape);
            }
            break;

        case HORIZONTAL:
            for(auto& e : legend)
            {
                ly = 0.0f ;
                e.text.setCharacterSize(font_size);
                e.text.setFont(font);
                if(before_text)
                {
                    e.shape->setPosition(sf::Vector2f(lx, ly));
                    ly += shape.height ;
                    SetTextAtCenter(e.text, lx, ly, shape.width, font_size);
                }
                else
                {
                    SetTextAtCenter(e.text, lx, ly, shape.width, font_size);
                    ly += font_size ;
                    e.shape->setPosition(sf::Vector2f(lx, ly));
                }
                lx += shape.width + 5.f ;
                texture.draw(e.text);
                texture.draw(*e.shape);
            }
            break;
        }
        texture.setSmooth(true);
        texture.display();
        FEND;
    }

    void Chart::createTexture()
    {
        FSTART;
        if(legend.exists)
            createLegendMetrics();

        chart_height = screen_height - screen_margins.top - screen_margins.bottom ;
        chart_width = screen_width - screen_margins.left - screen_margins.right ;

        chart_texture.create(chart_width, chart_height);
        chart_texture.clear(chart_bg_color);

        screen_texture.create(screen_width, screen_height);
        screen_texture.clear(screen_bg_color);

        FEND;
    }

    void Chart::drawAxes()
    {
        FSTART;
        sf::RectangleShape xaxis, yaxis ;
        xaxis.setFillColor(axes.color);
        yaxis.setFillColor(axes.color);

        // Y-axis
        yaxis.setPosition(sf::Vector2f(chart_offsets.x/2.f,
                                       chart_offsets.y/2.f - axes.labels.font_size));
        yaxis.setSize(sf::Vector2f(axes.thickness,  chart_height - chart_offsets.y));
        chart_texture.draw(yaxis);

        // X-axis
        xaxis.setPosition(sf::Vector2f(chart_offsets.x/2.f,
            chart_height - chart_offsets.y/2.f - axes.thickness - axes.labels.font_size));
        xaxis.setSize(sf::Vector2f(chart_width - chart_offsets.x, axes.thickness));
        chart_texture.draw(xaxis);
        FEND;
    }

    void Chart::copyToScreen(sf::RenderWindow *window)
    {
        FSTART;
        // background screen texture
        sf::Sprite bsprite;
        screen_texture.setSmooth(true);
        screen_texture.display();
        bsprite.setTexture(screen_texture.getTexture());
        window->draw(bsprite);

        // foreground chart texture (adjust for margins)
        sf::Sprite csprite;
        chart_texture.setSmooth(true);
        chart_texture.display();
        csprite.setTexture(chart_texture.getTexture());
        csprite.move(sf::Vector2f(screen_margins.left, screen_margins.top));
        window->draw(csprite);

        // legend drawing
        if(legend.exists)
        {
            sf::Sprite lsprite;
            legend.render();
            lsprite.setTexture(legend.texture.getTexture());
            lsprite.move(sf::Vector2f(legend.x, legend.y));
            window->draw(lsprite);
        }

        FEND;
    }

    void Chart::drawTextElements()
    {
        FSTART;
        for(int i = 0; i < text_elements.size(); ++i)
            screen_texture.draw(text_elements[i]);
        FEND;
    }

    void Chart::loadFonts()
    {
        FSTART;
        axes.labels.font.loadFromFile("NotoSans.ttf");
        legend.font.loadFromFile("NotoSans.ttf");
        FEND;
    }

    void Chart::drawToScreen(sf::RenderWindow* window)
    {
        FSTART;

        createTexture();
        loadFonts();
        render();
        drawTextElements();
        copyToScreen(window);

        FEND;
    }

    void Chart::createLegendMetrics()
    {
        FSTART;

        legend.x = legend.y = 0.0f ;

        switch(legend.position)
        {
        case LEFT:
            legend.orientation = VERTICAL ;
            legend.width = 0.2f * screen_width ;
            legend.height = 0.75f * screen_height ;
            legend.x = 0.0f ;
            legend.y = 0.125f * screen_height ;
            screen_margins.left += legend.width ;
            break;
        case RIGHT:
            legend.orientation = VERTICAL ;
            legend.width = 0.2f * screen_width ;
            legend.height = 0.75f * screen_height ;
            legend.x = 0.8f * screen_width ;
            legend.y = 0.125f * screen_height ;
            screen_margins.right += legend.width ;
            break;
        case TOP:
            legend.orientation = HORIZONTAL ;
            legend.width = 0.75f * screen_width ;
            legend.height = 0.2f * screen_height ;
            legend.x += 0.125f * screen_width ;
            screen_margins.top += legend.height ;
            break;
        case BOTTOM:
            legend.orientation = HORIZONTAL ;
            legend.x += 0.25f * screen_width ;
            legend.y += 0.8f * screen_height ;
            legend.width = 0.5f * screen_width ;
            legend.height = 0.2f * screen_height ;
            screen_margins.bottom += legend.height ;
            break;
        }

        legend.key_shape = RECTANGULAR ;

        FEND;
    }
}
