
#include "..\include\base.h"

namespace birch
{

	sf::RectangleShape MakeRect(sf::Vector2f first,
	                            sf::Vector2f second,
								float thickness)
	{
		sf::RectangleShape plot ;
		float dist = std::sqrt((first.x - second.x)*(first.x - second.x) +
						 (first.y - second.y)*(first.y - second.y));
		plot.setSize(sf::Vector2f(dist, thickness));
		if(first.y > second.y)
			std::swap(first, second);
		plot.setPosition(first);
		plot.setOrigin(0, plot.getSize().y / 2);
		float m = (second.y - first.y) / (second.x - first.x) ;
		float angle = (180.0f / 3.1415f) * std::atan((m >= 0.0f) ? m : -m);
		if((first.x - second.x) > 0.01f)
		   angle = 180.0f - angle ;
		plot.rotate(angle);
		return plot ;
	}

	void DrawDottedLine(sf::RenderTarget* window,
	                    const sf::Vector2f& start,
						const sf::Vector2f& end,
						const sf::Color& color,
						float gap, float thickness)
	{
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
				x = start.x * (1.0f - ratio) + end.x * ratio;
				y = start.y * (1.0f - ratio) + end.y * ratio;
				second = sf::Vector2f(x, y);
				sf::RectangleShape rect = MakeRect(first, second, thickness);
				rect.setFillColor(color);
				window->draw(rect);
			}
			else
			{
				ratio = covered / dist ;
				x = start.x * (1.0f - ratio) + end.x * ratio;
				y = start.y * (1.0f - ratio) + end.y * ratio;
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
	}

	GraphLegendUnit::GraphLegendUnit(float x, float y, const sf::Color& c, const std::string& str)
	{
        setRectangleShape(x, y, c);
        setString(str);
	}

	GraphLegendUnit::GraphLegendUnit(float r, const sf::Color& c, const std::string& str)
	{
        setCircleShape(r, c);
        setString(str);
	}

	void GraphLegendUnit::setRectangleShape(float x, float y, const sf::Color& c)
	{
	    shape = new sf::RectangleShape(sf::Vector2f(x, y));
	    shape->setFillColor(c);
	    shape_type = RECTANGULAR;
	}

	void GraphLegendUnit::setCircleShape(float r, const sf::Color& c)
	{
	    shape = new sf::CircleShape(r);
	    shape->setFillColor(c);
	    shape_type = CIRCULAR ;
	}

	void GraphLegendUnit::setCenterText(float x, float y, float w, float h)
	{
	    float offsetx = (w - text.getLocalBounds().width)/2 ,
	          offsety = (h - text.getLocalBounds().height)/2;
        text.setPosition(sf::Vector2f(x + offsetx, y + offsety));
	}

	void GraphLegend::createLegendObjects()
	{
	    LOG("start");

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
            std::cout << "\tDimensions [Shape] = " << shape.width << " * " << shape.height
                      << " [Font] = " << font_size << std::endl ;
        }
        LOG("finished");
	}

	unsigned int GraphLegend::getLongestName() const
	{
	    unsigned int size = 0u ;
	    for(auto& e : legend)
            if(size < e.getString().size())
                size = e.getString().size();
        return size;
	}

	void GraphLegend::render()
	{
        LOG("start");
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
                    e.setCenterText(lx, ly, shape.width, shape.height);
                }
                else
                {
                    e.setCenterText(lx, ly, shape.width, shape.height);
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
                    e.setCenterText(lx, ly, shape.width, font_size);
                }
                else
                {
                    e.setCenterText(lx, ly, shape.width, font_size);
                    ly += font_size ;
                    e.shape->setPosition(sf::Vector2f(lx, ly));
                }
                lx += shape.width + 5.f ;
                texture.draw(e.text);
                texture.draw(*e.shape);
            }
            break;
        }

	    texture.display();
	    LOG("end");
	}

	void GraphBase::createTexture()
    {
        LOG("start");
        createLegendMetrics();

        chart_height = screen_height - screen_margins.top - screen_margins.bottom ;
        chart_width = screen_width - screen_margins.left - screen_margins.right ;

        chart_texture.create(chart_width, chart_height);
        chart_texture.clear(chart_bg_color);

        screen_texture.create(screen_width, screen_height);
        screen_texture.clear(screen_bg_color);
        LOG("end");
    }

	void GraphBase::drawAxes(float thickness, sf::Color color)
	{
		LOG("start");
		sf::RectangleShape xaxis, yaxis ;
		xaxis.setFillColor(color);
		yaxis.setFillColor(color);
		axes_thickness = thickness ;

		// Y-axis
		yaxis.setPosition(sf::Vector2f(chart_offsets.x / 2, chart_offsets.y / 2));
		yaxis.setSize(sf::Vector2f(thickness,  chart_height - chart_offsets.y));
		chart_texture.draw(yaxis);

		// X-axis
		xaxis.setPosition(sf::Vector2f(chart_offsets.x / 2, chart_height - chart_offsets.y / 2 - thickness));
		xaxis.setSize(sf::Vector2f(chart_width - chart_offsets.x, thickness));
		chart_texture.draw(xaxis);
		LOG("end");
	}

	void GraphBase::copyToScreen(sf::RenderWindow *window)
	{
		LOG("start");
		// background screen texture
		sf::Sprite bsprite;
		screen_texture.display();
		bsprite.setTexture(screen_texture.getTexture());
		window->draw(bsprite);

		// foreground chart texture (adjust for margins)
		sf::Sprite csprite;
		chart_texture.display();
		csprite.setTexture(chart_texture.getTexture());
		csprite.move(sf::Vector2f(screen_margins.left, screen_margins.top));
		window->draw(csprite);

		// legend drawing
		sf::Sprite lsprite;
		legend.render();
		lsprite.setTexture(legend.texture.getTexture());
		lsprite.move(sf::Vector2f(legend.x, legend.y));
		window->draw(lsprite);

		LOG("end");
	}

	void GraphBase::drawTextElements()
	{
	    for(int i = 0; i < text_elements.size(); ++i)
            screen_texture.draw(text_elements[i]);
	}

	void GraphBase::drawToScreen(sf::RenderWindow* window)
	{
	    LOG("start");
	    createTexture();
	    render();
	    drawTextElements();
	    copyToScreen(window);
	    LOG("end");
	}

	void GraphBase::createLegendMetrics()
	{
	    LOG("start");

	    legend.x = legend.y = 0.0f ;

	    switch(legend.position)
        {
        case LEFT:
            legend.orientation = VERTICAL ;
            legend.width = 0.2f * screen_width ;
            legend.height = 0.75f * screen_height ;
            legend.x = 0.0f ;
	        legend.y = 0.125f ;
	        screen_margins.left += legend.width ;
            break;
        case RIGHT:
            legend.orientation = VERTICAL ;
            legend.width = 0.2f * screen_width ;
            legend.height = 0.75f * screen_height ;
            legend.x = 0.8f * screen_width ;
	        legend.y = 0.125f ;
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

	    legend.font.loadFromFile("NotoSans.ttf");
        legend.key_shape = RECTANGULAR ;
        std::cout << "\t" << screen_width << " " << screen_height << "\n";
        std::cout << "\t" << legend.x << " " << legend.y << "\n";
        std::cout << "\t" << legend.width << " " << legend.height << "\n";

        LOG("end");
	}
}
