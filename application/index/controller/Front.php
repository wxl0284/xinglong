<?php
namespace app\index\controller;

use think\Db;
use think\Session;
use think\Controller;

class Front extends Controller
{
		//首先执行此方法
		public function _initialize ()
		{
			//未登录
			if (!Session::has('login'))
			{
				$this->error('请完成注册/登录后，再进行相关操作！', 'index/index');
			}   
				
		}
		
		//显示主页
		public function index()
		{
			
			return $this->fetch('front');	        
				
		}

			//显示设备1页面
		public function dev1()
		{	
			//return $this->fetch('dev1');
			$this->redirect('index/page/dev_1_1');

		}

			//显示设备2页面
		public function dev2()
		{

			return $this->fetch('dev2');         
				
		}

		//测试socket
		public function socket ()
		{
				
				function udpGet ($sendMsg = '', $ip = '192.168.2.125', $port = '4545')
				{ 
					$handle = stream_socket_client("udp://{$ip}:{$port}", $errno, $errstr); 

					if( !$handle ){
					 echo "ERROR: {$errno} - {$errstr}\n"; 
					} 

					fwrite($handle, $sendMsg."\n"); 
					//$result = fread($handle, 1024); 
					fclose($handle); 
					//return $result; 
				} 
				
				$result = udpGet('qqqq'); 
				//echo $result;

	}

	    //显示上传表单页面
	    public function uploadForm ()
	    {
	    	return $this->fetch('upload');
	    }

	    //文件上传/////////////////////////////////////////////////
		public function upload ()
		{
			// 获取表单上传文件 
			$file = request()->file('file');
			//上传文件验证
			$result = $this->validate(
							['file' => $file],
							['file' => 'file|require|fileExt:txt|fileSize:1024|fileMime:txt'],
							['file.require' => '请选择上传文件',
							 'file.fileExt' => '文件后缀名必须为txt',
							 'file.fileSize' => '文件大小超出1k',
							 'file.fileMime' => '文件格式错误']);
			if (true !== $result)
			{
				return $this->error($result);
			}
			// 移动到框架应用根目录/public/uploads/ 目录下
			$dir = date('Y/m/d', time());
			$dir = str_replace('/', '', $dir);
			$info = $file/* ->validate(['size'=>10000,'ext'=>'txt', 'type'=>'txt']) */->move(ROOT_PATH . 'public' . DS . 'uploads/'.$dir,'');
			if($info){
				// 成功上传后 获取上传信息
				echo '文件上传成功！';
				// $dir = substr($info->getSaveName(), 0, 8);
				// $oldname = ROOT_PATH . 'public' . DS . 'uploads'.str_replace('\\', '/', $info->getSaveName());
				//  $newname = ROOT_PATH . 'public' . DS . 'uploads/'. $dir.'/abc.txt';
				
				 //rename($oldname, $newname);
			}else{// 上传失败获取错误信息
				echo $file->getError();
			}			 
				
		}

}