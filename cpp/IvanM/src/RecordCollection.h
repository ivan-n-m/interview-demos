#ifndef RECORD_COLLECTION_H
#define RECORD_COLLECTION_H

#include "QBRecord.h"
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <string_view>
#include <optional>
#include <type_traits>
#include <algorithm>

/// @brief Collection of QBRecord objects with indexing and search support
enum class Column
{
    Id,
    Value,
    Name,
    Description
};

using QBRecordCollection = std::vector<QBRecord>;
using Record = QBRecord;
using Indexes = std::vector<size_t>;

class RecordCollection
{
public:
    /// @brief Adds a record to the collection
    /// @param record The record to add
    /// @return true if added, false if duplicate id exists
    bool add(const Record& record);

    /// @brief Deletes a record by its unique id
    /// @param id The id of the record to delete
    /// @return true if deleted, false if not found
    bool deleteById(std::uint32_t id) noexcept;

    /// @brief Finds all records matching a predicate
    /// @tparam Predicate Callable that returns bool for a record
    /// @param pred The predicate function
    /// @return Collection of records that match
    template<typename Predicate>
    QBRecordCollection find(Predicate pred) const
    {
        QBRecordCollection result;
        std::copy_if(m_records.begin(),
                     m_records.end(),
                     std::back_inserter(result),
                     pred);
        return result;
    }

    /// @brief Finds indices of all records matching a predicate
    /// @tparam Predicate Callable that returns bool for a record
    /// @param pred The predicate function
    /// @return Vector of indices
    template<typename Predicate>
    Indexes findIndices(Predicate pred) const
    {
        Indexes result;
        result.reserve(m_records.size()); 

        for (std::size_t i = 0; i < m_records.size(); ++i)
        {
            if (pred(m_records[i]))
                result.push_back(i);
        }

        return result;
    }

    /// @brief Finds indices of records by specific column value
    /// @param column The column to search in
    /// @param value Value to match
    /// @return Vector of indices
    Indexes findByColumn(Column column, std::string_view) const;

    /// @brief Gets a record by index (throws std::out_of_range if invalid)
    const Record& getRecord(std::size_t index) const;
    Record& getRecord(std::size_t index);

    /// @brief Tries to get a record by index (returns nullopt if invalid)
    std::optional<std::reference_wrapper<const Record>>tryGet(std::size_t index) const;
    std::optional<std::reference_wrapper<Record>> tryGet(std::size_t index);

    /// @brief Returns current number of records
    /// @return size_t number of records
    size_t size() const noexcept;

private:
    QBRecordCollection m_records;
    std::unordered_map<std::uint32_t, std::size_t> m_id_index;
};

#endif