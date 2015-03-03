#ifndef __BIRCH_BAR_GRAPH__
#define __BIRCH_BAR_GRAPH__

#include "base.h"

namespace birch
{

    class BarGraph : public GraphBase
    {

    protected:
		std::vector<DataElement> data ;
		sf::RectangleShape bar ;

		float max ;
		float width ;

	public:
		BarGraph(const std::vector<DataElement>&, bool = true);

		void render();

		float gap ;
        bool  display_values ;

	};

	class MultiBarGraph : public GraphBase
	{

    protected:
		std::vector<std::vector<float>> multi_data ;
		std::vector<DataFormat>         data ;

		float gap ;
		float max ;
		float width ;

	public:

		MultiBarGraph(const std::vector<std::vector<float>>&,
                      const std::vector<DataFormat>&);

		void render();
		void setGap(float g) { gap = g; }
	};

}

#endif // __BIRCH_BAR_GRAPH__
