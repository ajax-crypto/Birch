
#include "..\include\histogram.h"

namespace birch
{
    /*void Histogram::render()
	{
		float x = (chart_offsets.x / 2), y = (chart_offsets.y / 2), bar_height, bar_width ;
		float max_height = std::get<0>(*std::max_element(data.begin(), data.begin() + data.size(),
				[](const std::tuple<float, float, float>& lhs, const std::tuple<float, float, float>& rhs) {
					return std::get<0>(lhs) < std::get<0>(rhs) ; })),
			  max_width = (std::get<2>(data[data.size() - 1]) - std::get<1>(data[0])) ;
	    float draw_height = chart_height - chart_offsets.y,
		      draw_width = chart_width - chart_offsets.x ;
		float ratiox = (max_width > draw_width) ? max_width / draw_width : draw_width / max_width,
		      ratioy = (max_height > draw_height) ? max_height / draw_height : draw_height / max_height ;
	    sf::RectangleShape bar ;
		for(int i = 0; i < data.size(); ++i)
		{
			bar_width = (std::get<2>(data[i]) - std::get<1>(data[i])) * ratiox ;
			bar_height = std::get<0>(data[i]) * ratioy ;
			bar.setPosition(x, chart_height - (chart_offsets.y / 2) - bar_height);
			bar.setSize(sf::Vector2f(bar_width, bar_height));
			x += bar_width ;
			if(outline)
				bar.setOutlineThickness(1);
			if(fill)
				bar.setFillColor(colors[i]);
			chart_texture.draw(bar);
		}
		drawAxes();
	}*/
}
