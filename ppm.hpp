#pragma once

#include <array>
#include <iostream>
#include <limits>

namespace ppm{
	typedef std::array<unsigned char, 3> pixel;
	template<std::size_t rows, std::size_t columns>
	using image = std::array<std::array<pixel, columns>, rows>;
};

template<std::size_t rows, std::size_t columns>
std::ostream& operator<<(
	std::ostream& os,
	const ppm::image<rows, columns>& img
){
	os << "P6\n"
	   << std::to_string(columns)
	   << ' '
	   << std::to_string(rows)
	   << '\n'
	   << std::to_string(std::numeric_limits<unsigned char>::max())
	   << '\n';
	for(auto& i: img) for(auto& j: i) for(auto& c: j) os << c;
	return os;
}

template<std::size_t rows, std::size_t columns>
std::istream& operator>>(
	std::istream& is,
	ppm::image<rows, columns>& img
){
	std::string burn;
	for(auto i = 0; i < 4; i++) is >> burn;
	is.get(); // idk why this is needed
	for(auto& i: img) for(auto& j: i) for(auto& c: j) c = is.get();
	return is;
}
