#include "skyline/inlinehook/And64InlineHook.hpp"
#include "skyline/utils/cpputils.hpp"
#include "skyline/inlinehook/memcpy_controlled.hpp"

//09 E8 A7 D2 69 66 C6 F2 69 E6 E7 F2 09 01 00 F9
constexpr uint8_t code[16] =   {0x09, 0xE8, 0xA7, 0xD2, 			//mov x9, #0x3f400000
                                0x69, 0x66, 0xC6, 0xF2, 			//movk x9, #0x3333, lsl #32
                                0x69, 0xE6, 0xE7, 0xF2, 			//movk x9, #0x3f33, lsl #48
                                0x09, 0x01, 0x00, 0xF9	 			//str x9, [x8]
                                };
constexpr uint8_t handheld_divider[4] = {0x09, 0xF0, 0xA7, 0xD2};		//mov x9, #0x3f800000
constexpr uint8_t dock_divider[8] = {0x09, 0x00, 0xC0, 0xF2,			//movk x9, #0x0, lsl#32
                                     0x09, 0xF0, 0xE7, 0xF2			//movk x9, #0x3f80, #lsl48
                                     };

bool memcmp_f (const unsigned char *s1, const unsigned char *s2, size_t count) {
    while (count-- > 0) 
        if (*s1++ != *s2++) 
            return false;
    return true;
}

size_t getCodeSize() {
        return (size_t)skyline::utils::getRegionAddress(skyline::utils::region::Rodata) - (size_t)skyline::utils::getRegionAddress(skyline::utils::region::Text);
}

/* You must provide full instructions in arrays of uint8_t.
It returns pointer to first found code in main 
or 0 if nothing have been found. */
uintptr_t findTextCode(const uint8_t* code, size_t size) {
    if (size % 4 != 0) return 0;
    uintptr_t addr = (uintptr_t)skyline::utils::getRegionAddress(skyline::utils::region::Text);
    size_t addr_size = getCodeSize();	
    uintptr_t addr_start = addr;
    while (addr != addr_start + addr_size) {
        bool result = memcmp_f((const unsigned char*)addr, code, size);
        if (result) return addr;
        addr += 4;
    }
    return 0;
}

void MHR_main() {	
    uintptr_t pointer = findTextCode(&code[0], sizeof(code));
    if (pointer) {
        sky_memcpy((void*)pointer, &handheld_divider[0], sizeof(handheld_divider));
        sky_memcpy((void*)(pointer+4), &dock_divider[0], sizeof(dock_divider));
    }
}
