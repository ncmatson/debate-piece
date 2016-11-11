from lxml import html
import requests

URL = "https://www.washingtonpost.com/news/the-fix/wp/2016/09/26/the-first-trump-clinton-presidential-debate-transcript-annotated/"
def getData():
    print('scraping \"%s\"' % URL)
    page = requests.get(URL)
    tree = html.fromstring(page.content)

    body = tree.xpath('//article/p/text()')

    f = open('./transcripts/transcript_1.txt', 'w');

    for p in body:
        f.write(p)
        f.write("\n")

    f.close()

    return