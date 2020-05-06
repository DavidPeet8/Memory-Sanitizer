# Author: davidpeet8
# David Peet

##################### INITIALIZATION #####################

# General Vars
COMPILER=g++
FLAGS=-Werror=vla -Wall -MMD 
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

${EXEC}: makeCommon compile link

-include ${DEPENDSPATHS}

# Individual File Compilation Target
${OBJDIR}/%.o: ${SRCDIR}/%.cc
	# $@ --> is the name of the makefile target
	# $< is the name of the first prerequisite
	${COMPILER} $< -std=${CPPSTANDARD} -fPIC $(INCLUDE_FLAGS) -c -o $@ ${FLAGS}

######################## PHONY TARGETS #########################

makeCommon:
	cd ${COMMON_DIR} && $(MAKE) ${COMMON_TARGET} # Make the common objects before trying to do any sort of linking

debug: FLAGS+=-g 
debug: COMMON_TARGET=debug
debug: ${EXEC}

compile: $(OBJECTPATHS)
	@echo Compiled

link: 
	${COMPILER} -std=${CPPSTANDARD} -shared -fPIC $(INCLUDE_FLAGS) ${OBJDIR}/*.o ${COMMON_OBJS_PATHS} -o ${EXEC} ${FLAGS} -ldl -L ~/mylibs -lmcheckstorage
	@echo Linking Complete

clean:
	cd ${COMMON_DIR} && $(MAKE) clean
	rm ${OBJDIR}/* ${EXEC}
