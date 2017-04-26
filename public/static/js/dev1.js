/* 
* 设备1js
*/

 $(function () {
    //给#devs下的a链接绑定点击事件,首先将元素变为红色
    $('#devs a').click(function () {
        var select = $('#devs a.selected');
        select.removeClass('selected');
        $(this).addClass('selected'); 
        
        
        //显示对应设备信息
        var display = $('.display');
        var dev = $(this).attr('name');
            dev = '#' + dev;
        dev = $(dev);
        display.removeClass('display');
        display.addClass('displayNo');
        dev.removeClass('displayNo');
        dev.addClass('display');

    });

    //发送操作区数据
    $('#dev1_submit').click(function () {
        //获取操作数据
         var form = $('#dev1_control');
         var validFlag                    = form.find("input[name='validFlag']").val();
         var startTime                    = form.find("input[name='startTime']").val();
         var duration                     = form.find("input[name='duration']").val();
         var delay                        = form.find("input[name='delay']").val();
         var objectName                   = form.find("input[name='objectName']").val();
         var objectType                   = form.find("input[name='objectType']").val();
         var objectRightAscension         = form.find("input[name='objectRightAscension']").val();
         var objectDeclination            = form.find("input[name='objectDeclination']").val();
         var objectEpoch                  = form.find("input[name='objectEpoch']").val();
         var objectBand                   = form.find("input[name='objectBand']").val();
         var objectFilter                 = form.find("input[name='objectFilter']").val();
         var isSaveImage                  = form.find("input[name='isSaveImage']").val();
         var weatherGatherTime            = form.find("input[name='weatherGatherTime']").val();
         var temperature                  = form.find("input[name='temperature']").val();
         var humidity                     = form.find("input[name='humidity']").val();
         var windSpeed                    = form.find("input[name='windSpeed']").val();
         var pressure                     = form.find("input[name='pressure']").val();
         var skyGatherTime                = form.find("input[name='skyGatherTime']").val();
         var skyState                     = form.find("input[name='skyState']").val();
         var clouds                       = form.find("input[name='clouds']").val();
         var seeingGatherTime             = form.find("input[name='seeingGatherTime']").val();
         var seeing                       = form.find("input[name='seeing']").val();
         var dustGatherTime               = form.find("input[name='dustGatherTime']").val();
         var dust                         = form.find("input[name='dust']").val();
         var AMS                          = form.find("input[name='AMS']").val();
         var extinctionGatherTime         = form.find("input[name='extinctionGatherTime']").val();
         var rightAscension               = form.find("input[name='rightAscension']").val();
         var declination                  = form.find("input[name='declination']").val();
         var band                         = form.find("input[name='band']").val();
         var extinctionFactor1            = form.find("input[name='extinctionFactor1']").val();
         var extinctionFactor2            = form.find("input[name='extinctionFactor2']").val();
         var extinctionFactor3            = form.find("input[name='extinctionFactor3']").val();
         var telescopeRightAscension      = form.find("input[name='telescopeRightAscension']").val();
         var telescopeDeclination         = form.find("input[name='telescopeDeclination']").val();
         var focusLength                  = form.find("input[name='focusLength']").val();
         var frameNum                     = form.find("input[name='frameNum']").val();

            $.ajax ({
                  type: 'post',
                  url : '/index/Dev1/sendData',

                  data:  {
                           validFlag : validFlag,
                           startTime : startTime,
                           duration  : duration,
                           delay     :  delay,
                          objectName : objectName,
                          objectType : objectType,
                          objectRightAscension : objectRightAscension,
                          objectDeclination : objectDeclination,
                          objectEpoch : objectEpoch,
                          objectBand : objectBand,
                          objectFilter : objectFilter,
                          isSaveImage : isSaveImage,
                          weatherGatherTime : weatherGatherTime,
                          temperature : temperature,
                          humidity : humidity,
                          windSpeed : windSpeed,
                          pressure : pressure,
                          skyGatherTime : skyGatherTime,
                          skyState : skyState,
                          clouds : clouds,
                          seeingGatherTime : seeingGatherTime,
                          seeing : seeing,
                          dustGatherTime : dustGatherTime,
                          dust : dust,
                          AMS : AMS,
                          extinctionGatherTime : extinctionGatherTime,
                          rightAscension : rightAscension,
                          declination : declination,
                          band : band,
                          extinctionFactor1 : extinctionFactor1,
                          extinctionFactor2 : extinctionFactor2,
                          extinctionFactor3 : extinctionFactor3,
                          telescopeRightAscension : telescopeRightAscension,
                          telescopeDeclination : telescopeDeclination,
                          focusLength : focusLength,
                          frameNum : frameNum,
                       }, 

                      
                 success:  function (info) {
                       alert(info);

                   },

                 error:  function () {
                    alert('数据格式错误或网络异常,请重新提交');
                  },
              });
    });

})