# C++ Playground

![GitHub License](https://img.shields.io/github/license/kurijlj/Cpp-Playground)
[![GitHub Super-Linter](https://github.com/kurijlj/Cpp-Playground/actions/workflows/code-syntax-style-check.yml/badge.svg)](https://github.com/marketplace/actions/super-linter)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/kurijlj/Cpp-Playground/cmake-multi-platform.yml?branch=main&event=push&style=flat&logo=cmake&label=CMake%20build&labelColor=%23064F8C)
![Static Badge](https://img.shields.io/badge/-v17-%23ffffff?style=flat&logo=cplusplus&labelColor=%2300599C)
![Static Badge](https://img.shields.io/badge/-3.14-%23ffffff?style=flat&logo=cmake&labelColor=%23064F8C)

Welcome to the C++ Playground repository! 🎉 This is a curated collection of
small, valuable, and interesting C++ projects that might not warrant individual
repositories but are still valuable and interesting to keep.

- [C++ Playground](#c-playground)
  - [Introduction](#introduction)
  - [Compile Targets](#compile-targets)
  - [Getting Started](#getting-started)
  - [License](#license)

## Introduction

This repository aims to be a home for my coding experiments, algorithm
explorations, visualization tricks, and more built up over the years. Whether
it's a tiny tool, a clever function, or a code snippet, they all have a place
here in the C++ Playground.

## Compile Targets

- **Target_Name:** Short description.

## Getting Started

To start exploring the projects in this repository, follow these steps:

1. **Clone the Repository:** Clone this repository to your local machine using
the following command:

    ```shell
    git clone git@github.com:kurijlj/Cpp-Playground.git
    ```

2. **Navigate to a Project Tree:** Browse through the project tree to find the
code examples that inerest you.

3. **Compile the code:** Build as a regular CMake project:

   1. Create a build directory and `cd` into it.
   2. Create a directory structure and project makefiles using (optionally you
   can specify the generator by invoking with the -G switch):

       ```shell
       cmake -DBUILD_SHARED_LIBS:BOOL=[ON|OFF] -B . -S <project_source_tree>
       ```

   3. Build executable using:

       ```shell
       cmake --build . --config [Debug|RelWithDebInfo|Release|MinSizeRel] --target <target-name>
       ```

4. **Run the Code:** Run the compiled executables to observe how it behaves.

5. **Experiment and Learn:** Tinker with the code, modify parameters, and see
the effects. Learn by experimentation and observation.

## License

This repository is licensed under the [GNU General Public License
v3.0](LICENSE), ensuring that the code remains open-source and accessible to the
community.