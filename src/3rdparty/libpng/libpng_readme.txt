1. Download version 1.6.8 of the libpng library from http://sourceforge.net/projects/libpng/files/libpng16/older-releases/1.6.8/

2. Extract the contents of lpng168.zip into the libpng folder.

3. Move scripts/pnglibconf.h.prebuilt into the root folder and rename it to pnglibconf.h

4. Replace lines 123-127 of pngpriv.h with #define PNG_ARM_NEON_OPT 0