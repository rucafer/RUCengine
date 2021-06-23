#pragma once

#include "Resource.h"

namespace RUC
{
	template <typename T>
	class ResPtr
	{
	public:
		ResPtr()
			:m_ResPointer(nullptr), m_Index(-1)
		{

		}

		template <typename S>
		ResPtr(const ResPtr<S>& other)
			:m_ResPointer((T*)other.m_ResPointer), m_Index(other.m_Index)
		{
			//RUC_INFO("Old refcount (Copy constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
			ResourceManager::s_Metadata[m_Index].RefCount++;
			//RUC_INFO("New refcount (Copy constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
		}

		ResPtr(const ResPtr<T>& other)
			:m_ResPointer(other.m_ResPointer), m_Index(other.m_Index)
		{
			//RUC_INFO("Old refcount (Copy constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
			ResourceManager::s_Metadata[m_Index].RefCount++;
			//RUC_INFO("New refcount (Copy constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
		}

		~ResPtr()
		{
			if (m_Index != -1)
			{
				//RUC_INFO("Old refcount (Destructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
				ResourceManager::s_Metadata[m_Index].RefCount--;
				//RUC_INFO("New refcount (Destructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);

				if (ResourceManager::s_Metadata[m_Index].RefCount == 0 && !(ResourceManager::s_Metadata[m_Index].ResPtr->m_Flags & (char)ResourceFlags::PERSISTENT))
				{
					//RUC_INFO("Object should be destroyed");
					ResourceManager::DeleteResource(m_Index);
				}
			}
		}

		T* operator->()
		{
			return m_ResPointer;
		}

		const T* operator->() const
		{
			return m_ResPointer;
		}

		template <typename S>
		ResPtr<T>& operator=(const ResPtr<S>& other)
		{
			m_ResPointer = (T*)other.m_ResPointer;
			m_Index = other.m_Index;

			//RUC_INFO("Old refcount (Copy) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
			ResourceManager::s_Metadata[m_Index].RefCount++;
			//RUC_INFO("New refcount (Copy) {0}", ResourceManager::s_Metadata[m_Index].RefCount);

			return *this;
		}

		ResPtr<T>& operator=(const ResPtr<T>& other)
		{
			m_ResPointer = other.m_ResPointer;
			m_Index = other.m_Index;

			//RUC_INFO("Old refcount (Copy) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
			ResourceManager::s_Metadata[m_Index].RefCount++;
			//RUC_INFO("New refcount (Copy) {0}", ResourceManager::s_Metadata[m_Index].RefCount);

			return *this;
		}

		template <typename NewType>
		operator ResPtr<NewType>()
		{
			return ResPtr<NewType>((NewType*)m_ResPointer, m_Index);
		}


	private:

		T* GetRawPointer()
		{
			return m_ResPointer;
		}

		ResPtr(T* resource, int index)
			: m_ResPointer(resource), m_Index(index)
		{
			//RUC_INFO("Old refcount (Constructor of {1}) {0}", ResourceManager::s_Metadata[m_Index].RefCount, ResourceManager::s_Metadata[m_Index].ResPtr->GetName());
			ResourceManager::s_Metadata[index].RefCount++;
			//RUC_INFO("New refcount (Constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
		}

	private:
		T* m_ResPointer;
		int m_Index;

		template <typename S>
		friend class ResPtr;

		friend class ResourceManager;
	};
}