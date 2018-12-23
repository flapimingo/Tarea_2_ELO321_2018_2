main: Tarea2.c Functions.c Functions.h
	gcc -o Tarea *.c *.h

clean:
	rm *.out Tarea

run:
	./Tarea > comm_log_file.txt