#ifndef __BIRCH_LINE_CHART__
#define __BIRCH_LINE_CHART__

#include "base.h"

namespace birch
{
    class LineChart : public Chart
    {
    protected:
        std::vector<DataElement> data ;
        float gap, start_pos;
        float max ;
        bool  hguide, vguide ;
        bool  yaxis_guide, xaxis_guide ;

        sf::CircleShape anchor ;

        void drawAxisAnchors(float, float);
        void drawValueAnchor(float, float, const sf::Color&);
        void drawAxisGuides(float, float);

    public:
        LineChart(std::vector<DataElement> const&);
        LineChart() {}

        void render();
        sf::Color       anchor_color, guide_color, line_color ;
        float           anchor_size, line_thickness ;
        bool  display_guides ;
        bool  display_values ;
    };

    class MultiLineChart : public Chart
    {
        std::vector<std::vector<float>> data ;
        std::vector<sf::Color>          colors ;
        std::vector<std::string>        axes_labels ;
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
        MultiLineChart(const std::vector<std::vector<float>>&,
                       const std::vector<std::string>&,
                       const std::vector<sf::Color>&);

        bool  display_guides ;
        bool  display_values ;

        void render();
        void setLineColor(unsigned int i, const sf::Color& c) { if(i < line_color.size()) line_color[i] = c; }
        void setGuideColor(unsigned int i, const sf::Color& c) { if(i < guide_color.size()) guide_color[i] = c; }
        void setAnchorColor(unsigned int i, const sf::Color& c) { if(i < anchor_color.size()) anchor_color[i] = c; }
    };
}


#endif // __BIRCH_LINE_CHART__
