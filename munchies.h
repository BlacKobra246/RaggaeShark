#ifndef MUNCHIES_H
#define MUNCHIES_H
#include "utillities.h"

class Munchies
{
	Vector2 pos;
	Texture2D munchies;

	public:

	Munchies();
	~Munchies();
	void draw();
	Vector2 generateRandomPos() const;
	Vector2 getPos() const;
	void setNewPos();
};

#endif //MUNCHIES_H