import xml.etree.ElementTree as etree
import mwparserfromhell
import re

STRIP_RE = re.compile(r"""^[\|!].*$|^Category:""", re.MULTILINE)
WS_RE = re.compile('[\n\t ]+')

def strip(text: str) -> str:
    res = mwparserfromhell.parse(text).strip_code()
    res = STRIP_RE.sub('', res)
    res = WS_RE.sub(' ', res)
    return res

print('Loading')
tree = etree.parse('en.xml')
print('Done')
root = tree.getroot()

with open('en.txt', 'w+') as of:
    for ind, child in enumerate(root):
        if child.tag == '{http://www.mediawiki.org/xml/export-0.10/}page' and child[3].tag == '{http://www.mediawiki.org/xml/export-0.10/}revision':
            print('Title:', child[0].text)
            of.write(strip(child[3][7].text))
        if ind > 100:
            break
