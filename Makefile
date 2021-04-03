GENERATED = .qmake.stash Makefile
TMP_DIRS = bin build

all mqtt-explorer:
	cd src && qmake && make

clean:
	cd $(PWD)/src && make clean ; rm $(GENERATED) ; rm -rf $(TMP_DIRS) 