
#include "..\include\bar.h"

namespace birch
{
    BarGraph::BarGraph(const std::vector<DataElement>& d, bool al) :
    data{d}, gap{10}
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

    void BarGraph::render()
	{
		FSTART;
		float x = chart_offsets.x/2.f + gap, y = chart_offsets.y/2.f ;
		float ratio = (chart_height - 2.f*chart_offsets.y) / max;
		float item ;
		sf::Text   text ;
		if(!legend.exists)
        {
            text.setFont(axes.labels.font);
            text.setColor(axes.labels.font_color);
            text.setCharacterSize(axes.labels.font_size);
        }

		width = (chart_width - 2.f*chart_offsets.x - gap*data.size()) / data.size() ;

		for(auto& d : data)
		{
			item = d.value ;
			item *= ratio ;
			bar.setPosition(x, chart_height - y - item);
			bar.setSize(sf::Vector2f(width, item - axes.labels.font_size));
			bar.setFillColor(d.color);
			chart_texture.draw(bar);
			if(!legend.exists)
            {
                text.setString(d.name);
                SetTextAtCenter(text, x, chart_height - y - axes.labels.font_size,
                                width + gap, axes.labels.font_size);
                text.move(sf::Vector2f(-gap/2.f, 0.f));
                chart_texture.draw(text);
            }
			x += width + gap;
		}

		drawAxes();
		FEND;
	}

    MultiBarGraph::MultiBarGraph(const std::vector<std::vector<float>>& d1,
                                 const std::vector<std::string>& d2,
                                 const std::vector<sf::Color>& d3)
	: multi_data{d1}, axes_labels{d2}, bar_colors{d3}
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

	void MultiBarGraph::render()
	{
		FSTART;
		float x = chart_offsets.x/2.f, y = chart_offsets.y/2.f ;
		float ratio = (chart_height - 2.f*chart_offsets.y) / max;
		float item ;
		sf::RectangleShape bar ;
		sf::Text           text ;

        text.setFont(axes.labels.font);
        text.setColor(axes.labels.font_color);
        text.setCharacterSize(axes.labels.font_size);
        width = (chart_width - 2.f*chart_offsets.x) /
            static_cast<float>((multi_data[0].size() + 1) * multi_data.size()) ;
		gap = width ;

		for(int i = 0; i < multi_data.size(); ++i)
		{
			x += gap ;
			text.setString(axes_labels[i]);
            SetTextAtCenter(text, x, chart_height - y - axes.labels.font_size,
                width + gap, axes.labels.font_size);
            chart_texture.draw(text);
			for(int j = 0; j < multi_data[i].size(); ++j)
			{
				item = multi_data[i][j] * ratio ;
				bar.setPosition(x, chart_height - y - item);
				bar.setSize(sf::Vector2f(width, item - axes.labels.font_size));
				bar.setFillColor(bar_colors[j]);
				chart_texture.draw(bar);
				x += width ;
			}
		}
		drawAxes();
		FEND;
	}

}
