
#include "..\include\pie.h"

namespace birch
{
    /*void PieChart::render()
	{
		float angle = 0.0f, total = std::accumulate(data.begin(), data.end(), 0) ;
		float x, y ;
		sf::VertexArray line, pline, triangle ;
		center = sf::Vector2f((chart_width - chart_offsets.x) / 2, (chart_height - chart_offsets.y) / 2);
		if(polygonal)
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
		if(polygonal)
		{
			if(outline)
				pline[0].position = line[1].position ;
			triangle[0].position = line[0].position ;
		}
		chart_texture.draw(line);
		for(unsigned int i = 0; i < data.size(); ++i)
		{
			float temp = angle ;
			angle += (data[i] / total) * (2 * 3.1415f) ;
			if(polygonal)
			{
				x = radius * std::cos(angle) + chart_offsets.x + center.x;
				y = radius * std::sin(angle) + chart_offsets.y + center.y;
				triangle[1].position = line[1].position ;
				line[1].position = sf::Vector2f(x, y);
				triangle[2].position = line[1].position ;
				triangle[0].color = colors[i] ;
				triangle[1].color = colors[i] ;
				triangle[2].color = colors[i] ;
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
					temp += 0.005f ;
					line[1].position = sf::Vector2f(x, y);
					line[0].color = colors[i];
					line[1].color = colors[i];
					chart_texture.draw(line);
				}
			}
		}
		if(polygonal)
			chart_texture.draw(pline);
	}*/

}
