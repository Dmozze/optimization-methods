cmake_minimum_required(VERSION 3.17)
project(optimization_methods)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -fsanitize=address,undefined,leak")
endif ()

set(CMAKE_CXX_STANDARD 17)
include_directories(utils)
include_directories(third-lab)
add_executable(optimization_methods main.cpp
        first-lab/search-metods.cpp first-lab/dichotomy.cpp
        first-lab/golden_ratio.cpp first-lab/fibonacci.cpp
        first-lab/parabolas.cpp first-lab/combined_brent.cpp
        first-lab/research_parabolas.cpp
        utils/algebra/Matrix.cpp utils/algebra/Vector.cpp
        second-lab/QuadraticFunction.cpp second-lab/gradient_methods.cpp
        second-lab/gradient_descent.cpp second-lab/steepest_descent.cpp
        second-lab/conjugate_gradient.cpp second-lab/GeneratorQuadraticFunction.cpp
        second-lab/DiagonalQuadraticFunction.cpp
        second-lab/DiagonalMatrix.cpp
        third-lab/MatrixProfileFormat.cpp third-lab/LUMatrix.cpp
        third-lab/LUSolver.h third-lab/HilbertMatrix.h third-lab/GeneratorTables.h
        third-lab/MatrixSparseFormat.cpp third-lab/MatrixSparseFormat.h
        third-lab/MatrixGenerator.cpp third-lab/ConjugateSolver.h)
add_executable(fourth-opt-lab fourth-lab.cpp)