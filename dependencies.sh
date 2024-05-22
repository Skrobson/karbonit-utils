# !/bin/sh

sudo apt update
sudo apt install cmake \
    git \
    -y
sudo apt install libspdlog-dev -y
sudo apt install libboost1.83-all-dev

install sudo apt install llvm clang-format clang-tidy uncrustify cppcheck iwyu -y

pip install pre-commit
pre-commit install

pip install cpplint
pip install cmakelint
