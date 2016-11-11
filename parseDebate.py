import scrape
import os

#check to see if file exists
if os.path.isfile('./transcripts/transcript_1.txt'):
    print 'transcript file already exists'
else:
    scrape.getData()

#read in the first paragraph (each paragraph in the file takes up 1 line)
f = open('./transcripts/transcript_1.txt')
line = f.readline()
print type(line)
print line
line = line.split()
print type(line)
print line
