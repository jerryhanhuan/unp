
CC = gcc
CFLAGS = -m64 -O1
INC = -I ./ 
DEFINES = $(CFLAGS) $(INC)

cli_objs = client.o 
cli = client

svr_obj = server.o
svr = server

all:$(cli) $(svr) final

%.o:%.cpp
	$(CC) $(DEFINES) -c $<
%.o:%.c
	$(CC) $(DEFINES) -c $<

$(cli):$(cli_objs)
	$(CC) -o $(cli) $(cli_objs)

$(svr):$(svr_obj)
	$(CC) -o $(svr) $(svr_obj)


final:$(null)
	rm -rf *.o
	
.PHONY:clean

clean:
	rm -rf *.o
	rm -rf $(cli)
	rm -rf $(svr)






