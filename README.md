# Webserver

I wrote this code as an exercise in systems programming with C. This is a simple multi-threaded webserver. Each request is executed in a separate thread and the threads are managed by a thread pool.

### How does it work?

The webserver serves cgi scripts, located in the `cgi-bin` subdirectory and static files, located in the `static` subdirectory.


### Usage:
```bash
$ make server
gcc -c -o server.o server.c
gcc -c -o threadpool.o threadpool.c
gcc -o server server.o threadpool.o
$ ./server
Running on port: 8000

(In a separate terminal)
$ curl 'localhost:8000/cgi-bin/simple.py?num1=5&num2=7'
Content-Type:text/html

<h1>Addition Results</h1>
<p>5 + 7 = 12</p>
```
### Implementation

Requests are served by a [thread pool](https://github.com/pminkov/threadpool) of workers.

### Debugging

It's pretty easy to create memory leaks in C. Therefore, it's highly recommended to use valgrind to check for them:

```bash
$ make server && valgrind --leak-check=full  ./server
```

Run some queries and press `Ctrl-C` in valgrind. You'll see a list of memory leaks.
