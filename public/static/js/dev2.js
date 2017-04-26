/* 
* 设备2js
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

})