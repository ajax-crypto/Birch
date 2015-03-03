#include "..\include\log.h"

 namespace birch
 {
     std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& v)
	{
		stream << "(" << v.x << ", " << v.y << ")" ;
		return stream ;
	}

	std::ostream& operator<<(std::ostream& stream, const sf::Vector2u& v)
	{
		stream << "(" << v.x << ", " << v.y << ")" ;
		return stream ;
	}

	std::ostream& operator<<(std::ostream& stream, const sf::Color& v)
	{
		stream << "(" << (int)v.r << ", " << (int)v.g << ", " << (int)v.b << ")" ;
		return stream ;
	}

	template <typename T> std::string to_string(const T& n)
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
 }
