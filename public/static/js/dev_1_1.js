$(function () {

                         var form = $('#gimbalCtrl');
                         var select = form.find('li');

                         select.click(function () {
                             $(this).find('input:radio').attr('checked', true);
                             var notcheck = form.find('input:radio:not([checked])').parent('li');
                             notcheck.addClass('notCheck');
                             notcheck.find('input[type="text"]').val('');
                             $(this).removeClass('notCheck');
                             
                         });

                        //按钮提交事件
                          $("#gimbalCtrlBtn").click(function (){
                                
                                /*var checkInput = form.find("input:checked");
                                var operation  = checkInput.val();
                                var pstData = checkInput.attr('dataName');
                               
                                var dataType = checkInput.attr('dataType');
                                
                                var data = form.find("input:checked + input").val();*/
                                var checkInput = form.find("input:checked");
                                var dataType = checkInput.attr('dataType');
                                 //alert(dataType);
                                //
                                //var form = $('#gimbalCtrl');
                                var formData = new FormData(form[0]);
                               
                                //执行数据验证
                                 //var uint8 = new RegExp("^[a-zA-Z0-9]{1, 48}$");      //1-48字符；
                                 var uint8 = "/^[a-zA-Z0-9]{1, 48}$/";          //数字字母
                                 //var db64 = new RegExp("^(-?\\d+)(\\.\\d+)?$");     //浮点数
                                 var db64 = /^-?\d+\.\d+$/;     //浮点数
                                 //var uint16 = new RegExp("^\\d{1, 5}$");            //16整数
                                 var uint16 = /^\d{1,5}$/;               //16整数
                                 var uint32 = /^\d{1,10}$/;            //32整数
                                 //var uint64 = new RegExp("^\\d{1, 20}$");            //64整数
                                
                                 
                                // switch (dataType)
                                // {
                                //     case 'double64':
                                //     if (!data.match(db64))
                                //     {
                                //         alert('输入数据格式错误1！');
                                //         return;
                                //     }
                                //     break;
                                //     case 'uint8':
                                //     if (!data.match(uint8))
                                //     {
                                //         alert('输入数据格式错误2！');
                                //         return;
                                //     }
                                //     break;
                                //     case 'uint16':
                                //     if (!data.match(uint16))
                                //     {
                                //         alert('输入数据格式错误3！');
                                //         return;
                                //     }
                                //     break;
                                //     case 'uint32':
                                //     if (!data.match(uint32))
                                //     {
                                //         alert('输入数据格式错误4！');
                                //         return;
                                //     }
                                //     break;
                                //     default :
                                //     alert('异常情况，请重新输入5！');
                                //     break;
                                // }  

                                //执行ajax
                                $.ajax ({
                                       type: 'post',
                                       url : '/index/dev1/sendData/',
                                      data : formData,
                                      processData : false,
                                      contentType : false,  
                                       
                                       success:  function (info) {
                                        alert(info);
                                        
                                      },

                                     error:  function () {
                                        alert('网络异常,请重新提交');
                                     },
                                   });

                          });
                           
                         
                       })