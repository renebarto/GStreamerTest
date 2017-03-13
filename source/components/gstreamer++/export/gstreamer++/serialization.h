#pragma once

#include <string>
#include <vector>

namespace GStreamer
{

template<typename EnumType>
struct EnumConversion
{
    EnumType value;
    const char * name;
};

template<typename EnumType>
struct EnumSerializationInfo
{
public:
    EnumSerializationInfo() {}
    EnumSerializationInfo(const EnumSerializationInfo &) = delete;
    EnumSerializationInfo & operator = (const EnumSerializationInfo &) = delete;

    static std::string Serialize(EnumType value)
    {
        for (const auto & item : Info)
        {
            if (item.value == value)
                return item.name;
        }
        return std::string{};
    }
private:
    static std::vector<EnumConversion<EnumType>> Info;
};

template<typename EnumType>
std::string Serialize(const EnumType & value)
{
    return EnumSerializationInfo<EnumType>::Serialize(value);
}

} // namespace GStreamer
