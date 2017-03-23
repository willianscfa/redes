PROTOCOLDIR = src/protocol
SENDERDIR = src/sender
RECEIVERDIR = src/receiver

sender : $(SENDERDIR)/%.c $(PROTOCOLDIR)/%.c 
	gcc $^ -I include -o bin/sender

receiver : src/protocol/protocolutils.c src/receiver/receiver.c src/receiver/receiversockets.c
	gcc $^ -I include -o bin/receiver

clean : 
	rm -rf 