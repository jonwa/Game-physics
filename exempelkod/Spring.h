#pragma once

#include "Eigen/Core"
#include "Object.h"

class Spring : public BaseObject<Spring>
{
public:

	static ptr_t make();

	Spring(this_is_protected&)
	{}

	Spring() = delete;
	Spring(const Spring&) = delete;
	Spring& operator=(const Spring&) = delete;

	void try_collision(base_ptr_t other) override
	{

	}

	void render(DemoHandler& demo) const override
	{

	}

	void update(float dt) override
	{
	
	}

private:
	
};