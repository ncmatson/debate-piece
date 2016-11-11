from lxml import html
import requests

URL = ["https://www.washingtonpost.com/news/the-fix/wp/2016/09/26/the-first-trump-clinton-presidential-debate-transcript-annotated/",
        "https://www.washingtonpost.com/news/the-fix/wp/2016/10/09/everything-that-was-said-at-the-second-donald-trump-vs-hillary-clinton-debate-highlighted/",
        "https://www.washingtonpost.com/news/the-fix/wp/2016/10/19/the-final-trump-clinton-debate-transcript-annotated/"]
def getData():
    num = 1
    for url in URL:
        print('-scraping \"%s\"' % url)
        page = requests.get(url)
        tree = html.fromstring(page.content)

        body = tree.xpath("//article/p/text()")


        path = "debate_"+str(num)
        f = open('./transcripts/'+path, 'w');

        for p in body:
            line = p+"\n"
            f.write(line)

        f.close()

        num = num+1
    return

getData()
