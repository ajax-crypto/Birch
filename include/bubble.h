#ifndef __BUBBLE_BIRCH__
#define __BUBBLE_BIRCH__

#include "base.h"

namespace birch
{
    class BubbleChart : public Chart
    {

    protected:
        std::vector<Triplet> data ;
        float                largest, max ;

    public:
        BubbleChart(const std::vector<Triplet>&, float = 50.f);

        void render() ;
    };
}

#endif // __BUBBLE_BIRCH__
