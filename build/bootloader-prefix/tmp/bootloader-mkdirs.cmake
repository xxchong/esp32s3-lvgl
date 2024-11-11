# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/xxchong/esp/esp-idf/components/bootloader/subproject"
  "/home/xxchong/esp32s3_lvgl_st7789/build/bootloader"
  "/home/xxchong/esp32s3_lvgl_st7789/build/bootloader-prefix"
  "/home/xxchong/esp32s3_lvgl_st7789/build/bootloader-prefix/tmp"
  "/home/xxchong/esp32s3_lvgl_st7789/build/bootloader-prefix/src/bootloader-stamp"
  "/home/xxchong/esp32s3_lvgl_st7789/build/bootloader-prefix/src"
  "/home/xxchong/esp32s3_lvgl_st7789/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/xxchong/esp32s3_lvgl_st7789/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/xxchong/esp32s3_lvgl_st7789/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
