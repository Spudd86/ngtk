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
FC=
AS=as.exe

# Macros
CND_PLATFORM=MinGW-Windows
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/backends/windows/ngtk-win-base.o \
	${OBJECTDIR}/src/widgets/ngtk-event-generator.o \
	${OBJECTDIR}/src-test/main.o \
	${OBJECTDIR}/src/backends/basic/ngtk-basic-component.o \
	${OBJECTDIR}/src/backends/basic/ngtk-basic-event-generator.o \
	${OBJECTDIR}/src/backends/windows/ngtk-widget-window.o \
	${OBJECTDIR}/src/object-system/ngtk-object.o \
	${OBJECTDIR}/src/backends/basic/ngtk-basic-container.o \
	${OBJECTDIR}/src/widgets/ngtk-container.o \
	${OBJECTDIR}/src/backends/windows/ngtk-win-component.o \
	${OBJECTDIR}/src/widgets/ngtk-component.o \
	${OBJECTDIR}/src/utils/ngtk-list.o \
	${OBJECTDIR}/src/backends/windows/ngtk-win-event-generator.o \
	${OBJECTDIR}/src/backends/windows/ngtk-win-container.o


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
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/MinGW-Windows/ngtk-c.exe

dist/Release/MinGW-Windows/ngtk-c.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/MinGW-Windows
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ngtk-c ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/backends/windows/ngtk-win-base.o: src/backends/windows/ngtk-win-base.c 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/ngtk-win-base.o src/backends/windows/ngtk-win-base.c

${OBJECTDIR}/src/widgets/ngtk-event-generator.o: src/widgets/ngtk-event-generator.c 
	${MKDIR} -p ${OBJECTDIR}/src/widgets
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/widgets/ngtk-event-generator.o src/widgets/ngtk-event-generator.c

${OBJECTDIR}/src-test/main.o: src-test/main.c 
	${MKDIR} -p ${OBJECTDIR}/src-test
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src-test/main.o src-test/main.c

${OBJECTDIR}/src/backends/basic/ngtk-basic-component.o: src/backends/basic/ngtk-basic-component.c 
	${MKDIR} -p ${OBJECTDIR}/src/backends/basic
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/basic/ngtk-basic-component.o src/backends/basic/ngtk-basic-component.c

${OBJECTDIR}/src/backends/basic/ngtk-basic-event-generator.o: src/backends/basic/ngtk-basic-event-generator.c 
	${MKDIR} -p ${OBJECTDIR}/src/backends/basic
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/basic/ngtk-basic-event-generator.o src/backends/basic/ngtk-basic-event-generator.c

${OBJECTDIR}/src/backends/windows/ngtk-widget-window.o: src/backends/windows/ngtk-widget-window.c 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/ngtk-widget-window.o src/backends/windows/ngtk-widget-window.c

${OBJECTDIR}/src/object-system/ngtk-object.o: src/object-system/ngtk-object.c 
	${MKDIR} -p ${OBJECTDIR}/src/object-system
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/object-system/ngtk-object.o src/object-system/ngtk-object.c

${OBJECTDIR}/src/backends/basic/ngtk-basic-container.o: src/backends/basic/ngtk-basic-container.c 
	${MKDIR} -p ${OBJECTDIR}/src/backends/basic
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/basic/ngtk-basic-container.o src/backends/basic/ngtk-basic-container.c

${OBJECTDIR}/src/widgets/ngtk-container.o: src/widgets/ngtk-container.c 
	${MKDIR} -p ${OBJECTDIR}/src/widgets
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/widgets/ngtk-container.o src/widgets/ngtk-container.c

${OBJECTDIR}/src/backends/windows/ngtk-win-component.o: src/backends/windows/ngtk-win-component.c 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/ngtk-win-component.o src/backends/windows/ngtk-win-component.c

${OBJECTDIR}/src/widgets/ngtk-component.o: src/widgets/ngtk-component.c 
	${MKDIR} -p ${OBJECTDIR}/src/widgets
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/widgets/ngtk-component.o src/widgets/ngtk-component.c

${OBJECTDIR}/src/utils/ngtk-list.o: src/utils/ngtk-list.c 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/utils/ngtk-list.o src/utils/ngtk-list.c

${OBJECTDIR}/src/backends/windows/ngtk-win-event-generator.o: src/backends/windows/ngtk-win-event-generator.c 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/ngtk-win-event-generator.o src/backends/windows/ngtk-win-event-generator.c

${OBJECTDIR}/src/backends/windows/ngtk-win-container.o: src/backends/windows/ngtk-win-container.c 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/ngtk-win-container.o src/backends/windows/ngtk-win-container.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/MinGW-Windows/ngtk-c.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
