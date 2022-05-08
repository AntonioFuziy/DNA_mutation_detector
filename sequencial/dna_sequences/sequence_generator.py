import random

max_sequence_length = 300
filename = 1

for n in range(20, max_sequence_length + 1, 30):
  for m in range(20, max_sequence_length + 1, 30):

    file = f"./all_sequences/dna{filename}.seq"
    f = open(file, 'w')
    seq=[str(n)+'\n',
        str(m)+'\n',
        ''.join(random.choices(['A','T','C','G','-'],k=n))+'\n',
        ''.join(random.choices(['A','T','C','G','-'],k=m))]
    f.writelines(seq)
    f.close()
    filename += 1

# print(''.join(seq))