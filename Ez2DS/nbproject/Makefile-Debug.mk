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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=gfortran.exe
AS=as.exe

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
	${OBJECTDIR}/e2dImage.o \
	${OBJECTDIR}/e2dMatrix.o \
	${OBJECTDIR}/Ez2DS.o \
	${OBJECTDIR}/e2dPath.o \
	${OBJECTDIR}/e2dPoint.o \
	${OBJECTDIR}/e2dElement.o \
	${OBJECTDIR}/e2dGroup.o \
	${OBJECTDIR}/e2dScene.o


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
LDLIBSOPTIONS=-Ldependencies/mxml-2.7/libunix -lmxml1

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Ez2DS_d.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Ez2DS_d.dll: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Ez2DS_d.dll ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/e2dImage.o: e2dImage.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Idependencies/mxml-2.7/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/e2dImage.o e2dImage.c

${OBJECTDIR}/e2dMatrix.o: e2dMatrix.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Idependencies/mxml-2.7/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/e2dMatrix.o e2dMatrix.c

${OBJECTDIR}/Ez2DS.o: Ez2DS.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Idependencies/mxml-2.7/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Ez2DS.o Ez2DS.c

${OBJECTDIR}/e2dPath.o: e2dPath.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Idependencies/mxml-2.7/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/e2dPath.o e2dPath.c

${OBJECTDIR}/e2dPoint.o: e2dPoint.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Idependencies/mxml-2.7/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/e2dPoint.o e2dPoint.c

${OBJECTDIR}/e2dElement.o: e2dElement.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Idependencies/mxml-2.7/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/e2dElement.o e2dElement.c

${OBJECTDIR}/e2dGroup.o: e2dGroup.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Idependencies/mxml-2.7/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/e2dGroup.o e2dGroup.c

${OBJECTDIR}/e2dScene.o: e2dScene.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -Idependencies/mxml-2.7/include  -MMD -MP -MF $@.d -o ${OBJECTDIR}/e2dScene.o e2dScene.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/Ez2DS_d.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
