add_library(FqBig SHARED FqBig.cpp FiniteField.h)
add_library(Fq2 SHARED Fq2.cpp FqBig.h FiniteField.h)
add_library(Fq SHARED Fq.cpp Fq.h FiniteField.h)
add_library(FqS SHARED FqS.cpp FqS.h)


target_link_libraries(FqBig gmp)
target_link_libraries(Fq gmp)
