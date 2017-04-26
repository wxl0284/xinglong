/* 
* 验证注册表单输入
*/

$(function () {
    //标题提交事件，验证提交数据
    $('input[type="button"]').click(function () {
          // console.log(username);
         var username   = $('input[name="username"]').val();
         var password   = $('input[name="password"]').val();
         var cfmpasd    = $('input[name="cfmpasd"]').val();

         var reg = new RegExp("^[a-zA-Z0-9-_]{6,10}$");
         //其他验证规则，match方法必须是string，所以获取提交的数据后直接进行判断，在php端转换类型
         // var uint8 = new RegExp("^[a-zA-Z0-9-_]{1,24}$");      //1-24字符；
         // var double64 = new RegExp("^(-?\\d+)(\\.\\d+)?$");     //浮点数
         // var isInt = new RegExp("^-?\\d+$");                    //整数

         var msg = ''; //错误提示

         if (!username.match(reg))  //用户名验证
         {
            msg += '用户名应为6-10位字母/数字组合\n';
         }

         if (!password.match(reg)) //密码验证

         {
            msg += '密码应为6-10位字母/数字组合\n';
         }

         if (!cfmpasd.match(reg)) //密码验证
         {
            msg += '密码应为6-10位字母/数字组合\n';
         }


        if (msg) //输入有错误
        {
             alert(msg); 
             return false;  //阻止提交
        }

           //ajax提交数据
           $.ajax ({
               type: 'post',
               url : '/index/index/doLogin',
               data:  {
                      username : username,
                      password : password,
                      cfmpasd  : cfmpasd,
                   },                  
            success:  function (info) {
                alert(info);
                
                 if (info.indexOf('注册成功') != -1)
                 {
                      window.location.href = '/index';
                 }
            },
            error:  function () {
                alert('网络异常,请重新提交');
            },
          });
                  
    });
});