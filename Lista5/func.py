def get_horizontal_wall_separation(wall, N):
    row = wall // (N - 1)
    col = wall % (N - 1)
    return row * N + col, row * N + col + 1

def get_vertical_wall_separation(wall, N):
    row = wall // N
    col = wall % N
    return row * N + col, (row + 1) * N + col

def is_horizontal_wall(wall, N):
    global num
    if(wall <= (N - 2)):
        return True
    elif((N - 1) <= wall <= (2 * N - 2)):
        return False
    else:
        num += 1
        return is_horizontal_wall(wall - (2 * N - 1), N)

wall = int(input("Wall: "))
N = int(input("N: "))
num = 0
if(is_horizontal_wall(wall, 4)):
    print(get_horizontal_wall_separation(wall - (N * num), N)) # N
else:
    print(get_vertical_wall_separation(wall - ((N - 1) * (num + 1)), N)) # N-1
