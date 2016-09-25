import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto("hello from client!".encode('utf-8'), ("127.0.0.1", 1234))
