CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

IF( WIN32 )
#	SET( FLTK_PATCH PATCH_COMMAND patch -p1 --binary < ${CMAKE_SOURCE_DIR}/0003-Update-built-in-JPEG-CMake-to-install-headers.patch )
	SET( FLTK_PATCH PATCH_COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_CURRENT_SOURCE_DIR}/FLTK_JPEG_CMakeLists.txt"
		"<SOURCE_DIR>/jpeg/CMakeLists.txt" )

ELSE()
	SET( FLTK_PATCH PATCH_COMMAND patch -p1 < ${CMAKE_SOURCE_DIR}/0001-Changes-to-CMakeLists.txt-to-build-on-llvm-on-MacOS.patch
COMMAND patch -p1 < ${CMAKE_SOURCE_DIR}/0002-Fix-LLVM-libc-errors-with-static_cast-CGFloat.patch
COMMAND patch -p1 < ${CMAKE_SOURCE_DIR}/0003-Update-built-in-JPEG-CMake-to-install-headers.patch )
ENDIF()

ExternalProject_Add( FLTK
	${FLTK_PATCH}
	URL ${CMAKE_SOURCE_DIR}/fltk-1.3.2-source.tar.gz
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
		-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
		-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
		-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
		-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
		-DOPTION_BUILD_EXAMPLES:BOOL=OFF
		-DOPTION_USE_SYSTEM_LIBJPEG:BOOL=OFF
		-DOPTION_USE_SYSTEM_ZLIB:BOOL=OFF
		-DOPTION_USE_SYSTEM_LIBPNG:BOOL=OFF
	
)
ExternalProject_Get_Property( FLTK INSTALL_DIR )
SET( FLTK_INSTALL_DIR ${INSTALL_DIR} )
