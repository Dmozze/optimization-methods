cmake_minimum_required(VERSION 3.17)
project(optimization_methods)

set(CMAKE_CXX_STANDARD 17)

add_executable(optimization_methods main.cpp first-lab/search-metods.cpp first-lab/dichotomy.cpp first-lab/golden_ratio.cpp first-lab/fibonacci.cpp first-lab/parabolas.cpp first-lab/combined_brent.cpp first-lab/research_parabolas.cpp second-lab/Matrix.cpp second-lab/Matrix.h second-lab/Vector.cpp second-lab/Vector.h second-lab/QuadraticFunction.cpp second-lab/QuadraticFunction.h second-lab/gradient_methods.cpp second-lab/gradient_methods.h second-lab/gradient_descent.cpp second-lab/steepest_descent.cpp second-lab/conjugate_gradient.cpp second-lab/GeneratorQuadraticFunction.cpp second-lab/GeneratorQuadraticFunction.h)