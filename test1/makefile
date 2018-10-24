
CC = gcc
CFLAGS = -O1 -m64
INCL = -I ./
DEFINES = $(CFLAGS) $(INCL)

cli_objs = client.o
exe_cli = client

svr_objs = server.o
exe_svr = server

all:$(exe_cli) $(exe_svr) final

%.o:%.cpp
	$(CC) $(DEFINES) -c $<

%.o:%.c
	$(CC) $(DEFINES) -c $<

$(exe_cli):$(cli_objs)
	$(CC) -o $(exe_cli) $(cli_objs)
$(exe_svr):$(svr_objs)
	$(CC) -o $(exe_svr) $(svr_objs)

final:$(null)
	rm -rf *.o

.PHONY:clean

clean:
	rm -rf *.o
	rm -rf $(exe_cli)
	rm -rf $(exe_svr)
