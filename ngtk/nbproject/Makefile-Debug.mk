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
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/backends/base/AbstractComponent.o \
	${OBJECTDIR}/src/backends/windows/WindowsComponent.o \
	${OBJECTDIR}/src/backends/base/AbstractWidget.o \
	${OBJECTDIR}/src/backends/windows/WindowsContainer.o \
	${OBJECTDIR}/src/backends/base/AbstractBackend.o \
	${OBJECTDIR}/src/events/MouseEvent.o \
	${OBJECTDIR}/src/backends/windows/WindowsWidget.o \
	${OBJECTDIR}/src/backends/windows/WindowsBackend.o \
	${OBJECTDIR}/src/backends/base/AbstractWindow.o \
	${OBJECTDIR}/src/backends/windows/WindowsButton.o \
	${OBJECTDIR}/src/backends/windows/WindowsWindow.o \
	${OBJECTDIR}/src/backends/base/AbstractContainer.o


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
	"${MAKE}"  -f nbproject/Makefile-Debug.mk dist/Debug/MinGW-Windows/libngtk.dll

dist/Debug/MinGW-Windows/libngtk.dll: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/MinGW-Windows
	${LINK.cc} -shared -shared -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libngtk.dll ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/backends/base/AbstractComponent.o: src/backends/base/AbstractComponent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/base
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/base/AbstractComponent.o src/backends/base/AbstractComponent.cpp

${OBJECTDIR}/src/backends/windows/WindowsComponent.o: src/backends/windows/WindowsComponent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/WindowsComponent.o src/backends/windows/WindowsComponent.cpp

${OBJECTDIR}/src/backends/base/AbstractWidget.o: src/backends/base/AbstractWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/base
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/base/AbstractWidget.o src/backends/base/AbstractWidget.cpp

${OBJECTDIR}/src/backends/windows/WindowsContainer.o: src/backends/windows/WindowsContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/WindowsContainer.o src/backends/windows/WindowsContainer.cpp

${OBJECTDIR}/src/backends/base/AbstractBackend.o: src/backends/base/AbstractBackend.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/base
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/base/AbstractBackend.o src/backends/base/AbstractBackend.cpp

${OBJECTDIR}/src/events/MouseEvent.o: src/events/MouseEvent.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/events
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/events/MouseEvent.o src/events/MouseEvent.cpp

${OBJECTDIR}/src/backends/windows/WindowsWidget.o: src/backends/windows/WindowsWidget.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/WindowsWidget.o src/backends/windows/WindowsWidget.cpp

${OBJECTDIR}/src/backends/windows/WindowsBackend.o: src/backends/windows/WindowsBackend.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/WindowsBackend.o src/backends/windows/WindowsBackend.cpp

${OBJECTDIR}/src/backends/base/AbstractWindow.o: src/backends/base/AbstractWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/base
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/base/AbstractWindow.o src/backends/base/AbstractWindow.cpp

${OBJECTDIR}/src/backends/windows/WindowsButton.o: src/backends/windows/WindowsButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/WindowsButton.o src/backends/windows/WindowsButton.cpp

${OBJECTDIR}/src/backends/windows/WindowsWindow.o: src/backends/windows/WindowsWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/windows
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/windows/WindowsWindow.o src/backends/windows/WindowsWindow.cpp

${OBJECTDIR}/src/backends/base/AbstractContainer.o: src/backends/base/AbstractContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/backends/base
	${RM} $@.d
	$(COMPILE.cc) -g  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/backends/base/AbstractContainer.o src/backends/base/AbstractContainer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/MinGW-Windows/libngtk.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
