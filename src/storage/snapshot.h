//
// snapshot.h
// Copyright (C) 2017 4paradigm.com
// Author vagrant
// Date 2017-07-24
//


#ifndef RTIDB_SNAPSHOT_H
#define RTIDB_SNAPSHOT_H

#include <vector>
#include <atomic>
#include "log/log_reader.h"
#include "proto/tablet.pb.h"
#include "boost/atomic.hpp"
#include "base/count_down_latch.h"
#include "storage/table.h"
#include "log/log_writer.h"
#include "log/sequential_file.h"

using ::rtidb::api::LogEntry;
namespace rtidb {
namespace base {
class Status;
}
namespace storage {

using ::rtidb::log::WriteHandle;


typedef ::rtidb::base::Skiplist<uint32_t, uint64_t, ::rtidb::base::DefaultComparator> LogParts;

// table snapshot
class Snapshot {

public:
    Snapshot(uint32_t tid, uint32_t pid, LogParts* log_part);

    ~Snapshot();

    bool Init();

    bool Recover(Table* table, uint64_t& latest_offset);

    void RecoverFromSnapshot(const std::string& snapshot_name, uint64_t expect_cnt, Table* table);
    bool RecoverFromBinlog(Table* table, uint64_t offset, uint64_t& latest_offset);

    inline uint64_t GetOffset() {
        return offset_;
    }

    int MakeSnapshot(Table* table, int& read_log_index);

    int TTLSnapshot(Table* table, const ::rtidb::api::Manifest& manifest, WriteHandle* wh, uint64_t& count);

    // Read manifest from local storage return 0 if ok , 1 if manifest does not exist,
    // or -1 if some error ocurrs 
    int GetSnapshotRecord(::rtidb::api::Manifest& manifest);

    int RecordOffset(const std::string& snapshot_name, uint64_t key_count, uint64_t offset);

private:

    // load single snapshot to table
    void RecoverSingleSnapshot(const std::string& path,
                               Table* table,
                               std::atomic<uint64_t>* g_succ_cnt,
                               std::atomic<uint64_t>* g_failed_cnt);

private:
    uint32_t tid_;
    uint32_t pid_;
    uint64_t offset_;
    boost::atomic<bool> making_snapshot_;
    LogParts* log_part_;
    // the snapshot path
    std::string snapshot_path_;
    std::string log_path_;
};

}
}

#endif /* !RTIDB_SNAPSHOT_H */
