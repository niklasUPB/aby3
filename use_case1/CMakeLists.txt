
#project(use_case1)


file(GLOB_RECURSE SRCS *.cpp)






add_executable(use_case1 use_case1.cpp)


target_link_libraries(use_case1  oc::tests_cryptoTools)
target_link_libraries(use_case1  com-psi)
target_link_libraries(use_case1  aby3-ML)
target_link_libraries(use_case1  com-psi_Tests)
target_link_libraries(use_case1  aby3_Tests)








