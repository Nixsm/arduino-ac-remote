def pairwise(iterable):
    a = iter(iterable)
    return zip(a, a)

raw_data = [6112, 7364, 564, 1632, 672, 1536, 628, 1564, 568, 1628, 564, 1628, 676, 1508, 684, 1536, 564, 1624, 572, 548, 652, 496, 604, 520, 568, 556, 600, 540, 660, 468, 568, 552, 600, 520, 652, 1568, 564, 1624, 568, 1628, 644, 1548, 648, 1564, 564, 1624, 568, 1620, 652, 1568, 628, 492, 600, 524, 564, 552, 656, 492, 568, 552, 568, 552, 680, 468, 568, 556, 596, 520, 680, 468, 564, 1628, 568, 1628, 648, 1544, 648, 1560, 600, 1592, 568, 1620, 652, 1564, 604, 1588, 568, 556, 676, 440, 632, 516, 572, 552, 596, 520, 656, 492, 632, 1560, 600, 520, 680, 1536, 568, 548, 720, 1484, 644, 496, 600, 520, 568, 1624, 632, 492, 676, 1532, 604, 520, 600, 1588, 656, 492, 600, 1588, 572, 1616, 684, 464, 564, 1628, 572, 1624, 632, 1552, 656, 1564, 564, 1624, 568, 552, 660, 1552, 576, 1620, 568, 560, 632, 504, 576, 544, 572, 552, 568, 580, 596, 1592, 568, 552, 572, 576, 632, 488, 568, 1620, 572, 548, 656, 1556, 572, 556, 568, 1620, 656, 488, 568, 556, 568, 1620, 688, 460, 564, 1628, 568, 556, 680, 1512, 620, 520, 568, 1620, 572, 1616, 684, 7296, 572]


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
