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
		float vsize ;

	public:
		BarGraph(const std::vector<DataElement>&, bool = true, bool = true);

		void render();

		float gap ;
        bool  display_values ;

	};

	class MultiBarGraph : public GraphBase
	{

    protected:
		std::vector<std::vector<float>> multi_data ;
		std::vector<std::string>        axes_labels ;
		std::vector<sf::Color>          bar_colors;

		float max ;
		float width ;
		float vsize ;

	public:

		MultiBarGraph(const std::vector<std::vector<float>>&,
                      const std::vector<std::string>&,
                      const std::vector<sf::Color>&);

		void render();

        float gap ;
		bool display_values ;
	};

}

#endif // __BIRCH_BAR_GRAPH__
