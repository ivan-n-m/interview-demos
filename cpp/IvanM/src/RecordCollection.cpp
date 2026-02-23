#include "RecordCollection.h"
#include <utility>



bool RecordCollection::add(const Record& record) {   
     if (m_id_index.contains(record.id))
        return false;

    m_records.push_back(record);
    m_id_index[record.id] = m_records.size() - 1;

    return true;
}

Indexes RecordCollection::findByColumn(Column column, std::string_view value) const
{
    Indexes result;

    switch (column)
    {
        case Column::Id:
        {
            // parse string_view -> uint32_t
            uint32_t id = static_cast<uint32_t>(std::stoul(std::string(value)));

            auto it = m_id_index.find(id);
            if (it != m_id_index.end())
                result.push_back(it->second);

            break;
        }

        case Column::Value:
        {
            uint64_t v = static_cast<uint64_t>(std::stoull(std::string(value)));

            for (std::size_t i = 0; i < m_records.size(); ++i)
                if (m_records[i].value == v)
                    result.push_back(i);

            break;
        }

        case Column::Name:
        {
            for (std::size_t i = 0; i < m_records.size(); ++i)
                if (m_records[i].name == value)
                    result.push_back(i);

            break;
        }

        case Column::Description:
        {
            for (std::size_t i = 0; i < m_records.size(); ++i)
                if (m_records[i].description == value)
                    result.push_back(i);

            break;
        }
    }

    return result;
}

bool RecordCollection::deleteById(uint32_t id) noexcept
{
    auto it = m_id_index.find(id);
    if (it == m_id_index.end())
        return false;

    size_t index = it->second;

    std::swap(m_records[index], m_records.back());

    m_id_index[m_records[index].id] = index;

    m_records.pop_back();
    m_id_index.erase(it);

    return true;
}

// an exception may be thrown
const Record& RecordCollection::getRecord(std::size_t index) const
{
    return m_records.at(index); 
}

// an exception may be thrown
Record& RecordCollection::getRecord(std::size_t index)
{
    return m_records.at(index);
}


std::optional<std::reference_wrapper<const Record>> RecordCollection::tryGet(std::size_t index) const
{
    if (index >= m_records.size())
        return std::nullopt;

    return m_records[index];
}


std::optional<std::reference_wrapper<Record>> RecordCollection::tryGet(std::size_t index)
{
    if (index >= m_records.size())
        return std::nullopt;

    return m_records[index];
}

size_t RecordCollection::size() const noexcept {
    return m_records.size();
}



