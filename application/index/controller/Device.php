<?php
namespace app\index\controller;

 use think\Controller;
 use think\Db;
 use think\Session;

//设备控制器
class Device extends Controller
{
    //首先执行此方法
    public function _initialize ()
    {
        //未登录
        if (Session::get('login') === null)
        {
            $this->error('请完成注册/登录后，再进行相关操作！', 'index/index');
        }   
            
    }

    public function dev1 ()
    {
        //echo '我来啦' . time();
        $status = Db::table('dev1')
                ->where('pk_dev1', rand(1, 4))
                ->field('status, item')
                ->select();
        echo json_encode($status);
        //var_dump($status);die;
        //echo $status[0]['status'];
    }
}
