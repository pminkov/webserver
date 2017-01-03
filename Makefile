# To deal with the Tabs getting converted to spaces, run vim as "vim -u NONE ./Makefile"
# $@ - left side of rule.
# $^ - right side of rule.

DEPS = threadpool/threadpool.h threadpool/threads.h

%.o: %.c $(DEPS)
	gcc -c -o $@ $< -pthread


OBJ_S = server.o threadpool/threadpool.o
server: $(OBJ_S)
	gcc -o $@ $^ -pthread

clean:
	rm -rf ./server
	rm -rf ./*.o
