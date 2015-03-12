#ifndef __BIRCH_PIE_CHART__
#define __BIRCH_PIE_CHART__

#include "base.h"

namespace birch
{

    enum ExplodeMode { NONE, LARGEST, ALL, SELECTIVE };
    enum PieChartType { NORMAL, POLYGONAL, DONUT };

    class PieChart : public Chart
    {
    protected:
        float total ;
        std::vector<DataElement> data ;

    public:
        PieChart(const std::vector<DataElement>&, ExplodeMode = LARGEST, PieChartType = NORMAL);

        void render();

        bool outline ;
        unsigned int explode_sector ;
        ExplodeMode explode_mode ;
        PieChartType type ;
        float radius ;
        float donut_radius ;

        sf::Vector2f center ;

    };
}

#endif // __BIRCH_PIE_CHART__
