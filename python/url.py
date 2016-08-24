#coding=utf-8
import urllib.request
import re
import linecache

def getURL(url,file_savepath="foo.txt",max_count=10):
    content = urllib.request.urlopen(url=url, timeout=3).read().decode("utf-8")
    fo = open(file_savepath, "w+")
    line_url_index = 1;
    anchor_index = 0
    while anchor_index >= 0 and max_count > 0:
        begin = content.find(r"<a",anchor_index)
        href_index = content.find(r'href=',begin)
        first_quota_index = content.find(r'"',href_index) + 1
        second_quota_index = content.find(r'"',first_quota_index)
        anchor_index = second_quota_index
        if begin <= 0 or anchor_index < 0:
            fo.close()
            fo = open(file_savepath, "a+")
            url_str = linecache.getline(file_savepath,line_url_index)
            line_url_index += 1
            print("new===========================")
            if not url_str is None:
                try:
                    content = urllib.request.urlopen(url_str, timeout=3).read().decode("utf-8")
                    anchor_index = 0
                except BaseException:
                    anchor_index = 0
                    content = ""
                    line_url_index+=1
            else:
                exit
        elif(re.match(r'(http(s)?)|(ftp(s)?)://\S+', content[first_quota_index:second_quota_index])):
                print(content[first_quota_index:second_quota_index])
                fo.write(content[first_quota_index:second_quota_index] + "\n")
                max_count -= 1
    fo.close()

getURL("http://www.hao123.com/", "foo.txt", 10000)

