<?php
/**
 * 设备控制器
 */
namespace app\index\controller;

use think\Db;
use think\Session;
use think\Controller;
use think\Request;
include_once (APP_PATH . 'common.php');     //引入公共函数文件

class Dev1 extends Controller
{
    //发送数据
    public function sendData()
    {
        //定义全局$sequence 此变量在packHead()函数中要使用
        $sequence = 0;

        if (!Request::instance()->post())
        {
            echo '网络异常，请重新提交指令！';
            return;
        }
        //dump(Request::instance()->post());return;
        //获取ajax提交的数据
        $at     = trim(Request::instance()->post('at'));                     //望远镜
        $device = trim(Request::instance()->post('device'));                   //望远镜子设备
        $operation = trim(Request::instance()->post('operation'));             //操作指令标识
        //进行头部信息的打包
        $headInfo = packHead($at, $device, $sequence, $operation);

        // $postData = trim(Request::instance()->post('validFlag'));          //提交来的指令数据
        // $type     = trim(Request::instance()->post('type'));

        //$packData = packData($postData, $type);         //将提交的指令pack
        //dump($packData); return;
        //下面是逐个打包每个指令, 占位
      /*   if (input('?post.validFlag'))  
        {
            $validFlag = trim(input('validFlag'));
            if (!preg_match('/^\d{1,5}$/', $validFlag))      //uint16
            {
              echo '只能输入整数！uint16'; return;
            }else{
              $sendMsg = pack('S', $validFlag); //第一个不用 .=, 后面的要用.=连接
            }

        }else{ 
            $sendMsg .= pack('S', 0);   //uint16
        } */
		
		 if (input('?post.validFlag'))  
        {
            $validFlag = trim(input('validFlag'));
            if (!preg_match('/^\d{1,5}$/', $validFlag))      //uint16
            {
              echo '只能输入整数！uint16'; return;
            }else{
              $sendMsg = pack('S', $validFlag); //第一个不用 .=, 后面的要用.=连接
            }

        }else{ 
            $sendMsg .= pack('S', 0);   //uint16
        }

        // if (input('?post.startTime'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('L', 0);   //uint32
        // }
        
        // if (input('?post.duration'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //double64
        // }
             
        // if (input('?post.delay'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //double64
        // }    

                
        // if (input('?post.objectName'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('a', '0');   //uint8
        // }     
    
        // if (input('?post.objectType'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('S', 0);   //uint16
        // } 
            
        // if (input('?post.objectRightAscension'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }
            
        // if (input('?post.objectDeclination'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }
        
        // if (input('?post.objectEpoch'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('S', 0);   //DOUBLE64
        // }

        // if (input('?post.objectBand'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('a', '0');   //UINT8
        // }

        // if (input('?post.objectFilter'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('S', 0);   //UINT16
        // }

        // if (input('?post.isSaveImage'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('S', 0);   //UINT16
        // }

        // if (input('?post.weatherGatherTime'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('L', 0);   //UINT32
        // }

        // if (input('?post.temperature'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.temperature'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.humidity'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }
         
        // if (input('?post.windSpeed'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }  

        // if (input('?post.pressure'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.skyGatherTime'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('L', 0);   //UINT32
        // }

        // if (input('?post.skyState'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('S', 0);   //UINT16
        // }

        // if (input('?post.clouds'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('S', 0);   //UINT16
        // }

        // if (input('?post.seeingGatherTime'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('L', 0);   //UINT32
        // }

        // if (input('?post.seeing'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.dustGatherTime'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('L', 0);   //UINT32
        // }

        // if (input('?post.dust'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.AMS'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.extinctionGatherTime'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.rightAscension'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.declination'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.band'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('a*', '0');   //UINT8
        // }

        // if (input('?post.extinctionFactor1'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.extinctionFactor2'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.extinctionFactor3'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.telescopeRightAscension'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.telescopeDeclination'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.focusLength'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('d', 0);   //DOUBLE64
        // }

        // if (input('?post.frameNum'))
        // {
        //     $sendMsg .= $packData;         
        // }else{
        //     $sendMsg .= pack('L', 0);   //DOUBLE64
        // }

        //瓶接完整pack数据
       // $sendMsg = $headInfo . $sendMsg;
       $sendMsg = $headInfo;
        //socket发送数据
        echo udpSend($sendMsg);

    }

}