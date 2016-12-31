#!/usr/bin/python

import cgi
import cgitb
cgitb.enable()

input_data = cgi.FieldStorage()

print 'Content-Type:text/html' #HTML is following
print                          #Leave a blank line
print '<h1>Addition Results</h1>'
try:
  num1=int(input_data["num1"].value)
  num2=int(input_data["num2"].value)
except:
  print '<p>Sorry, we cannot turn your inputs into numbers (integers).</p>'
  exit(0)

sum = num1 + num2
print '<p>{0} + {1} = {2}</p>'.format(num1, num2, sum)
