import string

translator = str.maketrans({key: None for key in string.punctuation})

infile = open('../transcripts/debate_1','r')

outfile = open('../data/word_lengths_1','w')

longest = 0
l = ''

for line in infile:
    line = line.split()
    for word in line:
        word = word.translate(translator)
        if len(word) > longest:
            longest = len(word)
            l = word
        outfile.write(str(len(word))+';\n')

print(longest)
print(l)
