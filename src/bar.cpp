
#include "..\include\bar.h"

namespace birch
{
    BarGraph::BarGraph(const std::vector<DataElement>& d, bool add_legend) :
    data{d}, gap{10}
    {
        max = (*std::max_element(data.begin(), data.end())).value;
        if(add_legend)
        {
            std::vector<DataFormat> temp ;
            for(int i = 0; i < d.size(); ++i)
                temp.push_back({ d[i].name, d[i].color });
            legend.addData(temp);
        }
    }

    void BarGraph::render()
	{
		float x = chart_offsets.x/2 + gap, y = chart_offsets.y/2 ;
		float ratio = (chart_height - 2*chart_offsets.y) / max;
		float item ;
		//sf::Text ;

		width = (chart_width - 2*chart_offsets.x - gap * data.size()) / data.size() ;

		for(auto& d : data)
		{
			item = d.value ;
			item *= ratio ;
			bar.setPosition(x, chart_height - y - item);
			bar.setSize(sf::Vector2f(width, item));
			bar.setFillColor(d.color);
			chart_texture.draw(bar);
			x += width + gap;
		}

		drawAxes();
	}

    MultiBarGraph::MultiBarGraph(const std::vector<std::vector<float>>& d1,
                                 const std::vector<DataFormat>& d2)
	: multi_data{d1}, data{d2}
	{
		//std::assert(bar_colors.size() == d[0].size());
		float temp ;
		max = *(std::max_element(d1[0].begin(), d1[0].end()));
		for(int i = 1; i < d1.size(); ++i)
		{
			temp = (*std::max_element(d1[i].begin(), d1[i].end()));
			if(temp > max)
				max = temp ;
		}
	}

	void MultiBarGraph::render()
	{
		float x = chart_offsets.x/2, y = chart_offsets.y/2 ;
		float ratio = (chart_height - 2*chart_offsets.y) / max;
		float item ;
		sf::RectangleShape bar ;
        width = (chart_width - 2*chart_offsets.x) / ((multi_data[0].size() + 1) * multi_data.size()) ;
		gap = width ;
		for(int i = 0; i < multi_data.size(); ++i)
		{
			x += gap ;
			for(int j = 0; j < multi_data[i].size(); ++j)
			{
				item = multi_data[i][j] * ratio ;
				bar.setPosition(x, chart_height - y - item);
				bar.setSize(sf::Vector2f(width, item));
				bar.setFillColor(data[j].color);
				chart_texture.draw(bar);
				x += width ;
			}
		}
		drawAxes();
	}

}
