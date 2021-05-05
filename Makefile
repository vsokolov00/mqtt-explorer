

.PHONY: all explorer clean simulator run run-explorer run-simulator doc

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
	@cd src && make run

run-explorer:
	@cd src && make run

run-simulator:
	@cd src && make run-simulator

doc:
	@cd doc && doxygen Doxyfile

pack: clean
	zip -r 1-xmihol00-xsokol15.zip doc src Makefile README.txt
