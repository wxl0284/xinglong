<?php
/**
 * @原始页面内容
 */
namespace app\index\controller;

use think\Db;
use think\Session;
use think\Controller;

class Page extends Controller
{
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
}