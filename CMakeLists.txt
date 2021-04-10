cmake_minimum_required(VERSION 3.17)
project(optimization_methods)

set(CMAKE_CXX_STANDARD 17)

add_executable(optimization_methods main.cpp first-lab/search-metods.cpp first-lab/dichotomy.cpp first-lab/golden_ratio.cpp first-lab/fibonacci.cpp first-lab/parabolas.cpp first-lab/combined_brent.cpp first-lab/research_parabolas.cpp second-lab/Matrix.cpp second-lab/Matrix.h second-lab/Vector.cpp second-lab/Vector.h)