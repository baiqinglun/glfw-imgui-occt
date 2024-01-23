#pragma once

#include "component.h"

namespace ui
{
	class AttributeDialog : public ui::Component
	{
	public:
		void render() override;

	private:
		float width_ = 400;
		float height_ = 600;
	};
}