#pragma once

#include <string>

namespace RUC
{

	class Layer
	{
	public:
		Layer(const std::string& name);
		~Layer() = default;

		void OnAttach();
		void OnDetach();

		void OnUpdate();
	private:
		const std::string m_Name;
	};

}