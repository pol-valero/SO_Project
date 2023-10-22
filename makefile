all: bowman poole

bowmanCmdProcessing.o: bowmanCmdProcessing.c bowmanCmdProcessing.h globals.h
	gcc -c bowmanCmdProcessing.c -Wall -Wextra

bowmanConfig.o: bowmanConfig.c bowmanConfig.h globals.h
	gcc -c bowmanConfig.c -Wall -Wextra

globals.o: globals.c globals.h
	gcc -c globals.c -Wall -Wextra

bowman.o: bowman.c globals.h bowmanConfig.h
	gcc -c bowman.c -Wall -Wextra

bowman: bowman.o globals.o bowmanConfig.o bowmanCmdProcessing.o
	gcc bowman.o globals.o bowmanConfig.o bowmanCmdProcessing.o -o bowman -Wall -Wextra

pooleCmdProcessing.o: pooleCmdProcessing.c pooleCmdProcessing.h globals.h
	gcc -c pooleCmdProcessing.c -Wall -Wextra

pooleConfig.o: pooleConfig.c pooleConfig.h globals.h
	gcc -c pooleConfig.c -Wall -Wextra

poole.o: poole.c globals.h pooleConfig.h
	gcc -c poole.c -Wall -Wextra

poole: poole.o globals.o pooleConfig.o pooleCmdProcessing.o
	gcc poole.o globals.o pooleConfig.o pooleCmdProcessing.o -o poole -Wall -Wextra

.PHONY: clean
clean:
	rm *.o
	rm bowman
	rm poole