import socket
import sys

import msgpack
import io

HOST, PORT = "localhost", 50007

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect((HOST, PORT))

while(1):

	data = raw_input ( "SEND( TYPE q or Q to Quit):" )
	if (data <> 'Q' and data <> 'q'):
		s.send(data)
		msg = s.recv(512)
		print ('packed data: %s' %(msg))
		print ('data length: %s' %(len(msg)))
		msg = msg.strip('%r%n')
		ret = msgpack.unpackb(msg)
		print ('unpacked data: %s' %(ret))
	else:
		s.send(data)
		s.close()
		break;