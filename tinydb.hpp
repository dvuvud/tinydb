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

/* Serialize header into 6-byte buffer */
inline void encode_header(uint8_t out[HEADER_SIZE], const EntryHeader& h) noexcept {
    out[0] = h.flags;
    out[1] = h.key_len;
    out[2] = static_cast<uint8_t>( h.val_len        & 0xFFu);
    out[3] = static_cast<uint8_t>((h.val_len >>  8) & 0xFFu);
    out[4] = static_cast<uint8_t>((h.val_len >> 16) & 0xFFu);
    out[5] = static_cast<uint8_t>((h.val_len >> 24) & 0xFFu);
}

/* Deserialise header from a 6-byte buffer */
inline EntryHeader decode_header(const uint8_t in[HEADER_SIZE]) noexcept {
    return {
        .flags   = in[0],
        .key_len = in[1],
        .val_len = static_cast<uint32_t>(in[2])
                 | static_cast<uint32_t>(in[3]) <<  8
                 | static_cast<uint32_t>(in[4]) << 16
                 | static_cast<uint32_t>(in[5]) << 24,
    };
}

/* In-memory index entry (points into the mmap'd file) */
struct IndexEntry {
    size_t val_offset;  // byte offset of value data in file
    uint32_t val_len;
};
}
}
