## Dependencies

conan install . -pr ./conan/conan_ubuntu --build=missing

cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

if cmake v > 3.23 use preset
