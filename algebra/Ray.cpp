#include "Ray.h"

std::ostream & operator<<(std::ostream & out, const Ray & r)
{
	out << "o: " << r.o << " d: " << r.d;
	return out;
}
