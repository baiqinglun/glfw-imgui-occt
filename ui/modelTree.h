#pragma once

#include "component.h"

namespace ui
{
	class ModelTree : public ui::Component
	{
	public:
		void render() override;
		ModelTree();
	};
}