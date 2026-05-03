#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>

namespace tinydb {

// --- public types ---
 
/* Raw byte view into mmap'd file */
using Bytes = std::span<const std::byte>;

// --- internal ---

namespace detail {

inline constexpr uint8_t MAGIC[8]  = { 'T','I','N','Y','D','B','0','1' };
inline constexpr uint8_t FLAG_LIVE = 0x00;
inline constexpr uint8_t FLAG_TOMB = 0x01;
inline constexpr uint8_t MAX_KEY   = 255;
inline constexpr size_t  HEADER_SIZE = 6;   // on-disk entry header size

/* On-disk entry header (6 bytes on disk) */
struct EntryHeader {
    uint8_t  flags;
    uint8_t  key_len;
    uint32_t val_len;
};

/* In-memory index entry (points into the mmap'd file) */
struct IndexEntry {
    size_t val_offset;  // byte offset of value data in file
    uint32_t val_len;
};
}
}
