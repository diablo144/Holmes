#ifndef RIFTCAP_H
#define RIFTCAP_H

#include <stdint.h>

#define RIFTCAP_MAGIC "RIFTCAP\0"
#define RIFTCAP_VERSION 2u
#define RIFTCAP_HEADER_SIZE 80u
#define RIFTCAP_MAX_FILE_SIZE 0x8000u
#define RIFTCAP_MAX_DATA_SIZE 0x800u
#define RIFTCAP_MIN_DATA_SIZE 0x700u
#define RIFTCAP_MAX_FIXUPS 64u
#define RIFTCAP_PAGE_SIZE 0x1000u

#define RIFTCAP_CODE_ADDRESS UINT64_C(0x500000000000)
#define RIFTCAP_CODE_SIZE 16u
#define RIFTCAP_UNWIND_SIZE 68u
#define RIFTCAP_SCRATCH_SIZE 0x1000u

struct __attribute__((packed)) riftcap_header {
    uint8_t magic[8];
    uint32_t version;
    uint32_t total_size;
    uint32_t code_offset;
    uint32_t code_size;
    uint32_t unwind_offset;
    uint32_t unwind_size;
    uint32_t data_offset;
    uint32_t data_size;
    uint32_t fixup_offset;
    uint32_t fixup_count;
    uint32_t entry_offset;
    uint32_t flags;
    uint8_t reserved[24];
};

struct __attribute__((packed)) riftcap_fixup {
    uint32_t data_offset;
    uint8_t width;
    uint8_t operation;
    uint16_t reserved;
    uint64_t value;
};

#ifdef __cplusplus
static_assert(sizeof(struct riftcap_header) == RIFTCAP_HEADER_SIZE,
              "riftcap header ABI changed");
static_assert(sizeof(struct riftcap_fixup) == 16,
              "riftcap fixup ABI changed");
#else
_Static_assert(sizeof(struct riftcap_header) == RIFTCAP_HEADER_SIZE,
               "riftcap header ABI changed");
_Static_assert(sizeof(struct riftcap_fixup) == 16,
               "riftcap fixup ABI changed");
#endif

#endif

/* handout variant: 7313a89e69fb4c9b4e05b6c976e03f8798543aed3e26c3e87ce8aa7b975c0615 */
