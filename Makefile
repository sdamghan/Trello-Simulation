HDIR = ./headers
SDIR = ./SRC
BIN=./bin

CC=g++
CFLAGS= -l PocoFoundation -lPocoUtil -lPocoXML -lPocoNet

$(BIN)/a.out: $(BIN)/Server.o $(BIN)/Multi_thread_server.o $(BIN)/trello.o $(BIN)/manager.o $(BIN)/user.o $(BIN)/board.o $(BIN)/list.o $(BIN)/card.o $(BIN)/comment.o $(BIN)/date.o $(BIN)/ID_Generator.o
	$(CC) $(BIN)/Server.o $(BIN)/Multi_thread_server.o $(BIN)/trello.o $(BIN)/manager.o $(BIN)/user.o $(BIN)/board.o $(BIN)/list.o $(BIN)/card.o $(BIN)/comment.o $(BIN)/date.o $(BIN)/ID_Generator.o $(CFLAGS)

$(BIN)/Server.o: $(SDIR)/Server.cpp $(HDIR)/*.h
	$(CC) -c $(SDIR)/Server.cpp

$(BIN)/Multi_thread_server.o: $(SDIR)/Multi_thread_server.cpp $(HDIR)/*.h
	$(CC) -c $(SDIR)/Multi_thread_server.cpp $(CFLAGS)

$(BIN)/trello.o: $(SDIR)/trello.cpp $(HDIR)/*.h 
	$(CC) -c $(SDIR)/trello.cpp

$(BIN)/user.o: $(SDIR)/user.cpp $(HDIR)/user.h $(HDIR)/board.h $(HDIR)/ID_Generator.h
	$(CC) -c $(SDIR)/user.cpp

$(BIN)/manager.o: $(SDIR)/manager.cpp $(HDIR)/*.h
	$(CC) -c $(SDIR)/manager.cpp


$(BIN)/board.o: $(SDIR)/board.cpp $(HDIR)/board.h $(HDIR)/list.h $(HDIR)/card.h $(HDIR)/comment.h  $(HDIR)/ID_Generator.h
	$(CC) -c $(SDIR)/board.cpp
$(BIN)/list.o: $(SDIR)/list.cpp $(HDIR)/list.h $(HDIR)/card.h $(HDIR)/board.h $(HDIR)/comment.h $(HDIR)/ID_Generator.h
	$(CC) -c $(SDIR)/list.cpp
$(BIN)/card.o: $(SDIR)/card.cpp $(HDIR)/card.h $(HDIR)/list.h $(HDIR)/date.h $(HDIR)/comment.h
	$(CC) -c $(SDIR)/card.cpp

$(BIN)/date.o: $(SDIR)/date.cpp $(HDIR)/date.h
	$(CC) -c $(SDIR)/date.cpp

$(BIN)/ID_Generator.o: $(SDIR)/ID_Generator.cpp $(HDIR)/ID_Generator.h
	$(CC) -c $(SDIR)/ID_Generator.cpp


clean:
	rm $(BIN)/*.o a.out
