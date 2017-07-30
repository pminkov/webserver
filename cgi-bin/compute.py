#!/usr/bin/python

import cgi
import cgitb
cgitb.enable()

input_data = cgi.FieldStorage()

print 'Content-Type:text/html' #HTML is following
print                          #Leave a blank line
print '<h1>Addition Results</h1>'

mil = 1000000
ss = 0
for i in range(0, 100 * mil):
  ss += (i * i) % 10
  ss %= 10

print 'Done: %d', ss

