#pragma once

#include "Eigen/Core"
#include "Object.h"
#include "Ball.h"

class Plane : public BaseObject<Plane> 
{
public:
	static ptr_t Plane::make(Vec_t normal, Vec_t position, float friction_factor, Color color = Color::GRAY)
	{
		return std::make_shared<Plane>(normal, position, friction_factor, color, this_is_protected());
	}
	
	Plane(Vec_t normal, Vec_t position, float friction_factor, Color color, this_is_protected&)
		: normal_(normal)
		, position_(position)
		, friction_factor_(friction_factor)
		, color_(color)
	{}

	Plane() = delete;
	Plane(const Plane&) = delete;
	Plane& operator=(const Plane&) = delete;

	void try_collision(base_ptr_t other) override
	{
		/*mBallHasRestingContact = false;
		float vrel = mNormal*ball->mVelocity;

		MyVector p_q = ball->mPos - mPointinplane;
		float project = p_q * mNormal;

		float penetration = ball->mR - project; //hur l�ngt ner i planet vi �r

		if (penetration >= 0) //Vi �r inne i planet eller exakt p�
		{
			if (vrel < -1)//vi �r p� v�g in i planet med fart (notera att den SMALLTHRESHOLD var f�r liten)
			{
				MyVector newVelocity = ball->mVelocity - mNormal * (1 + elasticy) * vrel;
				ball->mVelocity = newVelocity;
			}
			else if (vrel < 1)// VILANDE KONTAKT
			{
				MyVector moveUp = mNormal*penetration;
				ball->mPos += moveUp;
				ball->mVelocity -= mNormal * vrel;
				//all r�relse �r nu i planet s� vi kan motverka den
				ball->addForce(ball->mVelocity * -10 * ball->mMass * mFrictionFactor);//OBS. inte fysikaliskt korrekt friktion
				mBallHasRestingContact = true;
			}
			else{//vi �r p� v�g ur planet med fart

			}
		}*/
	}

	void render(DemoHandler& demo) const override
	{
		demo.drawPlane(vector_to_point(position_), vector_to_point(normal_), color_);
	}

	void update(float dt) override
	{

	}

private:
	Vec_t position_;
	Vec_t normal_;
	float friction_factor_; 
	Color color_;
};