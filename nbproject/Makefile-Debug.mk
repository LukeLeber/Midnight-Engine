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
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-Linux-x86
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
	${OBJECTDIR}/main.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1 \
	${TESTDIR}/TestFiles/f2

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/midnight_engine

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/midnight_engine: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/midnight_engine ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -ISource/Interface/core -ISource/Interface/glsl -ISource/Interface/io -ISource/Interface/scene -ISource/Interface/texture -ISource/Interface/util -ISource/Implementation/core -ISource/Implementation/glsl -ISource/Implementation/scene -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/Testing/core/Color.o ${TESTDIR}/Testing/core/Point.o ${TESTDIR}/Testing/core/Tuple.o ${TESTDIR}/Testing/core/Vector.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -LTesting/gtest\ 1.7.0 -lgtest -lpthread `pkg-config --libs gl` `pkg-config --libs glew` `pkg-config --libs glu` -lfreeglut   

${TESTDIR}/TestFiles/f2: ${TESTDIR}/Testing/glsl/Shader.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f2 $^ ${LDLIBSOPTIONS} -LTesting/gtest\ 1.7.0 -lgtest -lpthread `pkg-config --libs gl` `pkg-config --libs glew` `pkg-config --libs glu` -lfreeglut   


${TESTDIR}/Testing/core/Color.o: Testing/core/Color.cpp 
	${MKDIR} -p ${TESTDIR}/Testing/core
	${RM} "$@.d"
	$(COMPILE.cc) -g -ISource/Interface/core -ISource/Interface/glsl -ISource/Interface/io -ISource/Interface/scene -ISource/Interface/texture -ISource/Interface/util -ISource/Implementation/core -ISource/Implementation/glsl -ISource/Implementation/scene -ITesting/gtest\ 1.7.0/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/Testing/core/Color.o Testing/core/Color.cpp


${TESTDIR}/Testing/core/Point.o: Testing/core/Point.cpp 
	${MKDIR} -p ${TESTDIR}/Testing/core
	${RM} "$@.d"
	$(COMPILE.cc) -g -ISource/Interface/core -ISource/Interface/glsl -ISource/Interface/io -ISource/Interface/scene -ISource/Interface/texture -ISource/Interface/util -ISource/Implementation/core -ISource/Implementation/glsl -ISource/Implementation/scene -ITesting/gtest\ 1.7.0/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/Testing/core/Point.o Testing/core/Point.cpp


${TESTDIR}/Testing/core/Tuple.o: Testing/core/Tuple.cpp 
	${MKDIR} -p ${TESTDIR}/Testing/core
	${RM} "$@.d"
	$(COMPILE.cc) -g -ISource/Interface/core -ISource/Interface/glsl -ISource/Interface/io -ISource/Interface/scene -ISource/Interface/texture -ISource/Interface/util -ISource/Implementation/core -ISource/Implementation/glsl -ISource/Implementation/scene -ITesting/gtest\ 1.7.0/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/Testing/core/Tuple.o Testing/core/Tuple.cpp


${TESTDIR}/Testing/core/Vector.o: Testing/core/Vector.cpp 
	${MKDIR} -p ${TESTDIR}/Testing/core
	${RM} "$@.d"
	$(COMPILE.cc) -g -ISource/Interface/core -ISource/Interface/glsl -ISource/Interface/io -ISource/Interface/scene -ISource/Interface/texture -ISource/Interface/util -ISource/Implementation/core -ISource/Implementation/glsl -ISource/Implementation/scene -ITesting/gtest\ 1.7.0/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/Testing/core/Vector.o Testing/core/Vector.cpp


${TESTDIR}/Testing/glsl/Shader.o: Testing/glsl/Shader.cpp 
	${MKDIR} -p ${TESTDIR}/Testing/glsl
	${RM} "$@.d"
	$(COMPILE.cc) -g -ISource/Interface/core -ISource/Interface/glsl -ISource/Interface/io -ISource/Interface/scene -ISource/Interface/texture -ISource/Interface/util -ISource/Implementation/core -ISource/Implementation/glsl -ISource/Implementation/scene -ITesting/gtest\ 1.7.0/include -I. -std=c++11 -MMD -MP -MF "$@.d" -o ${TESTDIR}/Testing/glsl/Shader.o Testing/glsl/Shader.cpp


${OBJECTDIR}/main_nomain.o: ${OBJECTDIR}/main.o main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/main.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -ISource/Interface/core -ISource/Interface/glsl -ISource/Interface/io -ISource/Interface/scene -ISource/Interface/texture -ISource/Interface/util -ISource/Implementation/core -ISource/Implementation/glsl -ISource/Implementation/scene -std=c++11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_nomain.o main.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/main.o ${OBJECTDIR}/main_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	    ${TESTDIR}/TestFiles/f2 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/midnight_engine

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
