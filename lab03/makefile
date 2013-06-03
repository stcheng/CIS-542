
all: 	insulin-sim insulin-test1 insulin-test2

insulin-sim: insulin-controller insulin-human
	cc -o insulin insulin_sim.c insulin_controller.o insulin_human.o

insulin-test1: insulin-controller
	cc -o insulin-test1 insulin_test1.c insulin_controller.o
	rm insulin_controller.o

insulin-test2: insulin-controller
	cc -o insulin-test2 insulin_test2.c insulin_controller.o
	rm insulin_controller.o

insulin-human:
	cc -c insulin_human.c

insulin-controller:
	cc -c insulin_controller.c

insulin-test1-gcov:
	cc -fprofile-arcs -ftest-coverage -o insulin-test1 insulin_test1.c insulin_controller.c

insulin-test2-gcov:
	cc -fprofile-arcs -ftest-coverage -o insulin-test2 insulin_test2.c insulin_controller.c

clean:
	rm insulin insulin-test1 insulin-test2 insulin_controller.o insulin_human.o