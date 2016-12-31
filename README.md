# Webserver

This is a simple multi-threaded webserver. Each request is executed in a separate thread. The threads are managed by a thread pool.

It's interesting to look at the thread pool [code](https://github.com/pminkov/wip/blob/master/os/webserver/threadpool.c).

