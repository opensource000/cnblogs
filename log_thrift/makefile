THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/boost/

CXX = g++
CPPFLAGS = -g
INCLUDE = -I../gen-cpp -I$(THRIFT_DIR) -I$(BOOST_DIR)

LIB = -L/usr/local/lib -lthrift
NB_LIB = -L/usr/local/lib -lthrift -lthriftnb -levent
CLIENT = client
NONBLOCK_CLIENT = nonblock_client
SERVER = server
NONBLOCK_SERVER = nonblock_server
VPATH = ./gen-cpp

CLI_SOURCES = client.cpp \
	log_constants.cpp \
	LogSender.cpp \
	log_types.cpp

NONBLOCK_CLI_SOURCES = nonblock_client.cpp \
	log_constants.cpp \
	LogSender.cpp \
	log_types.cpp

SVR_SOURCES = server.cpp \
        log_constants.cpp \
        LogSender.cpp \
        log_types.cpp
		 
NONBLOCK_SVR_SOURCES = nonblock_server.cpp \
        log_constants.cpp \
        LogSender.cpp \
        log_types.cpp

CLIENT_OBJECTS=$(CLI_SOURCES:.cpp=.o)
NONBLOCK_CLIENT_OBJECTS=$(NONBLOCK_CLI_SOURCES:.cpp=.o)
SERVER_OBJECTS=$(SVR_SOURCES:.cpp=.o)
NONBLOCK_SERVER_OBJECTS=$(NONBLOCK_SVR_SOURCES:.cpp=.o)

all:$(CLIENT) $(NONBLOCK_CLIENT) $(SERVER) $(NONBLOCK_SERVER)

.SUFFIXES: .o .cpp
.cpp.o:
	$(CXX) $(CPPFLAGS) $(INCLUDE) -c $(filter %.cpp, $^) 

.o:
	$(CXX) $(CPPFLAGS) $(INCLUDE) -o $@ $^ 

$(CLIENT): $(CLIENT_OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB)

$(NONBLOCK_CLIENT): $(NONBLOCK_CLIENT_OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB)

$(SERVER): $(SERVER_OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB)

$(NONBLOCK_SERVER): $(NONBLOCK_SERVER_OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^ $(NB_LIB)

clean:
	rm -f *.o *.so *.~ *.bak $(CLIENT) $(NONBLOCK_CLIENT) $(SERVER) $(NONBLOCK_SERVER)

install:
	cp -f $(OUTPUT) $(INSTALL_PATH)

