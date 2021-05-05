
.PHONY: client simulator explorer json run run-simulator

all: simulator explorer

simulator:
	@mkdir -p build
	@mkdir -p bin
	@mkdir -p libs
	@cd simulator && make -j

explorer: client json
	@cd explorer && qmake
	@mkdir -p build
	@mkdir -p build/explorer
	@mkdir -p bin
	@cd explorer && make -j

client:
	@mkdir -p build
	@cd client && make

json:
	@mkdir -p build
	@cd json && make

clean:
	@cd client && make clean || true
	@cd simulator && make clean || true
	@cd json && make clean || true
	@cd explorer && make clean || true
	@rm -r bin || true
	@rm -r build || true
	@rm explorer/Makefile || true
	@rm explorer/.qmake.stash || true
	@rm -r explorer/ui/ || true
	@rm -r explorer/moc/ || true
	@rm -r explorer/rrc/ || true
	@rm -r libs || true

run: explorer
	./bin/explorer

run-simulator:
	@cd simulator && make -j run
