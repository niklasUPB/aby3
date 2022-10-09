
#project(use_case2_fast)


file(GLOB_RECURSE SRCS *.cpp)






add_executable(use_case2_fast use_case2_fast.cpp)


target_link_libraries(use_case2_fast oc::tests_cryptoTools)
target_link_libraries(use_case2_fast com-psi)
target_link_libraries(use_case2_fast aby3-ML)
target_link_libraries(use_case2_fast com-psi_Tests)
target_link_libraries(use_case2_fast aby3_Tests)








