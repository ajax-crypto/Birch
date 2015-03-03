
#include "..\include\line.h"

namespace birch
{
    /*LineGraph::LineGraph(std::vector<float> const& d)
	: anchor_size{8}, anchor_color{sf::Color(88, 172, 250)},
	  hguide{true}, vguide{true}, guide_color{sf::Color(100, 100, 100)},
	  line_color{sf::Color::Black}, gap{0.0f}, start_pos{0.0f},
	  yaxis_guide{true}, xaxis_guide{true}, line_thickness{2}
	{
		data = std::vector<float>(d) ;
		max = *std::max_element(data.begin(), data.end()) ;
		anchor.setRadius(anchor_size);
		anchor.setFillColor(anchor_color);
	}

	void LineGraph::drawAxisAnchors(float x, float y)
	{
		if(yaxis_guide)
		{
			anchor.setPosition(sf::Vector2f(chart_offsets.x/2 - anchor_size/2, y - anchor_size/2));
			anchor.setRadius(anchor_size/2);
			chart_texture.draw(anchor);
		}
		if(xaxis_guide)
		{
			anchor.setPosition(sf::Vector2f(x - anchor_size/2, chart_height - chart_offsets.y/2 - anchor_size/2));
			anchor.setRadius(anchor_size/2);
			chart_texture.draw(anchor);
		}
	}

	void LineGraph::drawAxisGuides(float x, float y)
	{
		if(vguide)
			DrawDottedLine(&chart_texture, sf::Vector2f(x, y),
			                         sf::Vector2f(x, chart_height - chart_offsets.y/2), guide_color);
		if(hguide)
			DrawDottedLine(&chart_texture, sf::Vector2f(chart_offsets.x/2, y),
			                         sf::Vector2f(x, y), guide_color);
	}

	void LineGraph::drawValueAnchor(float x, float y)
	{
		anchor.setPosition(sf::Vector2f(x - anchor_size, y - anchor_size));
		anchor.setRadius(anchor_size);
		chart_texture.draw(anchor);
	}

	void LineGraph::render()
	{
		float x = chart_offsets.x/2 + gap, y = chart_offsets.y/2 ;
		float ratio = (chart_height - chart_offsets.y - anchor_size) / max;
		float item = data[0];
		sf::RectangleShape line ;
		sf::Vector2f first, second ;
		item *= ratio ;
		gap = (chart_width - chart_offsets.x) / data.size();
		first = sf::Vector2f(x, chart_height - y - item);
		if(start_pos > 0.0f)
            drawAxisGuides(first.x, first.y);
		drawAxisAnchors(first.x, first.y);
		for(unsigned int i = 1; i < data.size(); ++i)
		{
			item = data[i] * ratio ;
			x += gap ;
			second = sf::Vector2f(x, chart_height - y - item);
			line = MakeRect(first, second, line_thickness);
			line.setFillColor(line_color);
			chart_texture.draw(line);
			first = second ;
            drawAxisGuides(first.x, first.y);
            drawAxisAnchors(first.x, first.y);
		}

		x = chart_offsets.x/2;
		for(auto item : data)
        {
            item *= ratio ;
            drawValueAnchor(x, chart_height - y - item);
            x += gap ;
        }
		drawAxes();
	}

	MultiLineGraph::MultiLineGraph(const std::vector<std::vector<float>>& d,
                                   const std::vector<sf::Color>& c)
    : data{d}, hguide{true}, vguide{true}, gap{0.0f}, start_pos{0.0f},
	  yaxis_guide{true}, xaxis_guide{true}, adjust{8.f}, anchor_color{c}
    {
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
    }

    void MultiLineGraph::drawAxisAnchors(float x, float y, unsigned int index)
	{
		anchor.setRadius(anchor_size[index]/2);
        anchor.setFillColor(anchor_color[index]);
		if(yaxis_guide)
		{
			anchor.setPosition(sf::Vector2f(chart_offsets.x/2 - anchor_size[index]/2, y - anchor_size[index]/2));
			chart_texture.draw(anchor);
		}
		if(xaxis_guide)
		{
			anchor.setPosition(sf::Vector2f(x - anchor_size[index]/2, chart_height - chart_offsets.y/2 - anchor_size[index]/2));
			chart_texture.draw(anchor);
		}
	}

	void MultiLineGraph::drawAxisGuides(float x, float y, unsigned int index)
	{
		if(vguide)
			DrawDottedLine(&chart_texture, sf::Vector2f(x, y),
			                         sf::Vector2f(x, chart_height - chart_offsets.y/2), guide_color[index]);
		if(hguide)
			DrawDottedLine(&chart_texture, sf::Vector2f(chart_offsets.x/2, y),
			                         sf::Vector2f(x, y), guide_color[index]);
	}

	void MultiLineGraph::drawValueAnchor(float x, float y, unsigned int index)
	{
		anchor.setPosition(sf::Vector2f(x - anchor_size[index], y - anchor_size[index]));
		anchor.setRadius(anchor_size[index]);
		anchor.setFillColor(anchor_color[index]);
		chart_texture.draw(anchor);
	}

    void MultiLineGraph::render()
    {
        float x, y = chart_offsets.y/2, item ;
		float ratio = (chart_height - chart_offsets.y - adjust) / max;
		unsigned int i, j ;
		sf::RectangleShape line ;
		sf::Vector2f first, second ;
		gap = (chart_width - chart_offsets.x) / data.size();
		for(j = 0; j < data[0].size(); ++j)
        {
            x = chart_offsets.x/2 ;
            item = data[0][j] * ratio ;
            first = sf::Vector2f(x, chart_height - y - item);
            if(start_pos > 0.0f)
                drawAxisGuides(first.x, first.y, j);
            drawAxisAnchors(first.x, first.y, j);
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
    }*/
}
