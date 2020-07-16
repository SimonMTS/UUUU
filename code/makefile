all: compile

compile:
	@echo "Compiling..."
	@test -d ./bin || mkdir bin
	@g++ -I./ -o bin/UUUU ./main.cpp -O0
	@clear
	@bin/UUUU example_source_file.uuuu

clean:
	@echo "Cleaning up..."
	@rm -R ./bin