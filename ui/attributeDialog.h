#pragma once

#include "component.h"

namespace ui
{
	class AttributeDialog : public ui::Component
	{
	public:
		void render() override;
		void isShow(bool* is_show);

	private:
		float width_ = 400;
		float height_ = 600;
		bool* is_show_;
	};
}