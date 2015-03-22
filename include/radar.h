#ifndef __BIRCH_RADAR_CHART__
#define __BIRCH_RADAR_CHART__

#include "base.h"

namespace birch
{
    class RadarChart : public Chart
    {

    protected:
        std::vector<DataElement> data ;
        float radius ;

    public:
        RadarChart(const std::vector<DataElement>& d, float r);

        void render();

        float guide_thickness, plot_thickness, point_radius ;
        bool  dotted_plot, dotted_guide ;

    };
}


#endif // __BIRCH_RADAR_CHART__
