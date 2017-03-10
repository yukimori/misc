# -*- coding: utf-8 -*-

import urllib2
from urllib import urlencode

params = {}
text = '巨人'
print "text type:", type(text)
params['text'] = text
params['pageValue'] = 1
params['limit'] = 100

data = urlencode(params, True)
print "data:", data


