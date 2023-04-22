from random import randint
MAX_SIZE = 1000

def generate_unsorted_random_instances():
    f = open("inputs/input_unsorted.csv", 'w')
    instances = range(1, MAX_SIZE+1, 10)
    f.write(f"{len(instances)}\n")
    for size in instances:
        f.write(f"{size}")
        for i in range(size):
            start = randint(0, 2*size-1)
            end = randint(start+1, 2*size)
            f.write(" " + str(start) + " " + str(end))
        f.write('\n')

def generate_sorted_random_instances():
    # Genera instancias ordenadas por end time
    f = open("inputs/input_sorted.csv", 'w')
    instances = range(1, MAX_SIZE+1, 10)
    f.write(f"{len(instances)}\n")
    for size in instances:
        f.write(f"{size}")
        temp = []
        for i in range(size):
            start = randint(0, 2*size-1)
            end = randint(start+1, 2*size)
            temp.append((start, end))
        f.write(" " + " ".join([str(start) + " " + str(end) for start, end in sorted(temp, key=lambda x: x[1])]) + '\n')

generate_sorted_random_instances()
generate_unsorted_random_instances()
