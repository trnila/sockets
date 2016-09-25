import socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(("127.0.0.1", 1234))
sock.listen(10)

client, addr = sock.accept()
str = client.recv(1024)
print("received: %s", str)

client.send(str.decode('utf-8').upper().encode('utf-8'))
