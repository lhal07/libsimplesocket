CC=gcc -O3
OBJ_LINK= -fPIC -Wall -c
SHR_LINK = -shared
LINK= ln -s
LIB=simplesocket
LIBNAME=lib$(LIB)
SRC_DIR=src
LIB_DIR=lib
BIN_DIR=bin
INC_DIR=include
RM=rm -f
CP=cp -rf
CLIENT=socket_cli
SERVER=socket_ser
TARGET=/usr

default: lib bin

all: lib bin install

install:
	$(CP) $(LIB_DIR)/$(LIBNAME).so.0.0 $(TARGET)/lib/
	$(CP) $(LIB_DIR)/$(LIBNAME).so.0 $(TARGET)/lib/
	$(CP) $(LIB_DIR)/$(LIBNAME).so $(TARGET)/lib/
	$(CP) $(INC_DIR)/$(LIB).h $(TARGET)/include/
	$(CP) $(BIN_DIR)/$(CLIENT) $(TARGET)/bin/
	$(CP) $(BIN_DIR)/$(SERVER) $(TARGET)/bin/

uninstall:
	$(RM) $(TARGET)/lib/$(LIBNAME).so.0.0
	$(RM) $(TARGET)/lib/$(LIBNAME).so.0
	$(RM) $(TARGET)/lib/$(LIBNAME).so
	$(RM) $(TARGET)/bin/$(CLIENT)
	$(RM) $(TARGET)/bin/$(SERVER)

lib_dir:
	mkdir -p $(LIB_DIR)

bin_dir:
	mkdir -p $(BIN_DIR)

lib: $(LIB_DIR)/$(LIBNAME).so

bin: $(BIN_DIR)/$(CLIENT) $(BIN_DIR)/$(SERVER)

$(LIB_DIR)/$(LIBNAME).so: $(SRC_DIR)/$(LIBNAME).o lib_dir
	$(CC) -fPIC -shared -I$(INC_DIR) -o $(LIB_DIR)/$(LIBNAME).so.0.0 $(SRC_DIR)/$(LIBNAME).o
	$(RM) $(LIB_DIR)/$(LIBNAME).so.0
	$(RM) $(LIB_DIR)/$(LIBNAME).so
	$(LINK) $(LIBNAME).so.0.0 $(LIB_DIR)/$(LIBNAME).so.0
	$(LINK) $(LIBNAME).so.0 $(LIB_DIR)/$(LIBNAME).so

$(SRC_DIR)/$(LIBNAME).o: $(INC_DIR)/$(LIB).h $(SRC_DIR)/$(LIBNAME).c
	$(CC) $(OBJ_LINK) -I$(INC_DIR) $(SRC_DIR)/$(LIBNAME).c -o $(SRC_DIR)/$(LIBNAME).o


$(BIN_DIR)/$(CLIENT): $(SRC_DIR)/$(CLIENT).c bin_dir
	$(CC) -I$(INC_DIR) -L$(LIB_DIR) $(SRC_DIR)/$(CLIENT).c -o $(BIN_DIR)/$(CLIENT) -l$(LIB)

$(BIN_DIR)/$(SERVER): $(SRC_DIR)/$(SERVER).c bin_dir
	$(CC) -I$(INC_DIR) -L$(LIB_DIR) $(SRC_DIR)/$(SERVER).c -o $(BIN_DIR)/$(SERVER) -l$(LIB)

clean:
	$(RM) $(LIB_DIR)/$(LIBNAME).so.0.0
	$(RM) $(LIB_DIR)/$(LIBNAME).so.0
	$(RM) $(LIB_DIR)/$(LIBNAME).so
	$(RM) $(SRC_DIR)/$(LIBNAME).o
	$(RM) $(BIN_DIR)/$(CLIENT)
	$(RM) $(BIN_DIR)/$(SERVER)
