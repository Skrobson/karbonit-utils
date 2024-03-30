from conan import ConanFile
from conan.tools.cmake import CMakeDeps, CMakeToolchain, CMake, cmake_layout
import os

class Karbonit_utils(ConanFile):
    name = "karbonit-utils"
    version = "0.1"
    license = "MIT"
    url = ""
    description = "A collection of utility functions"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        cmake_layout(self)
        self.folders.build = "build"


    # def build_requirements(self):
    #     self.tool_requires("cmake/3.23.5")


    def requirements(self):
        self.requires("boost/1.84.0")
        self.requires("spdlog/1.13.0")


    def configure(self):
        #self.options["spdlog"].use_std_fmt=True
        self.options["spdlog"].header_only=True



    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def package(self):
        cmake = CMake(self)
        cmake.cpack()
