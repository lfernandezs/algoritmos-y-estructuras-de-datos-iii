from random import randint
MAX_CANT_OFICINAS = 1000
MAX_DIST_UTP = 10000
INSTANCES_PER_TRY = 20


def generate_random_instances():
    f = open("inputs/input.csv", 'w')
    cant_oficinas = range(2, MAX_CANT_OFICINAS, 10)
    for i in cant_oficinas:
        for j in range(INSTANCES_PER_TRY):
            f.write("1 ")
            f.write(str(i) + " ")
            dist_utp = randint(1, MAX_DIST_UTP)
            modems = randint(1, MAX_CANT_OFICINAS-1)
            precio_utp = randint(1, 10)
            precio_fibra = randint(precio_utp, 10)
            f.write(str(dist_utp) + " ")
            f.write(str(modems) + " ")
            f.write(str(precio_utp) + " ")
            f.write(str(precio_fibra) + " ")
            for k in range(i):
                oficina = (randint(0, MAX_DIST_UTP), randint(0, MAX_DIST_UTP))
                f.write(str(oficina[0]) + " " + str(oficina[1]) + " ")
            f.write("\n")

generate_random_instances()
