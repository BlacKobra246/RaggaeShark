#ifndef RAGGAE_SHARK_H
#define RAGGAE_SHARK_H	
#include "utillities.h"

class RaggaeShark
{
	Texture2D chill_L, chill_R, chill_U, chill_D;
	Texture2D eat_L, eat_R, eat_U, eat_D;
	char facingDir;

	public:
		RaggaeShark();
		~RaggaeShark();
		void draw(bool eating);
		void update(bool eating);
		void setFacing(char facing);
		char getFacing() const;
		void centerTail(float* x, float* y) const;
		Vector2 getLocation() const;
		bool hitHimself() const;

		deque<Vector2> body = { Vector2{6,9},Vector2{5,9},Vector2{4,9} };
		Vector2 dir = { 1,0 };
};


#endif //RAGGAE_SHARK_H