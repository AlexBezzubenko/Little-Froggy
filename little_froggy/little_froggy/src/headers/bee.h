#ifndef BEE_H
#define BEE_H
#include <SFML/Graphics.hpp>
#include "fly.h"

using namespace sf;
class Bee : public Fly{
public:
	Bee::Bee();
	Bee::Bee(Texture &image, const IntRect intrects[]);
};
#endif