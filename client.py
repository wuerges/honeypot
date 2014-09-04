import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 32000
msg = bytes(input(), 'utf-8')

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.sendto(msg, (UDP_IP, UDP_PORT))
print("ECHO", str(sock.recv(1000)))

