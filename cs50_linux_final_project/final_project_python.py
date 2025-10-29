import sys
while True:
    print("User Options:", file=sys.stderr)
    print("Press q to log out", file=sys.stderr)
    print("Press r to see all your accounts", file=sys.stderr)
    print("Press w to add a new account", file=sys.stderr)
    print("Press d to delete one of your accounts", file=sys.stderr)
    print("Press m to delete and create a new account", file=sys.stderr)
    print("Type out DELETE to delete your Remember.r account", file=sys.stderr)
    i = input()
    if i == "q" or i == "r" or i == "w" or i == "d" or i == "m" or i=="DELETE":
        break
    else:
        print("Invalid input", file=sys.stderr)
    print()
print(i)