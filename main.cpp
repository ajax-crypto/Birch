#include "include\birch.h"
#include <thread>
#include <chrono>
#include <cstdlib>

void DrawOnScreen(birch::GraphBase* graph)
{
    sf::ContextSettings settings ;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Plotting", sf::Style::Default, settings);

    graph->chart_offsets.x = 2 ;
	graph->chart_offsets.y = 2 ;
	graph->setDimensions(400, 300);
	graph->screen_margins.top = 25 ;
	graph->screen_margins.bottom = 25 ;
	graph->screen_margins.left = 25 ;
	graph->screen_margins.right = 25 ;
	graph->setDefaultLegendMetrics();

	window.clear(sf::Color(255, 255, 255));
	graph->drawToScreen(&window);
	window.display();

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			else if(event.type == sf::Event::KeyPressed)
				if(event.key.code == sf::Keyboard::Escape)
					window.close();
        }
		//window.clear(sf::Color(255, 255, 255));
        //window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


void Demo()
{
    char option ;
    birch::GraphBase* graph ;

	do
    {
        std::cout << "Which graph do you want to see ?\n";
        std::cout << "1. Bar Graph\n";
        std::cout << "2. Multi Bar Graph\n";
        std::cout << "3. Histogram\n";
        std::cout << "4. Line Graph\n";
        std::cout << "5. Pie Chart\n";
        std::cout << "6. Radar Graph\n";
        std::cout << "7. Multi Line Graph\n";
        std::cout << "Enter your option [1-6] : ";
        std::cin >> option ;

        switch(option)
        {
        case '1':
            graph = new birch::BarGraph(std::vector<birch::DataElement>
                                        { birch::DataElement{ 23, "AAA", sf::Color(255, 105, 97) },
                                          birch::DataElement{ 14, "BBB", sf::Color(255, 179, 71) },
                                          birch::DataElement{ 33, "CCC", sf::Color(119, 190, 119) },
                                          birch::DataElement{ 12, "DDD", sf::Color(150, 111, 214) }
                                        }, true);
            break;

        case '2':
            graph = new birch::MultiBarGraph(
                    { { 20, 20 }, { 35, 56 }, { 12, 17 }, { 23, 29 } },
                    { { "AAA", sf::Color(50, 200, 50) }, { "BBB", sf::Color(50, 50, 200)} });
            graph->legend.addData({ { "AAA", sf::Color(50, 200, 50) }, { "BBB", sf::Color(50, 50, 200) } });
            break;

        /*
        case '3':
            graph = new birch::Histogram({
                      std::make_tuple(23, 0, 10),
                      std::make_tuple(12, 10, 20),
                      std::make_tuple(15, 20, 30),
                      std::make_tuple(45, 30, 40),
                      std::make_tuple(25, 40, 50),
                      std::make_tuple(26, 50, 60)
                     },
                    { sf::Color(0, 204, 102),
                      sf::Color(0, 102, 204),
                      sf::Color(153, 153, 0),
                      sf::Color(255, 51, 153),
                      sf::Color(102, 51, 0),
                      sf::Color(255, 255, 0)
                    });
            break;

        case '4':
            graph = new birch::LineGraph({ 23, 45, 18, 16, 33 });
            break;

        case '5':
            graph = new birch::PieChart({ 23, 45, 12, 42, 32 },
                    {sf::Color(0, 204, 102),
                     sf::Color(0, 102, 204),
                     sf::Color(153, 153, 0),
                     sf::Color(255, 51, 153),
                     sf::Color(102, 51, 0),
                     sf::Color(255, 255, 0) });
            std::cout << "Pie chart is polygonal ? (y/n) ";
            std::cin >> option ;
            dynamic_cast<birch::PieChart*>(graph)->setPolygonal(option == 'y');
            break ;

        case '6':
            graph = new birch::RadarGraph({ 23, 45, 26, 36, 20, 14, 19, 31 }, 100);
            std::cout << "Plot line is dotted ? (y/n) ";
            std::cin >> option ;
            dynamic_cast<birch::RadarGraph*>(graph)->makePlotLineDotted(option == 'y');
            break;

        case '7':
            graph = new birch::MultiLineGraph(
                    { { 20, 20 }, { 35, 56 }, { 17, 12 }, { 23, 29 } },
                    { sf::Color(50, 200, 50), sf::Color(50, 50, 200) });
            break ;
        */
        default:
            return;
        }


        DrawOnScreen(graph); // this actually draws the screen
        std::cin.get();
        std::cin.get();
        // Clear screen
        for(int i = 0; i < 1000; ++i)
            std::cout << "\n" ;

    }while(true);
}

int main()
{
    std::thread t(Demo);
	t.join();
    return 0;
}