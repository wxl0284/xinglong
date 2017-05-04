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
	//显示导航页面
	public function index ()
	{
		return view('navPage');
	}
	
	//显示dev1 Gimbal表单
	public function dev1Gimbal ()
	{
		return view('dev1Gimbal');
	}
	
	//显示dev1 ccd表单
	public function dev1Ccd ()
	{
		return view('dev1Ccd');
	}
	
	//发送dev1Gimbal数据
	public function dev1GimbalSendData ()
	{
		//dump(input(''));
		//定义全局$sequence 此变量在packHead()函数中要使用
        $sequence = 0;
		//echo input('command');die;
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 

        $at     = trim(Request::instance()->param('at'));                     //望远镜
        $device = trim(Request::instance()->param('device'));                   //望远镜子设备
        $operation = trim(Request::instance()->param('operation'));             //操作指令标识
        
		//发送连接指令
		if (input('connect') !== '')
		{
			$connect = input('connect');
			$length = 48 + 4;
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			$sendMsg = pack('L', $connect);  //uint32
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}elseif (input('findHome') !== '')	//发送找零指令
		{
			$findHome = input('findHome');
			$length = 48 + 4;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			$sendMsg = pack('L', $findHome);  //uint32
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}elseif (input('command') == 3)		//发送跟踪恒星指令
		{ 
			$length = 48 + 24;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			if (input('rightAscension') !== '')
			{
				$rightAscension = input('rightAscension');
				$sendMsg = pack('d', $rightAscension);     //double64
			}else{
				$sendMsg = pack('d', 0);
			}
			
			if (input('declination') !== '')
			{
				$declination = input('declination');
				$sendMsg .= pack('d', $declination);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			if (input('epoch') !== '')
			{
				$epoch = input('epoch');
				$sendMsg .= pack('L', $epoch);     //uint32
			}else{
				$sendMsg .= pack('L', 0);
			}
			
			if (input('speed') !== '')
			{
				$speed = input('speed');
				$sendMsg .= pack('L', $speed);     //uint32
			}else{
				$sendMsg .= pack('L', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		} elseif (input('command') == 4)		//设置目标名称  指令
		{
			$length = 48 + 10;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			if (input('objectName') !== '')
			{
				$objectName = input('objectName');
				$sendMsg = pack('a*', $objectName);     //uint8 数字字母48
			}else{
				$sendMsg = pack('a', '0');
			}
			
			if (input('objectType') !== '')
			{
				$objectType = input('objectType');
				$sendMsg .= pack('L', $objectType);     //uint32
			}else{
				$sendMsg .= pack('L', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		} elseif (input('command') == 5)		//指向固定位置  指令
		{
			$length = 48 + 16;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			if (input('azimuth') !== '')
			{
				$azimuth = input('azimuth');
				$sendMsg = pack('d', $azimuth);     //double64
			}else{
				$sendMsg = pack('d', 0);
			}
			
			if (input('elevation') !== '')
			{
				$elevation = input('elevation');
				$sendMsg .= pack('d', $elevation);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}elseif (input('command') == 7)					//设置轴3工作模式  指令
		{
			$length = 48 + 12;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			if (input('mode') !== '')
			{
				$mode = input('mode');
				$sendMsg = pack('L', $mode);     //uint32
			}else{
				$sendMsg = pack('L', 0);
			}
			
			if (input('polarizingAngle') !== '')
			{
				$polarizingAngle = input('polarizingAngle');
				$sendMsg .= pack('d', $polarizingAngle);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);			
		}elseif (input('stop') !== '')	//停止  指令，将$operation 定为8即可，
		{
			$length = 48;    //该结构体总长度, 只发送头部信息
			$headInfo = packHead($at, $device, $sequence, $operation=8, $length);
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);	
		}elseif (input('TrackSpeed') !== '')		//设置跟踪速度 指令
		{
			$length = 48 + 8;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			$TrackSpeed = input('TrackSpeed');
			$sendMsg = pack('d', $TrackSpeed);     //double64
	
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('park') !== '')		//设置复位 指令
		{
			$length = 48;    //该结构体总长度, 只发送头部信息
			$headInfo = packHead($at, $device, $sequence, $operation=10, $length);
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);	
		}elseif (input('command') == 11)		//设置恒速运动   指令
		{
			$length = 48 + 12;      //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			if (input('FixedMoveAxis') !== '')
			{
				$FixedMoveAxis = input('FixedMoveAxis');
				$sendMsg = pack('L', $FixedMoveAxis);     //uint32
			}else{
				$sendMsg = pack('L', 0);
			}
			
			if (input('FixedMoveSpeed') !== '')
			{
				$FixedMoveSpeed = input('FixedMoveSpeed');
				$sendMsg .= pack('d', $FixedMoveSpeed);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('command') == 12)			//位置修正  指令
		{
			$length = 48 + 12;      //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			if (input('PositionCorrectAxis') !== '')
			{
				$PositionCorrectAxis = input('PositionCorrectAxis');
				$sendMsg = pack('L', $PositionCorrectAxis);     //uint32
			}else{
				$sendMsg = pack('L', 0);
			}
			
			if (input('PositionCorrectVal') !== '')
			{
				$PositionCorrectVal = input('PositionCorrectVal');
				$sendMsg .= pack('d', $PositionCorrectVal);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('openCover') !== '')		//镜盖操作  指令
		{
			$length = 48 + 4;      //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation, $length);
			
			$openCover = input('openCover');
			$sendMsg = pack('L', $openCover);     //uint32
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('setFocusType') !== '')		//焦点切换镜操作  指令
		{
			$length = 48;      //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=14, $length);
			
			/* $setFocusType = input('setFocusType');
			$sendMsg = pack('L', $setFocusType);     //uint32 */
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);		
		}/* elseif (input('emergenceStop') !== '')		//急停  指令
		{
			$length = 48;      //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=14, $length);
			
			/* $setFocusType = input('setFocusType');
			$sendMsg = pack('L', $setFocusType);     //uint32 
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);		
		} */
	}	
		//发送dev1 ccd数据
		public function dev1CcdSendData ()
		{
			//定义全局$sequence 此变量在packHead()函数中要使用
			$sequence = 0;
			//echo input('command');die;
			if (!Request::instance()->param())
			{
				echo '提交数据失败！';
				return;
			} 

			$at     = trim(Request::instance()->param('at'));                     //望远镜
			$device = trim(Request::instance()->param('device'));                   //望远镜子设备
			$operation = trim(Request::instance()->param('operation'));             //操作指令标识
			
			if (input('connect') !== '')		//发送连接指令
			{
				$length = 48;      //该结构体总长度
				$headInfo = packHead($at, $device, $sequence, $operation=1, $length);
				
				/* $setFocusType = input('setFocusType');
				$sendMsg = pack('L', $setFocusType);     //uint32 */
				//socket发送数据
				$sendMsg = $headInfo;
				echo udpSend($sendMsg);	
			}elseif (input('temperature') !== '')		//设置制冷温度 
			{
				$length = 48 +8;      //该结构体总长度
				$headInfo = packHead($at, $device, $sequence, $operation, $length);
				
				$temperature = input('temperature');
				$sendMsg = pack('d', $temperature);     //double64
				//socket发送数据
				$sendMsg = $headInfo . $sendMsg;
				echo udpSend($sendMsg);	
			}elseif (input('command') == 3)		//设置曝光策略
			{
				$length = 48 + 202;      //该结构体总长度
				$headInfo = packHead($at, $device, $sequence, $operation, $length);
				
				if (input('PositionCorrectAxis') !== '')
				{
					$PositionCorrectAxis = input('PositionCorrectAxis');
					$sendMsg = pack('L', $PositionCorrectAxis);     //uint32
				}else{
					$sendMsg = pack('L', 0);
				}
				
				if (input('PositionCorrectVal') !== '')
				{
					$PositionCorrectVal = input('PositionCorrectVal');
					$sendMsg .= pack('d', $PositionCorrectVal);     //double64
				}else{
					$sendMsg .= pack('d', 0);
				}
				
				//socket发送数据
				$sendMsg = $headInfo . $sendMsg;
				echo udpSend($sendMsg);		
			}
		}
		
		//XXX
		
	

}