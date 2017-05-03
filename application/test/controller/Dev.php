<?php
/**
 * 设备控制器
 */
namespace app\test\controller;

use think\Db;
use think\Session;
use think\Controller;
use think\Request;
include_once (APP_PATH . 'common.php');     //引入公共函数文件

class Dev extends Controller
{
    //显示dev1 转台表单
	public function dev1_zhuanTai ()
	{
		return view('dev1_zhuanTai');
	}
	
	//发送dev1_zhuanTai数据
	public function dev1_zhuanTai_send ()
	{
		//dump(input(''));
		//定义全局$sequence 此变量在packHead()函数中要使用
        $sequence = 0;

        if (!Request::instance()->post())
        {
            echo '提交数据失败！';
            return;
        }

        $at     = trim(Request::instance()->post('at'));                     //望远镜
        $device = trim(Request::instance()->post('device'));                   //望远镜子设备
        $operation = trim(Request::instance()->post('operation'));             //操作指令标识
        
		//发送连接指令
		if (input('?post.connect'))
		{
			$connect = input('connect');
			$length = 48 + 4;
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			$sendMsg = pack('L', $connect);  //uint32
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}
		
		//发送找零指令
		if (input('?post.findHome'))
		{
			$findHome = input('findHome');
			$length = 48 + 4;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			$sendMsg = pack('L', $findHome);  //uint32
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}
		
		//发送跟踪恒星指令
		if (input('?post.TrackStar'))
		{
			//$findHome = input('findHome');
			$length = 48 + 24;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			if (input('?post.rightAscension'))
			{
				$rightAscension = input('rightAscension');
				$sendMsg = pack('d', $rightAscension);     //double64
			}else{
				$sendMsg = pack('d', 0);
			}
			
			if (input('?post.declination'))
			{
				$declination = input('declination');
				$sendMsg .= pack('d', $declination);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			if (input('?post.epoch'))
			{
				$epoch = input('epoch');
				$sendMsg .= pack('L', $epoch);     //uint32
			}else{
				$sendMsg .= pack('L', 0);
			}
			
			if (input('?post.speed'))
			{
				$speed = input('speed');
				$sendMsg .= pack('L', $speed);     //uint32
			}else{
				$sendMsg .= pack('L', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}
		
		//XXX
		
	}
	

}