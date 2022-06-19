
#project(db)


file(GLOB_RECURSE SRCS *.cpp)






add_executable(db db.cpp)


target_link_libraries(db oc::tests_cryptoTools)
target_link_libraries(db com-psi)
target_link_libraries(db aby3-ML)
target_link_libraries(db com-psi_Tests)
target_link_libraries(db aby3_Tests)








