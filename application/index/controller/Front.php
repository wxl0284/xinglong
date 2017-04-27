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

	    //文件上传
		public function upload ()
		{
			// 获取表单上传文件 例如上传了001.jpg
			$file = request()->file('file');
			// 移动到框架应用根目录/public/uploads/ 目录下
			$info = $file->move(ROOT_PATH . 'public' . DS . 'uploads');
			if($info){
				// 成功上传后 获取上传信息
				//echo $info->getExtension();		// 输出 txt
				
				//echo $info->getSaveName();		// 输出 20160820/42a79759f284b767dfcb2a0197904287.txt
				//$dir = substr($info->getSaveName(), 0, 8);
				//echo $info->getFilename(); 		// 输出 42a79759f284b767dfcb2a0197904287.txt
				// $oldname = '/uploads/'.$info->getSaveName();
				// $oldname = str_replace('\\', '/', $oldname);
				// $newname = '/uploads/'.$dir.'/abc.txt';
				// rename($oldname, $newname);
			}else{// 上传失败获取错误信息
				echo $file->getError();
			}			 
				
		}

}