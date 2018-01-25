#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Hashtable.h"

#include <string>
#include <vector>
#include <iostream>

namespace AEON_ENGINE {

	//Resource Handler
	template<class ResourceType>
	class ResourceHandle
	{
	private:
		int	index;
	public:

		//Default Constructor
		ResourceHandle() : index(-1) {}

		//Constructor to manually set the index of the Handle
		ResourceHandle(int idx) : index(idx) {}

		bool isNull() const
		{
			return index < 0;
		}

		void nullify()
		{
			index = -1;
		}

		int getIndex() const
		{
			return index;
		}

		//Overloaded operators
		ResourceHandle& operator=(ResourceHandle& other)
		{
			index = other.index;
			return *this;
		}

		bool operator==(ResourceHandle& other) const
		{
			return index == other.index;
		}

		bool operator!=(ResourceHandle& other) const
		{
			return index != other.index;
		}

		bool operator<(ResourceHandle& other) const
		{
			return index < other.index;
		}

		friend std::ostream& operator<<(std::ostream& os, ResourceHandle &hndl);
	};

	//Resource Manager
	template<class ResourceType>
	class ResourceManager
	{
	private:
		std::vector<ResourceType*> resourceList;
		Hashtable<std::string, ResourceHandle<ResourceType>> *nameTable;
	public:

		//Default Constructor with default hashtable size
		ResourceManager(void)
		{
			nameTable = new Hashtable<std::string, ResourceHandle<ResourceType>>(111);
		}

		//Constructor with specified size for hastable
		ResourceManager(int sz)
		{
			nameTable = new Hashtable<std::string, ResourceHandle<ResourceType>>(sz);
		}

		//Destructor -- This will not delete any of the resources stored in the ResourceManager
		~ResourceManager(void)
		{
			if (nameTable != NULL)
			{
				delete nameTable;
				nameTable = NULL;
			}
		}

		//Adds a resource to the ResourceManager
		//If a resource already exists in the manager it is neither added again or overwritten.
		ResourceHandle<ResourceType> put(std::string &name, ResourceType *res)
		{
			Hashtable<std::string, ResourceHandle<ResourceType>>::iterator	iter;
			int key = Hashtable<std::string, ResourceHandle<ResourceType>>::stringhash(name);

			iter = nameTable->get(key);
			if (iter == nameTable->end())
			{
				int idx = resourceList.size();
				resourceList.push_back(res);
				ResourceHandle<ResourceType> handle(idx);
				HashItem<std::string, ResourceHandle<ResourceType>> item(key, name, handle);
				nameTable->put(item);
				return handle;
			}
			return (*iter).getValue();
		}

		//Returns the pointer to the resource of the handle passed
		ResourceType* get(ResourceHandle<ResourceType> &handle) const
		{
			int idx = handle.getIndex();
			ResourceType *result = NULL;

			if (idx >= 0 && idx < int(resourceList.size()))
			{
				result = resourceList[idx];
			}
			return result;
		}

		//Returns the pointer to the resource of the string passed
		ResourceHandle<ResourceType> get(const std::string &name) const
		{
			Hashtable<std::string, ResourceHandle<ResourceType>>::iterator	iter;
			int key = Hashtable<std::string, ResourceHandle<ResourceType>>::stringhash((std::string)name);

			iter = nameTable->get(key);
			if (iter == nameTable->end())
			{
				return ResourceHandle<ResourceType>();
			}
			return (*iter).getValue();
		}

		//Remove resource based on string passed
		void remove(std::string &name)
		{
			Hashtable<std::string, ResourceHandle<ResourceType>>::iterator	iter;
			int key = Hashtable<std::string, ResourceHandle<ResourceType>>::stringhash(name);

			iter = nameTable->get(key);
			if (iter != nameTable->end())
			{
				int idx = (*iter).getValue().getIndex();
				resourceList[idx] = NULL;
				nameTable->remove(key);
			}
		}

		//Remove all keys and values
		void clearKeysAndValues()
		{
			std::vector<int>	deleteKeyList;
			Hashtable<std::string, ResourceHandle<ResourceType> >::iterator	iter = nameTable->begin();

			/////////////////////////////////////////////////////
			// First, we traverse the hashtable and delete the models.
			// We save the string keys to be deleted and delete these
			// on a second pass so we do not mess with the iterator.
			/////////////////////////////////////////////////////
			while (iter != nameTable->end())
			{
				HashItem<std::string, ResourceHandle<ResourceType> > item = *iter;
				ResourceHandle<ResourceType> handle = item.getValue();
				if (!handle.isNull())
				{
					ResourceType *res = resourceList[handle.getIndex()];
					if (res != NULL)
					{
						delete res;
						resourceList[handle.getIndex()] = NULL;
					}
					deleteKeyList.push_back(item.getKey());
				}
				iter++;
			}

			std::vector<int>::iterator viter = deleteKeyList.begin();
			while (viter != deleteKeyList.end())
			{
				int ke = *viter;
				nameTable->remove(ke);
				viter++;
			}

			////////////////////////////////////////////////////////
			// Now, clear the resource list so it does not grow forever
			////////////////////////////////////////////////////////
			resourceList.clear();
		}

		void realityCheck(std::string& msg)
		{
			nameTable->realityCheck(msg);
		}

	};

	template<class ResourceType>
	std::ostream& operator<<(std::ostream& os, ResourceHandle<ResourceType> &hndl)
	{
		os << hndl.index;
		return os;
	}

}

#endif