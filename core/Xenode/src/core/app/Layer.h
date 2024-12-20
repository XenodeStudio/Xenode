#pragma once

#include <Core.h>
#include "Events.h"

namespace Xen {
	class XEN_API Layer
	{
	protected:
		uint32_t layerID;
		std::string layerName;

	public:
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float timestep) {}
		virtual void OnFixedUpdate() {}
		virtual void OnRender() {}

		virtual void OnImGuiUpdate() {}

		virtual void OnEvent(Event& event) {}
	};
}