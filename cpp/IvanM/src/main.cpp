#include "RecordCollection.h"
#include <iostream>
#include <cassert>
#include <chrono>
#include <string>

/**
 * -------------------- Unit Tests --------------------
 */

/**
 * Test adding records and duplicate ID prevention
 */
void testDuplicateId() {
    RecordCollection db;

    bool ok1 = db.add({1, 100, "Alice", "First"});
    bool ok2 = db.add({1, 200, "Bob", "Duplicate"}); // should fail

    assert(ok1);
    assert(!ok2);
    assert(db.size() == 1);

    std::cout << "[UnitTest] testDuplicateId passed\n";
}

/**
 * Test adding records and findByColumn basic functionality
 */
void testAddAndFind() {
    RecordCollection db;

    db.add({1, 100, "Alice", "First"});
    db.add({2, 200, "Bob", "Second"});
    db.add({3, 300, "Charlie", "Third"});

    // find by ID
    auto res = db.findByColumn(Column::Id, "2");
    assert(res.size() == 1 && res[0] == 1);

    // find by Name
    res = db.findByColumn(Column::Name, "Alice");
    assert(res.size() == 1 && res[0] == 0);

    // non-existent
    res = db.findByColumn(Column::Description, "Nonexistent");
    assert(res.empty());

    std::cout << "[UnitTest] testAddAndFind passed\n";
}

/**
 * Test deleting records by ID
 */
void testDelete() {
    RecordCollection db;
    db.add({1, 100, "Alice", "First"});
    db.add({2, 200, "Bob", "Second"});

    bool deleted = db.deleteById(1);
    assert(deleted);

    // ensure it's gone
    auto res = db.findByColumn(Column::Id, "1");
    assert(res.empty());

    // deleting non-existent ID
    deleted = db.deleteById(42);
    assert(!deleted);

    std::cout << "[UnitTest] testDelete passed\n";
}

/**
 * Test tryGet optional return
 */
void testTryGet() {
    RecordCollection db;
    db.add({1, 100, "Alice", "First"});
    db.add({2, 200, "Bob", "Second"});

    auto r1 = db.tryGet(0);
    assert(r1.has_value() && r1->get().id == 1);

    auto r2 = db.tryGet(10);
    assert(!r2.has_value());

    std::cout << "[UnitTest] testTryGet passed\n";
}

/**
 * Test findIndices template function
 */
void testFindIndices() {
    RecordCollection db;
    db.add({1, 100, "Alice", "First"});
    db.add({2, 200, "Bob", "Second"});
    db.add({3, 100, "Charlie", "Third"});

    auto indices = db.findIndices([](const Record& r){ return r.value == 100; });
    assert(indices.size() == 2);
    assert(indices[0] == 0 && indices[1] == 2);

    std::cout << "[UnitTest] testFindIndices passed\n";
}

/**
 * Test generic find() template function
 */
void testFindPredicate() {
    RecordCollection db;
    db.add({1, 100, "Alice", "First"});
    db.add({2, 200, "Bob", "Second"});
    db.add({3, 300, "Charlie", "Third"});

    auto results = db.find([](const Record& r){ return r.id >= 2; });
    assert(results.size() == 2);
    assert(results[0].id == 2 && results[1].id == 3);

    std::cout << "[UnitTest] testFindPredicate passed\n";
}

/**
 * Test edge cases for findByColumn
 */
void testFindByColumnEdgeCases() {
    RecordCollection db;
    db.add({1, 100, "Alice", "First"});
    db.add({2, 100, "Bob", "Second"});

    // multiple matches
    auto res = db.findByColumn(Column::Value, "100");
    assert(res.size() == 2);

    // non-existent
    res = db.findByColumn(Column::Name, "Nonexistent");
    assert(res.empty());

    // invalid input parsing
    try {
        res = db.findByColumn(Column::Id, "abc");
    } catch (...) {
        std::cout << "[UnitTest] caught invalid input for ID\n";
    }

    std::cout << "[UnitTest] testFindByColumnEdgeCases passed\n";
}

/**
 * -------------------- Performance Tests --------------------
 */
void extendedPerformanceTest(std::size_t numRecords) {
    RecordCollection db;

    // Populate
    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < numRecords; ++i)
        db.add({static_cast<uint32_t>(i),
                i % 500,
                "Name" + std::to_string(i),
                "Desc" + std::to_string(i)});
    auto end = std::chrono::steady_clock::now();
    std::cout << "[Perf] Inserted " << numRecords << " records in "
              << std::chrono::duration<double>(end-start).count() << "s\n";

    // findByColumn performance
    start = std::chrono::steady_clock::now();
    auto res1 = db.findByColumn(Column::Value, "123");
    end = std::chrono::steady_clock::now();
    std::cout << "[Perf] findByColumn(Value=123) found " << res1.size() << " in "
              << std::chrono::duration<double>(end-start).count() << "s\n";

    // findIndices with predicate
    start = std::chrono::steady_clock::now();
    auto res2 = db.findIndices([](const Record& r){ return r.value == 123; });
    end = std::chrono::steady_clock::now();
    std::cout << "[Perf] findIndices(predicate) found " << res2.size() << " in "
              << std::chrono::duration<double>(end-start).count() << "s\n";

    // Delete first 10k records
    start = std::chrono::steady_clock::now();
    for (uint32_t i = 0; i < 10000 && i < numRecords; ++i)
        db.deleteById(i);
    end = std::chrono::steady_clock::now();
    std::cout << "[Perf] Deleted 10k records in "
              << std::chrono::duration<double>(end-start).count() << "s\n";

    std::cout << "[Perf] Remaining records: " << db.size() << "\n";
}

/**
 * -------------------- Main --------------------
 */
int main() {
    std::cout << "Running Unit Tests...\n";
    testAddAndFind();
    testDelete();
    testDuplicateId();
    testTryGet();
    testFindIndices();
    testFindPredicate();
    testFindByColumnEdgeCases();

    std::cout << "\nRunning Performance Tests...\n";
    extendedPerformanceTest(100000);

    return 0;
}