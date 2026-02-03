while True:
    try:
        Height = int(input("Height:"))
    except:
        continue
    if 0 < Height < 9:
        break
for i in range(Height):
    print(" " * (Height - 1 - i) + "#" * (i+1) + "  " + "#" * (i+1))
