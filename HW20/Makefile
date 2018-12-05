WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

TESTFLAGS = -DTEST_READHEADER -DTEST_DECODE -DTEST_MERGELIST -DDO_NOT_MODIFY

SRCS = main.c decode.c list.c tree.c utility.c
OBJS = $(SRCS:%.c=%.o)

hw20: $(OBJS) 
	$(GCC) $(TESTFLAGS) $(OBJS) -o hw20

.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

testall: test1 test2 test3 test4 test5 test6 test7 test8
#test1 -5 2 input/input1.bin
test1:
	hw20 input/input1.bin output/output1.txt
	diff output/output1.txt expected/expected1.txt
test2:
	hw20 input/input2.bin output/output2.txt
	diff output/output2.txt expected/expected2.txt
test3:
	hw20 input/input3.bin output/output3.txt
	diff output/output3.txt expected/expected3.txt
test4:
	hw20 input/input4.bin output/output4.txt
	diff output/output4.txt expected/expected4.txt
test5:
	hw20 input/input5.bin output/output5.txt
	diff output/output5.txt expected/expected5.txt
test6:
	hw20 input/input6.bin output/output6.txt
	diff output/output6.txt expected/expected6.txt
test7:
	hw20 input/input7.bin output/output7.txt
	diff output/output7.txt expected/expected7.txt
test8:
	hw20 input/input8.bin output/output8.txt
	diff output/output8.txt expected/expected8.txt


clean: # remove all machine generated files
	rm -f split *.o output* hw20
