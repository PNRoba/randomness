import gmpy2
from datetime import datetime


# Save an mpfr object to a text file
def save_mpfr_object(file_path, mpfr_object):
    with open(file_path, 'w') as file:
        mpfr_str = str(mpfr_object)
        file.write(mpfr_str + '\n')


# Load mpfr objects from a text file
def load_mpfr_objects(file_path):
    mpfr_objects = []
    with open(file_path, 'r') as file:
        for line in file:
            mpfr_str = line.strip()
            mpfr_obj = gmpy2.mpfr(mpfr_str)
            mpfr_objects.append(mpfr_obj)
    return mpfr_objects


def S_j(j, d, startTime):
    gmpy2.get_context().precision = 128
    sum1 = gmpy2.mpfr(0)
    sum2 = gmpy2.mpfr(0)
    num = gmpy2.mpfr(0)

    for k in range(d + 1):
        sum1 += (gmpy2.mpfr((16 ** (d - k)) % (8 * k + j)) / (8 * k + j))
        if k % 10000 == 0:
            print("SUM1: time: [" + str(datetime.now() - startTime) + "] | k: " + str(k) + " | sum1: " + str(sum1))
    sum1 = gmpy2.frac(sum1)

    for k in range(d + 1, d + (24 * 16) + 1):
        sum2 += gmpy2.mpfr(16 ** (d - k)) / (8 * k + j)

    print("SUM2: time: [" + str(datetime.now() - startTime) + "] | k: " + str(k) + " | sum2: " + str(sum2))

    # print(sum1+sum2)
    num = gmpy2.frac(sum1 + sum2)
    print("NUM: " + str(num))
    return num


def main():
    startTime = datetime.now()

    gmpy2.get_context().precision = 128

    arr = [  # 0,
        # 100,
        # 1000,
        # 10000,
        # 100000,
        1000000]  # (~8h)
        # 10000000,
        # 100000000,
        # 1000000000,
        # 10000000000]

    for n in arr:
        print("--- Computing n: " + str(n))
        S1 = S_j(1, n, startTime)
        save_mpfr_object('n' + str(n) + '-S1-.txt', S1)

        S2 = S_j(4, n, startTime)
        save_mpfr_object('n' + str(n) + '-S2-.txt', S2)

        S3 = S_j(5, n, startTime)
        save_mpfr_object('n' + str(n) + '-S3-.txt', S3)

        S4 = S_j(6, n, startTime)
        save_mpfr_object('n' + str(n) + '-S4-.txt', S4)


if __name__ == "__main__":
    main()
