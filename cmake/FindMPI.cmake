IF(NOT MPI_FOUND)
	GET_PROPERTY(MPI_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)

	FILE(GLOB MPI_PATHS "/opt/nec/ve/mpi/*")
	LIST(SORT MPI_PATHS)
	LIST(LENGTH MPI_PATHS MPI_LEN)

	SET(MPI_FOUND FALSE)

	IF(MPI_LEN GREATER 0)
		LIST(REVERSE MPI_PATHS)

		FOREACH(MPI_PATH ${MPI_PATHS})
			STRING(REGEX MATCH "[0-9]+.[0-9]+.[0-9]+" MPI_VERSION ${MPI_PATH})
			IF(NOT MPI_VERSION STREQUAL "")
				MESSAGE(STATUS "Found MPI ${MPI_VERSION}")

				SET(MPI_INCLUDE_PATH		${MPI_PATH}/include)
				SET(MPI_VERSION				${MPI_VERSION}	CACHE STRING "")
				SET(MPI_FOUND				TRUE			CACHE BOOL "")
				SET(MPIEXEC					mpirun			CACHE STRING "Executable for running MPI programs, if provided.")
				SET(MPIEXEC_MAX_NUMPROCS	""				CACHE STRING "Number of MPI processors to utilize. Defaults to the number of processors detected on the host system")
				SET(MPIEXEC_NUMPROC_FLAT	""				CACHE STRING "Flag to pass to MPIEXEC before giving it the number of processors to run on.")
				SET(MPIEXEC_POSTFLAGS		""				CACHE STRING "Flags to pass to MPIEXEC other flags")
				SET(MPIEXEC_PREFLAGS		""				CACHE STRING "Flags to pass to MPIEXEC directly before the executable to run")

				MARK_AS_ADVANCED(MPI_VERSION MPIEXEC MPIEXEC_NUMPROC_FLAT MPIEXEC_MAX_NUMPROCS MPIEXEC_PREFLAGS MPIEXEC_POSTFLAGS MPI_FOUND)

				FOREACH(LANG ${MPI_LANGUAGES})
					IF(LANG STREQUAL "C" OR LANG STREQUAL "CXX" OR LANG STREQUAL "Fortran")
						GET_FILENAME_COMPONENT(MPI_COMPILER_PATH	${CMAKE_${LANG}_COMPILER}	ABSOLUTE)
						GET_FILENAME_COMPONENT(MPI_COMPILER_BIN		${CMAKE_${LANG}_COMPILER}	NAME)
						
						SET(MPI_${LANG}_COMPILER		${MPI_COMPILER_PATH}/mpi${MPI_COMPILER_BIN}	CACHE FILEPATH "")
						SET(MPI_${LANG}_COMPILE_FLAGS	${CMAKE_${LANG}_FLAGS}						CACHE STRING "")
						SET(MPI_${LANG}_INCLUDE_PATH	${MPI_INCLUDE_PATH}							CACHE PATH "")
						SET(MPI_${LANG}_LINK_FLAGS		""											CACHE STRING "")
						SET(MPI_${LANG}_LIBRARIES		""											CACHE STRING "")

						MARK_AS_ADVANCED(MPI_${LANG}_COMPILER MPI_${LANG}_COMPILE_FLAGS MPI_${LANG}_INCLUDE_PATH MPI_${LANG}_LINK_FLAGS MPI_${LANG}_LIBRARIES)
						UNSET(MPI_COMPILER_PATH)
						UNSET(MPI_COMPILER_BIN)
					ENDIF()
				ENDFOREACH()

				UNSET(MPI_INCLUDE_PATH)
				BREAK()
			ENDIF()
		ENDFOREACH()

		IF(${MPI_FIND_REQUIRED} AND NOT MPI_FOUND)
			MESSAGE(FATAL_ERROR "Unable to detect NEC MPI")
		ENDIF()
	ENDIF()

	UNSET(MPI_PATHS)
	UNSET(MPI_LEN)
ENDIF()
