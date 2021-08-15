from cs50 import get_float
#  could also use int(input) in IDE not linked to cs50
coins = 0  # set coins counter to 0
while True:

    change = get_float("change($): ")  # get user input
    
    if change <= 0:  # must be positive number
        print("Please enter valid number")
        
    else:
        break  # break lop when condition met
    
# convert to pennies

Change = (change * 100)

while Change > 0:
    
    while Change >= 25:  # divide by 25 as many time as possible
        coins += 1
        Change -= 25
        
    while Change >= 10:  # divide by 10 amtap
        coins += 1
        Change -= 10
        
    while Change >= 5:  # divide by 5 amtap
        coins += 1
        Change -= 5
        
    while Change >= 1:  # divide by 1 amtap
        coins += 1
        Change -= 1
        
print(coins)  # print number of coins used
