def pairwise(iterable):
    a = iter(iterable)
    return zip(a, a)

raw_data = [6234, 7302, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 1540, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 530, 1540, 530, 1540, 530, 1540, 530, 530, 530, 1540, 530, 530, 530, 530, 530, 1540, 530, 530, 530, 530, 530, 530, 530, 1540, 530, 530, 530, 1540, 530, 1540, 530, 530, 530, 1540, 530, 530, 530, 530, 530, 1540, 530, 1540, 530, 530, 530, 1540, 530, 1540, 530, 1540, 530, 530, 530, 530, 530, 1540, 530, 530, 530, 1540, 530, 530, 530, 530, 530, 530, 530, 1540, 530, 530, 530, 1540, 530, 530, 530, 1540, 530, 530, 530, 530, 530, 1540, 530, 530, 530, 1540, 530, 530, 530, 1540, 530, 530, 530, 1540, 530, 1540, 608, 7372, 616]


offset_from_end = -27
offset_from_start = 2

header = raw_data[:offset_from_start]
footer = raw_data[offset_from_end:]

bit_threshold = 1000
bits = []

p2_zeros_average = 0
p2_ones_average = 0

zero_count = 0
one_count = 0

for p1, p2 in pairwise(raw_data[offset_from_start:len(raw_data) + offset_from_end]):
    if p2 > bit_threshold:
        p2_ones_average += p2
        bits.append(1)
        one_count += 1
        continue

    bits.append(0)
    p2_zeros_average += p2
    zero_count += 1

size = round(len(raw_data) / 2)
high = p2_ones_average / one_count
low = p2_zeros_average / zero_count

bits_str = "".join(str(x) for x in bits)

print(hex(int(bits_str, 2)))
