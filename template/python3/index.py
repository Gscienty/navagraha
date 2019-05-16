import sys
from function import handler

def getit():
    buf = ''
    while True:
        b = sys.stdin.read(1)
        if not b:
            break
        buf += b
    return buf

if __name__ == '__main__':
    sys.stdout.write(handler.handle(getit()))
