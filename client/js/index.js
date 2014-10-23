var loginVisible = false;
function setLoginVisible(visible){
    $('.login').stop(); $('.navigation').stop();
    $('.login').animate({ top: (visible ? '0px' : '-140px') }, 400);
    $('.navigation').animate({ top: (visible ? '140px' : '0px') }, 400);
    if(visible){ $('#username').focus(); }
    loginVisible = visible;
}

$(document).ready(function() {
    api.connect(function(){
    });
    $('#toggle-login').click(function(){ setLoginVisible(!loginVisible); });
    $('#cancel-login').click(function(){ setLoginVisible(false); });
    api.register(ApiRequest.Login, function(data){
        if(!data.s){ alert('Login failed: ' + data.error + ' ' + data.error_text); }
        else {
            setLoginVisible(false);
            $('#nav-user').text($('#username').val()).append('&#x25BE;');
            $('#nav-user').removeClass('hidden');
            $('#toggle-login').addClass('hidden');
        }
    });
    $('#login-form').submit(function(){
        api.send(ApiRequest.Login, {username : $('#username').val(), password : $('#password').val()});
        return false;
    });
    $('#nav-user').click(function(){
        $('.second-navigation').removeClass('hidden');
        $('#nav-user').addClass('active');
    });
});
$(window).on('beforeunload', function(){
    api.disconnect(); //Not needed but good practice
});
