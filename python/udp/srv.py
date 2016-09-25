import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("127.0.0.1", 1234))

data, addr = sock.recvfrom(1024)
print("received %s from %s" % (data, addr))

sock.sendto("hello!".encode('utf-8'), addr)
