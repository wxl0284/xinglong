<?php
namespace app\index\controller;

use think\Db;
use think\Session;
use think\Controller;
use think\Request;

class Index extends Controller
{
    public function index()
    {
        
        return $this->fetch('index');
    }

    //注册页面
    public function login()
    {
        return $this->fetch('login');
    }

     //注册
    public function doLogin()
    {
        $username = trim($_POST['username']);
        $password = trim($_POST['password']);
        $cfmpasd  = trim($_POST['cfmpasd']);

        if ($password !== $cfmpasd)
        {
            echo '两次密码不一致！请重新输入。';
            return;
          
        }

        $data = ['username'=>$username, 'password'=>md5($password)];

        $userData =  Db::table('user')
                   ->where('username', $username)
                   ->find();
        
        if ($userData)
        {
            echo '失败！该用户名已注册！';
            
        }else{
            //写入数据库
            $res = Db::table('user')->insertGetId($data);
            if ($res !== false)
            {
                Session::set('login_display', false); //注册成功
                echo '注册成功！请登录后进行相关操作！';
            }
            
        }
 
    }

    //登录
     public function signIn ()
    {
        $username = trim(input('username'));
        $password = trim(input('password'));
        
        //验证数据 validate方法
        
        $result	=	$this->validate(
            [
            '用户名' =>	$username,
            '__token__'	=> input('__token__'),
            '密码' => $password,
            ],
            [
            '用户名' =>	'require|max:10|min:5',
            '__token__'	=>	'token',
            '密码' => 'require|min:6',
            ]);
        if(true	!==	$result)    //验证失败 输出错误信息
        { 
            return $this->error($result);
        }

        //判断登录用户名和密码有效性
        $userData = Db::table('user')
                    ->where('username', $username)
                    ->where('status', 1)
                    ->find();

        if (!$userData) //用户名不存在
        {
            $this->error('用户名或密码错误!');
        }

        //判断密码
        if(md5($password) != $userData['password'])
        {
            $this->error('用户名或密码错误!');
        }
        //存入sessionId
        
        //登录成功，写入session, 跳转至主页面
        Session::set('login', $userData['username']);
        Session::set('role', $userData['role']);
        
        //session中已有之前的url,则跳转回此url
        if (Session::has('url'))
        {
            $this->redirect(Session::get('url'));
        }
        $this->redirect('/index/front');
    }

    

    //退出登录
    public function logOut ()
    {   //清空session
        Session::clear();
        //返回首页
         return $this->fetch('index');
    }
}
