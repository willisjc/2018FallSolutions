# ***
# *** Please modify this file as required
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

TESTFLAGS = -DTEST_MAIN -DTEST_CREATENODE -DTEST_LINKEDLISTCREATE -DTEST_REMOVED -DLINKEDLIST

SRCS = hw15.c main.c
OBJS = $(SRCS:%.c=%.o)

hw15: $(OBJS) 
	$(GCC) $(TESTFLAGS) $(OBJS) -o hw15

.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 
testall: test1 test2 test3 test4

test1: hw15
	./hw15 inputs/test1.txt > output1.txt
	diff output1.txt expected/expected1.txt

test2: hw15
	./hw15 inputs/test2.txt > output2.txt
	diff output2.txt expected/expected2.txt

test3: hw15
	./hw15 inputs/test3.txt > output3.txt
	diff output3.txt expected/expected3.txt

test4: hw15
	./hw15 inputs/test4.txt > output4.txt
	diff output4.txt expected/expected4.txt

clean:
	# remove all machine generated files
	rm -f main *.o output?.txt
