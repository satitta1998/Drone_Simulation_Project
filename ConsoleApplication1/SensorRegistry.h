#ifndef __SensorRegistry_h__
#define __SensorRegistry_h__

#include "Sensor.h"
#include <memory>
#include <map>
#include <typeindex>


namespace jb
{
struct SensorInfo
{
	std::unique_ptr<Sensor> instance;
	std::string key;
};

inline std::map<std::type_index, SensorInfo> sensorRegistry;

template<typename T>
void registerSensor(const std::string& key)
{
	sensorRegistry[typeid(T)] = { std::make_unique<T>(), key };
}

inline Sensor* getSensorPtr(const std::string& key)
{
	for (const std::pair<const std::type_index, SensorInfo>& item : sensorRegistry)
	{
		if (item.second.key == key)
		{
			return item.second.instance.get();
		}
	}
	return nullptr;
}

} // jb
#endif
