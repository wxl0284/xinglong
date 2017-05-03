<?php
// 应用公共文件

//pack表单提交的操作指令
//$at: 望远镜；$device: 该望远镜子设备；
//$sequence: 在thinkphp框架中的方法中定义
//$operation : 操作名称标识；

//返回值： pack成功，返回pack好的结构体数据

function packHead ($at, $device, $sequence, $operation, $length)
{
   // $head = '';                 //定义变量，存储pack后的数据
    //引入$sequence，此次pack自增1
    global $sequence;
    $sequence++;

    if (isset($magic))
    {
        $magic = $magic;
    }else{
        $magic = 0;
        //$magic = 4294836225;
    }

     $head = pack('L', $magic);  //uint32

    if (isset($majorVersion))
    {
        $majorVersion = $majorVersion;
    }else{
        $majorVersion = 0;
    }

    $head .= pack('S', $majorVersion);  //uint16


    if (isset($msg))
    {
        $msg = $msg;
    }else{
        $msg = 0;
    }

    $head .= pack('S', $msg);       //uint16

    if (isset($length))
    {
        $length = $length;      //要动态获取
    }else{
        $length = 0;
    }

    $head .= pack('L', $length);        //uint32

    if (isset($sequence))
    {
        $sequence = $sequence;
    }else{
        $sequence = 0;
    }

    $head .= pack('L', $sequence);      //uint32

    $tv_sec = time();

    $head .= pack('L', $tv_sec);        //uint32

    $tv_usec = substr(microtime(), 2, 8);

    $head .= pack('L', $tv_usec);        //uint32  精确到微妙 microtime();


    if (isset($at))
    {
        $at = $at;
    }else{
        $at = 0;
    }

    $head .= pack('S', $at);        //uint16

     if (isset($device))
    {
        $device = $device;
    }else{
        $device = 0;
    }

    $head .= pack('S', $device);    //uint16

    if (isset($user))
    {
        $user = $user;
    }else{
        //$user = 0;
        $user = 9999;
    }

    $head .= pack('L', $user);    //操作者id 

    if (isset($plan))
    {
        $plan = $plan;
    }else{
        $plan = 0;
    }

    $head .= pack('L', $plan);   //uint32

    if (isset($at))
    {
        $at = $at;
    }else{
        $at = 0;
    }

    $head .= pack('S', $at); //uint16

    if (isset($device))
    {
        $device = $device;
    }else{
        $device = 0;
    }

    $head .= pack('S', $device);    //uint16

    if (isset($sequence))
    {
        $sequence = $sequence;
    }else{
        $sequence = 0;
    }

    $head .= pack('L', $sequence);      //uint32

    if (isset($operation))
    {
        $operation = $operation;
    }else{
        $operation = 0;
    }

    $head .= pack('L', $operation);      //uint32

    return $head;
}


//packData(): 对ajax提交上来的数据进行验证和pack
//$dataName: 提交上来的指令名称
//$type : 数据类型（格式，用哪个格式进行pack）
function packData ($dataName, $type)
{ 
    //验证数据格式 pack数据
    switch ($type) {
        case 'uint8':   //仅限数字字母，不超过48字符
            if (!preg_match('/^[a-zA-Z0-9]{1,48}$/', $dataName))
            {
                echo '请输入至多48位字母数字!1';
                return;
            }else{
                $sendMsg = pack('a*', $dataName);
            }
            break;

        case 'uint16':   //0-65535,数字
        if (!preg_match('/^\d{1,5}$/', $dataName))
        {
              //echo '只能输入数字!2';
              return $dataName;
              return;
        }else{
                $sendMsg = pack('S', $dataName);
            }
        break;

        case 'uint32':   //0-4294836225,数字
        if (!preg_match('/^\d{1,10}$/', $dataName))
        {
              echo '只能输入数字!3';
              return;
        }else{
                $sendMsg = pack('L', $dataName);
            }
        break;

        case 'uint64':   //数字，长整型
        if (!preg_match('/^\d{1, 20}$/', $dataName))
        {
              echo '只能输入数字!4';
              return;
        }else{
                $sendMsg = pack('I', $dataName);
            }
        break;

        case 'int8':   //数字字母
        if (!preg_match('/^[a-zA-Z0-9]+$/', $dataName))
        {
              echo '只能输入数字和字母!5';
              return;
        }else{
                $sendMsg = pack('a*', $dataName);
            }
        break;

        case 'int16':   //有符号短整数
        if (!preg_match('/^-?\d{1,20}$/', $dataName))
        {
              echo '只能输入数字!6';
              return;
        }else{
                $sendMsg = pack('s', $dataName);
            }
        break;

        case 'int32':   //有符号整数
        if (!preg_match('/^-?\d{1,20}$/', $dataName))
        {
              echo '只能输入数字!7';
              return;
        }else{
                $sendMsg = pack('l', $dataName);
            }
        break;

        case 'double64':   //double64小数
        if (!preg_match('/^-?\d+(\.\d{0,15})?$/', $dataName))
        {
              echo '请输入小数!8';
              return;
        }else{
                $sendMsg = pack('d', $dataName);
            }
        break;

        
        default:
            echo '异常情况，请重新输入!';
            return;
    }

    return $sendMsg;

}


//udpSend(): udp协议下socket发送数据到后面控制端
//$sendMsg: 要发送的字串
//$ip : 目的端ip
//$port: 目的端程序端口


function udpSend ($sendMsg = '', $ip = '192.168.2.115', $port = '4747')
{ 
  $handle = stream_socket_client("udp://{$ip}:{$port}", $errno, $errstr); 

  if( !$handle ){
   return "ERROR: {$errno} - {$errstr}\n"; 
  } 


  $res = fwrite($handle, $sendMsg);
  
  fclose($handle); 

  if($res)
  {
    return '指令发送成功!';
  }else{
    return '指令发送失败!';
  }
  
} 
//socket发送数据
//$send = udpGet($sendMsg); 

                
