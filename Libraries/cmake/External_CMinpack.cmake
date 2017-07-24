SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm -fPIC")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -fPIC")

ExternalProject_Add( CMINPACK
    URL ${CMAKE_CURRENT_SOURCE_DIR}/cminpack-1.3.3.tar.gz
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
)
ExternalProject_Get_Property( CMINPACK BINARY_DIR INSTALL_DIR )
SET( CMINPACK_INSTALL_DIR ${INSTALL_DIR} )
