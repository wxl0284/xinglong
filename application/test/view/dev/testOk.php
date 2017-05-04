//----------------------
从中央气象台获取含有卫星云图的页面html代码
$a = file_get_contents('http://www.nmc.cn/publish/satellite/fy2.htm');

//正则获取卫星云图的<img>标签内容
$imgStr = preg_match('/<img id="imgpath"([\s\S]){50,260}不存在！\'">/', $a, $match);
          preg_match('/src="http:\/\/([\s\S]){50,200}\d+"/', $match[0], $match1);

echo $match1[0]; //即为实时的卫星云图
//-------------------------