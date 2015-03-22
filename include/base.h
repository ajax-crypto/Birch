#ifndef __BIRCH_BASE__
#define __BIRCH_BASE__

#include "graphics.h"
#include "log.h"
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#include <iomanip>

namespace birch
{

    unsigned int    DigitCount(float);

    struct DataFormat
    {
        std::string name ;
        sf::Color   color ;

        DataFormat(const std::string& n, const sf::Color& c)
        : name{n}, color{c} {}
    };

    struct DataElement : public DataFormat
    {
        float       value ;

        bool operator<(const DataElement& e) const
        {
            return value < e.value ;
        }

        DataElement(float v, const std::string& n, const sf::Color& c)
        : DataFormat{n, c}, value{v} {}
    };

    struct RangedDataElement : public DataFormat
    {
        float       value, high, low ;

        bool operator<(const DataElement& e) const
        {
            return value < e.value ;
        }
    };

    class GraphLegendUnit
    {

    protected:
        sf::Shape*          shape ;
        sf::Text            text ;
        Shape               shape_type ;

    public:
        GraphLegendUnit() : shape{nullptr} {}
        GraphLegendUnit(float, float, const sf::Color&, const std::string&);
        GraphLegendUnit(float, const sf::Color&, const std::string&);

        void setRectangleShape(float, float, const sf::Color&) ;
        void setCircleShape(float, const sf::Color&) ;
        void setOutlineThickness(float x) { shape->setOutlineThickness(x); }
        void setOutlineColor(const sf::Color &c) { shape->setOutlineColor(c); }
        void setString(const std::string& str) { text.setString(str); }
        void setTextColor(const sf::Color &c) { text.setColor(c); }
        std::string getString() const { return text.getString(); }

        friend class GraphLegend ;
        friend class Chart ;
    };

    class GraphLegend
    {

    protected:
        std::vector<GraphLegendUnit> legend ;
        std::vector<DataFormat>      legend_data ;
        sf::RenderTexture            texture ;
        float                        font_size ;

        unsigned int                 getLongestName() const ;
        void                         createLegendObjects();

    public:
        GraphLegend() :
            exists{true},
            before_text{true},
            text_matches_key_color{true},
            bg_color{sf::Color::White},
            font_color{sf::Color::Black} {}

        void addData(const std::vector<DataFormat>& d) { legend_data = d; }

        void render();
        Orientation                  orientation ;
        bool                         before_text ;
        bool                         text_matches_key_color ;
        bool                         exists ;


        float                        height, width ;
        float                        x, y ;
        Position                     position ;
        Shape                        key_shape ;
        sf::Font                     font ;
        sf::Color                    bg_color, font_color ;

        union {
            struct {
                float height, width ;
            };
            float radius ;
        } shape ;

        friend class Chart;
    };

    class Chart
    {

    protected:
        sf::RenderTexture chart_texture ;
        sf::RenderTexture screen_texture ;
        sf::RenderTexture legend_texture ;

        sf::Color         screen_bg_color ;
        sf::Color         chart_bg_color ;

        std::vector<sf::Text>     text_elements ;

        void copyToScreen(sf::RenderWindow*);
        void createTexture();
        void createLegendMetrics();
        void loadFonts();

    public:

        float chart_height, chart_width ;
        float screen_height, screen_width ;

        float axes_thickness ;

        struct {
            float x, y ;
        } chart_offsets ;

        struct {
            float top, bottom, right, left ;
        } screen_margins ;

        struct {
            float thickness ;
            sf::Color color ;
            struct {
                float font_size ;
                sf::Color font_color, bg_color ;
                sf::Font font ;
            } labels;
        } axes;

        GraphLegend            legend ;

        Chart() :
            screen_bg_color{sf::Color::White},
            chart_bg_color{sf::Color::White},
            chart_offsets{ 0.f, 0.f },
            axes{2.f, sf::Color::Black, {
                15.f, sf::Color::Black, sf::Color::White,
                sf::Font()
            }} {};

        Chart(const Chart&) = default ;

        void setChartBackgroundColor(const sf::Color& c) { chart_bg_color = c; }
        void setScreenBackgroundColor(const sf::Color& c) { screen_bg_color = c; }
        void addTextElement(const sf::Text& t) { text_elements.push_back(t); }
        void setDimensions(float x, float y) { screen_width = x; screen_height = y; }
        void setDefaultLegendMetrics(Position p = LEFT) { legend.position = p; }

        void drawAxes();
        void drawTextElements();
        void drawToScreen(sf::RenderWindow*);
        virtual void render() = 0 ;
    };

    typedef sf::Text TextElement ;

}

#endif // __BIRCH_BASE__
