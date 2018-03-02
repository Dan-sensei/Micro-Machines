#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AssetManager.o \
	${OBJECTDIR}/Car.o \
	${OBJECTDIR}/Collect.o \
	${OBJECTDIR}/Enemy.o \
	${OBJECTDIR}/Game.o \
	${OBJECTDIR}/Player.o \
	${OBJECTDIR}/SAT.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib /usr/lib/libsfml-graphics.so /usr/lib/libsfml-system.so /usr/lib/libsfml-window.so

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegaso

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegaso: /usr/lib/libsfml-graphics.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegaso: /usr/lib/libsfml-system.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegaso: /usr/lib/libsfml-window.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegaso: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegaso ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/AssetManager.o: AssetManager.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AssetManager.o AssetManager.cpp

${OBJECTDIR}/Car.o: Car.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Car.o Car.cpp

${OBJECTDIR}/Collect.o: Collect.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Collect.o Collect.cpp

${OBJECTDIR}/Enemy.o: Enemy.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Enemy.o Enemy.cpp

${OBJECTDIR}/Game.o: Game.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Game.o Game.cpp

${OBJECTDIR}/Player.o: Player.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Player.o Player.cpp

${OBJECTDIR}/SAT.o: SAT.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SAT.o SAT.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/SFML -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsfml-graphics.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsfml-system.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsfml-window.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/juegaso

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
