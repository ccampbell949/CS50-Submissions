from cs50 import get_int
# Number must be positive integer and must be less than 8

while True:
    h = get_int('height: ')  # get height from user
    
    if (h >= 1) and (h <= 8):  # height must be over 1 and below 8
        break
        
for i in range(h):
    print((h - 1 - i) * " ", end="")
    print((i + 1) * "#")
