<?php
/**
 * @原始页面内容
 */
namespace app\index\controller;

use think\Db;
use think\Session;
use think\Controller;
use think\Request;

class Page extends Controller
{
    public function _initialize ()
    {
        //未登录
            if (!Session::has('login'))
            {
                $this->error('请完成注册/登录后，再进行相关操作！', 'index/index');
            } 
    }
    
    //页面1 1米望远镜
    public function dev_1 ()
    {
        return view('dev_1');
    }

    //页面1 1米望远镜
    public function dev_1_1 ()
    {
       
        return view('dev_1_1');
    }

    //页面2 1米望远镜
    public function dev_2 ()
    {
        return view('dev_2');
    }

    //测试弹框插件
    public function dialog ()
    {
        return view('dialog');
    }

    //测试formData
    public function formdata ()
    {
        return view('formData');
    }

    //测试$_SERVER['PHP_SELF'] .'?'. $_SERVER['QUERY_STRING']
    public function test ()
    {
        dump(Request::instance()->param()); return;
        //rename('./22.txt', './33.txt');
        /*$nowUrl = substr($_SERVER['PHP_SELF'] . ($_SERVER['QUERY_STRING']?'?'.$_SERVER['QUERY_STRING']:''), 10);
        Session::set('url', $nowUrl);
        if (!Session::has('login'))
        {
            $this->error('请完成注册/登录后，再进行相关操作！', 'index/index');
        }*/ //判断登录，登陆后返回此页，验证ok

        /*//获取兴隆天气信息：101090404=兴隆
        $weatherData = file_get_contents('http://www.weather.com.cn/data/sk/101090404.html');
        print_r(json_decode($weatherData, true)); //转换为数组*/

        // 气温：.$info["temp"].℃;  
        // 风向： $info["WD"];  
        // 风力：$info["WS"];  
        // 湿度：$info["SD"];  
        // 更新时间 $info["time"]

        //return view('test');
    }
}