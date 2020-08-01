# Author: davidpeet8
# David Peet

##################### INITIALIZATION #####################

# General Vars
COMPILER=g++
COMPILATION_FLAGS=-Werror=vla -Wall -MMD -fPIC
LINKER_FLAGS=-L ~/mylibs -lmcheckstorage -shared
EXEC=libmcheck.so
CPPSTANDARD=c++17

# Vars for project objects
SRCDIR=./src
OBJDIR=./obj
OBJECTS=memcheck_shim.o
OBJECTPATHS=$(call addprefix, ${OBJDIR}/, ${OBJECTS})
DEPENDSPATHS=${OBJECTPATHS:.o=.d}

# Deal with common objects, common directory, and objects we need from common
COMMON_DIR=../common
COMMON_OBJS=
COMMON_OBJS_PATHS=$(call addprefix, ${COMMON_DIR}/obj/, ${COMMON_OBJS})
INCLUDE_PATHS=../common/src ../mcheckstorage/include
INCLUDE_FLAGS=$(call addprefix, -I , $(INCLUDE_PATHS))

.PHONY: clean makeCommon debug compile link

####################### TARGETS #########################

${EXEC}: makeObjDir makeCommon compile link

-include ${DEPENDSPATHS}

# Individual File Compilation Target
${OBJDIR}/%.o: ${SRCDIR}/%.cc
	# $@ --> is the name of the makefile target
	# $< is the name of the first prerequisite
	${COMPILER} $< -std=${CPPSTANDARD} $(INCLUDE_FLAGS) -c -o $@ ${COMPILATION_FLAGS}

######################## PHONY TARGETS #########################

makeObjDir:
	mkdir -p obj

makeCommon:
	cd ${COMMON_DIR} && $(MAKE) ${COMMON_TARGET} # Make the common objects before trying to do any sort of linking

makeObjDir: 
	mkdir -p obj

debug: COMPILATION_FLAGS+=-g 
debug: COMMON_TARGET=debug
debug: ${EXEC}

compile: $(OBJECTPATHS)
	@echo Compiled

link: 
	${COMPILER} ${OBJDIR}/*.o ${COMMON_OBJS_PATHS} -o ${EXEC} ${LINKER_FLAGS}
	@echo Linking Complete

clean:
	cd ${COMMON_DIR} && $(MAKE) clean
	rm -f ${OBJDIR}/* ${EXEC}
