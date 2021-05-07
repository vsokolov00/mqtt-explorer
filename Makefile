
#================================================================================================
# File:        Makefile
# Case:        VUT, FIT, ICP, project
# Author:      David Mihola, xmihol00@stud.fit.vutbr.cz
# Date:        summer semester 2021
# Description: Makefile used for calling Makefiles in subdirectories.
#================================================================================================

.PHONY: all explorer clean simulator run run-explorer run-simulator doc doxygen

all:
	@cd src && make

explorer:
	@cd src && make explorer

simulator:
	@cd src && make simulator

clean:
	@cd src && make clean || true
	@rm -r doc/html || true
	@rm 1-xmihol00-xsokol15.zip || true

run: explorer
	@cd src && make run & make run-simulator

run-explorer:
	@cd src && make run

run-simulator:
	@cd src && make run-simulator

doxygen:
	@cd doc && doxygen Doxyfile
	
doc:
	@cd doc && doxygen Doxyfile

pack: clean
	zip -r 1-xmihol00-xsokol15.zip doc src examples Makefile README.txt
