
CC = gcc
CFLAGS = -m64 -O1
INC = -I ./ 
DEFINES = $(CFLAGS) $(INC)

cli_objs = client.o 
cli = client

svr_obj = server.o
svr = server

simple_cli_objs = cli.o
simple_cli = cli

all:$(cli) $(svr) $(simple_cli) final

%.o:%.cpp
	$(CC) $(DEFINES) -c $<
%.o:%.c
	$(CC) $(DEFINES) -c $<

$(cli):$(cli_objs)
	$(CC) -o $(cli) $(cli_objs)

$(svr):$(svr_obj)
	$(CC) -o $(svr) $(svr_obj)

$(simple_cli):$(simple_cli_objs)
	$(CC) -o $(simple_cli) $(simple_cli_objs)


final:$(null)
	rm -rf *.o
	
.PHONY:clean

clean:
	rm -rf *.o
	rm -rf $(cli)
	rm -rf $(svr)






