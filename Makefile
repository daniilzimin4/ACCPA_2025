all: src/Stella/TestStella build/stella-interpreter

typecheck: build/stella-interpreter
	./build/stella-interpreter

interpret: build/stella-interpreter
	./build/stella-interpreter $(STELLA_FILE)

src/Stella/TestStella: Stella.cf
	mkdir -p src/Stella/
	cd src/Stella/ && (bnfc -m --cpp ../../Stella.cf -l -p Stella; cd ../../)
	cd src/Stella/ && (make; cd ../../)

build/stella-interpreter: src/Interpret.cpp src/TypeCheck.cpp src/TypeCheck.h src/Eval.cpp src/Eval.h src/Stella/TestStella
	cmake -S. -Bbuild
	cmake --build build/ --target stella-interpreter --

.PHONY: all typecheck interpret
