import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("127.0.0.1", 1234))
sock.send("hello".encode('utf-8'))

print(sock.recv(1024))
