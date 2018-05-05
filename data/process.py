import xml.etree.ElementTree as etree
import mwparserfromhell as mwparser
import re

STRIP_RE = re.compile(r"""^[\|!].*$|^Category:""", re.MULTILINE)
WS_RE = re.compile('[\n\t ]+')

LANGS = ['zh', 'es', 'en', 'ar', 'hi', 'bn', 'ru']

def strip(text: str) -> str:
    res = mwparserfromhell.parse(text).strip_code()
    res = STRIP_RE.sub('', res)
    res = WS_RE.sub(' ', res)
    return res

for l in LANGS:
    print('Loading {language}'.format(language=l))
    tree = etree.parse('%s.xml' % l)
    print('Done')
    root = tree.getroot()

    with open('%s.txt' % l, 'w+') as of:
        for ind, child in enumerate(root):
            if child.tag == '{http://www.mediawiki.org/xml/export-0.10/}page' and child[3].tag == '{http://www.mediawiki.org/xml/export-0.10/}revision':
                print('Title:', child[0].text)
                of.write(strip(child[3][7].text))
            if ind > 100:
                break
