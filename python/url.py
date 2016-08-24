#coding=utf-8
import urllib.request
import re
import linecache

content = urllib.request.urlopen('http://www.hao123.com/', timeout=3).read()
fo = open("foo.txt", "w+")
max_count = 10000
line = 1;
s1 = 0
print("start:\n")
while s1 >= 0 and max_count > 0:
    begin = content.find(r"<a".encode('utf-8'),s1)
    m1 = content.find(r'href='.encode('utf-8'),begin)
    m1 = content.find(r'"'.encode('utf-8'),m1) + 1
    m2 = content.find(r'"'.encode('utf-8'),m1)

    print("before===========================:")
    
    s1 = m2
    if begin <= 0 or s1 < 0:
        fo.close()
        fo = open("foo.txt", "a+")
        url_str = linecache.getline('foo.txt',line)
        line += 1
        print("new===========================:"+url_str)
        if not url_str is None:
            try:
                f = urllib.request.urlopen(url_str, timeout=3)
                content = f.read()
                print("after========================:"+content)
                s1 = 0
            except BaseException:
                s1 = 0
                content = ""
                line+=1
        else:
            exit
    elif(re.match(r'(http(s)?)|(ftp(s)?)://\S+'.encode('utf-8'), content[m1:m2])):
            print(content[m1:m2])
            fo.write(content[m1:m2].decode('utf-8') + "\n")
            max_count -= 1
fo.close()
print("end")


