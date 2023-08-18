
# A Makefile to build 'Duplicates' project

#Short cut to console commands
C11 = cc -std=c11
CFLAGS = -Wall -pedantic -Werror

duplicates : strSHA2.o duplicates.o alterHashtable.o scanDirectory.o output.o	
	$(C11) $(CFLAGS) -o duplicates strSHA2.o duplicates.o alterHashtable.o scanDirectory.o output.o -lm

strSHA2.o : strSHA2.c duplicates.h
	$(C11) $(CFLAGS) -c strSHA2.c 

testcode.o : duplicates.c duplicates.h
	$(C11) $(CFLAGS) -c duplicates.c

alterHashtable.o : alterHashtable.c duplicates.h
	$(C11) $(CFLAGS) -c alterHashtable.c

scanDirectory.o : scanDirectory.c duplicates.h
	$(C11) $(CFLAGS) -c scanDirectory.c

readHashtable.o : output.c duplicates.h
	$(C11) $(CFLAGS) -c output.c	

clean:
	rm -rf duplicates *.o