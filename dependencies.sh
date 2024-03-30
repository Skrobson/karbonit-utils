# !/bin/sh

sudo apt update
sudo apt install cmake \
    git \
    -y

install sudo apt install llvm clang-format clang-tidy uncrustify cppcheck iwyu -y

pip install pre-commit
pre-commit install

pip install cpplint
pip install cmakelint
