set(CMAKE_OBJCXX_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Tools/MSVC/14.29.30037/bin/Hostx64/x64/cl.exe")
set(CMAKE_OBJCXX_COMPILER_ARG1 "")
set(CMAKE_OBJCXX_COMPILER_ID "MSVC")
set(CMAKE_OBJCXX_COMPILER_VERSION "19.29.30037.0")
set(CMAKE_OBJCXX_COMPILER_VERSION_INTERNAL "")
set(CMAKE_OBJCXX_COMPILER_WRAPPER "")
set(CMAKE_OBJCXX_STANDARD_COMPUTED_DEFAULT "14")
set(CMAKE_OBJCXX_COMPILE_FEATURES "")
set(CMAKE_OBJCXX98_COMPILE_FEATURES "")
set(CMAKE_OBJCXX11_COMPILE_FEATURES "")
set(CMAKE_OBJCXX14_COMPILE_FEATURES "")
set(CMAKE_OBJCXX17_COMPILE_FEATURES "")
set(CMAKE_OBJCXX20_COMPILE_FEATURES "")
set(CMAKE_OBJCXX23_COMPILE_FEATURES "")

set(CMAKE_OBJCXX_PLATFORM_ID "Windows")
set(CMAKE_OBJCXX_SIMULATE_ID "")
set(CMAKE_OBJCXX_COMPILER_FRONTEND_VARIANT "")
set(CMAKE_OBJCXX_SIMULATE_VERSION "")
set(CMAKE_OBJCXX_COMPILER_ARCHITECTURE_ID x64)

set(CMAKE_AR "C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Tools/MSVC/14.29.30037/bin/Hostx64/x64/lib.exe")
set(CMAKE_OBJCXX_COMPILER_AR "")
set(CMAKE_RANLIB ":")
set(CMAKE_OBJCXX_COMPILER_RANLIB "")
set(CMAKE_LINKER "C:/Program Files (x86)/Microsoft Visual Studio/2019/Professional/VC/Tools/MSVC/14.29.30037/bin/Hostx64/x64/link.exe")
set(CMAKE_MT "C:/Program Files (x86)/Windows Kits/10/bin/10.0.18362.0/x86/mt.exe")
set(CMAKE_COMPILER_IS_GNUOBJCXX )
set(CMAKE_OBJCXX_COMPILER_LOADED 1)
set(CMAKE_OBJCXX_COMPILER_WORKS TRUE)
set(CMAKE_OBJCXX_ABI_COMPILED 0)

set(CMAKE_OBJCXX_COMPILER_ENV_VAR "OBJCXX")

set(CMAKE_OBJCXX_COMPILER_ID_RUN 1)
set(CMAKE_OBJCXX_SOURCE_FILE_EXTENSIONS M;m;mm)
set(CMAKE_OBJCXX_IGNORE_EXTENSIONS inl;h;hpp;HPP;H;o;O)

if (CMAKE_OBJC_COMPILER_ID_RUN)
  foreach(extension IN LISTS CMAKE_OBJC_SOURCE_FILE_EXTENSIONS)
    list(REMOVE_ITEM CMAKE_OBJCXX_SOURCE_FILE_EXTENSIONS ${extension})
  endforeach()
endif()

foreach (lang C CXX OBJC)
  foreach(extension IN LISTS CMAKE_OBJCXX_SOURCE_FILE_EXTENSIONS)
    if (CMAKE_${lang}_COMPILER_ID_RUN)
      list(REMOVE_ITEM CMAKE_${lang}_SOURCE_FILE_EXTENSIONS ${extension})
    endif()
  endforeach()
endforeach()

set(CMAKE_OBJCXX_LINKER_PREFERENCE 25)
set(CMAKE_OBJCXX_LINKER_PREFERENCE_PROPAGATES 1)

# Save compiler ABI information.
set(CMAKE_OBJCXX_SIZEOF_DATA_PTR "")
set(CMAKE_OBJCXX_COMPILER_ABI "")
set(CMAKE_OBJCXX_BYTE_ORDER "")
set(CMAKE_OBJCXX_LIBRARY_ARCHITECTURE "")

if(CMAKE_OBJCXX_SIZEOF_DATA_PTR)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_OBJCXX_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_OBJCXX_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_OBJCXX_COMPILER_ABI}")
endif()

if(CMAKE_OBJCXX_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()





set(CMAKE_OBJCXX_IMPLICIT_INCLUDE_DIRECTORIES "")
set(CMAKE_OBJCXX_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_OBJCXX_IMPLICIT_LINK_DIRECTORIES "")
set(CMAKE_OBJCXX_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
