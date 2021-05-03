

.PHONY: all explorer clean simulator run run-explorer run-simulator

all:
	@cd src && make

explorer:
	@cd src && make explorer

simulator:
	@cd src && make simulator

clean:
	@cd src && make clean

run: explorer
	@cd src && make run

run-explorer:
	@cd src && make run

run-simulator:
	@cd src && make run-simulator
