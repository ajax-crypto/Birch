
#include "..\include\.h"

namespace birch
{
    void RadarGraph::drawToScreen(sf::RenderWindow* window)
	{
		float max = *std::max_element(data.begin(), data.begin() + data.size());
		float ratio = radius / max ;
		float guide_angle = 360.0f / static_cast<float>(data.size()),
		      angle = 0.0f, line_angle, x, y, m, dist ;
		std::vector<sf::Vector2f> plot_points ;
		sf::Vector2f center((chart_width - offsetx) / 2, (chart_height - offsety) / 2);
		sf::RectangleShape guide ;
		sf::CircleShape point(point_radius);
		guide.setPosition(center);
		guide.setSize(sf::Vector2f(max * ratio, 2));
		guide.setOrigin(0, guide.getSize().y / 2);
		guide.setFillColor(sf::Color(0, 0, 0));
		texture.create(chart_width, chart_height);
		texture.clear(sf::Color::White);
		for(int i = 0; i < data.size(); ++i)
		{
			x = (ratio * max * std::cos((3.1415f / 180.0f) * angle)) + center.x;
			y = (ratio * max * std::sin((3.1415f / 180.0f) * angle)) + center.y;
			angle += guide_angle ;
			guide.rotate(guide_angle);
			m = data[i] / max ;
			x = m * x + (1.0f - m) * center.x ;
			y = m * y + (1.0f - m) * center.y ;
			plot_points.push_back(sf::Vector2f(x, y));
			texture.draw(guide);
		}

		for(int i = 0; i < plot_points.size(); ++i)
		{
			sf::Vector2f first = plot_points[i] ,
			             second = plot_points[(i + 1) % plot_points.size()];
			sf::RectangleShape plot ;
			point.setPosition(sf::Vector2f(first.x - point_radius, first.y - point_radius));
			point.setFillColor(sf::Color(100, 100, 100));
			plot = MakeRect(first, second, 2.f);
			plot.setFillColor(sf::Color::Black);
			texture.draw(plot);
			texture.draw(point);
		}
		copyToScreen(window);
	}

}
