#ifndef MATH_COLOR_H_
#define MATH_COLOR_H_

namespace g2e {
namespace math {

class Color {
public:
	Color() : Color(0.0f, 0.0f, 0.0f) {}
	Color(double, double, double);
	virtual ~Color();

	double red, green, blue;

//	static Color BLACK = 	Color(0.0f, 0.0f, 0.0f);
//	static Color WHITE = 	Color(1.0f, 1.0f, 1.0f);
//	static Color GREY = 	Color(0.5f, 0.5f, 0.5f);
//	static Color RED = 		Color(1.0f, 0.0f, 0.0f);
//	static Color GREEN = 	Color(0.0f, 1.0f, 0.0f);
//	static Color BLUE = 	Color(0.0f, 0.0f, 1.0f);
};

} /* namespace math */
} /* namespace g2e */

#endif /* MATH_COLOR_H_ */
