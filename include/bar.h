#ifndef __BIRCH_BAR_GRAPH__
#define __BIRCH_BAR_GRAPH__

#include "base.h"

namespace birch
{

    class BarChart : public Chart
    {

    protected:
        std::vector<DataElement> data ;
        sf::RectangleShape bar ;

        float max ;
        float width ;
        float vsize ;

    public:
        BarChart(const std::vector<DataElement>&, bool = true, bool = true);

        void render();

        float gap ;
        unsigned int guides ;
        bool  display_guides ;
        bool  display_values ;

    };

    class MultiBarChart : public Chart
    {

    protected:
        std::vector<std::vector<float>> multi_data ;
        std::vector<std::string>        axes_labels ;
        std::vector<sf::Color>          bar_colors;

        float max ;
        float width ;
        float vsize ;

    public:

        MultiBarChart(const std::vector<std::vector<float>>&,
                      const std::vector<std::string>&,
                      const std::vector<sf::Color>&);

        void render();

        float gap ;
        unsigned int guides ;
        bool  display_guides ;
        bool  display_values ;
    };

    class StackedBarChart : public Chart
    {
        protected:
        std::vector<std::vector<float>> multi_data ;
        std::vector<std::string>        axes_labels ;
        std::vector<sf::Color>          bar_colors;

        float max ;
        float width ;

    public:

        StackedBarChart(const std::vector<std::vector<float>>&,
                    const std::vector<std::string>&,
                    const std::vector<sf::Color>&);

        void render();

        float gap ;
        unsigned int guides ;
        bool  display_guides ;
    };

}

#endif // __BIRCH_BAR_GRAPH__
