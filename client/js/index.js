var hideIgnores = {
    userMenu : false
};

//Login show/hide
var loginVisible = false;
function setLoginVisible(visible){
    $('.login').stop(); $('.navigation').stop();
    $('.login').animate({ top: (visible ? '0px' : '-140px') }, 400);
    $('.navigation').animate({ top: (visible ? '140px' : '0px') }, 400);
    if(visible){ $('#username').focus(); }
    loginVisible = visible;
}

//UserMenu show/hide
var userMenuVisible = false;
function setUserMenuVisible(visible){
    if(visible){
        hideIgnores.userMenu = true;
        $('.second-navigation').removeClass('hidden');
        $('#nav-user').addClass('active');
    } else {
        $('.second-navigation').addClass('hidden');
        $('#nav-user').removeClass('active');
    }
    userMenuVisible = visible;
}

function hideAll() {
    if(!hideIgnores.userMenu){ setUserMenuVisible(false); }
    hideIgnores.userMenu = false;
}

$(document).ready(function() {
    //Register hide all listener
    $('html').click(function() { hideAll(); });
    //Open connection
    api.connect(function(){});
    //Login
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
    //User Menu
    $('#nav-user').click(function(){ setUserMenuVisible(!userMenuVisible); });
    $('#user-menu').click(function(){ setUserMenuVisible(true); }); //Keep open => ignores html click
});
$(window).on('beforeunload', function(){
    api.disconnect(); //Not needed but good practice
});
