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
CND_PLATFORM=MinGW-Windows
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Ez2DSDebugDraw.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=-Wall

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Ldependencies/gl/lib -Ldependencies/IL/lib -L../Ez2DS/dist/Debug/MinGW-Windows -lEz2DS -lglu32 -lopengl32 -lglut32 -lDevIL -lILU -lILUT

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e2dtester.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e2dtester.exe: ../Ez2DS/dist/Debug/MinGW-Windows/libEz2DS.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e2dtester.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	gcc -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e2dtester ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Ez2DSDebugDraw.o: Ez2DSDebugDraw.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I../Ez2DS -Idependencies/gl/include -Idependencies/IL/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/Ez2DSDebugDraw.o Ez2DSDebugDraw.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I../Ez2DS -Idependencies/gl/include -Idependencies/IL/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:
	cd ../Ez2DS && ${MAKE}  -f Makefile CONF=Debug
	cd ../Ez2DS && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/e2dtester.exe

# Subprojects
.clean-subprojects:
	cd ../Ez2DS && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Ez2DS && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
