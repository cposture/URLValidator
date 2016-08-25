## 适用场景
1. 对 url 实现准确匹配的场景可以使用

## 缺陷
1. 目前没有添加对 # 锚点的匹配
2. 匹配速度会比较慢（测试时逐行读文本匹配12000条url，共花7s）
3. 只支持 http 和 https
4. 不识别含有 “{”, “}”, “|”, “", ”^“,”~“,”[“, ”]“,和”\`" 等 RFC 文档中指定的不安全的字符，因为对方代码必须对URL中所有不安全的字符进行编码

## 测试
1. 通过 python 爬虫得到了 10000 个左右的正确 url，其中匹配出有效：10984，无效：60（包含#和|）

## RFC 文档
http://man.chinaunix.net/develop/rfc/RFC1738.txt

## 生成 url 数据

> 需要 python 3

```
python3 url.py
```

## 编译

> 需要安装 CMake

```shell
cd URLValidator
mkdir build
cd build
cmake ..
make
```

## 运行

```
# 生成 url 数据之后
mv ../python/foo.txt .
./URLValidator
```
