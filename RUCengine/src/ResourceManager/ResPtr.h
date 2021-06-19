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
			RUC_INFO("Old refcount (Copy constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
			ResourceManager::s_Metadata[m_Index].RefCount++;
			RUC_INFO("New refcount (Copy constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
		}

		ResPtr(const ResPtr<T>& other)
			:m_ResPointer(other.m_ResPointer), m_Index(other.m_Index)
		{
			RUC_INFO("Old refcount (Copy constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
			ResourceManager::s_Metadata[m_Index].RefCount++;
			RUC_INFO("New refcount (Copy constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
		}

		~ResPtr()
		{
			if (m_Index != -1)
			{
				RUC_INFO("Old refcount (Destructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
				ResourceManager::s_Metadata[m_Index].RefCount--;
				RUC_INFO("New refcount (Destructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);

				if (ResourceManager::s_Metadata[m_Index].RefCount == 0)
				{
					RUC_INFO("Object should be destroyed");
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

			RUC_INFO("Old refcount (Copy) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
			ResourceManager::s_Metadata[m_Index].RefCount++;
			RUC_INFO("New refcount (Copy) {0}", ResourceManager::s_Metadata[m_Index].RefCount);

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
			RUC_INFO("Old refcount (Constructor of {1}) {0}", ResourceManager::s_Metadata[m_Index].RefCount, ResourceManager::s_Metadata[m_Index].ResPtr->GetName());
			ResourceManager::s_Metadata[index].RefCount++;
			RUC_INFO("New refcount (Constructor) {0}", ResourceManager::s_Metadata[m_Index].RefCount);
		}

	private:
		T* m_ResPointer;
		int m_Index;

		template <typename S>
		friend class ResPtr;

		friend class ResourceManager;
	};


	/*template <typename T>
	class ResPtr
	{
	public:
		ResPtr(const ResPtr<T>& other)
			:m_Resource(other.m_Resource)
		{
			//Increase refCount, a new pointer was created
			m_Resource->m_RefCount++;
		}

		ResPtr<T>& operator=(const ResPtr<T>& other)
		{
			m_Resource = nullptr;

			//Increase refCount, a new pointer was created
			//m_Resource->m_RefCount++;

			return *this;
		}

		ResPtr<Resource> getBasePointer()
		{
			return ResPtr((Resource*)m_Resource,)
		}

		~ResPtr()
		{
			int refCount = --m_Resource->m_RefCount;

			if (refCount == 0)
			{
				delete m_Resource;
			}
		}

		T* Get() const
		{
			return m_Resource;
		}

		//Cast a Resource ResPtr to a T ResPtr
		static ResPtr<T> Cast(const ResPtr<Resource>& other)
		{
			return ResPtr<T>(dynamic_cast<T*>(other.Get()));
		}

	private:

		ResPtr(Resource* resource, char flags)
			: m_Resource(resource)
		{
			RUC_ASSERT(resource->m_RefCount == 0, "A pointer to the given resource already exists. Use a copy of that ResPtr instead of creating another one");

			m_Resource->m_Flags = flags;
		}
		
		ResPtr(T* resource)
			: m_Resource(resource)
		{
		}

		ResPtr()
		{
			m_Resource = nullptr;
		}



	private:
		T* m_Resource;

		friend class ResourceManager;
	};*/
}