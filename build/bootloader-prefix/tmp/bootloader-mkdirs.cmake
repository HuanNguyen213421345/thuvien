# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/esp/Espressif/frameworks/esp-idf-v4.4.7/components/bootloader/subproject"
  "D:/esp/helloworld/build/bootloader"
  "D:/esp/helloworld/build/bootloader-prefix"
  "D:/esp/helloworld/build/bootloader-prefix/tmp"
  "D:/esp/helloworld/build/bootloader-prefix/src/bootloader-stamp"
  "D:/esp/helloworld/build/bootloader-prefix/src"
  "D:/esp/helloworld/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/esp/helloworld/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
