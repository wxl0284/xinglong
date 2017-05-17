<?php
/**
 * 设备控制器
 */
namespace app\test\controller;

use think\Db;
use think\Session;
use think\Controller;
use think\Request;
use think\Cache;
use think\Cookie;

include_once (APP_PATH . 'common.php');     //引入公共函数文件

class Dev extends Controller
{
	//测试数据库
    public function db ()
    {
        $res = Db::table('at60ccdstatus')->select();
        dump($res);return;
    }
    
    //测试读取观测计划文件，并发送
    public function sendFile ()
    {
        $file = fopen(ROOT_PATH	.'public'.'/'.	'uploads/'.'20170429/1.txt', "r");
        $fileData=array();
        $i=0;
        
        while(!feof($file)) //输出文本中所有的行，直到文件结束为止。
        {
         $fileData[$i]= fgets($file);   //fgets()从文件指针中读取一行
         $i++;
        }
        fclose($file);
        array_filter($fileData);  //删除$fileData中等值为false的元素
        
        //遍历每行数据
        foreach ($fileData as $data)
        {
            //$str[0],$str[1]每个数组中包含每个指令
            $str[] = explode(' ', $data); 
            //pack,然后发送数据
        }
        
        print_r($str);
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
    
    //显示dev1 plan计划的表单
	public function dev1Plan ()
	{
		return view('dev1Plan');
	}
	
    //下面是发送数据的方法
    
    //接管望远镜指令
    public function dev1TakeOver ()
    {
        
        //定义全局$sequence 此变量在packHead()函数中要使用
        if (Cookie::has('sequence'))
        {
            $sequence = Cookie::get('sequence');
            Cookie::set('sequence', $sequence+1);
        }else{
            Cookie::set('sequence', 1);
            $sequence = 0;
        }
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 
        //望远镜
        //$at  = trim(Request::instance()->param('at')); 
          $at = 37;
        //$operation = trim(Request::instance()->param('operation'));  //操作指令标识
        $msg = 11; $magic = 439041101; $version = 1;
        
        if (input('takeOver') !== '')
        {
            $length = 28 +20;      //只发送头部前面的信息
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device=0);
            dump(input('takeOver'));return;
            $takeOver = trim(input('takeOver'));
            if (!preg_match('/^[0-1]$/', $takeOver))
            {
               echo '连接指令无效!'; return; 
            }
           //接管指令数据体
           $user = 1; 
           $occupation = input('takeOver');
           $start = time();
           $end = time() + 1000;
           $priority = 1;
           $sendMsg = pack('L', $user);     //uint32
           $sendMsg .= pack('S', $at);     //uint16
           $sendMsg .= pack('S', $occupation);     //uint16
           $sendMsg .= pack('L', $start);     //uint32
           $sendMsg .= pack('L', $end);     //uint32
           $sendMsg .= pack('L', $priority);     //uint32
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }
    }
    
	//发送dev1Gimbal数据
	public function dev1GimbalSendData ()
	{
		//定义全局$sequence 此变量在packHead()函数中要使用
        if (Cookie::has('sequence'))
        {
            $sequence = Cookie::get('sequence');
            Cookie::set('sequence', $sequence+1);
        }else{
            Cookie::set('sequence', 1);
            $sequence = 0;
        }
        //echo $sequence;return;
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 
        //望远镜
        $at  = Request::instance()->param('at'); 
         //望远镜子设备
        $device = Request::instance()->param('device');            
        $msg = 6; $magic = 439041101; $version = 1;
        //头部后部数据
        $user = 1;  $plan = 0; 
        
		//发送连接指令
		if (input('connect') !== '')
		{
			$connect = trim(input('connect'));
            if (!preg_match('/^[0-1]$/', $connect))
            {
               echo '连接指令无效!'; return; 
            }
			$length = 48 + 2;
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=1);
          
			$sendMsg = pack('S', $connect);  //unsigned short
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}elseif (input('findHome') !== '')	//发送找零指令
		{
			$findHome = trim(input('findHome'));
            if (!preg_match('/^\d{1}$/', $findHome))
            {
               echo '找零指令必须为数字!'; return; 
            }
			$length = 48 + 2;    //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=2);
			$sendMsg = pack('S', $findHome);  //unsigned short
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		}elseif (input('command') == 3)		//发送跟踪恒星指令
		{ 
			$length = 48 + 20;    //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=3);
			
			if (input('rightAscension') !== '')
			{
                //赤经
				$rightAscension = trim(input('rightAscension')); 
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $rightAscension))
                {
                    echo '赤经必须为数字！';return;
                }
				$sendMsg = pack('d', $rightAscension);     //double64
			}else{
				$sendMsg = pack('d', 0);
			}
			
			if (input('declination') !== '')
			{
                //赤纬
				$declination = trim(input('declination'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $declination))
                {
                    echo '赤纬必须为数字！';return;
                }
				$sendMsg .= pack('d', $declination);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			if (input('epoch') !== '')
			{
				$epoch = trim(input('epoch'));    //历元
                if (!preg_match('/^\d{1,10}$/', $epoch))
                {
                    echo '历元必须为数字！';return;
                }
				$sendMsg .= pack('S', $epoch);     //unsigned short
			}else{
				$sendMsg .= pack('S', 0);
			}
			
			if (input('speed') !== '')
			{
				$speed = trim(input('speed'));        //跟踪速度
                if (!preg_match('/^\d{1,10}$/', $speed))
                {
                    echo '历元必须为数字！';return;
                }
				$sendMsg .= pack('S', $speed);     //unsigned short
			}else{
				$sendMsg .= pack('S', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		} elseif (input('command') == 4)    //设置目标名称  指令
		{
			$length = 48 + 50;    //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=4);
			
			if (input('objectName') !== '')
			{
                //目标名称
				$objectName = trim(input('objectName')); 
                if (!preg_match('/^[a-zA-Z0-9]{1,48}$/', $objectName))
                {
                    echo '目标名称只能是数字字母！';return;
                }
				$sendMsg = pack('a48', $objectName);   //uint8,48表示长度
			}else{
				$sendMsg = pack('a48', '0');
			}
			
			if (input('objectType') !== '')
			{
                //目标类型
				$objectType = trim(input('objectType')); 
                if (!preg_match('/^\d{1,5}$/', $objectType))
                {
                    echo '目标名称只能是数字！';return;
                }
				$sendMsg .= pack('S', $objectType);     //unsigned short
			}else{
				$sendMsg .= pack('S', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
		} elseif (input('command') == 5)		//指向固定位置  指令
		{
			$length = 48 + 16;    //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=5);
			
			if (input('azimuth') !== '')
			{
                //方位
				$azimuth = trim(input('azimuth'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $azimuth))
                {
                    echo '方位必须为数字！';return;
                }
				$sendMsg = pack('d', $azimuth);     //double64
			}else{
				$sendMsg = pack('d', 0);
			}
			
			if (input('elevation') !== '')
			{
				//俯仰
                $elevation = trim(input('elevation'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $elevation))
                {
                    echo '俯仰必须为数字！';return;
                }
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
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=6);
            
            $slewDerotator = trim(input('slewDerotator'));
            if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $slewDerotator))
            {
                echo '轴3指向固定位置必须为数字！';return;
            }
			$sendMsg = pack('d', $slewDerotator);  //double64
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);
        }elseif (input('command') == 7)		//设置轴3工作模  指令	
		{
			$length = 48 + 10;    //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=7);
			
			if (input('mode') !== '')
			{
                //轴三工作模式
				$mode = trim(input('mode'));
                if (!preg_match('/^\d{1,15}$/', $mode))
                {
                    echo '轴三工作模式只能是数字！';return;
                }
				$sendMsg = pack('S', $mode);     //unsigned short
			}else{
				$sendMsg = pack('S', 0);
			}
			
			if (input('polarizingAngle') !== '')
			{
				//轴三 起偏角
                $polarizingAngle = trim(input('polarizingAngle'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $polarizingAngle))
                {
                    echo '轴三起偏角只能是数字！';return;
                }
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
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=8);
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);	
		}elseif (input('command') == 9)		//设置速度修正 
		{
			$length = 48 + 10;    //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=9);
			//轴
            if (input('axis') !== '')
			{
                //轴
				$axis = trim(input('axis'));
                if (!preg_match('/^\d{1,5}$/', $axis))
                {
                    echo '速度修正:轴必须为数字！';return;
                }
				$sendMsg = pack('S', $axis);     //unsigned short
			}else{
				$sendMsg = pack('S', 0);
			}
            
            if (input('correction') !== '')
			{
                //方位
				$correction = trim(input('correction'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $correction))
                {
                    echo '速度修正值必须为数字！';return;
                }
				$sendMsg .= pack('d', $correction);   //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
            
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('park') !== '')		//设置复位 指令
		{
			$length = 48;    //该结构体总长度, 只发送头部信息
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=10);
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);	
		}elseif (input('command') == 11)		//设置恒速运动
		{
			$length = 48 + 10;      //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=11);
			
			if (input('FixedMoveAxis') !== '')
			{
                //恒速运动  轴
				$FixedMoveAxis = trim(input('FixedMoveAxis'));
                if (!preg_match('/^\d{1,5}$/', $FixedMoveAxis))
                {
                    echo '恒速运动(轴参数)只能是数字！';return;
                }
				$sendMsg = pack('S', $FixedMoveAxis);  //unsigned short
			}else{
				$sendMsg = pack('S', 0);
			}
			
			if (input('FixedMoveSpeed') !== '')
			{
                //恒速运动  速度
				$FixedMoveSpeed = trim(input('FixedMoveSpeed'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $FixedMoveSpeed))
                {
                    echo '恒速运动(速度)只能是数字！';return;
                }
				$sendMsg .= pack('d', $FixedMoveSpeed);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('command') == 12)	 //位置修正 
		{
			$length = 48 + 10;      //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=12);
			
			if (input('PositionCorrectAxis') !== '')
			{
                //位置修正 轴参数
				$PositionCorrectAxis = trim(input('PositionCorrectAxis'));
                if (!preg_match('/^\d{1,5}$/', $PositionCorrectAxis))
                {
                    echo '位置修正(轴参数)只能是数字！';return;
                }
				$sendMsg = pack('S', $PositionCorrectAxis);  //16位
			}else{
				$sendMsg = pack('S', 0);
			}
			
			if (input('PositionCorrectVal') !== '')
			{
				// 修正值
                $PositionCorrectVal = trim(input('PositionCorrectVal'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $PositionCorrectVal))
                {
                    echo '位置修正值只能是数字！';return;
                }
				$sendMsg .= pack('d', $PositionCorrectVal);     //double64
			}else{
				$sendMsg .= pack('d', 0);
			}
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('openCover') !== '')		//镜盖操作
		{
			$length = 48 + 2;      //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=13);
			
			$openCover = trim(input('openCover'));
            if (!preg_match('/^\d{1,5}$/', $openCover))
            {
                echo '镜盖只能是数字！';return;
            }
			$sendMsg = pack('S', $openCover);     //unsigned short
			
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		}elseif (input('setFocusType') !== '')		//焦点切换镜操作
		{
			$length = 48 + 2;      //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=14);
			
			$setFocusType = trim(input('setFocusType'));
            if (!preg_match('/^\d{1,5}$/', $setFocusType))
            {
                echo '焦点切换镜只能是数字！';return;
            }
			$sendMsg = pack('S', $setFocusType);   //unsigned short
			//socket发送数据
			$sendMsg = $headInfo . $sendMsg;
			echo udpSend($sendMsg);		
		} elseif (input('emergenceStop') !== '') //急停  无参数
		{
			$length = 48;      //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=15);
			
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);		
		} elseif (input('configProperties') !== '') //属性设置  无参数
		{
			$length = 48;      //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=18);
			
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);		
		}elseif (input('saveSyncData') !== '') //保存同步数据  无参数
		{
			$length = 48;      //该结构体总长度
			$headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=16);
			
			//socket发送数据
			$sendMsg = $headInfo;
			echo udpSend($sendMsg);		
		}
    
	}
    
    //发送dev1 ccd数据
    public function dev1CcdSendData ()
    {
        //定义全局$sequence 此变量在packHead()函数中要使用
        if (Cookie::has('sequence'))
        {
            $sequence = Cookie::get('sequence');
            Cookie::set('sequence', $sequence+1);
        }else{
            Cookie::set('sequence', 1);
            $sequence = 0;
        }
  
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 
        //望远镜
        $at  = Request::instance()->param('at'); 
         //望远镜子设备
        $device = Request::instance()->param('device');            
        $msg = 6; $magic = 439041101; $version = 1; 
        //头部后部数据
        $user = 1;  $plan = 0;
        
        if (input('connect') !== '')		//发送连接指令
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=1);
            $connect = trim(input('connect'));
            if (!preg_match('/^[0-1]$/', $connect))
            {
               echo '连接指令无效!'; return; 
            }
           
            $sendMsg = pack('S', $connect);   //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }elseif (input('temperature') !== '')		//设置制冷温度 
        {
            $length = 48 +8;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=2);
            
            $temperature = trim(input('temperature'));
            if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $temperature))
            {
                echo '制冷温度只能是数字！'; return;
            }
            $sendMsg = pack('d', $temperature);     //double64
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 3)		//设置曝光策略
        {
            $length = 48 + 264;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=3);
            
            if (input('validFlag') !== '')      //数据有效标志位
            {
                $validFlag = trim(input('validFlag'));
                if (!preg_match('/^\d{1,5}$/', $validFlag))
                {
                    echo '数据有效标志位只能是数字！'; return;
                }
                $sendMsg = pack('d', $validFlag);//原来为Q格式
            }else{
                $sendMsg = pack('d', 0); //unsigned long long
            }
            
            if (input('startTime') !== '')      //起始时间
            {
                $startTime = trim(input('startTime'));
                if (!preg_match('/^\d{1,10}$/', $startTime))
                {
                    echo '起始时间只能是数字！'; return;
                }
                $sendMsg .= pack('I', $startTime);     
            }else{
                $sendMsg .= pack('I', 0);   //unsigned int
            }
            
            if (input('duration') !== '')       //曝光时间
            {
                $duration = trim(input('duration'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $duration))
                {
                    echo '曝光时间只能是数字！'; return;
                }
                $sendMsg .= pack('d', $duration);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('delay') !== '')      //延迟时间
            {
                $delay = trim(input('delay'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $delay))
                {
                    echo '延迟时间只能是数字！'; return;
                }
                $sendMsg .= pack('d', $delay);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('objectName') !== '')      //拍摄目标
            {
                $objectName = trim(input('objectName'));
                if (!preg_match('/^[a-zA-Z0-9]{1,24}$/', $objectName))
                {
                    echo '拍摄目标只能是字母和数字！'; return;
                }
                $sendMsg .= pack('a48', $objectName);     //objectName uint8-48
            }else{
                $sendMsg .= pack('a48', '0');
            }
            
            if (input('objectType') !== '')      //拍摄目标类型
            {
                $objectType = trim(input('objectType'));
                if (!preg_match('/^\d{1,5}$/', $objectType))
                {
                    echo '目标类型只能是数字！'; return;
                }
                $sendMsg .= pack('S', $objectType); 
            }else{
                $sendMsg .= pack('S', 0);  //unsigned short
            }
            
            if (input('objectRightAscension') !== '')  //当前拍摄目标赤经
            {
                $objectRightAscension = trim(input('objectRightAscension'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $objectRightAscension))
                {
                    echo '拍摄目标赤经只能是数字！'; return;
                }
                $sendMsg .= pack('d', $objectRightAscension);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('objectDeclination') !== '')    //当前拍摄目标赤纬
            {
                $objectDeclination = trim(input('objectDeclination'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $objectDeclination))
                {
                    echo '拍摄目标赤纬只能是数字！'; return;
                }
                $sendMsg .= pack('d', $objectDeclination);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('objectEpoch') !== '')      //当前拍摄目标历元
            {
                $objectEpoch = trim(input('objectEpoch'));
                if (!preg_match('/^\d{1,5}$/', $objectEpoch))
                {
                    echo '拍摄目标赤纬只能是数字！'; return;
                }
                $sendMsg .= pack('S', $objectEpoch);   
            }else{
                $sendMsg .= pack('S', 0);   //unsigned short
            }
            
            if (input('objectBand') !== '')      //当前拍摄波段
            {
                $objectBand = trim(input('objectBand'));      //objectBand
                if (!preg_match('/^[a-zA-Z0-9]{1,8}$/', $objectBand))
                {
                    echo '当前拍摄波段只能是8位字母数字！'; return;
                }
                $sendMsg .= pack('a8', $objectBand);     //uint8-8
            }else{
                $sendMsg .= pack('a8', '0');
            }
            
            if (input('objectFilter') !== '')      //拍摄波段滤光片系统
            {
                $objectFilter = trim(input('objectFilter'));
                if (!preg_match('/^\d{1,5}$/', $objectFilter))
                {
                    echo '当前拍摄波段只能是数字！'; return;
                }
                $sendMsg .= pack('S', $objectFilter);     //uint16
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            if (input('isSaveImage') !== '')      //是否保存图像
            {
                $isSaveImage = trim(input('isSaveImage'));
                if (!preg_match('/^\d{1,5}$/', $isSaveImage))
                {
                    echo '是否保存图像只能是数字！'; return;
                }
                $sendMsg .= pack('S', $isSaveImage);     
            }else{
                $sendMsg .= pack('S', 0);   //uint16
            }
            
            if (input('weatherGatherTime') !== '')   //气象数据采集时间
            {
                $weatherGatherTime = trim(input('weatherGatherTime'));
                if (!preg_match('/^\d{1,10}$/', $weatherGatherTime))
                {
                    echo '象数据采集时间只能是数字！'; return;
                }
                $sendMsg .= pack('I', $weatherGatherTime);     //uint32
            }else{
                $sendMsg .= pack('I', 0); //unsigned int
            }
            
            if (input('temperature1') !== '')      //温度
            {
                $temperature1 = trim(input('temperature1'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $temperature1))
                {
                    echo '温度只能是数字！'; return;
                }
                $sendMsg .= pack('d', $temperature1);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('humidity') !== '')      //湿度
            {
                $humidity = trim(input('humidity'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $humidity))
                {
                    echo '湿度只能是数字！'; return;
                }
                $sendMsg .= pack('d', $humidity);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('windSpeed') !== '')      //风速
            {
                $windSpeed = trim(input('windSpeed'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $windSpeed))
                {
                    echo '风速只能是数字！'; return;
                }
                $sendMsg .= pack('d', $windSpeed);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('pressure') !== '')      //气压
            {
                $pressure = trim(input('pressure'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $pressure))
                {
                    echo '气压只能是数字！'; return;
                }
                $sendMsg .= pack('d', $pressure);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('skyGatherTime') !== '')      //天气状态采集时间
            {
                $skyGatherTime = trim(input('skyGatherTime'));
                if (!preg_match('/^\d{1,10}$/', $skyGatherTime))
                {
                    echo '气象数据采集时间只能是数字！'; return;
                }
                $sendMsg .= pack('I', $skyGatherTime);     //uint32
            }else{
                $sendMsg .= pack('I', 0);   //unsigned int
            }
            
            if (input('skyState') !== '')      //天气状态
            {
                $skyState = trim(input('skyState'));
                if (!preg_match('/^\d{1,5}$/', $skyState))
                {
                    echo '天气状态只能是数字！'; return;
                }
                $sendMsg .= pack('S', $skyState);     
            }else{
                $sendMsg .= pack('S', 0);   //unsigned short
            }
            
            if (input('clouds') !== '')      //云量
            {
                $clouds = trim(input('clouds'));
                if (!preg_match('/^\d{1,5}$/', $clouds))
                {
                    echo '云量只能是数字！'; return;
                }
                $sendMsg .= pack('S', $clouds);  
            }else{
                $sendMsg .= pack('S', 0); //unsigned short
            }
            
            if (input('seeingGatherTime') !== '')      //视宁度采集时间
            {
                $seeingGatherTime = trim(input('seeingGatherTime'));
                if (!preg_match('/^\d{1,10}$/', $seeingGatherTime))
                {
                    echo '视宁度采集时间只能是数字！'; return;
                }
                $sendMsg .= pack('I', $seeingGatherTime);     //uint32
            }else{
                $sendMsg .= pack('I', 0); //unsigned int
            }
            
            if (input('seeing') !== '')      //视宁度
            {
                $seeing = trim(input('seeing'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $seeing))
                {
                    echo '视宁度只能是数字！'; return;
                }
                $sendMsg .= pack('d', $seeing);     //double
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('dustGatherTime') !== '')      //粉尘采集时间
            {
                $dustGatherTime = trim(input('dustGatherTime'));
                if (!preg_match('/^\d{1,10}$/', $dustGatherTime))
                {
                    echo '粉尘采集时间只能是数字！'; return;
                }
                $sendMsg .= pack('I', $dustGatherTime);     //uint32
            }else{
                $sendMsg .= pack('I', 0);
            }
            
            if (input('dust') !== '')      //粉尘
            {
                $dust = trim(input('dust'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $dust))
                {
                    echo '粉尘数据只能是数字！'; return;
                }
                $sendMsg .= pack('d', $dust);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('AMS') !== '')      //AMS
            {
                $AMS = trim(input('AMS'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $AMS))
                {
                    echo 'AMS数据只能是数字！'; return;
                }
                $sendMsg .= pack('d', $AMS);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('extinctionGatherTime') !== '')      //消光系数采集时间
            {
                $extinctionGatherTime = trim(input('extinctionGatherTime'));
                if (!preg_match('/^\d{1,10}$/', $extinctionGatherTime))
                {
                    echo '消光系数采集时间只能是数字！'; return;
                }
                $sendMsg .= pack('I', $extinctionGatherTime);     
            }else{
                $sendMsg .= pack('I', 0); //unsigned int
            }
            
            if (input('rightAscension') !== '')      //赤经
            {
                $rightAscension = trim(input('rightAscension'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $rightAscension))
                {
                    echo '赤经只能是数字！'; return;
                }
                $sendMsg .= pack('d', $rightAscension);     
            }else{
                $sendMsg .= pack('d', 0); //double64
            }
            
            if (input('declination') !== '')      //赤纬
            {
                $declination = trim(input('declination'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $declination))
                {
                    echo '赤纬只能是数字！'; return;
                }
                $sendMsg .= pack('d', $declination);     
            }else{
                $sendMsg .= pack('d', 0); //double64
            }
            
            if (input('band') !== '')      //波段
            {
                $band = trim(input('band'));
                if (!preg_match('/^[a-zA-Z0-9]{1,8}$/', $band))
                {
                    echo '波段只能是数字！'; return;
                }
                $sendMsg .= pack('a8', $band);     //band  uint8-8
            }else{
                $sendMsg .= pack('a8', '0');
            }
            //消光系数1
            if (input('extinctionFactor1') !== '')      
            {
                $extinctionFactor1 = trim(input('extinctionFactor1'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $extinctionFactor1))
                {
                    echo '消光系数1只能是数字！'; return;
                }
                $sendMsg .= pack('d', $extinctionFactor1);     
            }else{
                $sendMsg .= pack('d', 0); //double64
            }
            
            if (input('extinctionFactor2') !== '')      //消光系数2
            {
                 $extinctionFactor2 = trim(input('extinctionFactor2'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $extinctionFactor2))
                {
                    echo '消光系数2只能是数字！'; return;
                }
                $sendMsg .= pack('d', $extinctionFactor2);     
            }else{
                $sendMsg .= pack('d', 0);//double64
            }
            
            if (input('extinctionFactor3') !== '')      //消光系数3
            {
                 $extinctionFactor3 = trim(input('extinctionFactor3'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $extinctionFactor3))
                {
                    echo '消光系数3只能是数字！'; return;
                }
                $sendMsg .= pack('d', $extinctionFactor3);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('telescopeRightAscension') !== '')      //望远镜赤经
            {
                $telescopeRightAscension = trim(input('telescopeRightAscension'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $telescopeRightAscension))
                {
                    echo '望远镜赤经只能是数字！'; return;
                }
                $sendMsg .= pack('d', $telescopeRightAscension);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('telescopeDeclination') !== '')      //望远镜赤纬
            {
                $telescopeDeclination = trim(input('telescopeDeclination'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $telescopeDeclination))
                {
                    echo '望远镜赤纬只能是数字！'; return;
                }
                $sendMsg .= pack('d', $telescopeDeclination);     //double64
            }else{
                $sendMsg .= pack('d', 0);
            }
            
            if (input('focusLength') !== '')      //焦距
            {
                $focusLength = trim(input('focusLength'));
                if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $focusLength))
                {
                    echo '焦距数据只能是数字！'; return;
                }
                $sendMsg .= pack('d', $focusLength);     //double64
            }else{
                    $sendMsg .= pack('d', 0);
            }
            
            if (input('frameNum') !== '')      //帧数
            {
                $frameNum = trim(input('frameNum'));
                if (!preg_match('/^\d{1,10}$/', $frameNum))
                {
                    echo '帧数只能是数字！'; return;
                }
                $sendMsg .= pack('I', $frameNum);     //uint32
            }else{
                $sendMsg .= pack('I', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);		
        }elseif (input('command') == 4)		//开始曝光 指令 
        {
            $length = 48 +6;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=4);
            
            if (input('isReadFrameSeq') !== '')      //是否读取帧序号
            {
                $isReadFrameSeq = trim(input('isReadFrameSeq'));
                if (!preg_match('/^\d{1,5}$/', $isReadFrameSeq))
                {
                    echo '是否读取帧序号只能是数字！'; return;
                }
                $sendMsg = pack('S', $isReadFrameSeq);    //unsigned short
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('frameSequence') !== '')      //起始时间
            {
                $frameSequence = trim(input('frameSequence'));
                if (!preg_match('/^\d{1,10}$/', $frameSequence))
                {
                    echo '起始时间只能是数字！'; return;
                }
                $sendMsg .= pack('I', $frameSequence);    //unsigned int
            }else{
                $sendMsg .= pack('I', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
            
        }elseif (input('command') == 5)      //停止曝光
        {
            $length = 48 ;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=5);
            
            //socket发送数据        
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 6)      //终止曝光
        {
            $length = 48 ;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=6);
            
            //socket发送数据        
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 7)		//设置增益 指令
        {
            $length = 48 +4;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=7);
            
            if (input('mode') !== '')      //增益模式
            {
                $mode = trim(input('mode'));
                if (!preg_match('/^\d{1,5}$/', $mode))
                {
                    echo '增益模式只能是数字！'; return;
                }
                $sendMsg = pack('S', $mode);     //unsigned short
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('gear') !== '')      //增益档位
            {
                $gear = trim(input('gear'));
                if (!preg_match('/^\d{1,5}$/', $gear))
                {
                    echo '增益模式只能是数字！'; return;
                }
                $sendMsg .= pack('S', $gear);     //unsigned short
            }else{
                $sendMsg .= pack('S', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
            
        }elseif (input('ReadSpeedMode') !== '')   //读出速度模式值
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=8);
            
        
            $ReadSpeedMode = trim(input('ReadSpeedMode'));
            if (!preg_match('/^\d{1,10}$/', $ReadSpeedMode))
            {
                echo '读出速度模式值只能是数字！'; return;
            }
            $sendMsg = pack('S', $ReadSpeedMode);     //unsigned short
                            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }elseif (input('SetTransferSpeed') !== '') //转移速度模式值
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=9);
            
            $SetTransferSpeed = trim(input('SetTransferSpeed'));
            if (!preg_match('/^\d{1,10}$/', $SetTransferSpeed))
            {
                echo '转移速度模式值只能是数字！'; return;
            }
            $sendMsg = pack('S', $SetTransferSpeed);     //uint32
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 9)     //设置BIN
        {
            $length = 48 +8;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=10);
            
            if (input('BinX') !== '')      //binx
            {
                $BinX = trim(input('BinX'));
                if (!preg_match('/^\d{1,10}$/', $BinX))
                {
                    echo 'BinX值只能是数字！'; return;
                }
                $sendMsg = pack('I', $BinX);     //uint32
            }else{
                $sendMsg = pack('I', 0);
            }
            
            if (input('BinY') !== '')      //BinY
            {
                $BinY = trim(input('BinY'));
                if (!preg_match('/^\d{1,10}$/', $BinY))
                {
                    echo 'BinY值只能是数字！'; return;
                }
                $sendMsg .= pack('I', $BinY);     //uint32
            }else{
                $sendMsg .= pack('I', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);	
        }elseif (input('command') == 10 )      //设置ROI 指令
        {
            $length = 48 + 16;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=11);
            
            if (input('startX') !== '')      //startX
            {
                $startX = trim(input('startX'));
                if (!preg_match('/^\d{1,10}$/', $startX))
                {
                    echo 'startX值只能是数字！'; return;
                }
                $sendMsg = pack('I', $startX);     //unsigned int
            }else{
                $sendMsg = pack('I', 0);
            }
            
            if (input('startY') !== '')      //unsigned int
            {
                $startY = trim(input('startY'));
                if (!preg_match('/^\d{1,10}$/', $startY))
                {
                    echo 'startY值只能是数字！'; return;
                }
                $sendMsg .= pack('I', $startY);     //unsigned int
            }else{
                $sendMsg .= pack('I', 0);
            }
            
            if (input('imageWidth') !== '')      //imageWidth
            {
                $imageWidth = trim(input('imageWidth'));
                if (!preg_match('/^\d{1,10}$/', $imageWidth))
                {
                    echo 'imageWidth值只能是数字！'; return;
                }
                $sendMsg .= pack('I', $imageWidth);     //unsigned int
            }else{
                $sendMsg .= pack('I', 0);
            }
            
            if (input('imageHeight') !== '')      //imageWidth
            {
                $imageHeight = trim(input('imageHeight'));
                if (!preg_match('/^\d{1,10}$/', $imageHeight))
                {
                    echo 'imageHeight值只能是数字！'; return;
                }
                $sendMsg .= pack('I', $imageHeight);     //unsigned int
            }else{
                $sendMsg .= pack('I', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('shutter') !== '')  //设置快门指令
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=12);
            
            $shutter = trim(input('shutter'));
            if (!preg_match('/^\d{1,10}$/', $shutter))
            {
                echo 'shutter值只能是数字！'; return;
            }
            $sendMsg = pack('S', $shutter);     //unsigned short
    
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('isFullFrame') !== '')       //设置帧转移
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=13);
            
            $isFullFrame = trim(input('isFullFrame'));
            if (!preg_match('/^\d{1,10}$/', $isFullFrame))
            {
                echo 'isFullFrame值只能是数字！'; return;
            }
            $sendMsg = pack('S', $isFullFrame);     //unsigned short
    
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('command') == 13 )     //SetEM     指令
        {
            $length = 48 + 6;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=14);
            
            if (input('isEM') !== '')      //isEM
            {
                $isEM = trim(input('isEM'));
                if (!preg_match('/^\d{1,5}$/', $isEM))
                {
                    echo 'isEM值只能是数字！'; return;
                }
                $sendMsg = pack('S', $isEM);     //unsigned short
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('eMValue') !== '')      //eMValue
            {
                $eMValue = trim(input('eMValue'));
                if (!preg_match('/^\d{1,10}$/', $eMValue))
                {
                    echo 'eMValue值只能是数字！'; return;
                }
                $sendMsg .= pack('I', $eMValue);     //unsigned int
            }else{
                $sendMsg .= pack('I', 0);
            }
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('isNoiseFilter') !== '' )  //isNoiseFilter
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=15);
            
            $isNoiseFilter = trim(input('isNoiseFilter'));
            if (!preg_match('/^\d{1,5}$/', $isNoiseFilter))
            {
                echo 'isNoiseFilter值只能是数字！'; return;
            }
            $sendMsg = pack('S', $isNoiseFilter);     //unsigned short
                
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('command') == 15 )     //SetBaseline 指令
        {
            $length = 48 + 6;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=16);
            
            if (input('isBaseline') !== '')      //isBaseline
            {
                $isBaseline = trim(input('isBaseline'));
                if (!preg_match('/^\d{1,5}$/', $isBaseline))
                {
                    echo 'isBaseline值只能是数字！'; return;
                }
                $sendMsg = pack('S', $isBaseline);     //unsigned short
            }else{
                $sendMsg = pack('S', 0);
            }
            
            if (input('baselineValue') !== '')      //baselineValue
            {
                $baselineValue = trim(input('baselineValue'));
                if (!preg_match('/^\d{1,10}$/', $baselineValue))
                {
                    echo 'baselineValue值只能是数字！'; return;
                }
                $sendMsg .= pack('I', $baselineValue);     //unsigned int
            }else{
                $sendMsg .= pack('I', 0);
            }
                
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('isOverScan') !== '')   //set over scan
        {
            $length = 48 + 2;      //该结构体总长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=17);
            
            $isOverScan = trim(input('isOverScan'));  //isOverScan
            if (!preg_match('/^\d{1,5}$/', $isOverScan))
            {
                echo 'isOverScan值只能是数字！'; return;
            }
            $sendMsg = pack('S', $isOverScan);     //unsigned short
            
            //socket发送数据        
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }
            
	}
		
        
    //发送dev1 滤光片数据
    public function dev1FilterSendData ()
    {
        //定义全局$sequence 此变量在packHead()函数中要使用
        if (Cookie::has('sequence'))
        {
            $sequence = Cookie::get('sequence');
            Cookie::set('sequence', $sequence+1);
        }else{
            Cookie::set('sequence', 1);
            $sequence = 0;
        }
  
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 
        //望远镜
        $at  = Request::instance()->param('at'); 
         //望远镜子设备
        $device = Request::instance()->param('device');            
        $msg = 6; $magic = 439041101; $version = 1;
        //头部后部数据
        $user = 1;  $plan = 0;
            
        if (input('connect') !== '')     //发送连接指令
        {
            $length = 48 +2;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=1);
            
            $connect = trim(input('connect'));
            $sendMsg = pack('S', $connect ); //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('filterPosition') !== '')  //设置滤光片位置
        {
            $length = 48 + 2;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=2);
            
            $filterPosition = trim(input('filterPosition'));
            if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            }
            $sendMsg = pack('S', $filterPosition);  //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('filterFindHome') !== '')    //滤光片找零 无参数
        {
            $length = 48;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=3);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }
    }
	
    //发送设备1 随动圆顶指令
    public function dev1SlaveDomeSendData ()
    {
        //定义全局$sequence 此变量在packHead()函数中要使用
        if (Cookie::has('sequence'))
        {
            $sequence = Cookie::get('sequence');
            Cookie::set('sequence', $sequence+1);
        }else{
            Cookie::set('sequence', 1);
            $sequence = 0;
        }
  
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 
        //望远镜
        $at  = Request::instance()->param('at'); 
         //望远镜子设备
        $device = Request::instance()->param('device');            
        $msg = 6; $magic = 439041101; $version = 1;
        //头部后部数据
        $user = 1;  $plan = 0;
          
        if (input('command') == 1)     //发送连接指令
        {
            $length = 48 +2;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=1);
            
            $connect = input('connect');
            $sendMsg = pack('S', $connect); //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('domePosition') !== '')   //设置圆顶目标方位
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=2);
            
            $domePosition = trim(input('domePosition')); //double64
            if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $domePosition))
            {
                echo '圆顶位置的值必须是数字！';return;
            }
            $sendMsg = pack('d', $domePosition);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('shadePosition') !== '')      //设置风帘 
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=3);
            
            $shadePosition = trim(input('shadePosition'));
            if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $shadePosition))
            {
                echo '风帘位置的值必须是数字！';return; //double64
            }
        
            $sendMsg = pack('d', $shadePosition);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('RotateSpeed') !== '')      //设置转动速度
        {
            $length = 48 + 8;      //结构体长度
           $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=4);
            
            $RotateSpeed = trim(input('RotateSpeed'));    //double64
            if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $RotateSpeed))
            {
                echo '转动速度值必须是数字！';return; //double64
            }
            $sendMsg = pack('d', $RotateSpeed);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('command') == 5)          //停止运动
        {
            $length = 48;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=5);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }elseif (input('OpenScuttle') !== '')      //开关天窗
        {
            $length = 48 + 4;      //结构体长度
           $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=6);
            
            $OpenScuttle = trim(input('OpenScuttle'));      //uint32
            if (!preg_match('/^\d{1,10}$/', $OpenScuttle))
            {
                echo '开关天窗值必须是数字！';return; 
            }
            $sendMsg = pack('L', $OpenScuttle);
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('shadeAction') !== '')      //控制风帘运动
        {
            $length = 48 + 4;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=7);
            
            $shadeAction = trim(input('shadeAction'));    //uint32
            if (!preg_match('/^\d{1,10}$/', $shadeAction))
            {
                echo '风帘运动值必须是数字！';return; 
            }
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
        if (Cookie::has('sequence'))
        {
            $sequence = Cookie::get('sequence');
            Cookie::set('sequence', $sequence+1);
        }else{
            Cookie::set('sequence', 1);
            $sequence = 0;
        }
  
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 
        //望远镜
        $at  = Request::instance()->param('at'); 
         //望远镜子设备
        $device = Request::instance()->param('device');            
        $msg = 6; $magic = 439041101; $version = 1;
        //头部后部数据
        $user = 1;  $plan = 0;
        
        if (input('openDome') !== '')     //打开  全开圆顶
        {
            $length = 48 + 2;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=2);
            
            $openDome = trim(input('openDome'));
            if (!preg_match('/^\d{1,10}$/', $openDome))
            {
                echo '打开圆顶的值必须是数字！';return; 
            }
            $sendMsg = pack('S', $openDome);    //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('domeConnect') !== '')      //全开圆顶  连接
        {
            $length = 48 + 2;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=1);
            
            $domeConnect = input('domeConnect');
            $sendMsg = pack('S', $domeConnect);  //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }
    }
    
    //发送dev1  调焦器指令
    public function dev1FocusSendData ()
    {
        //定义全局$sequence 此变量在packHead()函数中要使用
        if (Cookie::has('sequence'))
        {
            $sequence = Cookie::get('sequence');
            Cookie::set('sequence', $sequence+1);
        }else{
            Cookie::set('sequence', 1);
            $sequence = 0;
        }
  
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 
        //望远镜
        $at  = Request::instance()->param('at'); 
         //望远镜子设备
        $device = Request::instance()->param('device');            
        $msg = 6; $magic = 439041101; $version = 1;
        //头部后部数据
        $user = 1;  $plan = 0;
        
        if (input('connect') !== '')     //连接指令 
        {
            $length = 48 + 2;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=1);
            
            $connect = trim(input('connect'));
            $sendMsg = pack('S', $connect);  //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('setPosition') !== '')      //设置目标位置
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=2);
            
            $setPosition = trim(input('setPosition'));
            if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $setPosition))
            {
                echo '目标位置的值必须是数字！';return; 
            }
            $sendMsg = pack('d', $setPosition);    //double64
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('speed') !== '')     //设置恒速转动
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=3);
            
            $speed = trim(input('speed'));
            if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $speed))
            {
                echo '恒速转动的值必须是数字！';return; 
            }
            $sendMsg = pack('d', $speed);    //double64
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('stop') !== '')   //停止运动
        {
            $length = 48 ;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=4);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }elseif (input('enable') !== '')   //使能温度补偿
        {
            $length = 48 + 2;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=5);
            
            $enable = trim(input('enable'));
            if (!preg_match('/^\d{1,5}$/', $enable))
            {
                echo '使能温度补偿的值必须是数字！';return; 
            }
            $sendMsg = pack('S', $enable);      //uint16
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('coefficient') !== '')   //使能温度补偿系数
        {
            $length = 48 + 8;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=6);
            
            $coefficient = trim(input('coefficient'));
            if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $coefficient))
            {
                echo '温度补偿系数的值必须是数字！';return; 
            }
            $sendMsg = pack('d', $coefficient);      //double64
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }elseif (input('command') == 7)      //找零  指令
        {
            $length = 48 ;      //结构体长度
            $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);

            $headInfo .= packHead2 ($user,$plan,$at,$device,$sequence,$operation=7);
            
            //socket发送数据
            $sendMsg = $headInfo;
            echo udpSend($sendMsg);
        }
    }
    
    //发送计划 plan
    public function dev1PlanSendData ()
    {
        //定义全局$sequence 此变量在packHead()函数中要使用
        if (Cookie::has('sequence'))
        {
            $sequence = Cookie::get('sequence');
            Cookie::set('sequence', $sequence+1);
        }else{
            Cookie::set('sequence', 1);
            $sequence = 0;
        }
  
        if (!Request::instance()->param())
        {
            echo '提交数据失败！';
            return;
        } 
        //望远镜
        $at  = Request::instance()->param('at'); 
         //望远镜子设备
        $device = Request::instance()->param('device'); 
        $msg = 8; $magic = 439041101; $version = 1;
        //头部后部数据
        $user = 1;  $plan = 0;
        
        $length = 28 + 71;      //结构体长度
        $headInfo = packHead($magic,$version,$msg,$length,$sequence,$at,$device);
        
        if (input('at') !== '')     //连接指令 
        {
            $at = trim(input('at'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg = pack('S', $at);  //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
            echo udpSend($sendMsg);
        }else{
            $sendMsg = pack('S', 0);  //unsigned short
            //socket发送数据
            $sendMsg = $headInfo . $sendMsg;
        }
        
        
        if (input('user') !== '')
        {
            $user = trim(input('user'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('a48', $user);  //unsigned short
        }else{
            $sendMsg .= pack('a48', '0');  //unsigned short
        }
        
        if (input('project') !== '')
        {
            $project = trim(input('project'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('a48', $project);  //unsigned short
        }else{
            $sendMsg .= pack('a48', '0');  //unsigned short
        }
        
        if (input('target') !== '')
        {
            $target = trim(input('target'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('a48', $target);  //unsigned short
        }else{
            $sendMsg .= pack('a48', '0');  //unsigned short
        }
        
        if (input('type') !== '')
        {
            $type = trim(input('type'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('I', $type);  //unsigned int
        }else{
            $sendMsg .= pack('I', 0);  //unsigned int
        }
        
        if (input('rightAscension') !== '')
        {
            $rightAscension = trim(input('rightAscension'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('d', $rightAscension);  //unsigned int
        }else{
            $sendMsg .= pack('d', 0);  //unsigned int
        }
        
        if (input('declination') !== '')
        {
            $declination = trim(input('declination'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('d', $declination);  //unsigned int
        }else{
            $sendMsg .= pack('d', 0);  //unsigned int
        }
        
        if (input('epoch') !== '')
        {
            $epoch = trim(input('epoch'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('I', $epoch);  //unsigned int
        }else{
            $sendMsg .= pack('I', 0);  //unsigned int
        }
        
        if (input('exposureTime') !== '')
        {
            $exposureTime = trim(input('exposureTime'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('d', $exposureTime);  //unsigned int
        }else{
            $sendMsg .= pack('d', 0);  //unsigned int
        }
        
        if (input('delayTime') !== '')
        {
            $delayTime = trim(input('delayTime'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('d', $delayTime);  //unsigned int
        }else{
            $sendMsg .= pack('d', 0);  //unsigned int
        }
        
        if (input('exposureCount') !== '')
        {
            $exposureCount = trim(input('exposureCount'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('I', $exposureCount);  //unsigned int
        }else{
            $sendMsg .= pack('I', 0);  //unsigned int
        }
        
        if (input('filter') !== '')
        {
            $filter = trim(input('filter'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('a8', $filter);  //unsigned int
        }else{
            $sendMsg .= pack('a8', '0');  //unsigned int
        }
        
        if (input('gain') !== '')
        {
            $gain = trim(input('gain'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('S', $gain);  //unsigned int
        }else{
            $sendMsg .= pack('S', 0);  //unsigned int
        }
        
        if (input('bin') !== '')
        {
            $bin = trim(input('bin'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('S', $bin);  //unsigned int
        }else{
            $sendMsg .= pack('S', 0);  //unsigned int
        }
        
        if (input('readout') !== '')
        {
            $readout = trim(input('readout'));
            /* if (!preg_match('/^\d{1,5}$/', $filterPosition))
            {
                echo '滤光片位置必须是数字！';return;
            } */
            $sendMsg .= pack('S', $readout);  //unsigned int
        }else{
            $sendMsg .= pack('S', 0);  //unsigned int
        }
        
        //socket发送数据
        echo udpSend($sendMsg);
    }
		
	

}