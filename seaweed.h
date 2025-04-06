#ifndef SEA_WEED_H
#define SEA_WEED_H
#include "utillities.h"

class Seaweed 
{
	Texture2D firstAnimation, secondAnimation;
	unsigned int ticks, animationState, Random_X_Cords;

	public:
		Seaweed();
		~Seaweed();
		void draw() const;
		void Animation(int speedUp);
};


#endif //SEA_WEED_H