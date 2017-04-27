<?php
/**
 * 设备控制器
 */
namespace app\index\controller;

use think\Db;
use think\Session;
use think\Controller;

class Dev1 extends Controller
{
    //显示主页
    public function sendData()
    {
        if (Session::get('login') !== null)
        { 
            //已登录，可以执行操作
             $sendMsg = '';  //要发送的数据
             // $validFlag = trim($_POST['validFlag']);
             // $sendMsg .= pack('l', $validFlag);   //UINT16 n:无符号16整数

             // $startTime =  trim($_POST['startTime']);
             // $sendMsg = pack('L', $startTime);      //UINT32
             
             // $duration = trim($_POST['duration']);
             // $sendMsg .= pack('d', $duration);      //DOUBLE64

                $delay = trim($_POST['delay']);
               // $delay = $delay + 0;
                echo $delay;
                $sendMsg .= pack('l', $delay);      //DOUBLE64
            
                 // $objectName =  trim($_POST['objectName']);
                 // $sendMsg .= pack('A24', $objectName);      //UINT8 C:无符号8位整数

            //  $objectType = trim($_POST['objectType']);
            //  $sendMsg .= pack('l', $objectType);      //UINT16 n:无符号16整数

            //  $objectRightAscension = trim($_POST['objectRightAscension']);
            //  $sendMsg .= pack('d', $objectRightAscension);      //DOUBLE64 

            //  $objectDeclination = trim($_POST['objectDeclination']);
            //  $sendMsg .= pack('d', $objectDeclination);      //DOUBLE64 

            //  $objectEpoch =  trim($_POST['objectEpoch']);
            //  $sendMsg .= pack('l', $objectEpoch);      //UINT16 n:无符号16整数

            //  $objectBand =  trim($_POST['objectBand']);
            //  $sendMsg .= pack('C', $objectBand);      //UINT8 C:无符号8位整数

            //  $objectFilter = trim($_POST['objectFilter']);
            //  $sendMsg .= pack('l', $objectFilter);      //UINT16 n:无符号16整数

            //  $isSaveImage =  trim($_POST['isSaveImage']);
            //  $sendMsg .= pack('l', $isSaveImage);      //UINT16 n:无符号16整数

            //  $weatherGatherTime =  trim($_POST['weatherGatherTime']);
            //  $sendMsg .= pack('L', $weatherGatherTime);      //UINT32 L:无符号32整数

            //  $temperature = trim($_POST['temperature']);
            //  $sendMsg .= pack('d', $temperature);      //DOUBLE64

            //  $humidity = trim($_POST['humidity']);
            //  $sendMsg .= pack('d', $humidity);      //DOUBLE64

            //  $windSpeed = trim($_POST['windSpeed']);
            //  $sendMsg .= pack('d', $windSpeed);      //DOUBLE64

            //  $pressure = trim($_POST['pressure']);
            //  $sendMsg .= pack('d', $pressure);      //DOUBLE64

            //  $skyGatherTime = trim($_POST['skyGatherTime']);
            //  $sendMsg .= pack('L', $skyGatherTime);      //UINT32 L:无符号32整数

            //  $skyState =  trim($_POST['skyState']);
            //  $sendMsg .= pack('l', $skyState);      //UINT16 n:无符号16整数

            // $clouds =  trim($_POST['clouds']);
            // $sendMsg .= pack('l', $clouds);      //UINT16 n:无符号16整数

            // $seeingGatherTime =  trim($_POST['seeingGatherTime']);
            // $sendMsg .= pack('L', $seeingGatherTime);      //UINT32 L:无符号32整数

            // $seeing = trim($_POST['seeing']);
            // $sendMsg .= pack('d', $seeing);      //DOUBLE64

            // $dustGatherTime =  trim($_POST['dustGatherTime']);
            // $sendMsg .= pack('L', $dustGatherTime);      //UINT32 L:无符号32整数

            // $dust = trim($_POST['dust']);
            // $sendMsg .= pack('d', $dust);      //DOUBLE64

            // $AMS = trim($_POST['AMS']);
            // $sendMsg .= pack('d', $AMS);      //DOUBLE64

            // $extinctionGatherTime =  trim($_POST['extinctionGatherTime']);
            // $sendMsg .= pack('L', $extinctionGatherTime);      //UINT32 L:无符号32整数

            // $rightAscension = trim($_POST['rightAscension']);
            // $sendMsg .= pack('d', $rightAscension);      //DOUBLE64

            // $declination = trim($_POST['declination']);
            // $sendMsg .= pack('d', $declination);      //DOUBLE64

            // $band =  trim($_POST['band']);
            // $sendMsg .= pack('C', $band);      //UINT8 C:无符号8位整数

            // $extinctionFactor1 = trim($_POST['extinctionFactor1']);
            // $sendMsg .= pack('d', $extinctionFactor1);      //DOUBLE64

            // $extinctionFactor2 = trim($_POST['extinctionFactor2']);
            // $sendMsg .= pack('d', $extinctionFactor2);      //DOUBLE64

            // $extinctionFactor3 = trim($_POST['extinctionFactor3']);
            // $sendMsg .= pack('d', $extinctionFactor3);      //DOUBLE64

            // $telescopeRightAscension = trim($_POST['telescopeRightAscension']);
            // $sendMsg .= pack('d', $telescopeRightAscension);      //DOUBLE64

            // $telescopeDeclination = trim($_POST['telescopeDeclination']);
            // $sendMsg .= pack('d', $telescopeDeclination);      //DOUBLE64

            // $focusLength = trim($_POST['focusLength']);
            // $sendMsg .= pack('d', $focusLength);      //DOUBLE64

            // $frameNum = trim($_POST['frameNum']);
            // $sendMsg .= pack('L', $frameNum);      //UINT32 L:无符号32整数

            //echo $sendMsg;

            //socket发送数据
            //
            function udpGet ($sendMsg = '', $ip = '192.168.2.125', $port = '4545')
            { 
              $handle = stream_socket_client("udp://{$ip}:{$port}", $errno, $errstr); 

              if( !$handle ){
               echo "ERROR: {$errno} - {$errstr}\n"; 
              } 


              fwrite($handle, $sendMsg."\n");
              
              fclose($handle); 
              
            } 
            //socket发送数据
            $send = udpGet($sendMsg); 

            /*function udpGet ($sendMsg = '', $ip = '192.168.2.125', $port = '4545')
            { 
                $handle = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);

                if (!$handle)
                {
                    echo '数据通信失败！';
                    return; 
                }
                
                $connect = socket_connect($handle, $ip, $port);

                if (!$connect)
                {
                    echo '连接后台控制中心失败!';
                    return;
                }

                //发送数据
                socket_write($handle, $sendMsg);
            } 
            //socket发送数据
            $send = udpGet($sendMsg); */

        }else{//未登录，显示登录页

            $this->error('请完成注册/登录后，再进行相关操作！', 'index/index');
        }            
        
    }

}