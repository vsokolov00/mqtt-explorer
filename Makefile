

.PHONY: all explorer clean simulator run run-explorer run-simulator doc

all:
	@cd src && make

explorer:
	@cd src && make explorer

simulator:
	@cd src && make simulator

clean:
	@cd src && make clean || true
	@rm -r doc/html

run: explorer
	@cd src && make run

run-explorer:
	@cd src && make run

run-simulator:
	@cd src && make run-simulator

doc:
	@cd doc && doxygen Doxyfile
