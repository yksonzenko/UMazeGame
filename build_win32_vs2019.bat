@REM Build for Visual Studio compiler. 

cmake -G "Visual Studio 16 2019" -A x64 -Bbuild -DCMAKE_CONFIGURATION_TYPES="Debug;Release"

cmake --build ./build
