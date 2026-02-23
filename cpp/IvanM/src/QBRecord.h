// #pragma once  // can be used, but it is not part of ISO C++
#ifndef QB_RECORD_H
#define QB_RECORD_H
#include <cstdint>
#include <string>

/// @brief Represents a single database record
struct QBRecord
{
    QBRecord() = default;
    QBRecord(uint32_t i, uint64_t v, std::string n, std::string d)
    : id(i), value(v), name(std::move(n)), description(std::move(d)) {}
    uint64_t value;          ///< Numeric value associated with the record
    uint32_t id;             ///< Unique record identifier
    std::string name;        ///< Name field
    std::string description; ///< Description field
};

#endif 