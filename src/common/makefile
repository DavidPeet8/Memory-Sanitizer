# Author: davidpeet8
# David Peet
# Project: Common

##################### INITIALIZATION #####################

# General Vars
COMPILER=g++
FLAGS=-Werror=vla -Wall -MMD
CPPSTANDARD=c++14

# Vars for project objects
SRCDIR=./src
OBJDIR=./obj
OBJECTS=Logger.o commonMethods.o messageManager.o customExceptions.o
OBJECTPATHS=$(call addprefix, ${OBJDIR}/, ${OBJECTS})
DEPENDSPATHS=${OBJECTPATHS:.o=.d}

.PHONY: clean debug

####################### TARGETS #########################

all: $(OBJECTPATHS)
	@echo finished making ALL

-include ${DEPENDSPATHS}

# Individual File Compilation Target
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo making $@
	# $@ --> is the name of the makefile target
	# $< is the name of the first prerequisite
	${COMPILER} $< -std=${CPPSTANDARD} -c -o $@ ${FLAGS}

######################## PHONY TARGETS #########################

debug: FLAGS+=-g 
debug: ${OBJECTPATHS}

clean:
	rm -f ${OBJDIR}/*.o ${OBJDIR}/*.d


