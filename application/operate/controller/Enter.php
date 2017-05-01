<?php
namespace app\operate\controller;

use think\Db;
use think\Session;
use think\Controller;

class Enter extends Controller
{
	//首先执行此方法
	public function _initialize ()
	{
		//未登录
		// if (!Session::has('login'))
		// {
		// 	$this->error('请完成注册/登录后，再进行相关操作！', 'index/index');
		// }   
		echo '123';
	}
	
	//
	public function front ()
	{
		return view('/404');
	}
}