DIR=EXE

all: $(DIR)
	make -C $(DIR)

$(DIR):
	mkdir $(DIR)
	cd $(DIR); cmake ..; cd ..

check: clean all
	./$(DIR)/imaProjet_auto.exe

clean:
	rm -rf $(DIR)