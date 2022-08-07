
#project(use_case2)


file(GLOB_RECURSE SRCS *.cpp)






add_executable(use_case2 use_case2.cpp)


target_link_libraries(use_case2 oc::tests_cryptoTools)
target_link_libraries(use_case2 com-psi)
target_link_libraries(use_case2 aby3-ML)
target_link_libraries(use_case2 com-psi_Tests)
target_link_libraries(use_case2 aby3_Tests)








