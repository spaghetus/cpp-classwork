artifacts = $(shell find . -name main.cpp | sed s/cpp/o/)
objects = $(shell find . -name main.cpp | sed s/\.cpp//)
tests = $(shell find . -name test.sh)

.PHONY: all $(tests)

all: $(objects)

tests: $(tests) $(objects)

$(objects): %: %.o
	g++ -o $@ $@.o

$(artifacts): %.o: %.cpp

$(tests): %.sh:
	bash $@

clean:
	rm $(shell find -name \*.o) */main