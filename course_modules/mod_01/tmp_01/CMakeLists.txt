

add_executable("${PROJECT_NAME}_00_tmp")
target_compile_features("${PROJECT_NAME}_00_tmp" PUBLIC cxx_std_20)
target_sources("${PROJECT_NAME}_00_tmp" PRIVATE "main.cpp" "gnuplot.hpp" "MetropolisEvolver.hpp" "MetropolisEvolver.cpp" "gnuplot.hpp")

find_package(LC REQUIRED)
target_link_libraries("${PROJECT_NAME}_00_tmp" PRIVATE LC)

