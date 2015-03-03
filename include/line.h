#ifndef __BIRCH_LINE_CHART__
#define __BIRCH_LINE_CHART__

#include "base.h"

namespace birch
{
    /*class LineGraph : public DataGraph<LineGraph>
	{
    protected:
		std::vector<float> data ;
		float gap, start_pos;
		float max ;
		bool  hguide, vguide ;
		bool  yaxis_guide, xaxis_guide ;

		sf::CircleShape anchor ;
		sf::Color       anchor_color, guide_color, line_color ;
		float           anchor_size, line_thickness ;

		void drawAxisAnchors(float, float);
		void drawValueAnchor(float, float);
		void drawAxisGuides(float, float);

	public:
		LineGraph(std::vector<float> const&);
		LineGraph() {}
		LineGraph& operator=(const LineGraph&) = default ;

		void render();
		void setAnchorSize(int s) { anchor_size = s; }
		void setAnchorColor(const sf::Color& c) { anchor_color = c; }
		void setGuideColor(const sf::Color& c) { guide_color = c; }
		void setLineColor(const sf::Color& c) { line_color = c; }
	};

	class MultiLineGraph : public DataGraph<MultiLineGraph>
	{
	    std::vector<std::vector<float>> data ;
	    float gap, start_pos;
		float max, adjust ;
		bool  hguide, vguide ;
		bool  yaxis_guide, xaxis_guide ;

		std::vector<sf::Color>  anchor_color, guide_color, line_color ;
		std::vector<float>      anchor_size, line_thickness ;

		sf::CircleShape anchor ;

		void drawAxisAnchors(float, float, unsigned int);
		void drawValueAnchor(float, float, unsigned int);
		void drawAxisGuides(float, float, unsigned int);

    public:
        MultiLineGraph(const std::vector<std::vector<float>>&,
                       const std::vector<sf::Color>&);

        void render();
        void setLineColor(unsigned int i, const sf::Color& c) { if(i < line_color.size()) line_color[i] = c; }
        void setGuideColor(unsigned int i, const sf::Color& c) { if(i < guide_color.size()) guide_color[i] = c; }
        void setAnchorColor(unsigned int i, const sf::Color& c) { if(i < anchor_color.size()) anchor_color[i] = c; }
	};*/
}


#endif // __BIRCH_LINE_CHART__
