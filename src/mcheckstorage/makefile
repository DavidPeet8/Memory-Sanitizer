# Author: davidpeet8
# David Peet

##################### INITIALIZATION #####################

# General Vars
COMPILER=g++
# -ldl lib dynamic lib
FLAGS=-Werror=vla -Wall -MMD -shared -fPIC -static-libstdc++ -ldl -lrt -Wl,-Bsymbolic-functions
EXEC=libmcheckstorage.so
CPPSTANDARD=c++17

# Vars for project objects
SRCDIR=./src
OBJDIR=./obj
OBJECTS=LeakChecker.o mcheckstorage_api.o
OBJECTPATHS=$(call addprefix, ${OBJDIR}/, ${OBJECTS})
DEPENDSPATHS=${OBJECTPATHS:.o=.d}

# Deal with common objects, common directory, and objects we need from common
COMMON_DIR=../common
COMMON_OBJS=Logger.o Args.o customExceptions.o messageManager.o commonMethods.o
COMMON_OBJS_PATHS=$(call addprefix, ${COMMON_DIR}/obj/, ${COMMON_OBJS})
INCLUDE_PATHS=../common/src ./include
INCLUDE_FLAGS=$(call addprefix, -I , $(INCLUDE_PATHS))

.PHONY: clean makeCommon debug compile link

####################### TARGETS #########################

${EXEC}: makeCommon compile link

-include ${DEPENDSPATHS}

# Individual File Compilation Target
${OBJDIR}/%.o: ${SRCDIR}/%.cc
	# $@ --> is the name of the makefile target
	# $< is the name of the first prerequisite
	${COMPILER} $< -std=${CPPSTANDARD} $(INCLUDE_FLAGS) -c -o $@ ${FLAGS}

######################## PHONY TARGETS #########################

makeCommon:
	cd ${COMMON_DIR} && $(MAKE) ${COMMON_TARGET} # Make the common objects before trying to do any sort of linking

debug: FLAGS+=-g 
debug: COMMON_TARGET=debug
debug: ${EXEC}

compile: $(OBJECTPATHS)
	@echo Compiled

link: 
	${COMPILER} -o ${EXEC} ${FLAGS} ${OBJDIR}/*.o ${COMMON_OBJS_PATHS}
	@echo Linking Complete

clean:
	cd ${COMMON_DIR} && $(MAKE) clean
	rm ${OBJDIR}/* ${EXEC}
