HDIR = ./headers
SDIR = ./SRC
BIN=./bin

CC=g++
CFLAGS= -l PocoFoundation -lPocoUtil -lPocoXML -lPocoNet

Trello: Server.o Multi_thread_server.o trello.o manager.o user.o board.o list.o card.o comment.o date.o ID_Generator.o
	$(CC) $(BIN)/*.o $(CFLAGS) -o Trello

Server.o: $(SDIR)/Server.cpp $(HDIR)/*.h
	$(CC) -c $(SDIR)/Server.cpp -o $(BIN)/Server.o

Multi_thread_server.o: $(SDIR)/Multi_thread_server.cpp $(HDIR)/*.h
	$(CC) -c $(SDIR)/Multi_thread_server.cpp $(CFLAGS) -o $(BIN)/Multi_thread_server.o

trello.o: $(SDIR)/trello.cpp $(HDIR)/*.h 
	$(CC) -c $(SDIR)/trello.cpp -o $(BIN)/trello.o

user.o: $(SDIR)/user.cpp $(HDIR)/user.h $(HDIR)/board.h $(HDIR)/ID_Generator.h
	$(CC) -c $(SDIR)/user.cpp -o $(BIN)/user.o

manager.o: $(SDIR)/manager.cpp $(HDIR)/*.h
	$(CC) -c $(SDIR)/manager.cpp -o $(BIN)/manager.o

comment.o: $(SDIR)/comment.cpp $(HDIR)/*.h
	$(CC) -c $(SDIR)/comment.cpp -o $(BIN)/comment.o

board.o: $(SDIR)/board.cpp $(HDIR)/board.h $(HDIR)/list.h $(HDIR)/card.h $(HDIR)/comment.h  $(HDIR)/ID_Generator.h
	$(CC) -c $(SDIR)/board.cpp -o $(BIN)/board.o

list.o: $(SDIR)/list.cpp $(HDIR)/list.h $(HDIR)/card.h $(HDIR)/board.h $(HDIR)/comment.h $(HDIR)/ID_Generator.h
	$(CC) -c $(SDIR)/list.cpp -o $(BIN)/list.o

card.o: $(SDIR)/card.cpp $(HDIR)/card.h $(HDIR)/list.h $(HDIR)/date.h $(HDIR)/comment.h
	$(CC) -c $(SDIR)/card.cpp -o $(BIN)/card.o

date.o: $(SDIR)/date.cpp $(HDIR)/date.h
	$(CC) -c $(SDIR)/date.cpp -o $(BIN)/date.o

ID_Generator.o: $(SDIR)/ID_Generator.cpp $(HDIR)/ID_Generator.h
	$(CC) -c $(SDIR)/ID_Generator.cpp -o $(BIN)/ID_Generator.o


clean:
	rm -rf $(BIN)/ a.out
	mkdir ./bin
