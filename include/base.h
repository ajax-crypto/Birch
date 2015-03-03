#ifndef __BIRCH_BASE__
#define __BIRCH_BASE__

#include <SFML/Graphics.hpp>
#include "log.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <string>
#include <sstream>

namespace birch
{

    enum Position { LEFT, RIGHT, TOP, BOTTOM };
    enum Shape    { RECTANGULAR, CIRCULAR };
    enum Orientation { HORIZONTAL, VERTICAL };

	sf::RectangleShape MakeRect(sf::Vector2f,
	                            sf::Vector2f,
								float = 1.f);

	void DrawDottedLine(sf::RenderTarget*,
	                    const sf::Vector2f&,
						const sf::Vector2f&,
						const sf::Color&,
						float = 3.f,
						float = 1.f);


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

    /*class DrawingElement
    {

        sf::Shape*    drawable ;
        sf::Text      text ;

    public:
        DrawingElement() {};

        struct {
            float top, bottom, left, right ;
        } margins ;

        struct {
            float thickness ;
            sf::Color color ;
        } border;

        float width, height ;

        void setRectangleShape


        sf::RenderTexture      texture ;

    };*/

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
        void setCenterText(float, float, float, float);

        friend class GraphLegend ;
        friend class GraphBase ;
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
        GraphLegend() : before_text{true},
                        text_matches_key_color{true},
                        bg_color{sf::Color::White},
                        font_color{sf::Color::Black} {}

        void addData(const std::vector<DataFormat>& d) { legend_data = d; }

        void render();
        Orientation                  orientation ;
        bool                         before_text ;
        bool                         text_matches_key_color ;


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

        friend class GraphBase;
    };

	class GraphBase
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

		GraphLegend            legend ;

		GraphBase() :
		    axes_thickness{2.0},
		    screen_bg_color{sf::Color::White},
		    chart_bg_color{sf::Color::White},
		    chart_offsets{ 0.f, 0.f } {};
        GraphBase(const GraphBase&) = default ;

        void setChartBackgroundColor(const sf::Color& c) { chart_bg_color = c; }
        void setScreenBackgroundColor(const sf::Color& c) { screen_bg_color = c; }
        void addTextElement(const sf::Text& t) { text_elements.push_back(t); }
        void setDimensions(float x, float y) { screen_width = x; screen_height = y; }
        void setDefaultLegendMetrics(Position p = BOTTOM) { legend.position = p; }

		void drawAxes(float = 2.f, sf::Color = sf::Color::Black);
		void drawTextElements();
		void drawToScreen(sf::RenderWindow*);
		virtual void render() = 0 ;
	};

	typedef sf::Text TextElement ;

}

#endif // __BIRCH_BASE__