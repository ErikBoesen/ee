import xml.etree.ElementTree as etree
import re

# Regular Expression borrowed from https://github.com/fitnr/unwiki
# TODO: Make your own
STRIP_RE = re.compile(r"""\[\[(File|Category):[\s\S]+\]\]|
        \[\[[^|^\]]+\||
        \[\[|
        \]\]|
        \'{2,5}|
        (<s>|<!--)[\s\S]+(</s>|-->)|
        {{[\s\S\n]+?}}|
        <ref>[\s\S]+</ref>|
        ^(\* *)|
        ={1,6}""", re.VERBOSE)

def strip(text: str) -> str:
    res = STRIP_RE.sub('', text)
    res = re.sub('[\n\t ]+', ' ', res)
    return res

print('Loading')
tree = etree.parse('en.xml')
print('Done')
root = tree.getroot()

with open('en.txt', 'w+') as of:
    for ind, child in enumerate(root):
        if child.tag == '{http://www.mediawiki.org/xml/export-0.10/}page' and child[3].tag == '{http://www.mediawiki.org/xml/export-0.10/}revision':
            try:
                print(child[0].text)  # Title
                of.write(strip(child[3][7].text))

            except:
                pass
        if ind > 100:
            break
