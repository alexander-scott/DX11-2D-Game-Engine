#pragma once

#include <map>
#include <memory>

class PersistentValueInterface
{
public:
	virtual ~PersistentValueInterface() = 0;
};
inline PersistentValueInterface::~PersistentValueInterface() {}

template<class T>
class PersistentValue : public PersistentValueInterface
{
public:
	typedef T Type;
	explicit PersistentValue(const Type& data) : data(data) {}
	PersistentValue() {}
	Type data;
};

class ScenePersistentValues
{
public:
	template<class T>
	T GetValue(std::string s)
	{
		return dynamic_cast<PersistentValue<T>&>(*Instance().Values[s]).data;
	}

	template<class T>
	T* GetPointer(std::string s)
	{
		return dynamic_cast<PersistentValue<T>*>(*Instance().Values[s]);
	}

	template<class T>
	T& GetRef(std::string s)
	{
		return dynamic_cast<PersistentValue<T>&>(*Instance().Values[s]).data;
	}

	static ScenePersistentValues& Instance()
	{
		static ScenePersistentValues Instance;
		return Instance;
	}

	std::map<std::string, std::unique_ptr<PersistentValueInterface>> Values;
};