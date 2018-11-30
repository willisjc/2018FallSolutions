WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

TESTFLAGS = -DTEST_MAIN -DTEST_CREATENODE -DTEST_LINKEDLISTCREATE -DTEST_DIST -DTEST_CENT -DTEST_FUSE -DTEST_CLUSTER

SRCS = main.c hw19.c
OBJS = $(SRCS:%.c=%.o)

hw19: $(OBJS) 
	$(GCC) $(TESTFLAGS) $(OBJS) -o hw19

.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

testall: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10
#test1 -> 5 2 inputs/test1.txt
test1:
	hw19 inputs/test1.txt > outputs/output1.txt
	diff outputs/output1.txt expected/expected1.txt
test2:
	hw19 inputs/test2.txt > outputs/output2.txt
	diff outputs/output2.txt expected/expected2.txt
test3:
	hw19 inputs/test3.txt > outputs/output3.txt
	diff outputs/output3.txt expected/expected3.txt
test4:
	hw19 inputs/test4.txt > outputs/output4.txt
	diff outputs/output4.txt expected/expected4.txt
test5:
	hw19 inputs/test5.txt > outputs/output5.txt
	diff outputs/output5.txt expected/expected5.txt
test6:
	hw19 inputs/test6.txt > outputs/output6.txt
	diff outputs/output6.txt expected/expected6.txt
test7:
	hw19 inputs/test7.txt > outputs/output7.txt
	diff outputs/output7.txt expected/expected7.txt
test8:
	hw19 inputs/test8.txt > outputs/output8.txt
	diff outputs/output8.txt expected/expected8.txt
test9:
	hw19 inputs/test9.txt > outputs/output9.txt
	diff outputs/output9.txt expected/expected9.txt
test10:
	hw19 inputs/test10.txt > outputs/output10.txt
	diff outputs/output10.txt expected/expected10.txt

clean: # remove all machine generated files
	rm -f split *.o output* hw19
