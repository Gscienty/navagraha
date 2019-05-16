import sys
from function import handler

def getit():
    buf = b''
    while True:
        b = sys.stdin.read(1)
        if not b:
            break
        buf += b.encode('utf-8')
    return buf

if __name__ == '__main__':
    print(handler.handle(getit()))
