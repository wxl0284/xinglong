//----------------------
从中央气象台获取含有卫星云图的页面html代码，然后写入缓存
$a = file_get_contents('http://www.nmc.cn/publish/satellite/fy2.htm');

//正则获取卫星云图的<img>标签内容
$imgStr = preg_match('/<img id="imgpath"([\s\S]){50,260}不存在！\'">/', $a, $match);
          preg_match('/src="http:\/\/([\s\S]){50,200}\d+"/', $match[0], $match1);

echo $match1[0]; //即为实时的卫星云图
//-------------------------

//-------------------------如下为从中央气象台获取天气预报数据
//$a = file_get_contents('http://www.nmc.cn/publish/forecast/AHE/xinglong.html');    //从www.nmc.cn获取网站代码，然后写入tp文件缓存
//if ($a) {....进行下一步}，else {告知前端错误提示}
$a = file_get_contents('4.txt');//从缓存中读取数据，再进行处理

$res = preg_match('/今天[\s\S]*今天/', $a, $match);
//echo $match[0];return;
//因为白天和晚上的$match匹配结果有区别，因此要做判断
if (strpos($match[0],'colspan="2"'))    //晚上，天气，合二为一
{
    $res = preg_match_all('/> ?[^a-zA-Z\s]{2,} ?</', $match[0], $matchs);
    //获取天气图标
    preg_match('/http:[\S]*white[\S]{5,15}png/', $match[0],$matchImg);
    
    $nightPic = $matchImg[0][0];        //晚上的天气图标
    echo $nightPic;return;
    //天气状况
    $weather = str_replace(['<','>'], '', $matchs[0][2]);
    //温度
    $temperature = str_replace(['<','>'], '', $matchs[0][3]);
    //风向
    $wind = str_replace(['<','>'], '', $matchs[0][4]);
    //风力
    $windPower = str_replace(['<','>'], '', $matchs[0][5]);
    
}else{//白天，晚上均有预报
    preg_match_all('/> ?[^a-zA-Z\s]{2,} ?</', $match[0], $matchs);
    //获取天气图标
    preg_match_all('/http:[\S]*white[\S]{5,15}png/', $match[0],$matchImg);
   
    $dayPic = $matchImg[0][0];      //白天的气象图标
    $nightPic = $matchImg[0][1];    //晚上的气象图标
    //天气状况
    $weather = str_replace(['<','>'], '', $matchs[0][2]);
    $weather1 = str_replace(['<','>'], '', $matchs[0][3]);
    //温度
    $temperature = str_replace(['<','>'], '', $matchs[0][4]);
    $temperature1 = str_replace(['<','>'], '', $matchs[0][5]);
    //风向
    $wind = str_replace(['<','>'], '', $matchs[0][6]);
    $wind1 = str_replace(['<','>'], '', $matchs[0][7]);
    //风力
    $windPower = str_replace(['<','>'], '', $matchs[0][8]);
    $windPower1 = str_replace(['<','>'], '', $matchs[0][9]);
}