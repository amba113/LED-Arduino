data = [1, 0, 1, 0, 0, 1, 1, 1, 0]
led = [0, 0, 0, 0]
start = 0

for ledI in range(len(led)-1, -1, -1):
    for dataI in range(start, len(led) + start, 1):
        if dataI > len(led):
            start += 1
        
        print(ledI, dataI)
        led[ledI] = data[dataI]
        
        print(led)
