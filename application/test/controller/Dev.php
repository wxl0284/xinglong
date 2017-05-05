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
	//测试fit
    public function fitTest ()
    {
        return view('testFit');
    }
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
    
    //显示dev1 滤光片表单
	public function dev1Filter ()
	{
		return view('dev1Filter');
	}
    
    //显示dev1 随动圆顶表单
	public function dev1SlaveDome ()
	{
		return view('dev1SlaveDome');
	}
    
    //显示dev1 全开式圆顶表单
	public function dev1OpenDome ()
	{
		return view('dev1OpenDome');
	}
    
    //显示dev1 调焦器表单
	public function dev1Focus ()
	{
		return view('dev1Focus');
	}
	
    //下面是发送数据的方法
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
			$headInfo = packHead($at, $device, $sequence, $operation=1, $length, $msg);
			$sendMsg = pack('L', $connect);  //uint32
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}elseif (input('findHome') !== '')	//发送找零指令
		{
			$findHome = input('findHome');
			$length = 48 + 4;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=2, $length, $msg);
			$sendMsg = pack('L', $findHome);  //uint32
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}elseif (input('command') == 3)		//发送跟踪恒星指令
		{ 
			$length = 48 + 24;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=3, $length, $msg);
			
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
			$headInfo = packHead($at, $device, $sequence, $operation=4, $length, $msg);
			
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
			$headInfo = packHead($at, $device, $sequence, $operation=5, $length, $msg);
			
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
		}elseif (input('slewDerotator') !== '')    //轴3指向固定位置 
        {
			$length = 48 + 8;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=6, $length, $msg);
            
            $slewDerotator = input('slewDerotator');
			$sendMsg = pack('d', $slewDerotator);  //double64
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
        }elseif (input('command') == 7)		//设置轴3工作模式  指令	
		{
			$length = 48 + 12;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=7, $length, $msg);
			
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
		}elseif (input('stop') !== '')	//停止 指令，将$operation=8，
		{
			$length = 48;    //该结构体总长度, 只发送头部信息
			$headInfo = packHead($at, $device, $sequence, $operation=8, $length, $msg);
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);	
		}elseif (input('TrackSpeed') !== '')		//设置跟踪速度 指令
		{
			$length = 48 + 8;    //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=9, $length, $msg);
			
			$TrackSpeed = input('TrackSpeed');
			$sendMsg = pack('d', $TrackSpeed);     //double64
	
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('park') !== '')		//设置复位 指令
		{
			$length = 48;    //该结构体总长度, 只发送头部信息
			$headInfo = packHead($at, $device, $sequence, $operation=10, $length, $msg);
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);	
		}elseif (input('command') == 11)		//设置恒速运动   指令
		{
			$length = 48 + 12;      //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=11, $length, $msg);
			
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
			$headInfo = packHead($at, $device, $sequence, $operation=12, $length, $msg);
			
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
			$headInfo = packHead($at, $device, $sequence, $operation=13, $length, $msg);
			
			$openCover = input('openCover');
			$sendMsg = pack('L', $openCover);     //uint32
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('setFocusType') !== '')		//焦点切换镜操作  指令
		{
			$length = 48 +4;      //该结构体总长度
			$headInfo = packHead($at, $device, $sequence, $operation=14, $length, $msg);
			
			$setFocusType = input('setFocusType');
			$sendMsg = pack('L', $setFocusType);     //uint32
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
            $headInfo = packHead($at, $device, $sequence, $operation=1, $length, $msg);
            
            /* $setFocusType = input('setFocusType');
            $sendMsg = pack('L', $setFocusType);     //uint32 */
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);	
        }elseif (input('temperature') !== '')		//设置制冷温度 
        {
            $length = 48 +8;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=2, $length, $msg);
            
            $temperature = input('temperature');
            $sendMsg = pack('d', $temperature);     //double64
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 3)		//设置曝光策略
        {
            $length = 48 + 202;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=3, $length, $msg);
            
            if (input('validFlag') !== '')      //数据有效标志位
            {
                $validFlag = input('validFlag');
                $sendMsg = pack('S', $validFlag);     //uint16
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('startTime') !== '')      //起始时间
            {
                $startTime = input('startTime');
                $sendMsg .= pack('S', $startTime);     //uint32
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('duration') !== '')       //曝光时间
            {
                $duration = input('duration');
                $sendMsg .= pack('d', $duration);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('delay') !== '')      //延迟时间
            {
                $delay = input('delay');
                $sendMsg .= pack('d', $delay);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('objectName') !== '')      //拍摄目标
            {
                $objectName = input('objectName');
                $sendMsg .= pack('a*', $objectName);     //uint8
            }else{
                $sendMsg .= pack('a*', '0');
            }
            
            if (input('objectType') !== '')      //拍摄目标类型
            {
                $objectType = input('objectType');
                $sendMsg .= pack('S', $objectType);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('objectRightAscension') !== '')      //当前拍摄目标赤经
            {
                $objectRightAscension = input('objectRightAscension');
                $sendMsg .= pack('d', $objectRightAscension);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('objectDeclination') !== '')      //当前拍摄目标赤纬
            {
                $objectDeclination = input('objectDeclination');
                $sendMsg .= pack('d', $objectDeclination);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('objectDeclination') !== '')      //当前拍摄目标赤纬
            {
                $objectDeclination = input('objectDeclination');
                $sendMsg .= pack('d', $objectDeclination);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('objectEpoch') !== '')      //当前拍摄目标历元
            {
                $objectEpoch = input('objectEpoch');
                $sendMsg .= pack('S', $objectEpoch);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('objectEpoch') !== '')      //当前拍摄目标历元
            {
                $objectEpoch = input('objectEpoch');
                $sendMsg .= pack('S', $objectEpoch);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('objectBand') !== '')      //当前拍摄波段
            {
                $objectBand = input('objectBand');
                $sendMsg .= pack('a*', $objectBand);     //uint8
            }else{
                $sendMsg .= pack('a*', '0');
            }
            
            if (input('objectFilter') !== '')      //拍摄波段滤光片系统
            {
                $objectFilter = input('objectFilter');
                $sendMsg .= pack('S', $objectFilter);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('isSaveImage') !== '')      //是否保存图像
            {
                $isSaveImage = input('isSaveImage');
                $sendMsg .= pack('S', $isSaveImage);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('weatherGatherTime') !== '')      //气象数据采集时间
            {
                $weatherGatherTime = input('weatherGatherTime');
                $sendMsg .= pack('L', $weatherGatherTime);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            if (input('temperature') !== '')      //温度
            {
                $temperature = input('temperature');
                $sendMsg .= pack('d', $temperature);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('humidity') !== '')      //湿度
            {
                $humidity = input('humidity');
                $sendMsg .= pack('d', $humidity);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('windSpeed') !== '')      //风速
            {
                $windSpeed = input('windSpeed');
                $sendMsg .= pack('d', $windSpeed);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('pressure') !== '')      //气压
            {
                $pressure = input('pressure');
                $sendMsg .= pack('d', $pressure);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('skyGatherTime') !== '')      //天气状态采集时间
            {
                $skyGatherTime = input('skyGatherTime');
                $sendMsg .= pack('L', $skyGatherTime);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            if (input('skyState') !== '')      //天气状态
            {
                $skyState = input('skyState');
                $sendMsg .= pack('S', $skyState);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('clouds') !== '')      //云量
            {
                $clouds = input('clouds');
                $sendMsg .= pack('S', $clouds);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('seeingGatherTime') !== '')      //视宁度采集时间
            {
                $seeingGatherTime = input('seeingGatherTime');
                $sendMsg .= pack('L', $seeingGatherTime);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            if (input('seeing') !== '')      //视宁度
            {
                $seeing = input('seeing');
                $sendMsg .= pack('d', $seeing);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('dustGatherTime') !== '')      //粉尘采集时间
            {
                $dustGatherTime = input('dustGatherTime');
                $sendMsg .= pack('L', $dustGatherTime);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            if (input('dust') !== '')      //粉尘
            {
                $dust = input('dust');
                $sendMsg .= pack('d', $dust);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('AMS') !== '')      //AMS
            {
                $AMS = input('AMS');
                $sendMsg .= pack('d', $AMS);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('extinctionGatherTime') !== '')      //消光系数采集时间
            {
                $extinctionGatherTime = input('extinctionGatherTime');
                $sendMsg .= pack('L', $extinctionGatherTime);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            if (input('rightAscension') !== '')      //赤经
            {
                $rightAscension = input('rightAscension');
                $sendMsg .= pack('d', $rightAscension);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('declination') !== '')      //赤纬
            {
                $declination = input('declination');
                $sendMsg .= pack('d', $declination);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('band') !== '')      //波段
            {
                $band = input('band');
                $sendMsg .= pack('a*', $band);     //uint8
            }else{
                $sendMsg .= pack('a*', '0');
            }
            
            if (input('extinctionFactor1') !== '')      //消光系数1
            {
                $extinctionFactor1 = input('extinctionFactor1');
                $sendMsg .= pack('d', $extinctionFactor1);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('extinctionFactor2') !== '')      //消光系数2
            {
                $extinctionFactor2 = input('extinctionFactor2');
                $sendMsg .= pack('d', $extinctionFactor2);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('extinctionFactor3') !== '')      //消光系数3
            {
                $extinctionFactor3 = input('extinctionFactor3');
                $sendMsg .= pack('d', $extinctionFactor3);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('telescopeRightAscension') !== '')      //望远镜赤经
            {
                $telescopeRightAscension = input('telescopeRightAscension');
                $sendMsg .= pack('d', $telescopeRightAscension);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('telescopeDeclination') !== '')      //望远镜赤纬
            {
                $telescopeDeclination = input('telescopeDeclination');
                $sendMsg .= pack('d', $telescopeDeclination);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('focusLength') !== '')      //焦距
            {
                $focusLength = input('focusLength');
                $sendMsg .= pack('d', $focusLength);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('frameNum') !== '')      //帧数
            {
                $frameNum = input('frameNum');
                $sendMsg .= pack('L', $frameNum);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);		
        }elseif (input('command') == 4)		//开始曝光 指令 
        {
            $length = 48 +6;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=4, $length, $msg);
            
            if (input('isReadFrameSeq') !== '')      //是否读取帧序号
            {
                $isReadFrameSeq = input('isReadFrameSeq');
                $sendMsg = pack('S', $isReadFrameSeq);     //uint16
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('frameSequence') !== '')      //起始时间
            {
                $frameSequence = input('frameSequence');
                $sendMsg .= pack('L', $frameSequence);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
            
        }elseif (input('command') == 5)      //停止曝光
        {
            $length = 48 ;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=5, $length, $msg);
            
            //socket发送数据        
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 6)      //终止曝光
        {
            $length = 48 ;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=6, $length, $msg);
            
            //socket发送数据        
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 7)		//设置增益 指令
        {
            $length = 48 +4;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=7, $length, $msg);
            
            if (input('mode') !== '')      //增益模式
            {
                $mode = input('mode');
                $sendMsg = pack('S', $mode);     //uint16
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('geer') !== '')      //起始时间
            {
                $geer = input('geer');
                $sendMsg .= pack('S', $geer);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
            
        }elseif (input('ReadSpeedMode') !== '')   //读出速度模式值
        {
            $length = 48 +4;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=8, $length, $msg);
            
        
            $ReadSpeedMode = input('ReadSpeedMode');
            $sendMsg = pack('L', $ReadSpeedMode);     //uint32
                            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }elseif (input('SetTransferSpeed') !== '') //转移速度模式值
        {
            $length = 48;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=9, $length, $msg);
                            
            //socket发送数据        
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 9)     //设置BIN
        {
            $length = 48 +8;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=10, $length, $msg);
            
            if (input('BinX') !== '')      //binx
            {
                $BinX = input('BinX');
                $sendMsg = pack('L', $BinX);     //uint32
            }else{
                $sendMsg = pack('L', 0);
            }
            
            if (input('BinY') !== '')      //BinY
            {
                $BinY = input('BinY');
                $sendMsg .= pack('L', $BinY);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 10 )      //设置ROI 指令
        {
            $length = 48 + 16;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=11, $length, $msg);
            
            if (input('startX') !== '')      //startX
            {
                $startX = input('startX');
                $sendMsg = pack('L', $startX);     //uint32
            }else{
                $sendMsg = pack('L', 0);
            }
            
            if (input('startY') !== '')      //startY
            {
                $startY = input('startY');
                $sendMsg .= pack('L', $startY);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            if (input('imageWidth') !== '')      //imageWidth
            {
                $imageWidth = input('imageWidth');
                $sendMsg .= pack('L', $imageWidth);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            if (input('imageHeight') !== '')      //imageWidth
            {
                $imageHeight = input('imageHeight');
                $sendMsg .= pack('L', $imageHeight);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('shutter') !== '')  //设置快门指令
        {
            $length = 48 + 4;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=12, $length, $msg);
            
            $shutter = input('shutter');
            $sendMsg = pack('L', $shutter);     //uint32
    
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input(isFullFrame) !== '')       //设置帧转移
        {
            $length = 48 + 4;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=13, $length, $msg);
            
            $isFullFrame = input('isFullFrame');
            $sendMsg = pack('L', $isFullFrame);     //uint32
    
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('command') == 13 )     //SetEM     指令
        {
            $length = 48 + 6;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=14, $length, $msg);
            
            if (input('isEM') !== '')      //isEM
            {
                $isEM = input('isEM');
                $sendMsg = pack('S', $isEM);     //uint16
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('eMValue') !== '')      //eMValue
            {
                $eMValue = input('eMValue');
                $sendMsg .= pack('L', $eMValue);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('isNoiseFilter') !== '' )  //isNoiseFilter
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=15, $length, $msg);
            
            $isNoiseFilter = input('isNoiseFilter');
            $sendMsg = pack('S', $isNoiseFilter);     //uint16
                
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('command') == 15 )        //SetBaseline 指令
        {
            $length = 48 + 6;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=16, $length, $msg);
            
            if (input('isBaseline') !== '')      //isBaseline
            {
                $isBaseline = input('isBaseline');
                $sendMsg = pack('S', $isBaseline);     //uint16
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('baselineValue') !== '')      //baselineValue
            {
                $baselineValue = input('baselineValue');
                $sendMsg .= pack('L', $baselineValue);     //uint32
            }else{
                $sendMsg .= pack('L', 0);
            }
                
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('isOverScan') !== '')   //set over scan 指令
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($at, $device, $sequence, $operation=17, $length, $msg);
            
            $isOverScan = input('isOverScan');      //isOverScan
            $sendMsg = pack('S', $isOverScan);     //uint16
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }
            
	}
		
        
    //发送dev1 滤光片数据
    public function dev1FilterSendData ()
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
            
            
        if (input('command') == 1)     //发送连接指令
        {
            $length = 48 ;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation=1, $length);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }elseif (input('filterPosition') !== '')      //设置滤光片位置
        {
            $length = 48 + 4;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $filterPosition = input('filterPosition');
            $sendMsg = pack('L', $filterPosition);
            //socket发送数据
            $sendMsg = $headInfo . $filterPosition;
            echo udpSend($sendMsg);
        }elseif (input('filterFindHome') !== '')      //滤光片找零
        {
            $length = 48;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation=3, $length);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }
    }
	
    //发送设备1 随动圆顶指令
    public function dev1SlaveDomeSendData ()
    {
        //定义全局$sequence 此变量在packHead()函数中要使用
        $sequence = 0;
        //echo input('command');die;
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 

        $at     = trim(Request::instance()->param('at'));            //望远镜
        $device = trim(Request::instance()->param('device'));       //望远镜子设备
        $operation = trim(Request::instance()->param('operation'));   //操作指令标识
          
        if (input('command') == 1)     //发送连接指令
        {
            $length = 48;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation=1, $length);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }elseif (input('domePosition') !== '')      //设置目标方位
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $domePosition = input('domePosition');      //double64
            $sendMsg = pack('d', $domePosition);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('shadePosition') !== '')      //设置风帘 
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $shadePosition = input('shadePosition');      //double64
            $sendMsg = pack('d', $shadePosition);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('RotateSpeed') !== '')      //设置转动速度
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $RotateSpeed = input('RotateSpeed');      //double64
            $sendMsg = pack('d', $RotateSpeed);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('command') == 5)          //停止运动
        {
            $length = 48;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation=5, $length);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }elseif (input('OpenScuttle') !== '')      //开关天窗
        {
            $length = 48 + 4;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $OpenScuttle = input('OpenScuttle');      //uint32
            $sendMsg = pack('L', $OpenScuttle);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('shadeAction') !== '')      //控制风帘运动
        {
            $length = 48 + 4;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $shadeAction = input('shadeAction');      //uint32
            $sendMsg = pack('L', $shadeAction);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }
    }
    
    //发送dev1  全开式圆顶指令
    public function dev1OpenDomeSendData ()
    {
        //定义全局$sequence 此变量在packHead()函数中要使用
        $sequence = 0;
        //echo input('command');die;
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 

        $at     = trim(Request::instance()->param('at'));            //望远镜
        $device = trim(Request::instance()->param('device'));       //望远镜子设备
        $operation = trim(Request::instance()->param('operation'));   //操作指令标识
        
        if (input('openDome') !== '')     //打开  全开圆顶
        {
            $length = 48 +4;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $openDome = input('openDome');
            $sendMsg = pack('L', $openDome);    //uint32
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('domeConnect') !== '')      //全开圆顶  连接
        {
            $length = 48 +4;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $domeConnect = input('domeConnect');
            $sendMsg = pack('L', $domeConnect);    //uint32
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }
    }
    
    //发送dev1  调焦器指令
    public function dev1FocusSendData ()
    {
         //定义全局$sequence 此变量在packHead()函数中要使用
        $sequence = 0;
        //echo input('command');die;
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 

        $at     = trim(Request::instance()->param('at'));            //望远镜
        $device = trim(Request::instance()->param('device'));       //望远镜子设备
        $operation = trim(Request::instance()->param('operation'));   //操作指令标识
        
        if (input('connect') !== '')     //打开  全开圆顶
        {
            $length = 48 +4;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $connect = input('connect');
            $sendMsg = pack('L', $connect);    //uint32
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('setPosition') !== '')      //设置目标位置
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $setPosition = input('setPosition');
            $sendMsg = pack('d', $setPosition);    //double64
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('speed') !== '')     //设置恒速转动
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation, $length, $msg);
            
            $speed = input('speed');
            $sendMsg = pack('d', $speed);    //double64
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('stop') !== '')   //停止运动
        {
            $length = 48 ;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation=4, $length);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }elseif (input('enable') !== '')   //使能温度补偿
        {
            $length = 48 + 2;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation=4, $length);
            
            $enable = input('enable');
            $sendMsg = pack('S', $enable);      //uint16
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('coefficient') !== '')   //使能温度补偿系数
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation=4, $length);
            
            $coefficient = input('coefficient');
            $sendMsg = pack('d', $coefficient);      //uint16
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('command') == 7)      //找零  指令
        {
             $length = 48 ;      //结构体长度
            $headInfo = packHead($at, $device, $sequence, $operation=7, $length);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }
    }
    //XXX  
		
	

}